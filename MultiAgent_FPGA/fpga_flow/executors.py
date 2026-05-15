"""Execution and result-parsing helpers for the AES MVP Verilator workflow."""

from __future__ import annotations

import json
import shutil
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import Protocol

from MultiAgent_FPGA.fpga_flow.artifacts import (
    IntegrationRegressionManifest,
    ModuleRunResult,
    PlanDAGNode,
)
from MultiAgent_FPGA.fpga_flow.executor_contracts import (
    ResolvedIntegrationRegressionInputs,
    resolve_integration_regression_inputs,
    resolve_l2_campaign_inputs,
    resolve_node_compile_inputs,
    resolve_path,
    summarize_required_checkpoints,
)

CHECKPOINT_PREFIX = 'CHECKPOINT|'


def _run_async(coro):
    """Run an async coroutine from synchronous code, handling nested event loops."""
    import asyncio

    try:
        loop = asyncio.get_running_loop()
    except RuntimeError:
        loop = None
    if loop is None:
        return asyncio.run(coro)
    # Already inside an event loop — run in a thread to avoid RuntimeError
    import concurrent.futures

    with concurrent.futures.ThreadPoolExecutor(max_workers=1) as pool:
        return pool.submit(asyncio.run, coro).result()


class SupportsVerilatorAdapter(Protocol):
    async def compile(
        self,
        *,
        files: list[str],
        top_module: str,
        output_dir: str,
        extra_arguments: dict | None = None,
    ) -> str: ...

    async def simulate(
        self,
        *,
        design: str,
        top_module: str,
        output_dir: str,
        extra_arguments: dict | None = None,
    ) -> str: ...


@dataclass(frozen=True)
class WrittenReport:
    path: Path
    payload: dict


class CheckpointParser:
    """Parse stable `CHECKPOINT|...` lines from simulation.log."""

    def parse_text(self, text: str) -> dict[str, str]:
        summary: dict[str, str] = {}
        for raw_line in text.splitlines():
            line = raw_line.strip()
            if not line.startswith(CHECKPOINT_PREFIX):
                continue
            parts = line.split('|', 3)
            if len(parts) < 4:
                continue
            _, name, status, detail = parts
            summary[name] = f'{status}|{detail}'
        return summary

    def parse_file(self, path: Path) -> dict[str, str]:
        if not path.is_file():
            raise FileNotFoundError(f'Missing simulation log: {path}')
        return self.parse_text(path.read_text(encoding='utf-8'))


class RunReportWriter:
    """Write structured run artifacts next to the simulation outputs."""

    def __init__(self, *, package_root: Path) -> None:
        self.package_root = package_root

    def _resolve(self, path: str | Path) -> Path:
        candidate = Path(path)
        if candidate.is_absolute():
            return candidate
        return (self.package_root / candidate).resolve()

    def write_module_result(
        self, result: ModuleRunResult, *, path: str | Path
    ) -> WrittenReport:
        target = self._resolve(path)
        target.parent.mkdir(parents=True, exist_ok=True)
        payload = result.model_dump()
        target.write_text(
            json.dumps(payload, indent=2, sort_keys=True), encoding='utf-8'
        )
        return WrittenReport(path=target, payload=payload)

    def write_json_payload(self, payload: dict, *, path: str | Path) -> WrittenReport:
        target = self._resolve(path)
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(
            json.dumps(payload, indent=2, sort_keys=True), encoding='utf-8'
        )
        return WrittenReport(path=target, payload=payload)


class _BaseExecutor:
    def __init__(
        self,
        *,
        adapter: SupportsVerilatorAdapter,
        package_root: Path,
        integration_manifest: IntegrationRegressionManifest | None = None,
    ) -> None:
        self.adapter = adapter
        self.package_root = package_root
        self.checkpoints = CheckpointParser()
        self.writer = RunReportWriter(package_root=package_root)
        self.integration_manifest = integration_manifest

    def _resolve(self, value: str) -> Path:
        return (self.package_root / value).resolve()

    def _rtl_and_tb_files(
        self,
        node: PlanDAGNode,
        *,
        manifest: IntegrationRegressionManifest | None = None,
    ) -> list[str]:
        resolved = resolve_node_compile_inputs(
            package_root=self.package_root,
            node=node,
            manifest=manifest if manifest is not None else self.integration_manifest,
        )
        return list(resolved.compile_files)

    def _ensure_directory(self, path: Path) -> Path:
        path.mkdir(parents=True, exist_ok=True)
        return path

    def _mirror_rtl_for_simulation(
        self,
        *,
        build_output_dir: Path,
        compile_files: list[str],
    ) -> None:
        rtl_mirror_dir = self._ensure_directory(build_output_dir.parents[1] / 'rtl')
        for file_path in compile_files:
            source = Path(file_path)
            if source.suffix != '.v':
                continue
            destination = rtl_mirror_dir / source.name
            if destination.resolve() == source.resolve():
                continue
            shutil.copyfile(source, destination)

    def _ensure_waveform(
        self,
        *,
        output_dir: Path,
        scope_name: str,
    ) -> Path:
        preferred = output_dir / 'simulation.vcd'
        if preferred.is_file():
            return preferred
        preferred.write_text(
            '\n'.join(
                [
                    '$date',
                    '    generated by fpga_flow',
                    '$end',
                    '$version',
                    '    placeholder waveform',
                    '$end',
                    '$timescale 1ns $end',
                    f'$scope module {scope_name} $end',
                    '$upscope $end',
                    '$enddefinitions $end',
                    '$dumpvars',
                    '$end',
                    '',
                ]
            ),
            encoding='utf-8',
        )
        return preferred

    _CAMPAIGN_PROFILE_SEEDS: dict[str, int] = {
        'rand_small': 1001,
        'rand_medium': 2001,
        'back_to_back': 3001,
        'mid_reset': 4001,
    }

    def _aes128_campaign_seed(self, profile: str) -> int:
        seed = self._CAMPAIGN_PROFILE_SEEDS.get(profile)
        if seed is None:
            raise ValueError(f'Unsupported AES campaign profile: {profile}')
        return seed

    def _next_rng(self, state: int) -> int:
        state &= (1 << 64) - 1
        state ^= (state << 13) & ((1 << 64) - 1)
        state &= (1 << 64) - 1
        state ^= state >> 7
        state &= (1 << 64) - 1
        state ^= (state << 17) & ((1 << 64) - 1)
        return state & ((1 << 64) - 1)

    def _random_block_hex(self, state: int) -> tuple[int, str]:
        bytes_out: list[int] = []
        current = state
        for _ in range(16):
            current = self._next_rng(current)
            bytes_out.append((current >> 56) & 0xFF)
        return current, ''.join(f'{byte:02x}' for byte in bytes_out)

    def _write_campaign_oracle_file(
        self,
        *,
        sim_output_dir: Path,
        profile: str,
        cases: int,
        seed: int,
    ) -> Path:
        if shutil.which('openssl') is None:
            raise RuntimeError('openssl is required to generate AES campaign oracles')

        oracle_dir = self._ensure_directory(sim_output_dir / 'oracle')
        oracle_path = oracle_dir / f'{profile}_campaign.txt'
        current_seed = seed
        lines: list[str] = [f'# AES-128 oracle campaign for {profile}']

        with tempfile.TemporaryDirectory(dir=str(oracle_dir)) as tmpdir:
            tmp_root = Path(tmpdir)
            for index in range(cases):
                current_seed, key_hex = self._random_block_hex(current_seed)
                current_seed, plaintext_hex = self._random_block_hex(current_seed)
                plain_path = tmp_root / f'{index}.bin'
                cipher_path = tmp_root / f'{index}.cipher'
                plain_path.write_bytes(bytes.fromhex(plaintext_hex))
                subprocess.run(
                    [
                        'openssl',
                        'enc',
                        '-aes-128-ecb',
                        '-nopad',
                        '-nosalt',
                        '-K',
                        key_hex,
                        '-in',
                        str(plain_path),
                        '-out',
                        str(cipher_path),
                    ],
                    check=True,
                    capture_output=True,
                    text=True,
                )
                ciphertext_hex = cipher_path.read_bytes().hex()
                lines.append(
                    '|'.join(
                        [
                            f'label={profile}_case_{index}',
                            f'key={key_hex}',
                            f'plaintext={plaintext_hex}',
                            f'ciphertext={ciphertext_hex}',
                        ]
                    )
                )

        oracle_path.write_text('\n'.join(lines) + '\n', encoding='utf-8')
        return oracle_path

    def _build_result(
        self,
        *,
        node: PlanDAGNode,
        compile_result: str,
        sim_result: str,
        log_path: Path,
        waveform_path: Path,
    ) -> ModuleRunResult:
        return ModuleRunResult(
            module_id=node.module_id,
            compile_result=compile_result,
            sim_result=sim_result,
            log_path=str(log_path),
            waveform_path=str(waveform_path),
            checkpoint_summary=self.checkpoints.parse_file(log_path),
        )


class L0Executor(_BaseExecutor):
    """Run the fixed L0 compile gate."""

    def run(
        self,
        node: PlanDAGNode,
        *,
        manifest: IntegrationRegressionManifest | None = None,
    ) -> WrittenReport:
        build_output_dir = self._resolve(node.build_output_dir)
        # Clean stale artifacts from previous compiles to prevent linker
        # errors caused by orphaned .o/.d files referencing removed headers.
        if build_output_dir.exists():
            shutil.rmtree(build_output_dir)
        build_output_dir = self._ensure_directory(build_output_dir)
        compile_files = self._rtl_and_tb_files(node, manifest=manifest)
        compile_result = _run_async(
            self.adapter.compile(
                files=compile_files,
                top_module=node.top_module,
                output_dir=str(build_output_dir),
            )
        )
        payload = {
            'module_id': node.module_id,
            'stage': 'L0',
            'compile_result': compile_result,
            'output_dir': str(build_output_dir),
        }
        return self.writer.write_json_payload(
            payload,
            path=Path(node.build_output_dir).parent / 'l0_result.json',
        )


class L1Executor(_BaseExecutor):
    """Run the fixed L1 compile+simulate gate and parse checkpoints.

    When ``skip_compile=True``, the caller must supply ``reuse_compile_result``
    from a successful :meth:`L0Executor.run` on the same ``node``/manifest and
    an unchanged ``build_output_dir`` (``_run_node`` hot path).
    """

    def run(
        self,
        node: PlanDAGNode,
        *,
        manifest: IntegrationRegressionManifest | None = None,
        skip_compile: bool = False,
        reuse_compile_result: str | None = None,
    ) -> WrittenReport:
        """Run L1. Set ``skip_compile`` to avoid a second Verilator compile after L0."""
        build_output_dir = self._ensure_directory(self._resolve(node.build_output_dir))
        compile_files = self._rtl_and_tb_files(node, manifest=manifest)
        if skip_compile:
            if reuse_compile_result is None:
                raise ValueError(
                    'reuse_compile_result is required when skip_compile=True '
                    '(pass the compile log/text from a successful L0Executor.run).'
                )
            compile_result = reuse_compile_result
        else:
            compile_result = _run_async(
                self.adapter.compile(
                    files=compile_files,
                    top_module=node.top_module,
                    output_dir=str(build_output_dir),
                )
            )
        self._mirror_rtl_for_simulation(
            build_output_dir=build_output_dir,
            compile_files=compile_files,
        )
        sim_output_dir = self._ensure_directory(self._resolve(node.sim_output_dir))
        plusargs: dict[str, str] = {
            'fpga_flow_package_root': str(self.package_root.resolve()),
        }
        vecfile = node.pass_criteria.l1.vector_set
        if vecfile:
            resolved_vec = resolve_path(self.package_root, vecfile)
            plusargs['vecfile'] = str(resolved_vec)
        sim_result = _run_async(
            self.adapter.simulate(
                design=str(build_output_dir),
                top_module=node.top_module,
                output_dir=str(sim_output_dir),
                extra_arguments={
                    'plusargs': plusargs,
                },
            )
        )
        log_path = sim_output_dir / 'simulation.log'
        waveform_path = self._ensure_waveform(
            output_dir=sim_output_dir,
            scope_name=node.top_module,
        )
        result = self._build_result(
            node=node,
            compile_result=compile_result,
            sim_result=sim_result,
            log_path=log_path,
            waveform_path=waveform_path,
        )
        return self.writer.write_module_result(
            result,
            path=Path(node.sim_output_dir) / 'module_run_result.json',
        )


class L2CampaignExecutor(_BaseExecutor):
    """Run the bounded L2 campaign with fixed plusargs knobs."""

    def run(
        self,
        node: PlanDAGNode,
        *,
        profile: str,
        vecfile: str | None = None,
        cases: int | None = None,
        seed: int | None = None,
        manifest: IntegrationRegressionManifest | None = None,
    ) -> WrittenReport:
        resolved = resolve_l2_campaign_inputs(
            package_root=self.package_root,
            node=node,
            profile=profile,
            vecfile=vecfile,
            cases=cases,
            seed=seed,
        )

        sim_output_dir = self._ensure_directory(
            self._resolve(node.sim_output_dir) / 'l2' / profile
        )
        campaign_vecfile: Path | None = None
        if node.module_id == 'aes128_encrypt_core':
            campaign_vecfile = self._write_campaign_oracle_file(
                sim_output_dir=sim_output_dir,
                profile=profile,
                cases=resolved.cases,
                seed=resolved.seed,
            )
        compile_inputs = self._rtl_and_tb_files(node, manifest=manifest)
        self._mirror_rtl_for_simulation(
            build_output_dir=self._resolve(node.build_output_dir),
            compile_files=compile_inputs,
        )
        plusargs = {
            'fpga_flow_package_root': str(self.package_root.resolve()),
            **resolved.plusargs,
        }
        sim_result = _run_async(
            self.adapter.simulate(
                design=str(self._resolve(node.build_output_dir)),
                top_module=node.top_module,
                output_dir=str(sim_output_dir),
                extra_arguments={
                    'plusargs': plusargs,
                    **(
                        {'campaignVecfile': str(campaign_vecfile)}
                        if campaign_vecfile is not None
                        else {}
                    ),
                },
            )
        )
        log_path = sim_output_dir / 'simulation.log'
        waveform_path = self._ensure_waveform(
            output_dir=sim_output_dir,
            scope_name=node.top_module,
        )
        checkpoint_summary = self.checkpoints.parse_file(log_path)
        checkpoint_contract = node.pass_criteria.l1.checkpoint_contract
        summary = summarize_required_checkpoints(
            checkpoint_summary,
            tuple(node.pass_criteria.l1.coverage_checkpoints),
        )
        counterexample_payload = {
            'artifact_type': 'counterexample',
            'module_id': node.module_id,
            'profile': resolved.profile,
            'vecfile': str(resolved.vecfile),
            'cases': resolved.cases,
            'seed': resolved.seed,
            'l2_policy': node.l2_policy,
            'checkpoint_contract': checkpoint_contract,
            'output_dir': str(sim_output_dir),
            'log_path': str(log_path),
            'waveform_path': str(waveform_path),
            'sim_result': sim_result,
            'checkpoint_summary': checkpoint_summary,
            'missing_checkpoints': summary['missing'],
            'failed_checkpoints': summary['failed'],
        }
        fragility_summary_payload = {
            'artifact_type': 'fragility_summary',
            'module_id': node.module_id,
            'profile': resolved.profile,
            'vecfile': str(resolved.vecfile),
            'cases': resolved.cases,
            'seed': resolved.seed,
            'l2_policy': node.l2_policy,
            'checkpoint_contract': checkpoint_contract,
            'output_dir': str(sim_output_dir),
            'log_path': str(log_path),
            'waveform_path': str(waveform_path),
            'sim_result': sim_result,
            'checkpoint_summary': checkpoint_summary,
            'observed_checkpoints': list(checkpoint_summary.keys()),
            'checkpoint_count': len(checkpoint_summary),
        }
        self.writer.write_json_payload(
            fragility_summary_payload,
            path=sim_output_dir / 'fragility_summary.json',
        )
        self.writer.write_json_payload(
            counterexample_payload,
            path=sim_output_dir / 'counterexample.json',
        )
        payload = {
            'module_id': node.module_id,
            'profile': resolved.profile,
            'vecfile': str(resolved.vecfile),
            'cases': resolved.cases,
            'seed': resolved.seed,
            'l2_policy': node.l2_policy,
            'output_dir': str(sim_output_dir),
            'log_path': str(log_path),
            'waveform_path': str(waveform_path),
            'sim_result': sim_result,
            'checkpoint_summary': checkpoint_summary,
            'counterexample_path': str(
                (sim_output_dir / 'counterexample.json').resolve()
            ),
            'fragility_summary_path': str(
                (sim_output_dir / 'fragility_summary.json').resolve()
            ),
            'missing_checkpoints': summary['missing'],
            'failed_checkpoints': summary['failed'],
        }
        return self.writer.write_json_payload(
            payload, path=sim_output_dir / 'l2_result.json'
        )


class IntegrationRegressionExecutor(_BaseExecutor):
    """Run the manifest-driven top-level reintegration regression."""

    def run(
        self,
        manifest: IntegrationRegressionManifest,
    ) -> WrittenReport:
        resolved: ResolvedIntegrationRegressionInputs = (
            resolve_integration_regression_inputs(
                package_root=self.package_root,
                manifest=manifest,
            )
        )
        compile_result = _run_async(
            self.adapter.compile(
                files=list(resolved.compile_files),
                top_module=resolved.top_module,
                output_dir=str(self._ensure_directory(resolved.build_output_dir)),
                extra_arguments={'language': 'verilog'},
            )
        )
        self._mirror_rtl_for_simulation(
            build_output_dir=resolved.build_output_dir,
            compile_files=list(resolved.compile_files),
        )
        campaign_specs: list[tuple[str, Path, dict | None]] = [
            ('baseline', resolved.sim_output_dir, None)
        ]
        if resolved.back_to_back_required:
            campaign_specs.append(
                (
                    'back_to_back',
                    resolved.sim_output_dir / 'back_to_back',
                    {'plusargs': {'profile': 'back_to_back'}},
                )
            )
        if resolved.mid_reset_scenarios:
            campaign_specs.append(
                (
                    'mid_reset',
                    resolved.sim_output_dir / 'mid_reset',
                    {'plusargs': {'profile': 'mid_reset'}},
                )
            )

        campaign_results: list[dict] = []
        aggregate_missing: list[str] = []
        aggregate_failed: list[str] = []
        aggregate_passed: list[str] = []

        package_plusargs: dict[str, str] = {
            'fpga_flow_package_root': str(self.package_root.resolve()),
            'vecfile': str(resolved.vector_set),
        }
        for campaign_name, output_dir, extra_arguments in campaign_specs:
            campaign_output_dir = self._ensure_directory(output_dir)
            simulate_arguments: dict = {
                'useExistingBuild': True,
                'autoGenerateTestbench': False,
                'enableWaveform': True,
                'plusargs': dict(package_plusargs),
            }
            if extra_arguments:
                for key, value in extra_arguments.items():
                    if key == 'plusargs' and isinstance(value, dict):
                        simulate_arguments['plusargs'] = {
                            **package_plusargs,
                            **value,
                        }
                    elif key != 'plusargs':
                        simulate_arguments[key] = value
            sim_result = _run_async(
                self.adapter.simulate(
                    design=str(self._ensure_directory(resolved.build_output_dir)),
                    top_module=resolved.top_module,
                    output_dir=str(campaign_output_dir),
                    extra_arguments=simulate_arguments,
                )
            )
            log_path = campaign_output_dir / 'simulation.log'
            waveform_path = self._ensure_waveform(
                output_dir=campaign_output_dir,
                scope_name=resolved.top_module,
            )
            checkpoint_summary = self.checkpoints.parse_file(log_path)
            checkpoint_rollup = summarize_required_checkpoints(
                checkpoint_summary,
                resolved.regression_checkpoints,
            )
            aggregate_missing.extend(
                f'{campaign_name}:{item}' for item in checkpoint_rollup['missing']
            )
            aggregate_failed.extend(
                f'{campaign_name}:{item}' for item in checkpoint_rollup['failed']
            )
            aggregate_passed.extend(
                f'{campaign_name}:{item}' for item in checkpoint_rollup['passed']
            )
            campaign_results.append(
                {
                    'campaign': campaign_name,
                    'output_dir': str(campaign_output_dir),
                    'log_path': str(log_path),
                    'waveform_path': str(waveform_path),
                    'sim_result': sim_result,
                    'checkpoint_summary': checkpoint_summary,
                    'missing_checkpoints': checkpoint_rollup['missing'],
                    'failed_checkpoints': checkpoint_rollup['failed'],
                    'passed_checkpoints': checkpoint_rollup['passed'],
                }
            )

        baseline_campaign = campaign_results[0]
        payload = {
            'artifact_type': 'integration_regression_result',
            'module_id': resolved.top_module,
            'compile_files': [str(path) for path in resolved.rtl_files]
            + [str(resolved.tb_file)],
            'build_output_dir': str(resolved.build_output_dir),
            'sim_output_dir': str(resolved.sim_output_dir),
            'vector_set': str(resolved.vector_set),
            'required_modules': list(resolved.required_modules),
            'regression_checkpoints': list(resolved.regression_checkpoints),
            'interface_freeze_hash': resolved.interface_freeze_hash,
            'latency_target_cycles': resolved.latency_target_cycles,
            'back_to_back_required': resolved.back_to_back_required,
            'mid_reset_scenarios': list(resolved.mid_reset_scenarios),
            'checkpoint_contract': resolved.checkpoint_contract,
            'compile_result': compile_result,
            'sim_result': baseline_campaign['sim_result'],
            'log_path': baseline_campaign['log_path'],
            'waveform_path': baseline_campaign['waveform_path'],
            'checkpoint_summary': baseline_campaign['checkpoint_summary'],
            'campaign_results': campaign_results,
            'missing_checkpoints': aggregate_missing,
            'failed_checkpoints': aggregate_failed,
            'passed_checkpoints': aggregate_passed,
            'status': (
                'passed' if not aggregate_missing and not aggregate_failed else 'failed'
            ),
        }
        return self.writer.write_json_payload(
            payload,
            path=resolved.sim_output_dir / 'integration_regression_result.json',
        )
