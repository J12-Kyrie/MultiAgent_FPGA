"""Resolution helpers for the AES MVP executor contracts."""

from __future__ import annotations

from dataclasses import dataclass
from enum import Enum
from pathlib import Path

from pydantic import BaseModel, ConfigDict, Field

from MultiAgent_FPGA.fpga_flow.artifacts import (
    IntegrationRegressionManifest,
    PlanDAGNode,
)

# C++ self-checking TBs: Verilator often runs with cwd under workspace validation/sim.
# The executor injects +fpga_flow_package_root=...; vector files must be opened via
# aes_tb::resolve_path(argc, argv, requested, fallback). Do not use the legacy
# two-argument resolve_path(requested, fallback) from main — it ignores plusargs.
AES_CPP_TB_VECTOR_PATH_CONTRACT = (
    'Pass argc/argv from main into aes_tb::resolve_path(argc, argv, requested, fallback); '
    'never resolve KAT paths with only (requested, fallback).'
)

DEFAULT_L2_PROFILES = ('rand_small', 'rand_medium', 'back_to_back', 'mid_reset')
DEFAULT_TOP_ONLY_L2_PROFILES = ('back_to_back', 'mid_reset')


class ExecutorKind(str, Enum):
    GENERATE_NODE = 'generate_node'
    RUN_NODE = 'run_node'
    RECORD_REPAIR_EDIT = 'record_repair_edit'
    RUN_INTEGRATION = 'run_integration'


class ExecutorStatus(str, Enum):
    PASSED = 'passed'
    FAILED = 'failed'
    RECORDED = 'recorded'
    SKIPPED = 'skipped'


class NextAction(str, Enum):
    READ_ARTIFACTS = 'read_artifacts'
    EDIT_PRIMARY_TARGET = 'edit_primary_target'
    WAIT_FOR_NEXT_BATCH = 'wait_for_next_batch'
    ESCALATE_TO_ORCHESTRATOR = 'escalate_to_orchestrator'


class NextReadHints(BaseModel):
    model_config = ConfigDict(extra='forbid')

    action: NextAction = NextAction.READ_ARTIFACTS
    paths: list[str] = Field(default_factory=list)
    reason: str | None = None


class ExecutorObservation(BaseModel):
    model_config = ConfigDict(extra='forbid')

    executor_kind: ExecutorKind
    status: ExecutorStatus
    phase: str
    request_path: str
    module_id: str | None = None
    summary: str
    result_paths: dict[str, str] = Field(default_factory=dict)
    next_read_paths: list[str] = Field(default_factory=list)
    next_read_hints: list[NextReadHints] = Field(default_factory=list)
    repair_request_path: str | None = None
    repair_verify_failure_path: str | None = None
    recommended_next_phase: str | None = None
    workflow_gate_hint: str | None = None
    payload: dict[str, object] = Field(default_factory=dict)


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

    if manifest is None or node.module_id != manifest.top_module:
        compile_files = tuple(str(path) for path in (*rtl_files, tb_file))
        return ResolvedNodeCompileInputs(
            module_id=node.module_id,
            compile_files=compile_files,
            build_output_dir=resolve_path(package_root, node.build_output_dir),
        )

    dependency_closure_expanded = (
        bool(node.depends_on)
        and len(rtl_files) >= len(node.depends_on) + 1
        and all(path.is_file() for path in rtl_files)
    )
    if dependency_closure_expanded:
        compile_files = tuple(str(path) for path in (*rtl_files, tb_file))
        return ResolvedNodeCompileInputs(
            module_id=node.module_id,
            compile_files=compile_files,
            build_output_dir=resolve_path(package_root, node.build_output_dir),
        )

    manifest_rtl_files = tuple(
        resolve_path(package_root, path) for path in manifest.rtl_files
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


def _l2_profiles_for_node(node: PlanDAGNode) -> tuple[str, ...]:
    profiles = tuple(node.design_context.get('l2_profiles', ()))
    return profiles or DEFAULT_L2_PROFILES


def _top_only_profiles_for_node(node: PlanDAGNode) -> tuple[str, ...]:
    top_only = tuple(node.design_context.get('top_only_l2_profiles', ()))
    return top_only or DEFAULT_TOP_ONLY_L2_PROFILES


def _resolve_l2_vecfile(
    package_root: Path,
    node: PlanDAGNode,
    profile: str,
) -> Path:
    defaults = dict(node.design_context.get('l2_defaults', {})).get(profile, {})
    vecfile = defaults.get('vecfile', f'vectors/{node.module_id}_l2_{profile}.txt')
    return resolve_path(package_root, str(vecfile))


def resolve_l2_campaign_inputs(
    *,
    package_root: Path,
    node: PlanDAGNode,
    profile: str,
    vecfile: str | None = None,
    cases: int | None = None,
    seed: int | None = None,
) -> ResolvedL2CampaignInputs:
    if profile not in _l2_profiles_for_node(node):
        raise ValueError(f'Unsupported L2 profile: {profile}')

    is_top_module = node.integration_role in {'top', 'sink'}
    if is_top_module:
        expected_vecfile = _resolve_l2_vecfile(package_root, node, profile)
        resolved_vecfile = resolve_path(package_root, vecfile or expected_vecfile)
        if resolved_vecfile != expected_vecfile:
            raise ValueError(
                f'L2 profile {profile} must use {expected_vecfile}, got '
                f'{resolved_vecfile}'
            )
    else:
        if profile in _top_only_profiles_for_node(node):
            raise ValueError(
                f'L2 profile {profile} is reserved for integration sink nodes'
            )
        resolved_vecfile = resolve_path(
            package_root, vecfile or node.pass_criteria.l1.vector_set
        )
        if vecfile is not None and not resolved_vecfile.is_file():
            raise FileNotFoundError(f'Missing L2 vector corpus: {resolved_vecfile}')

    if is_top_module:
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
    if is_top_module or vecfile is not None:
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
