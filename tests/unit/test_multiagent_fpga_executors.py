from __future__ import annotations

from pathlib import Path

import pytest

from MultiAgent_FPGA.aes_mvp.artifacts import (
    load_default_integration_manifest,
    load_default_plan_dag,
)
from MultiAgent_FPGA.aes_mvp.executors import (
    IntegrationRegressionExecutor,
    L1Executor,
    L2CampaignExecutor,
)


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
        checkpoint_names = (
            self.l2_checkpoints
            if extra_arguments and extra_arguments.get('plusargs')
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
    plan_dag = load_default_plan_dag()
    top_node = plan_dag.nodes[-1]
    adapter = FakeVerilatorAdapter(
        l2_checkpoints=top_node.pass_criteria.l1.coverage_checkpoints,
        integration_checkpoints=[],
    )
    executor = L2CampaignExecutor(adapter=adapter, package_root=package_root)

    report = executor.run(top_node, profile='rand_small')

    l2_compile = next(call for call in adapter.calls if call[0] == 'simulate')
    assert l2_compile[1]['extra_arguments']['plusargs'] == {
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
    leaf_node = load_default_plan_dag().nodes[0]
    adapter = FakeVerilatorAdapter(l2_checkpoints=[], integration_checkpoints=[])
    executor = L2CampaignExecutor(adapter=adapter, package_root=package_root)

    with pytest.raises(ValueError, match='reserved for aes128_encrypt_core'):
        executor.run(leaf_node, profile='back_to_back', cases=32, seed=3001)


def test_integration_regression_executor_compiles_manifest_and_validates_checkpoints(
    tmp_path,
):
    package_root = tmp_path
    _write_common_aes_tree(package_root)
    manifest = load_default_integration_manifest()
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
    top_node = load_default_plan_dag().nodes[-1]
    adapter = FakeVerilatorAdapter(
        l2_checkpoints=[],
        integration_checkpoints=top_node.pass_criteria.l1.coverage_checkpoints,
    )
    executor = L1Executor(adapter=adapter, package_root=package_root)

    report = executor.run(top_node)

    compile_call = next(call for call in adapter.calls if call[0] == 'compile')
    assert compile_call[1]['files'] == [
        str((package_root / 'rtl/aes_sbox.v').resolve()),
        str((package_root / 'rtl/aes_key_schedule_128.v').resolve()),
        str((package_root / 'rtl/aes_round_transform.v').resolve()),
        str((package_root / 'rtl/aes128_encrypt_core.v').resolve()),
        str((package_root / 'tb/aes128_encrypt_core_tb.cpp').resolve()),
    ]
    assert report.payload['module_id'] == 'aes128_encrypt_core'
