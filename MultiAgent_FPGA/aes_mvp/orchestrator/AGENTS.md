<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-04-16 -->

# orchestrator

## Purpose

Pure decision-logic wrapper around the AES state machine. Provides state transitions, work order construction, and progression tracing — no mutable state.

## Key Files

| File | Description |
|------|-------------|
| `state_machine.py` | `AESWorkflowOrchestrator` — wraps `SpecIR`, `PlanDAG`, `AgentExecutionPolicy`, `IntegrationRegressionManifest`. Provides `next_state_after_success()`, `build_module_work_order()`, `build_l2_campaign_request()`, `should_escalate()`, `describe_state_progression()`. |

## For AI Agents

### State Transition Table
```
SPEC_INTAKE → ARCHITECTING → PLANNING → MODULE_DESIGN → MODULE_L0 → MODULE_L1
  → [MODULE_L2_OPTIONAL if requires_l2] → INTEGRATION_READY → INTEGRATION_REGRESSION → DONE
```

### Escalation Rule
`should_escalate()` returns `True` if `repair_attempts >= 2` OR any of `cross_module_issue`, `state_machine_issue`, `interface_issue` is `True`.

<!-- MANUAL: -->
