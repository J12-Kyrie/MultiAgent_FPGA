"""Resolution helpers for the AES MVP executor contracts."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

from MultiAgent_FPGA.aes_mvp.artifacts import (
    IntegrationRegressionManifest,
    PlanDAGNode,
)

AES_TOP_MODULE = 'aes128_encrypt_core'
L2_PROFILES = ('rand_small', 'rand_medium', 'back_to_back', 'mid_reset')
TOP_ONLY_L2_PROFILES = ('back_to_back', 'mid_reset')


@dataclass(frozen=True)
class ResolvedL2CampaignInputs:
    module_id: str
    profile: str
    vecfile: Path
    cases: int
    seed: int
    plusargs: dict[str, int | str]


@dataclass(frozen=True)
class ResolvedIntegrationRegressionInputs:
    top_module: str
    rtl_files: tuple[Path, ...]
    tb_file: Path
    compile_files: tuple[str, ...]
    build_output_dir: Path
    sim_output_dir: Path
    vector_set: Path
    required_modules: tuple[str, ...]
    regression_checkpoints: tuple[str, ...]
    interface_freeze_hash: str
    latency_target_cycles: int
    back_to_back_required: bool
    mid_reset_scenarios: tuple[str, ...]
    checkpoint_contract: str


@dataclass(frozen=True)
class ResolvedNodeCompileInputs:
    module_id: str
    compile_files: tuple[str, ...]
    build_output_dir: Path


def resolve_path(package_root: Path, value: str | Path) -> Path:
    candidate = Path(value)
    if candidate.is_absolute():
        return candidate
    return (package_root / candidate).resolve()


def resolve_node_compile_inputs(
    *,
    package_root: Path,
    node: PlanDAGNode,
    manifest: IntegrationRegressionManifest | None = None,
) -> ResolvedNodeCompileInputs:
    rtl_files = tuple(resolve_path(package_root, path) for path in node.rtl_files)
    tb_file = resolve_path(package_root, node.tb_file)

    if manifest is None or node.module_id != AES_TOP_MODULE:
        compile_files = tuple(str(path) for path in (*rtl_files, tb_file))
        return ResolvedNodeCompileInputs(
            module_id=node.module_id,
            compile_files=compile_files,
            build_output_dir=resolve_path(package_root, node.build_output_dir),
        )

    manifest_rtl_files = tuple(
        resolve_path(package_root, path) for path in manifest.rtl_files
    )
    if manifest.top_module != AES_TOP_MODULE:
        raise ValueError(
            f'Integration manifest top module must be {AES_TOP_MODULE}, '
            f'got {manifest.top_module}'
        )
    if all(path.is_file() for path in manifest_rtl_files):
        compile_files = tuple(str(path) for path in (*manifest_rtl_files, tb_file))
        return ResolvedNodeCompileInputs(
            module_id=node.module_id,
            compile_files=compile_files,
            build_output_dir=resolve_path(package_root, node.build_output_dir),
        )

    compile_files = tuple(str(path) for path in (*rtl_files, tb_file))
    return ResolvedNodeCompileInputs(
        module_id=node.module_id,
        compile_files=compile_files,
        build_output_dir=resolve_path(package_root, node.build_output_dir),
    )


def _parse_key_value_file(path: Path) -> dict[str, str]:
    values: dict[str, str] = {}
    for raw_line in path.read_text(encoding='utf-8').splitlines():
        line = raw_line.strip()
        if not line or line.startswith('#'):
            continue
        if '=' not in line:
            raise ValueError(f'Invalid key/value line in {path}: {raw_line!r}')
        key, value = line.split('=', 1)
        values[key.strip()] = value.strip()
    return values


def _resolve_l2_vecfile(package_root: Path, profile: str) -> Path:
    return resolve_path(
        package_root, f'vectors/aes128/{AES_TOP_MODULE}_l2_{profile}.txt'
    )


def resolve_l2_campaign_inputs(
    *,
    package_root: Path,
    node: PlanDAGNode,
    profile: str,
    vecfile: str | None = None,
    cases: int | None = None,
    seed: int | None = None,
) -> ResolvedL2CampaignInputs:
    if profile not in L2_PROFILES:
        raise ValueError(f'Unsupported L2 profile: {profile}')

    if node.module_id == AES_TOP_MODULE:
        expected_vecfile = _resolve_l2_vecfile(package_root, profile)
        resolved_vecfile = resolve_path(package_root, vecfile or expected_vecfile)
        if resolved_vecfile != expected_vecfile:
            raise ValueError(
                f'L2 profile {profile} must use {expected_vecfile}, got '
                f'{resolved_vecfile}'
            )
    else:
        if profile in TOP_ONLY_L2_PROFILES:
            raise ValueError(
                f'L2 profile {profile} is reserved for {AES_TOP_MODULE} in the AES MVP'
            )
        resolved_vecfile = resolve_path(
            package_root, vecfile or node.pass_criteria.l1.vector_set
        )
        if vecfile is not None and not resolved_vecfile.is_file():
            raise FileNotFoundError(f'Missing L2 vector corpus: {resolved_vecfile}')

    if node.module_id == AES_TOP_MODULE:
        if not resolved_vecfile.is_file():
            raise FileNotFoundError(f'Missing L2 vector corpus: {resolved_vecfile}')
        metadata = _parse_key_value_file(resolved_vecfile)
        file_profile = metadata.get('profile')
        if file_profile != profile:
            raise ValueError(
                f'L2 vector corpus {resolved_vecfile} declares profile={file_profile!r}'
            )

        try:
            default_cases = int(metadata['cases'])
            default_seed = int(metadata['seed'])
        except KeyError as exc:
            raise ValueError(
                f'L2 vector corpus {resolved_vecfile} must declare cases and seed'
            ) from exc

        if cases is not None and cases != default_cases:
            raise ValueError(
                f'L2 profile {profile} must use cases={default_cases}, got {cases}'
            )
        if seed is not None and seed != default_seed:
            raise ValueError(
                f'L2 profile {profile} must use seed={default_seed}, got {seed}'
            )
    else:
        if cases is None or seed is None:
            raise ValueError(
                'Non-top L2 campaigns must provide explicit cases and seed knobs'
            )
        default_cases = cases
        default_seed = seed
        if cases <= 0 or seed <= 0:
            raise ValueError('L2 cases and seed must be positive integers')

    plusargs: dict[str, int | str] = {
        'profile': profile,
        'cases': default_cases,
        'seed': default_seed,
    }
    if node.module_id == AES_TOP_MODULE or vecfile is not None:
        plusargs['vecfile'] = str(resolved_vecfile)
    return ResolvedL2CampaignInputs(
        module_id=node.module_id,
        profile=profile,
        vecfile=resolved_vecfile,
        cases=default_cases,
        seed=default_seed,
        plusargs=plusargs,
    )


def resolve_integration_regression_inputs(
    *,
    package_root: Path,
    manifest: IntegrationRegressionManifest,
) -> ResolvedIntegrationRegressionInputs:
    rtl_files = tuple(resolve_path(package_root, path) for path in manifest.rtl_files)
    tb_file = resolve_path(package_root, manifest.tb_file)
    compile_files = tuple(str(path) for path in (*rtl_files, tb_file))
    build_output_dir = resolve_path(package_root, manifest.build_output_dir)
    sim_output_dir = resolve_path(package_root, manifest.sim_output_dir)
    vector_set = resolve_path(package_root, manifest.vector_set)

    required_modules = tuple(manifest.required_modules)
    rtl_modules = tuple(path.stem for path in rtl_files)
    if rtl_modules != required_modules:
        raise ValueError(
            'Integration manifest required_modules must match rtl_files in order'
        )

    if not vector_set.is_file():
        raise FileNotFoundError(f'Missing integration vector corpus: {vector_set}')

    return ResolvedIntegrationRegressionInputs(
        top_module=manifest.top_module,
        rtl_files=rtl_files,
        tb_file=tb_file,
        compile_files=compile_files,
        build_output_dir=build_output_dir,
        sim_output_dir=sim_output_dir,
        vector_set=vector_set,
        required_modules=required_modules,
        regression_checkpoints=tuple(manifest.regression_checkpoints),
        interface_freeze_hash=manifest.interface_freeze_hash,
        latency_target_cycles=manifest.latency_target_cycles,
        back_to_back_required=manifest.back_to_back_required,
        mid_reset_scenarios=tuple(manifest.mid_reset_scenarios),
        checkpoint_contract=manifest.checkpoint_contract,
    )


def summarize_required_checkpoints(
    checkpoint_summary: dict[str, str],
    required_checkpoints: tuple[str, ...],
) -> dict[str, list[str]]:
    missing = [
        checkpoint
        for checkpoint in required_checkpoints
        if checkpoint not in checkpoint_summary
    ]
    failed = [
        checkpoint
        for checkpoint in required_checkpoints
        if checkpoint_summary.get(checkpoint, '').split('|', 1)[0] != 'PASS'
    ]
    passed = [
        checkpoint
        for checkpoint in required_checkpoints
        if checkpoint in checkpoint_summary
        and checkpoint_summary[checkpoint].split('|', 1)[0] == 'PASS'
    ]
    return {
        'missing': missing,
        'failed': failed,
        'passed': passed,
    }
