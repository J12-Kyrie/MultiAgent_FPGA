---
name: multiagent-fpga-runbook
description: Runbook for executing and validating the MultiAgent_FPGA AES MVP framework in this repository, including the required `conda activate openhands` environment, provider preflight, execution modes, tests, and Verilator MCP smoke tests.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - multiagent_fpga run
  - aes mvp run
  - conda activate openhands
  - verilator smoke test
  - framework validation
---

# Purpose And Scope

Use this skill when the task is about running or validating the `MultiAgent_FPGA` AES MVP framework in this repository.

This runbook is for the current SDK-ready framework under `MultiAgent_FPGA/aes_mvp`. Do not use it for the old prototype under `MultiAgent_FPGA/old_code_autogen`.

# Required Environment

Always start from the repository root and activate the Conda environment first:

```bash
cd /Users/kyrie/Downloads/OpenHands-1.5.0
conda activate openhands
export PYTHONPATH=.
```

When Verilator MCP is needed, also export:

```bash
export VERILATOR_MCP_ENTRYPOINT=/Users/kyrie/Downloads/OpenHands-1.5.0/mcp4eda/verilator-mcp/dist/index.js
```

When DeepSeek-backed LLM profiles are needed, also export:

```bash
export DEEPSEEK_API_KEY=<your-secret>
```

Hard rules:

- keep using the `openhands` Conda environment
- run commands from `/Users/kyrie/Downloads/OpenHands-1.5.0`
- do not hardcode the DeepSeek API key in files
- use `deepseek-chat` as the stable request model for the official DeepSeek path
- treat `deepseek-reasoner` as a reasoning-only boundary, not the tool-using runtime model
- do not use `MultiAgent_FPGA/old_code_autogen` as the mainline runtime path

# Core Commands

Framework summary and asset validation:

```bash
cd /Users/kyrie/Downloads/OpenHands-1.5.0
conda activate openhands
export PYTHONPATH=.
python -m MultiAgent_FPGA.aes_mvp validate
```

Provider preflight for DeepSeek official routing:

```bash
cd /Users/kyrie/Downloads/OpenHands-1.5.0
conda activate openhands
export PYTHONPATH=.
export DEEPSEEK_API_KEY=<your-secret>
python -m MultiAgent_FPGA.aes_mvp smoke-provider
```

SDK bootstrap smoke test:

```bash
cd /Users/kyrie/Downloads/OpenHands-1.5.0
conda activate openhands
export PYTHONPATH=.
export DEEPSEEK_API_KEY=<your-secret>
python -m MultiAgent_FPGA.aes_mvp smoke-sdk
```

Unit tests for the AES MVP framework:

```bash
cd /Users/kyrie/Downloads/OpenHands-1.5.0
conda activate openhands
export PYTHONPATH=.
python -m pytest tests/unit/test_multiagent_fpga_aes_mvp.py tests/unit/test_multiagent_fpga_runtime.py tests/unit/test_multiagent_fpga_executors.py
```

Deterministic integration regression:

```bash
cd /Users/kyrie/Downloads/OpenHands-1.5.0
conda activate openhands
export PYTHONPATH=.
python -m MultiAgent_FPGA.aes_mvp run-integration
```

End-to-end AES MVP (autonomous-generate; default):

```bash
cd /Users/kyrie/Downloads/OpenHands-1.5.0
conda activate openhands
export PYTHONPATH=.
export DEEPSEEK_API_KEY=<your-secret>
python -m MultiAgent_FPGA.aes_mvp run-aes-mvp
```

Direct Verilator MCP smoke test:

```bash
cd /Users/kyrie/Downloads/OpenHands-1.5.0
conda activate openhands
export PYTHONPATH=.
export VERILATOR_MCP_ENTRYPOINT=/Users/kyrie/Downloads/OpenHands-1.5.0/mcp4eda/verilator-mcp/dist/index.js
python examples/verilator_mcp/run_direct_mcp.py
```

File-scoped pre-commit check for the AES MVP framework:

```bash
cd /Users/kyrie/Downloads/OpenHands-1.5.0
conda activate openhands
poetry run pre-commit run --files $(find MultiAgent_FPGA/aes_mvp -type f | sort) tests/unit/test_multiagent_fpga_aes_mvp.py --config ./dev_config/python/.pre-commit-config.yaml
```

# Current Runtime Boundary

These commands now cover the full AES MVP lane:

- framework asset validation
- policy validation
- DeepSeek provider preflight
- Verilator MCP connectivity and smoke tests
- deterministic node and integration execution
- live `run-aes-mvp` execution (`autonomous-generate` only; legacy `hybrid-*` and `deterministic-review` modes were removed from the runtime)

The stable request model is `deepseek-chat`. The official reasoning-only model boundary is `deepseek-reasoner`.

# Command Selection Guidance

Use the commands in this order:

1. `python -m MultiAgent_FPGA.aes_mvp validate`
   Use this first to validate framework assets and required skill references.
2. `python -m MultiAgent_FPGA.aes_mvp smoke-provider`
   Use this before any live run to verify `deepseek-chat` routing for both logical fast and logical thinking profiles.
3. `python -m MultiAgent_FPGA.aes_mvp smoke-sdk`
   Use this to verify SDK bootstrap, delegate registration, and report tree setup.
4. `python -m MultiAgent_FPGA.aes_mvp run-integration`
   Use this to verify deterministic AES integration before involving a live agent.
5. `python -m MultiAgent_FPGA.aes_mvp run-aes-mvp`
   Use this for the full autonomous generate / validate / repair / integrate lane (default mode).
6. `python examples/verilator_mcp/run_direct_mcp.py`
   Use this when you need to verify that the local Verilator MCP path is healthy.
7. `poetry run pre-commit run ...`
   Use this before handing changes back or committing.
