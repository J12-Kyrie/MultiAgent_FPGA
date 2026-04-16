"""Goal-driven synthesis and planning helpers for autonomous-generate."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any

from pydantic import BaseModel, ConfigDict, Field

from MultiAgent_FPGA.aes_mvp.artifacts import (
    IntegrationRegressionManifest,
    L1PassCriteria,
    ModuleContract,
    ModuleDesignBrief,
    NodeWorkspaceRecord,
    NodeWorkspaceState,
    PassCriteria,
    PlanDAG,
    PlanDAGNode,
    PortSpec,
    SpecIR,
    TestbenchContract,
)
from MultiAgent_FPGA.aes_mvp.delegation import SubagentWorkMode
from MultiAgent_FPGA.aes_mvp.paths import PACKAGE_ROOT
from MultiAgent_FPGA.aes_mvp.policy import (
    AgentExecutionPolicy,
    LLMProfileName,
    OrchestratorState,
    SubagentPolicy,
)
from MultiAgent_FPGA.aes_mvp.skill_refs import select_skill_refs

DEFAULT_AUTONOMOUS_GOAL = (
    'Autonomously design, implement, validate, repair, and integrate an AES-128 '
    'encrypt-only FPGA full-system using block-level handshake and an iterative '
    '10-round microarchitecture.'
)

_CRITICALITY_RANK: dict[str, int] = {'high': 0, 'medium': 1, 'low': 2}
_INTEGRATION_ROLE_RANK = {'top': 0, 'sink': 1, 'leaf': 2, 'support': 3}


def resolve_vector_path(vector_set: str) -> Path | None:
    """Return the first existing vector file for common AES MVP layouts."""
    vs = str(vector_set).strip()
    if not vs:
        return None
    candidates = [PACKAGE_ROOT / vs]
    rel = Path(vs)
    if not rel.is_absolute():
        candidates.append((PACKAGE_ROOT / 'vectors' / vs).resolve())
        candidates.append((PACKAGE_ROOT / 'vectors' / rel.name).resolve())
    seen: set[Path] = set()
    for c in candidates:
        r = c.resolve()
        if r in seen:
            continue
        seen.add(r)
        if r.is_file():
            return r
    return None


def validate_plan_dag_l1_vector_paths(plan_dag: PlanDAG) -> list[str]:
    """Return human-readable missing vector entries (module_id: vector_set)."""
    missing: list[str] = []
    for node in plan_dag.nodes:
        vs = getattr(node.pass_criteria.l1, 'vector_set', '') or ''
        vs = str(vs).strip()
        if not vs:
            continue
        if resolve_vector_path(vs) is None:
            missing.append(f'{node.module_id}: {vs}')
    return missing


def _vector_examples(vector_set: str, *, max_lines: int = 12) -> list[str]:
    vector_path = resolve_vector_path(vector_set)
    if vector_path is None:
        return []
    examples: list[str] = []
    for raw_line in vector_path.read_text(encoding='utf-8').splitlines():
        line = raw_line.strip()
        if not line or line.startswith('#'):
            continue
        examples.append(line)
        if len(examples) >= max_lines:
            break
    return examples


def _vector_implementation_hints(module_id: str, vector_set: str) -> list[str]:
    examples = _vector_examples(vector_set)
    if not examples:
        return []
    if module_id == 'aes_sbox':
        formatted_pairs = []
        for example in examples:
            if ',' not in example:
                continue
            input_hex, output_hex = (part.strip() for part in example.split(',', 1))
            formatted_pairs.append(f"8'h{input_hex} -> 8'h{output_hex}")
        if formatted_pairs:
            return [
                'Use a combinational lookup or case statement that satisfies these '
                'frozen KAT mappings first: ' + ', '.join(formatted_pairs) + '.'
            ]
    return [
        'Use these frozen vector anchors from '
        f'{vector_set} as concrete acceptance targets: ' + '; '.join(examples) + '.'
    ]


class FragilitySignal(BaseModel):
    model_config = ConfigDict(extra='forbid')

    profile: str
    status: str
    failing_checkpoints: list[str] = Field(default_factory=list)
    missing_checkpoints: list[str] = Field(default_factory=list)
    counterexample_path: str | None = None
    vecfile: str | None = None
    seed: int | None = None
    cases: int | None = None


class FragilityMemory(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_history: dict[str, list[FragilitySignal]] = Field(default_factory=dict)
    runtime_signals: list[dict[str, Any]] = Field(default_factory=list)


@dataclass(frozen=True)
class AdaptiveL2Request:
    module_id: str
    profile: str
    vecfile: str
    cases: int | None = None
    seed: int | None = None


@dataclass(frozen=True)
class PlannedBatchTask:
    module_id: str
    mode: SubagentWorkMode
    profile: str | None = None
    vecfile: str | None = None
    cases: int | None = None
    seed: int | None = None


@dataclass(frozen=True)
class PlannedBatch:
    batch_id: str
    stage: OrchestratorState
    include_spawn: bool
    tasks: tuple[PlannedBatchTask, ...]


def _port(name: str, direction: str, width: int, description: str) -> dict[str, Any]:
    return {
        'name': name,
        'direction': direction,
        'width': width,
        'description': description,
    }


def _aes_blueprints() -> list[dict[str, Any]]:
    return [
        {
            'module_id': 'aes_sbox',
            'depends_on': [],
            'rtl_files': ['rtl/aes_sbox.v'],
            'tb_file': 'tb/aes_sbox_tb.cpp',
            'build_output_dir': 'reports/l0/aes_sbox/obj_dir',
            'sim_output_dir': 'reports/l1/aes_sbox',
            'l2_policy': 'skip',
            'criticality': 'medium',
            'integration_role': 'leaf',
            'vector_set': 'vectors/aes128/aes_sbox_kat.txt',
            'coverage_checkpoints': ['CHK_SBOX_MATCH'],
            'latency_expectation': 'combinational_lookup',
            'checkpoint_contract': 'CHECKPOINT|CHK_SBOX_MATCH|PASS|<detail>',
            'design_context': {
                'summary': 'Implement the combinational AES S-box byte substitution.',
                'ports': [
                    _port('in_byte', 'input', 8, 'Input byte to substitute.'),
                    _port('out_byte', 'output', 8, 'Substituted output byte.'),
                ],
                'design_goals': [
                    'Preserve the frozen aes_sbox interface exactly.',
                    'Implement pure combinational substitution with no sequential state.',
                    'Produce CHK_SBOX_MATCH through the self-checking .cpp testbench.',
                ],
                'vector_format': (
                    'Exhaustive byte sweep plus optional vecfile with in_hex/out_hex pairs.'
                ),
                'plusargs': [
                    '+profile=rand_small|rand_medium',
                    '+cases',
                    '+seed',
                    '+vecfile',
                ],
                'prohibited_constructs': [
                    'Do not introduce SystemVerilog-only syntax.',
                    'Do not rename frozen ports or checkpoint identifiers.',
                    'Do not edit cross-module architecture from a node-local task.',
                ],
                'l2_profiles': [],
                'l2_defaults': {},
                'sink_role': False,
            },
        },
        {
            'module_id': 'aes_key_schedule_128',
            'depends_on': ['aes_sbox'],
            'rtl_files': ['rtl/aes_key_schedule_128.v'],
            'tb_file': 'tb/aes_key_schedule_128_tb.cpp',
            'build_output_dir': 'reports/l0/aes_key_schedule_128/obj_dir',
            'sim_output_dir': 'reports/l1/aes_key_schedule_128',
            'l2_policy': 'conditional',
            'criticality': 'high',
            'integration_role': 'leaf',
            'vector_set': 'vectors/aes128/aes_key_schedule_128_kat.txt',
            'coverage_checkpoints': ['CHK_ROUNDKEY_MATCH'],
            'latency_expectation': 'round_key_per_cycle',
            'checkpoint_contract': 'CHECKPOINT|CHK_ROUNDKEY_MATCH|PASS|<detail>',
            'design_context': {
                'summary': 'Implement the AES-128 round-key expansion helper.',
                'ports': [
                    _port(
                        'key',
                        'input',
                        128,
                        'Current key input used to derive the requested round key.',
                    ),
                    _port(
                        'round_index', 'input', 4, 'Round selector in the range 0..10.'
                    ),
                    _port(
                        'round_key',
                        'output',
                        128,
                        'Derived AES-128 round key for the requested round.',
                    ),
                ],
                'design_goals': [
                    'Preserve the frozen aes_key_schedule_128 interface exactly.',
                    'Support round_index values 0 through 10.',
                    'Produce CHK_ROUNDKEY_MATCH through the self-checking .cpp testbench.',
                ],
                'vector_format': 'Key/value file with round_key_0 through round_key_10 entries.',
                'plusargs': [
                    '+profile=rand_small|rand_medium',
                    '+cases',
                    '+seed',
                    '+vecfile',
                ],
                'prohibited_constructs': [
                    'Do not introduce SystemVerilog-only syntax.',
                    'Do not rename frozen ports or checkpoint identifiers.',
                    'Do not edit cross-module architecture from a node-local task.',
                ],
                'l2_profiles': ['rand_small', 'rand_medium'],
                'l2_defaults': {
                    'rand_small': {
                        'vecfile': 'vectors/aes128/aes_key_schedule_128_kat.txt',
                        'cases': 8,
                        'seed': 7,
                    },
                    'rand_medium': {
                        'vecfile': 'vectors/aes128/aes_key_schedule_128_kat.txt',
                        'cases': 16,
                        'seed': 17,
                    },
                },
                'sink_role': False,
            },
        },
        {
            'module_id': 'aes_round_transform',
            'depends_on': ['aes_sbox'],
            'rtl_files': ['rtl/aes_round_transform.v'],
            'tb_file': 'tb/aes_round_transform_tb.cpp',
            'build_output_dir': 'reports/l0/aes_round_transform/obj_dir',
            'sim_output_dir': 'reports/l1/aes_round_transform',
            'l2_policy': 'conditional',
            'criticality': 'high',
            'integration_role': 'leaf',
            'vector_set': 'vectors/aes128/aes_round_transform_kat.txt',
            'coverage_checkpoints': ['CHK_ROUND_STATE_MATCH'],
            'latency_expectation': 'single_round_transform',
            'checkpoint_contract': 'CHECKPOINT|CHK_ROUND_STATE_MATCH|PASS|<detail>',
            'design_context': {
                'summary': 'Implement one AES round transform with optional final-round bypass.',
                'ports': [
                    _port(
                        'state_in',
                        'input',
                        128,
                        'Input AES state before the round transform.',
                    ),
                    _port('round_key', 'input', 128, 'Round key for AddRoundKey.'),
                    _port(
                        'final_round', 'input', 1, 'When asserted, bypass MixColumns.'
                    ),
                    _port(
                        'sub_bytes_state',
                        'output',
                        128,
                        'Intermediate state after SubBytes.',
                    ),
                    _port(
                        'shift_rows_state',
                        'output',
                        128,
                        'Intermediate state after ShiftRows.',
                    ),
                    _port(
                        'mix_columns_state',
                        'output',
                        128,
                        'Intermediate state after MixColumns or bypass.',
                    ),
                    _port(
                        'state_out',
                        'output',
                        128,
                        'Final state after the round transform.',
                    ),
                ],
                'design_goals': [
                    'Preserve the frozen aes_round_transform interface exactly.',
                    'Support both normal rounds and final-round bypass of MixColumns.',
                    'Produce CHK_ROUND_STATE_MATCH through the self-checking .cpp testbench.',
                ],
                'vector_format': 'Key/value file describing intermediate round states and outputs.',
                'plusargs': [
                    '+profile=rand_small|rand_medium',
                    '+cases',
                    '+seed',
                    '+vecfile',
                ],
                'prohibited_constructs': [
                    'Do not introduce SystemVerilog-only syntax.',
                    'Do not rename frozen ports or checkpoint identifiers.',
                    'Do not edit cross-module architecture from a node-local task.',
                ],
                'l2_profiles': ['rand_small', 'rand_medium'],
                'l2_defaults': {
                    'rand_small': {
                        'vecfile': 'vectors/aes128/aes_round_transform_kat.txt',
                        'cases': 8,
                        'seed': 7,
                    },
                    'rand_medium': {
                        'vecfile': 'vectors/aes128/aes_round_transform_kat.txt',
                        'cases': 16,
                        'seed': 17,
                    },
                },
                'sink_role': False,
            },
        },
        {
            'module_id': 'aes128_encrypt_core',
            'depends_on': ['aes_key_schedule_128', 'aes_round_transform'],
            'rtl_files': ['rtl/aes128_encrypt_core.v'],
            'tb_file': 'tb/aes128_encrypt_core_tb.cpp',
            'build_output_dir': 'reports/l0/aes128_encrypt_core/obj_dir',
            'sim_output_dir': 'reports/l1/aes128_encrypt_core',
            'l2_policy': 'required',
            'criticality': 'high',
            'integration_role': 'top',
            'vector_set': 'vectors/aes128/aes128_encrypt_core_kat.txt',
            'coverage_checkpoints': [
                'CHK_RESET_CLEAR',
                'CHK_START_ACCEPTED',
                'CHK_BUSY_ASSERTED',
                'CHK_DONE_PULSE',
                'CHK_CIPHERTEXT_MATCH',
                'CHK_BUSY_DEASSERTED',
            ],
            'latency_expectation': '11_cycles',
            'checkpoint_contract': 'CHECKPOINT|CHK_*|PASS|<detail>',
            'design_context': {
                'summary': 'Implement the iterative AES-128 encrypt core with block-level handshake.',
                'ports': [
                    _port('clk', 'input', 1, 'Primary rising-edge clock.'),
                    _port('rst_n', 'input', 1, 'Active-low reset.'),
                    _port('start', 'input', 1, 'Start pulse sampled when busy is low.'),
                    _port('key', 'input', 128, 'AES-128 key input.'),
                    _port('plaintext', 'input', 128, 'AES plaintext input block.'),
                    _port(
                        'busy',
                        'output',
                        1,
                        'Busy indicator for the active encryption window.',
                    ),
                    _port('done', 'output', 1, 'Single-cycle completion pulse.'),
                    _port('ciphertext', 'output', 128, 'Ciphertext output block.'),
                ],
                'design_goals': [
                    'Preserve the frozen top-level handshake and signal names exactly.',
                    'Honor the 11-cycle latency target and ignore start while busy.',
                    'Produce the frozen top-level checkpoint set through the self-checking .cpp testbench.',
                ],
                'vector_format': 'Key/value file with key, plaintext, ciphertext, and optional L2 profiles.',
                'plusargs': [
                    '+profile=rand_small|rand_medium|back_to_back|mid_reset',
                    '+cases',
                    '+seed',
                    '+vecfile',
                ],
                'prohibited_constructs': [
                    'Do not introduce SystemVerilog-only syntax.',
                    'Do not rename frozen ports or checkpoint identifiers.',
                    'Do not edit cross-module architecture from a node-local task.',
                ],
                'l2_profiles': [
                    'rand_small',
                    'rand_medium',
                    'back_to_back',
                    'mid_reset',
                ],
                'l2_defaults': {
                    'rand_small': {
                        'vecfile': 'vectors/aes128/aes128_encrypt_core_l2_rand_small.txt',
                    },
                    'rand_medium': {
                        'vecfile': 'vectors/aes128/aes128_encrypt_core_l2_rand_medium.txt',
                    },
                    'back_to_back': {
                        'vecfile': 'vectors/aes128/aes128_encrypt_core_l2_back_to_back.txt',
                    },
                    'mid_reset': {
                        'vecfile': 'vectors/aes128/aes128_encrypt_core_l2_mid_reset.txt',
                    },
                },
                'integration_vector_set': 'vectors/aes128/aes128_encrypt_core_regress.txt',
                'integration_checkpoints': [
                    'CHK_RESET_CLEAR',
                    'CHK_START_ACCEPTED',
                    'CHK_BUSY_ASSERTED',
                    'CHK_DONE_PULSE',
                    'CHK_CIPHERTEXT_MATCH',
                    'CHK_BUSY_DEASSERTED',
                ],
                'mid_reset_scenarios': ['reset_during_busy', 'reset_after_done'],
                'sink_role': True,
            },
        },
    ]


def synthesize_spec_ir(
    *,
    system_goal: str | None,
    history_memory: list[dict[str, Any]] | None = None,
) -> SpecIR:
    del history_memory
    goal = (system_goal or DEFAULT_AUTONOMOUS_GOAL).strip() or DEFAULT_AUTONOMOUS_GOAL
    module_candidates = [entry['module_id'] for entry in _aes_blueprints()]
    return SpecIR(
        system_goal=goal,
        algorithm='AES',
        variant='AES-128',
        operation='encrypt',
        interface_style='block_handshake',
        microarchitecture='iterative_10_round',
        block_width=128,
        key_width=128,
        clock_reset_assumptions={
            'clock': 'single synchronous rising-edge clock',
            'reset': 'active-low reset for top-level control paths',
        },
        timing_targets={
            'latency_cycles': 11,
            'throughput': 'one block per transaction',
        },
        latency_target_cycles=11,
        accept_condition='sample key/plaintext when start && !busy',
        output_valid_condition='done pulse with stable ciphertext',
        frozen_interfaces=[
            'clk',
            'rst_n',
            'start',
            'key[127:0]',
            'plaintext[127:0]',
            'busy',
            'done',
            'ciphertext[127:0]',
        ],
        module_candidates=module_candidates,
        verification_redlines=[
            'do not use SystemVerilog-only syntax',
            'do not use generated testbenches on the stable path',
            'do not bypass executor-based compile and simulation validation',
        ],
    )


def synthesize_plan_dag(spec_ir: SpecIR) -> PlanDAG:
    nodes: list[PlanDAGNode] = []
    for entry in _aes_blueprints():
        nodes.append(
            PlanDAGNode(
                module_id=entry['module_id'],
                depends_on=list(entry['depends_on']),
                top_module=entry['module_id'],
                rtl_files=list(entry['rtl_files']),
                tb_file=entry['tb_file'],
                language='verilog',
                build_output_dir=entry['build_output_dir'],
                sim_output_dir=entry['sim_output_dir'],
                l2_policy=entry['l2_policy'],
                criticality=entry['criticality'],
                integration_role=entry['integration_role'],
                pass_criteria=PassCriteria(
                    l1=L1PassCriteria(
                        sim_pass_required=True,
                        assertion_pass_required=True,
                        coverage_checkpoints=list(entry['coverage_checkpoints']),
                        vector_set=entry['vector_set'],
                        latency_expectation=entry['latency_expectation'],
                        checkpoint_contract=entry['checkpoint_contract'],
                    )
                ),
                design_context={
                    **entry['design_context'],
                    'system_goal': spec_ir.system_goal,
                    'algorithm': spec_ir.algorithm,
                    'variant': spec_ir.variant,
                    'operation': spec_ir.operation,
                    'interface_style': spec_ir.interface_style,
                    'microarchitecture': spec_ir.microarchitecture,
                },
            )
        )
    return PlanDAG(nodes=nodes)


class IntegrationReadinessResolver:
    def sink_nodes(self, plan_dag: PlanDAG) -> list[PlanDAGNode]:
        dependency_targets = {
            dependency for node in plan_dag.nodes for dependency in node.depends_on
        }
        sinks = [
            node
            for node in plan_dag.nodes
            if node.module_id not in dependency_targets
            or node.integration_role in {'top', 'sink'}
        ]
        return sorted(
            sinks,
            key=lambda node: (
                _INTEGRATION_ROLE_RANK.get(node.integration_role, 9),
                _CRITICALITY_RANK.get(node.criticality, 9),
                node.module_id,
            ),
        )

    def _dependency_closure(self, plan_dag: PlanDAG, module_id: str) -> list[str]:
        by_id = {node.module_id: node for node in plan_dag.nodes}
        ordered: list[str] = []
        seen: set[str] = set()

        def visit(current: str) -> None:
            if current in seen:
                return
            seen.add(current)
            for dependency in by_id[current].depends_on:
                visit(dependency)
            ordered.append(current)

        visit(module_id)
        return ordered

    def select_primary_sink(
        self,
        plan_dag: PlanDAG,
        *,
        promoted_modules: set[str] | None = None,
    ) -> PlanDAGNode:
        sinks = self.sink_nodes(plan_dag)
        if promoted_modules is None:
            return sinks[0]
        for node in sinks:
            closure = set(self._dependency_closure(plan_dag, node.module_id))
            if closure.issubset(promoted_modules):
                return node
        raise ValueError('No integration-ready sink node is available')

    def ready_sink_modules(
        self, plan_dag: PlanDAG, *, promoted_modules: set[str]
    ) -> list[str]:
        ready: list[str] = []
        for node in self.sink_nodes(plan_dag):
            closure = set(self._dependency_closure(plan_dag, node.module_id))
            if closure.issubset(promoted_modules):
                ready.append(node.module_id)
        return ready

    def dependency_closure(self, plan_dag: PlanDAG, module_id: str) -> list[str]:
        return self._dependency_closure(plan_dag, module_id)


def synthesize_integration_manifest(
    spec_ir: SpecIR,
    plan_dag: PlanDAG,
) -> IntegrationRegressionManifest:
    resolver = IntegrationReadinessResolver()
    sink = resolver.select_primary_sink(plan_dag)
    required_modules = resolver.dependency_closure(plan_dag, sink.module_id)
    nodes_by_id = {node.module_id: node for node in plan_dag.nodes}
    rtl_files: list[str] = []
    for module_id in required_modules:
        rtl_files.extend(nodes_by_id[module_id].rtl_files)
    integration_vector_set = str(
        sink.design_context.get(
            'integration_vector_set', sink.pass_criteria.l1.vector_set
        )
    )
    regression_checkpoints = list(
        sink.design_context.get(
            'integration_checkpoints',
            sink.pass_criteria.l1.coverage_checkpoints,
        )
    )
    return IntegrationRegressionManifest(
        top_module=sink.module_id,
        rtl_files=rtl_files,
        tb_file=sink.tb_file,
        build_output_dir='reports/integration/obj_dir',
        sim_output_dir='reports/integration',
        required_modules=required_modules,
        interface_freeze_hash=(
            f'{spec_ir.variant.lower()}-'
            f'{spec_ir.interface_style}-'
            f'{spec_ir.microarchitecture}-autonomous-v1'
        ),
        regression_checkpoints=regression_checkpoints,
        vector_set=integration_vector_set,
        latency_target_cycles=spec_ir.latency_target_cycles,
        back_to_back_required='back_to_back'
        in sink.design_context.get('l2_profiles', []),
        mid_reset_scenarios=list(sink.design_context.get('mid_reset_scenarios', [])),
        checkpoint_contract=str(
            sink.design_context.get(
                'integration_checkpoint_contract',
                'CHECKPOINT|<name>|PASS|<detail>',
            )
        ),
    )


def synthesize_agent_execution_policy() -> AgentExecutionPolicy:
    return AgentExecutionPolicy(
        state_profiles={
            OrchestratorState.SPEC_INTAKE: LLMProfileName.DEEPSEEK_OFFICIAL_THINKING,
            OrchestratorState.ARCHITECTING: LLMProfileName.DEEPSEEK_OFFICIAL_THINKING,
            OrchestratorState.PLANNING: LLMProfileName.DEEPSEEK_OFFICIAL_THINKING,
            OrchestratorState.MODULE_DESIGN: LLMProfileName.DEEPSEEK_OFFICIAL_FAST,
            OrchestratorState.MODULE_L0: LLMProfileName.DEEPSEEK_OFFICIAL_FAST,
            OrchestratorState.MODULE_L1: LLMProfileName.DEEPSEEK_OFFICIAL_FAST,
            OrchestratorState.MODULE_L2_OPTIONAL: LLMProfileName.DEEPSEEK_OFFICIAL_FAST,
            OrchestratorState.INTEGRATION_READY: LLMProfileName.DEEPSEEK_OFFICIAL_THINKING,
            OrchestratorState.INTEGRATION_REGRESSION: LLMProfileName.DEEPSEEK_OFFICIAL_THINKING,
        },
        state_subagents={
            OrchestratorState.SPEC_INTAKE: SubagentPolicy.FORBIDDEN,
            OrchestratorState.ARCHITECTING: SubagentPolicy.FORBIDDEN,
            OrchestratorState.PLANNING: SubagentPolicy.FORBIDDEN,
            OrchestratorState.MODULE_DESIGN: SubagentPolicy.MODULE_WORKER_ALLOWED,
            OrchestratorState.MODULE_L0: SubagentPolicy.MODULE_WORKER_ALLOWED,
            OrchestratorState.MODULE_L1: SubagentPolicy.MODULE_WORKER_ALLOWED,
            OrchestratorState.MODULE_L2_OPTIONAL: SubagentPolicy.L2_CAMPAIGN_ALLOWED,
            OrchestratorState.INTEGRATION_READY: SubagentPolicy.FORBIDDEN,
            OrchestratorState.INTEGRATION_REGRESSION: SubagentPolicy.FORBIDDEN,
        },
        repair_attempt_threshold=2,
    )


class ContractCompiler:
    def __init__(self, *, spec_ir: SpecIR, plan_dag: PlanDAG) -> None:
        self.spec_ir = spec_ir
        self.plan_dag = plan_dag
        self.nodes_by_id = {node.module_id: node for node in plan_dag.nodes}

    def compile_module_contract(self, node: PlanDAGNode) -> ModuleContract:
        context = node.design_context
        ports = [
            PortSpec(**port_payload) for port_payload in list(context.get('ports', []))
        ]
        dependency_interfaces = [
            (
                f'{dependency} must remain compatible with '
                f'{self.nodes_by_id[dependency].module_id} and its checkpoint contract '
                f'{self.nodes_by_id[dependency].pass_criteria.l1.checkpoint_contract}.'
            )
            for dependency in node.depends_on
        ]
        return ModuleContract(
            module_id=node.module_id,
            summary=str(context.get('summary', f'Implement {node.module_id}.')),
            ports=ports,
            dependencies=list(node.depends_on),
            dependency_interfaces=dependency_interfaces,
            required_checkpoints=list(node.pass_criteria.l1.coverage_checkpoints),
            prohibited_constructs=list(
                context.get(
                    'prohibited_constructs',
                    [
                        'Do not introduce SystemVerilog-only syntax.',
                        'Do not rename frozen ports or checkpoint identifiers.',
                    ],
                )
            ),
            writable_targets=[*node.rtl_files, node.tb_file],
            canonical_rtl_targets=list(node.rtl_files),
            canonical_tb_target=node.tb_file,
        )

    def compile_testbench_contract(self, node: PlanDAGNode) -> TestbenchContract:
        context = node.design_context
        return TestbenchContract(
            module_id=node.module_id,
            tb_language='cpp',
            vector_format=str(
                context.get(
                    'vector_format', 'Key/value file with deterministic vectors.'
                )
            ),
            checkpoint_names=list(node.pass_criteria.l1.coverage_checkpoints),
            checkpoint_contract=node.pass_criteria.l1.checkpoint_contract,
            plusargs=list(context.get('plusargs', [])),
            success_rules=[
                (
                    'Emit the required CHECKPOINT lines to simulation.log using the '
                    f'exact frozen contract {node.pass_criteria.l1.checkpoint_contract}.'
                ),
                'Remain self-checking and deterministic for generated vectors.',
                'Do not rely on auto-generated testbenches.',
            ],
            writable_target=node.tb_file,
        )

    def compile_design_brief(self, node: PlanDAGNode) -> ModuleDesignBrief:
        context = node.design_context
        dependency_notes = []
        for dependency in node.depends_on:
            dependency_node = self.nodes_by_id[dependency]
            dependency_notes.append(
                f'{dependency} must remain compatible with '
                f'{dependency_node.top_module} and '
                f'{dependency_node.pass_criteria.l1.checkpoint_contract}.'
            )
        skill_paths = [
            str(ref.path)
            for ref in select_skill_refs(
                'aes_spec_decomposition',
                'aes_module_patterns',
                'aes_tb_contracts',
                'aes_repair_heuristics',
                'aes_verilator_profile',
                'verilog_verilator',
                'verilator_mcp_setup',
            )
        ]
        port_names = ', '.join(port['name'] for port in context.get('ports', []))
        checkpoint_names = ', '.join(node.pass_criteria.l1.coverage_checkpoints)
        implementation_hints = [
            (
                'Start from the frozen interface and keep these ports stable: '
                f'{port_names}.'
            ),
            (
                'Use the declared vectors and required checkpoints as the first '
                f'acceptance targets: {checkpoint_names}.'
            ),
            (
                'Emit checkpoints using the exact frozen contract '
                f'{node.pass_criteria.l1.checkpoint_contract}.'
            ),
            (
                'Verify draft RTL and draft TB produce correct results before '
                'the second validation pass.'
            ),
        ]
        if node.depends_on:
            implementation_hints.append(
                'Preserve compatibility with dependency outputs before optimizing '
                'local implementation details.'
            )
        if node.integration_role == 'top':
            implementation_hints.extend(
                [
                    (
                        'A valid MVP implementation strategy is a sequential '
                        '11-cycle handshake FSM around a local AES-128 block '
                        'encrypt helper; do not wait for dependency modules to '
                        'be perfect before making the top core executable.'
                    ),
                    (
                        'Cover the three L1 acceptance vectors first: '
                        'aes128_encrypt_core_kat, aes128_encrypt_core_zero, and '
                        'aes128_encrypt_core_regress.'
                    ),
                    (
                        'Preserve these behavioral rules exactly: reset clears '
                        'busy/done, start is accepted only when busy is low, '
                        'busy asserts immediately after start, done pulses once '
                        'at 11 cycles, and busy deasserts on the following cycle.'
                    ),
                    (
                        'The top testbench and integration regression will also '
                        'exercise rand_small, rand_medium, back_to_back, and '
                        'mid_reset profiles with arbitrary key/plaintext pairs.'
                    ),
                ]
            )
        implementation_hints.extend(
            _vector_implementation_hints(
                node.module_id,
                node.pass_criteria.l1.vector_set,
            )
        )
        repair_hints = [
            'Read generation_result.json, workspace_state.json, and validation_summary.json before editing after a failed validation run.',
            'Fix the first missing or failed checkpoint before broader refactors.',
            (
                'When editing a .cpp testbench, emit the exact CHECKPOINT contract '
                f'{node.pass_criteria.l1.checkpoint_contract} rather than a bare '
                'checkpoint name.'
            ),
            'After a failed executor run, make at least one concrete draft RTL or TB edit before rerunning the executor command.',
        ]
        if node.integration_role == 'top':
            repair_hints.extend(
                [
                    (
                        'For top-core RTL repairs, prioritize the handshake FSM '
                        'and 11-cycle latency contract before micro-optimizing '
                        'round logic.'
                    ),
                    (
                        'If dependency modules are too weak for arbitrary-vector '
                        'campaigns, it is acceptable in this MVP to repair the '
                        'top core with a local AES-128 block-encrypt helper as '
                        'long as ports, latency, and checkpoint contracts stay frozen.'
                    ),
                    (
                        'Use the zero and regress vectors in addition to the KAT '
                        'vector when deciding whether the top core is genuinely repaired.'
                    ),
                ]
            )
        repair_hints.extend(
            _vector_implementation_hints(
                node.module_id,
                node.pass_criteria.l1.vector_set,
            )
        )
        return ModuleDesignBrief(
            module_id=node.module_id,
            summary=(
                f'Generate {node.module_id} for the {self.spec_ir.variant} '
                f'{self.spec_ir.operation} autonomous full-system.'
            ),
            design_goals=list(context.get('design_goals', [])),
            dependency_notes=dependency_notes,
            vectors=[node.pass_criteria.l1.vector_set],
            checkpoints=list(node.pass_criteria.l1.coverage_checkpoints),
            implementation_hints=implementation_hints,
            repair_hints=repair_hints,
            skill_paths=skill_paths,
            workspace_strategy=(
                'Generate and edit only draft files under the session workspace. '
                'Promote to canonical RTL/TB only after L0 and L1 pass.'
            ),
        )


class NodePolicyEngine:
    def decide_next_mode(
        self,
        *,
        workspace_record: NodeWorkspaceRecord,
        validation_status: str | None,
        repair_budget: int,
    ) -> SubagentWorkMode | None:
        state = workspace_record.state
        if state in {NodeWorkspaceState.BLOCKED, NodeWorkspaceState.FAILED}:
            return None
        if state in {NodeWorkspaceState.PROMOTED, NodeWorkspaceState.VALIDATED}:
            return None
        if state in {NodeWorkspaceState.MISSING, NodeWorkspaceState.DRAFT_READY}:
            return SubagentWorkMode.GENERATE
        if validation_status == 'passed':
            return None
        if workspace_record.repair_edit_count <= repair_budget:
            return SubagentWorkMode.REPAIR
        return None

    def next_state(
        self,
        *,
        workspace_record: NodeWorkspaceRecord,
        validation_status: str | None,
        repair_budget: int,
    ) -> NodeWorkspaceState:
        if workspace_record.state == NodeWorkspaceState.FAILED:
            return NodeWorkspaceState.FAILED
        if workspace_record.state == NodeWorkspaceState.PROMOTED:
            return NodeWorkspaceState.PROMOTED
        if workspace_record.state == NodeWorkspaceState.VALIDATED:
            return NodeWorkspaceState.VALIDATED
        if validation_status == 'passed':
            return NodeWorkspaceState.VALIDATED
        if workspace_record.repair_edit_count > repair_budget:
            return NodeWorkspaceState.BLOCKED
        return NodeWorkspaceState.REPAIRING


class L2AdaptivePlanner:
    def plan(
        self,
        *,
        node: PlanDAGNode,
        fragility_memory: FragilityMemory,
        integration_manifest: IntegrationRegressionManifest,
    ) -> AdaptiveL2Request | None:
        if node.l2_policy == 'skip':
            return None
        context = node.design_context
        profiles = list(context.get('l2_profiles', []))
        if not profiles:
            return None
        history = fragility_memory.module_history.get(node.module_id, [])
        selected_index = 0
        if history:
            last = history[-1]
            if last.status != 'passed':
                try:
                    selected_index = min(
                        profiles.index(last.profile) + 1, len(profiles) - 1
                    )
                except ValueError:
                    selected_index = 0
            else:
                selected_index = profiles.index(last.profile)
        profile = profiles[selected_index]
        defaults = dict(context.get('l2_defaults', {})).get(profile, {})
        vecfile = str(defaults.get('vecfile', node.pass_criteria.l1.vector_set))
        cases = defaults.get('cases')
        seed = defaults.get('seed')
        if node.module_id == integration_manifest.top_module:
            return AdaptiveL2Request(
                module_id=node.module_id,
                profile=profile,
                vecfile=vecfile,
                cases=None if cases is None else int(cases),
                seed=None if seed is None else int(seed),
            )
        return AdaptiveL2Request(
            module_id=node.module_id,
            profile=profile,
            vecfile=vecfile,
            cases=8 if cases is None else int(cases),
            seed=7 if seed is None else int(seed),
        )


class DAGBatchPlanner:
    def _node_sort_key(self, node: PlanDAGNode) -> tuple[int, int, str]:
        return (
            _INTEGRATION_ROLE_RANK.get(node.integration_role, 9),
            _CRITICALITY_RANK.get(node.criticality, 9),
            node.module_id,
        )

    def _topological_layers(self, plan_dag: PlanDAG) -> list[list[PlanDAGNode]]:
        by_id = {node.module_id: node for node in plan_dag.nodes}
        indegree = {node.module_id: len(node.depends_on) for node in plan_dag.nodes}
        dependents: dict[str, list[str]] = {
            node.module_id: [] for node in plan_dag.nodes
        }
        for node in plan_dag.nodes:
            for dependency in node.depends_on:
                dependents.setdefault(dependency, []).append(node.module_id)

        ready = sorted(
            [
                node.module_id
                for node in plan_dag.nodes
                if indegree[node.module_id] == 0
            ],
            key=lambda module_id: self._node_sort_key(by_id[module_id]),
        )
        layers: list[list[PlanDAGNode]] = []
        while ready:
            current_layer_ids = ready
            ready = []
            current_nodes = [by_id[module_id] for module_id in current_layer_ids]
            layers.append(sorted(current_nodes, key=self._node_sort_key))
            next_candidates: list[str] = []
            for module_id in current_layer_ids:
                for dependent in dependents.get(module_id, []):
                    indegree[dependent] -= 1
                    if indegree[dependent] == 0:
                        next_candidates.append(dependent)
            ready = sorted(
                next_candidates,
                key=lambda module_id: self._node_sort_key(by_id[module_id]),
            )
        return layers

    def plan(
        self,
        *,
        plan_dag: PlanDAG,
        integration_manifest: IntegrationRegressionManifest,
        fragility_memory: FragilityMemory,
        max_children: int,
        l2_planner: L2AdaptivePlanner,
        enable_l2: bool = False,
    ) -> list[PlannedBatch]:
        batches: list[PlannedBatch] = []
        for layer_index, layer in enumerate(
            self._topological_layers(plan_dag), start=1
        ):
            for chunk_index, start in enumerate(
                range(0, len(layer), max_children), start=1
            ):
                chunk = layer[start : start + max_children]
                tasks = tuple(
                    PlannedBatchTask(
                        module_id=node.module_id,
                        mode=SubagentWorkMode.GENERATE,
                    )
                    for node in chunk
                )
                batches.append(
                    PlannedBatch(
                        batch_id=f'generation_layer_{layer_index}_{chunk_index}',
                        stage=OrchestratorState.MODULE_DESIGN,
                        include_spawn=True,
                        tasks=tasks,
                    )
                )

        if enable_l2:
            l2_requests = [
                request
                for node in plan_dag.nodes
                if (
                    request := l2_planner.plan(
                        node=node,
                        fragility_memory=fragility_memory,
                        integration_manifest=integration_manifest,
                    )
                )
                is not None
            ]
            for chunk_index, start in enumerate(
                range(0, len(l2_requests), max_children), start=1
            ):
                chunk = l2_requests[start : start + max_children]
                tasks = tuple(
                    PlannedBatchTask(
                        module_id=request.module_id,
                        mode=SubagentWorkMode.L2_EXECUTE,
                        profile=request.profile,
                        vecfile=request.vecfile,
                        cases=request.cases,
                        seed=request.seed,
                    )
                    for request in chunk
                )
                batches.append(
                    PlannedBatch(
                        batch_id=f'l2_campaigns_{chunk_index}',
                        stage=OrchestratorState.MODULE_L2_OPTIONAL,
                        include_spawn=False,
                        tasks=tasks,
                    )
                )
        return batches
