from __future__ import annotations

from pathlib import Path

import pytest

from MultiAgent_FPGA.aes_mvp.artifacts import (
    PlanDAG,
)
from MultiAgent_FPGA.aes_mvp.executors import (
    IntegrationRegressionExecutor,
    L0Executor,
    L1Executor,
    L2CampaignExecutor,
)
from MultiAgent_FPGA.aes_mvp.synthesis import (
    DEFAULT_AUTONOMOUS_GOAL,
    synthesize_integration_manifest,
    synthesize_plan_dag,
    synthesize_spec_ir,
)


def _synthesized_context() -> tuple[PlanDAG, object]:
    spec_ir = synthesize_spec_ir(system_goal=DEFAULT_AUTONOMOUS_GOAL)
    plan_dag = synthesize_plan_dag(spec_ir)
    manifest = synthesize_integration_manifest(spec_ir, plan_dag)
    return plan_dag, manifest


class FakeVerilatorAdapter:
    def __init__(
        self,
        *,
        l2_checkpoints: list[str],
        integration_checkpoints: list[str],
    ) -> None:
        self.calls: list[tuple[str, dict]] = []
        self.l2_checkpoints = l2_checkpoints
        self.integration_checkpoints = integration_checkpoints

    async def compile(
        self,
        *,
        files: list[str],
        top_module: str,
        output_dir: str,
        extra_arguments: dict | None = None,
    ) -> str:
        self.calls.append(
            (
                'compile',
                {
                    'files': files,
                    'top_module': top_module,
                    'output_dir': output_dir,
                    'extra_arguments': extra_arguments or {},
                },
            )
        )
        Path(output_dir).mkdir(parents=True, exist_ok=True)
        return f'compiled:{top_module}'

    async def simulate(
        self,
        *,
        design: str,
        top_module: str,
        output_dir: str,
        extra_arguments: dict | None = None,
    ) -> str:
        self.calls.append(
            (
                'simulate',
                {
                    'design': design,
                    'top_module': top_module,
                    'output_dir': output_dir,
                    'extra_arguments': extra_arguments or {},
                },
            )
        )
        out = Path(output_dir)
        out.mkdir(parents=True, exist_ok=True)
        plusargs = (extra_arguments or {}).get('plusargs') or {}
        checkpoint_names = (
            self.l2_checkpoints
            if 'profile' in plusargs
            else self.integration_checkpoints
        )
        log_lines = [f'CHECKPOINT|{name}|PASS|ok' for name in checkpoint_names]
        (out / 'simulation.log').write_text(
            '\n'.join(log_lines) + ('\n' if log_lines else ''),
            encoding='utf-8',
        )
        (out / 'simulation.vcd').write_text('wave', encoding='utf-8')
        return f'simulated:{top_module}'


def _write_text(package_root: Path, relative_path: str, content: str) -> None:
    target = package_root / relative_path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(content, encoding='utf-8')


def _write_common_aes_tree(package_root: Path) -> None:
    _write_text(
        package_root,
        'rtl/aes_sbox.v',
        'module aes_sbox; endmodule\n',
    )
    _write_text(
        package_root,
        'rtl/aes_key_schedule_128.v',
        'module aes_key_schedule_128; endmodule\n',
    )
    _write_text(
        package_root,
        'rtl/aes_round_transform.v',
        'module aes_round_transform; endmodule\n',
    )
    _write_text(
        package_root,
        'rtl/aes128_encrypt_core.v',
        'module aes128_encrypt_core; endmodule\n',
    )
    _write_text(package_root, 'tb/aes_sbox_tb.cpp', '// leaf tb\n')
    _write_text(package_root, 'tb/aes128_encrypt_core_tb.cpp', '// top tb\n')
    _write_text(
        package_root,
        'vectors/aes128/aes_sbox_kat.txt',
        'key=00\nplaintext=00\nciphertext=00\n',
    )
    _write_text(
        package_root,
        'vectors/aes128/aes128_encrypt_core_l2_rand_small.txt',
        '# L2 campaign seed corpus\nprofile=rand_small\ncases=32\nseed=1001\n',
    )
    _write_text(
        package_root,
        'vectors/aes128/aes128_encrypt_core_regress.txt',
        '# regression corpus\n',
    )


def test_l2_campaign_executor_resolves_top_profile_inputs_and_outputs(tmp_path):
    package_root = tmp_path
    _write_common_aes_tree(package_root)
    plan_dag, manifest = _synthesized_context()
    top_node = plan_dag.nodes[-1]
    adapter = FakeVerilatorAdapter(
        l2_checkpoints=top_node.pass_criteria.l1.coverage_checkpoints,
        integration_checkpoints=[],
    )
    executor = L2CampaignExecutor(
        adapter=adapter,
        package_root=package_root,
        integration_manifest=manifest,
    )

    report = executor.run(top_node, profile='rand_small')

    l2_compile = next(call for call in adapter.calls if call[0] == 'simulate')
    assert l2_compile[1]['extra_arguments']['plusargs'] == {
        'aes_mvp_package_root': str(package_root.resolve()),
        'profile': 'rand_small',
        'vecfile': str(
            (
                package_root / 'vectors/aes128/aes128_encrypt_core_l2_rand_small.txt'
            ).resolve()
        ),
        'cases': 32,
        'seed': 1001,
    }
    assert report.path.name == 'l2_result.json'
    assert report.payload['profile'] == 'rand_small'
    assert report.payload['missing_checkpoints'] == []
    assert report.payload['failed_checkpoints'] == []
    assert Path(report.payload['counterexample_path']).is_file()
    assert Path(report.payload['fragility_summary_path']).is_file()


def test_l2_campaign_executor_rejects_top_only_profiles_for_leaf_nodes(tmp_path):
    package_root = tmp_path
    _write_common_aes_tree(package_root)
    plan_dag, manifest = _synthesized_context()
    leaf_node = plan_dag.nodes[0]
    adapter = FakeVerilatorAdapter(l2_checkpoints=[], integration_checkpoints=[])
    executor = L2CampaignExecutor(
        adapter=adapter,
        package_root=package_root,
        integration_manifest=manifest,
    )

    with pytest.raises(ValueError, match='reserved for integration sink nodes'):
        executor.run(leaf_node, profile='back_to_back', cases=32, seed=3001)


def test_integration_regression_executor_compiles_manifest_and_validates_checkpoints(
    tmp_path,
):
    package_root = tmp_path
    _write_common_aes_tree(package_root)
    _, manifest = _synthesized_context()
    adapter = FakeVerilatorAdapter(
        l2_checkpoints=list(manifest.regression_checkpoints),
        integration_checkpoints=manifest.regression_checkpoints,
    )
    executor = IntegrationRegressionExecutor(
        adapter=adapter,
        package_root=package_root,
    )

    report = executor.run(manifest)

    compile_call = next(call for call in adapter.calls if call[0] == 'compile')
    assert compile_call[1]['files'] == [
        str((package_root / 'rtl/aes_sbox.v').resolve()),
        str((package_root / 'rtl/aes_key_schedule_128.v').resolve()),
        str((package_root / 'rtl/aes_round_transform.v').resolve()),
        str((package_root / 'rtl/aes128_encrypt_core.v').resolve()),
        str((package_root / 'tb/aes128_encrypt_core_tb.cpp').resolve()),
    ]
    assert compile_call[1]['extra_arguments'] == {'language': 'verilog'}

    simulate_call = next(call for call in adapter.calls if call[0] == 'simulate')
    assert simulate_call[1]['extra_arguments'] == {
        'useExistingBuild': True,
        'autoGenerateTestbench': False,
        'enableWaveform': True,
        'plusargs': {'aes_mvp_package_root': str(package_root.resolve())},
    }
    assert report.path.name == 'integration_regression_result.json'
    assert report.payload['status'] == 'passed'
    assert report.payload['missing_checkpoints'] == []
    assert report.payload['failed_checkpoints'] == []
    assert 'baseline:CHK_RESET_CLEAR' in report.payload['passed_checkpoints']
    assert 'back_to_back:CHK_DONE_PULSE' in report.payload['passed_checkpoints']
    assert 'mid_reset:CHK_BUSY_DEASSERTED' in report.payload['passed_checkpoints']
    assert report.payload['compile_files'] == [
        str((package_root / 'rtl/aes_sbox.v').resolve()),
        str((package_root / 'rtl/aes_key_schedule_128.v').resolve()),
        str((package_root / 'rtl/aes_round_transform.v').resolve()),
        str((package_root / 'rtl/aes128_encrypt_core.v').resolve()),
        str((package_root / 'tb/aes128_encrypt_core_tb.cpp').resolve()),
    ]
    assert [
        campaign['campaign'] for campaign in report.payload['campaign_results']
    ] == [
        'baseline',
        'back_to_back',
        'mid_reset',
    ]


def test_l1_executor_uses_manifest_rtl_files_for_top_level_reintegration(tmp_path):
    package_root = tmp_path
    _write_common_aes_tree(package_root)
    plan_dag, manifest = _synthesized_context()
    top_node = plan_dag.nodes[-1]
    adapter = FakeVerilatorAdapter(
        l2_checkpoints=[],
        integration_checkpoints=top_node.pass_criteria.l1.coverage_checkpoints,
    )
    l0 = L0Executor(
        adapter=adapter,
        package_root=package_root,
        integration_manifest=manifest,
    )
    l1 = L1Executor(
        adapter=adapter,
        package_root=package_root,
        integration_manifest=manifest,
    )

    l0_report = l0.run(top_node)
    report = l1.run(
        top_node,
        skip_compile=True,
        reuse_compile_result=str(l0_report.payload['compile_result']),
    )

    compile_calls = [call for call in adapter.calls if call[0] == 'compile']
    assert len(compile_calls) == 1
    simulate_calls = [call for call in adapter.calls if call[0] == 'simulate']
    assert len(simulate_calls) == 1

    simulate_call = simulate_calls[0]
    assert simulate_call[1]['extra_arguments'] == {
        'plusargs': {'aes_mvp_package_root': str(package_root.resolve())},
    }

    compile_call = compile_calls[0]
    assert compile_call[1]['files'] == [
        str((package_root / 'rtl/aes_sbox.v').resolve()),
        str((package_root / 'rtl/aes_key_schedule_128.v').resolve()),
        str((package_root / 'rtl/aes_round_transform.v').resolve()),
        str((package_root / 'rtl/aes128_encrypt_core.v').resolve()),
        str((package_root / 'tb/aes128_encrypt_core_tb.cpp').resolve()),
    ]
    assert report.payload['module_id'] == 'aes128_encrypt_core'
    assert report.payload['compile_result'] == l0_report.payload['compile_result']


def test_l1_executor_prefers_expanded_workspace_closure_for_top_node(tmp_path):
    package_root = tmp_path
    _write_common_aes_tree(package_root)
    plan_dag, manifest = _synthesized_context()
    top_node = plan_dag.nodes[-1]

    promoted_root = package_root / 'reports' / 'conversations' / 'test' / 'promoted'
    promoted_root.mkdir(parents=True, exist_ok=True)
    promoted_rtl_files: list[str] = []
    for node in plan_dag.nodes:
        promoted_module_rtl = (
            promoted_root / node.module_id / 'rtl' / Path(node.rtl_files[0]).name
        )
        promoted_module_rtl.parent.mkdir(parents=True, exist_ok=True)
        promoted_module_rtl.write_text(
            f'module {node.top_module}; endmodule\n',
            encoding='utf-8',
        )
        promoted_rtl_files.append(str(promoted_module_rtl.resolve()))

    workspace_tb = (
        package_root
        / 'reports'
        / 'conversations'
        / 'test'
        / 'workspaces'
        / top_node.module_id
        / 'draft'
        / 'tb'
        / Path(top_node.tb_file).name
    )
    workspace_tb.parent.mkdir(parents=True, exist_ok=True)
    workspace_tb.write_text('// workspace top tb\n', encoding='utf-8')

    execution_node = top_node.model_copy(
        update={
            'rtl_files': promoted_rtl_files,
            'tb_file': str(workspace_tb.resolve()),
            'build_output_dir': str(
                (
                    package_root
                    / 'reports'
                    / 'conversations'
                    / 'test'
                    / 'workspaces'
                    / top_node.module_id
                    / 'validation'
                    / 'build'
                ).resolve()
            ),
            'sim_output_dir': str(
                (
                    package_root
                    / 'reports'
                    / 'conversations'
                    / 'test'
                    / 'workspaces'
                    / top_node.module_id
                    / 'validation'
                    / 'sim'
                ).resolve()
            ),
        }
    )
    adapter = FakeVerilatorAdapter(
        l2_checkpoints=[],
        integration_checkpoints=top_node.pass_criteria.l1.coverage_checkpoints,
    )
    l0 = L0Executor(
        adapter=adapter,
        package_root=package_root,
        integration_manifest=manifest,
    )
    l1 = L1Executor(
        adapter=adapter,
        package_root=package_root,
        integration_manifest=manifest,
    )

    l0_report = l0.run(execution_node)
    l1.run(
        execution_node,
        skip_compile=True,
        reuse_compile_result=str(l0_report.payload['compile_result']),
    )

    compile_calls = [call for call in adapter.calls if call[0] == 'compile']
    assert len(compile_calls) == 1
    compile_call = compile_calls[0]
    assert compile_call[1]['files'] == [
        *promoted_rtl_files,
        str(workspace_tb.resolve()),
    ]
