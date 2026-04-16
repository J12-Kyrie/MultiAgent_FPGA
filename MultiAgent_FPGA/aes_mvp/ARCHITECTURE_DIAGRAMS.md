# AES MVP Multi-Agent System — Architecture Diagrams

## 1. High-Level End-to-End Workflow

```mermaid
flowchart TB
    subgraph Phase0["Phase 0: Bootstrap"]
        CLI["CLI Entry\n__main__.py\nrun-aes-mvp"] --> Boot["RuntimeBootstrap.build()"]
        Boot --> SDK["load_sdk_modules()\nsdk_shim.py"]
        Boot --> Skills["validate_skill_paths()\n16 .md files"]
        Boot --> Synth["Synthesis Layer\nsynthesis.py"]
        Synth --> SpecIR["SpecIR"]
        Synth --> PlanDAG["PlanDAG\n4 nodes"]
        Synth --> Manifest["IntegrationRegression\nManifest"]
        Boot --> MCP["build_verilator_stdio_server()\nMCP config"]
        Boot --> LLM["DeepSeek LLM Profiles\nthinking + fast"]
    end

    subgraph Phase1["Phase 1: Session Setup"]
        Boot --> Factory["SdkAgentFactory"]
        Factory --> RegTools["register_execution_tools()\nrun_executor"]
        Factory --> RegAgents["register_delegate_agents()\nworker x 4, repair x 4,\nl2 x N"]
        Factory --> Runner["ConversationRunner"]
        Runner --> ExecConv["create_execution_conversation()\nOrchestrator Agent"]
    end

    subgraph Phase2["Phase 2: Autonomous Execution Loop"]
        ExecConv --> Plan["_build_delegate_plan()\nDAGBatchPlanner"]
        Plan --> BatchLoop{"while True"}
        BatchLoop --> CollectState["_collect_existing_\ngeneration_summary()"]
        CollectState --> EvalGate["_evaluate_workflow_gate()"]
        EvalGate -->|success| Done["Return SUCCESS"]
        EvalGate -->|blocked| Blocked["Return BLOCKED"]
        EvalGate -->|continue| NextBatch["_next_eligible_\nautonomous_batch()"]
        EvalGate -->|"ready_for_\nintegration"| IntBatch["_build_integration_batch()"]
        NextBatch --> RunBatch["run_current_batch_until_gate()"]
        IntBatch --> RunBatch
        RunBatch --> PostRun["Post-run artifact check\n+ repair verification"]
        PostRun --> BatchLoop
    end

    subgraph Phase3["Phase 3: Finalizer"]
        Done --> Finalizer["_run_autonomous_finalizer()"]
        Blocked --> Finalizer
        Finalizer --> FinConv["create_finalizer_conversation()\nThinking LLM"]
        FinConv --> Accept["final_acceptance_summary.json"]
    end

    subgraph Phase4["Phase 4: Report Assembly"]
        Accept --> Extract["_extract_delegate_results()"]
        Extract --> Summary["session_summary.json\nreport_tree.json"]
    end

    style Phase0 fill:#eff6ff,stroke:#93c5fd,color:#1e3a5f
    style Phase1 fill:#f0fdf4,stroke:#86efac,color:#14532d
    style Phase2 fill:#fefce8,stroke:#fde047,color:#713f12
    style Phase3 fill:#fdf2f8,stroke:#f9a8d4,color:#831843
    style Phase4 fill:#f5f3ff,stroke:#c4b5fd,color:#3b0764
```

---

## 2. AES Node DAG (Frozen Topology)

```mermaid
graph LR
    subgraph Layer1["Layer 1"]
        sbox["aes_sbox\nCHK_SBOX_MATCH\nL2: skip"]
    end

    subgraph Layer2["Layer 2"]
        ks["aes_key_schedule_128\nCHK_ROUNDKEY_MATCH\nL2: conditional"]
        rt["aes_round_transform\nCHK_ROUND_STATE_MATCH\nL2: conditional"]
    end

    subgraph Layer3["Layer 3 — Top / Sink"]
        core["aes128_encrypt_core\n6 checkpoints\nL2: required"]
    end

    sbox --> ks
    sbox --> rt
    ks --> core
    rt --> core

    style Layer1 fill:#f0fdf4,stroke:#86efac,color:#14532d
    style Layer2 fill:#eff6ff,stroke:#93c5fd,color:#1e3a5f
    style Layer3 fill:#fef3c7,stroke:#fbbf24,color:#78350f
    style sbox fill:#dcfce7,stroke:#4ade80,color:#14532d
    style ks fill:#dbeafe,stroke:#60a5fa,color:#1e3a5f
    style rt fill:#dbeafe,stroke:#60a5fa,color:#1e3a5f
    style core fill:#fef9c3,stroke:#facc15,color:#78350f
```

---

## 3. Batch Execution Loop

```mermaid
flowchart TB
    Start(["Loop Start"]) --> Collect["Collect State\nRead results + promotions"]
    Collect --> Gate["Evaluate Gate"]

    Gate -->|"success"| ReturnOK(["SUCCESS"])
    Gate -->|"blocked"| ReturnBlocked(["BLOCKED"])
    Gate -->|"continue"| SelectBatch["Select Next Batch"]
    Gate -->|"ready for\nintegration"| BuildInt["Build Integration Batch"]

    SelectBatch --> CheckDeps{"Upstream\ndeps promoted?"}
    CheckDeps -->|"No"| Defer["Defer to\nnext iteration"]
    CheckDeps -->|"Yes"| Materialize["Prepare Batch"]

    BuildInt --> Materialize

    Materialize --> RunBatch["Run Batch\n(gated conversation)"]

    RunBatch --> PostProcess["Post-Process\nVerify artifacts + hooks"]

    PostProcess --> FailCheck{"Batch\nfailed?"}
    FailCheck -->|"No"| BudgetCheck["Check budget"]
    FailCheck -->|"Yes"| CascadeBlock["Cascade-block\ndependents"]
    CascadeBlock --> BudgetCheck

    BudgetCheck --> Start

    Defer --> Start

    style Start fill:#f5f3ff,stroke:#a78bfa,color:#3b0764
    style ReturnOK fill:#dcfce7,stroke:#4ade80,color:#14532d
    style ReturnBlocked fill:#fee2e2,stroke:#f87171,color:#7f1d1d
    style Gate fill:#fef9c3,stroke:#facc15,color:#78350f
    style RunBatch fill:#dbeafe,stroke:#60a5fa,color:#1e3a5f
    style CascadeBlock fill:#fee2e2,stroke:#f87171,color:#7f1d1d
```

---

## 4. Node Workspace State Machine

```mermaid
stateDiagram-v2
    [*] --> MISSING: Node created

    MISSING --> DRAFT_READY: Initialize + pre-populate memory

    DRAFT_READY --> GENERATED: Generate pass (L0 + L1 OK)

    DRAFT_READY --> REPAIRING: Generate fail (L0 or L1 error)

    GENERATED --> VALIDATED: All checkpoints pass

    GENERATED --> REPAIRING: Checkpoints missing or failed

    REPAIRING --> GENERATED: Repair + revalidation pass

    REPAIRING --> REPAIRING: Revalidation fail (budget remaining)

    REPAIRING --> BLOCKED: Repair budget exhausted

    VALIDATED --> PROMOTED: Copy draft to promoted/

    BLOCKED --> [*]: Terminal
    PROMOTED --> [*]: Terminal
```

---

## 5. SDK Agent Hierarchy and Delegation

```mermaid
flowchart TB
    subgraph Orchestrator["Execution Orchestrator — Thinking LLM"]
        direction TB
        OTools["Tools: terminal, ThinkTool,\nDelegateTool, run_executor"]
        OMCP["MCP: verilator (filtered)"]
        OCond["Condenser: LLMSummarizing\nmax_events=12, keep_first=2"]
    end

    subgraph Workers["Module Workers — Fast LLM"]
        direction TB
        W1["module_worker__aes_sbox"]
        W2["module_worker__aes_key_schedule_128"]
        W3["module_worker__aes_round_transform"]
        W4["module_worker__aes128_encrypt_core"]
        WTools["Tools: terminal, file_editor,\ntask_tracker, run_executor"]
    end

    subgraph Repair["Repair Workers — Fast LLM"]
        direction TB
        R1["module_repair__aes_sbox"]
        R2["module_repair__aes_key_schedule_128"]
        R3["module_repair__aes_round_transform"]
        R4["module_repair__aes128_encrypt_core"]
        RTools["Tools: file_editor,\ntask_tracker"]
    end

    subgraph Finalizer["Finalizer — Thinking LLM"]
        FTools["Tools: FinishTool, ThinkTool"]
        FNo["No MCP, No Delegate"]
    end

    Orchestrator -->|"DelegateTool"| Workers
    Orchestrator -->|"DelegateTool"| Repair
    Workers -->|"run_executor"| Executors["L0 / L1 / L2 Executors"]
    Executors -->|"async"| Verilator["Verilator MCP Server"]

    style Orchestrator fill:#eff6ff,stroke:#93c5fd,color:#1e3a5f
    style Workers fill:#f0fdf4,stroke:#86efac,color:#14532d
    style Repair fill:#fef3c7,stroke:#fbbf24,color:#78350f
    style Finalizer fill:#f5f3ff,stroke:#c4b5fd,color:#3b0764
    style Executors fill:#e0f2fe,stroke:#38bdf8,color:#0c4a6e
    style Verilator fill:#f1f5f9,stroke:#94a3b8,color:#334155
```

---

## 6. Repair Cycle

```mermaid
flowchart TB
    Fail["Validation Failed"] --> SelectTarget["Select Repair Target\n(RTL or testbench)"]

    SelectTarget --> WriteReq["Write Repair Request\n(baseline hashes + constraints)"]

    WriteReq --> RepairBatch["Dispatch to\nRepair Agent"]

    subgraph RepairAgent["Repair Agent"]
        Edit["Read request\n+ edit target file"]
    end

    RepairBatch --> RepairAgent

    Edit --> Verify["Framework Verify\n(hash changed? tokens present?)"]

    Verify -->|"Pass"| Receipt["Record Edit Receipt"]
    Verify -->|"Fail"| BudgetCheck

    Receipt --> Reval["Revalidate\n(L0 + L1 re-run)"]

    Reval -->|"Pass"| Promote(["Promote Workspace"])
    Reval -->|"Fail"| BudgetCheck{"Budget\nremaining?"}

    BudgetCheck -->|"Yes"| RepairBatch
    BudgetCheck -->|"No"| BlockedState(["BLOCKED"])

    style RepairAgent fill:#fef3c7,stroke:#fbbf24,color:#78350f
    style BlockedState fill:#fee2e2,stroke:#f87171,color:#7f1d1d
    style Promote fill:#dcfce7,stroke:#4ade80,color:#14532d
    style Verify fill:#eff6ff,stroke:#93c5fd,color:#1e3a5f
```

---

## 7. Memory Injection Architecture (3 Paths)

```mermaid
flowchart LR
    subgraph SkillFiles["Skill Files\n.openhands/skills/*.md"]
        M["AES memory files\n(sbox, key_schedule,\nround_transform,\nencrypt_core, shared)"]
    end

    subgraph MemoryStore["MemoryStore"]
        Select["Select by module"]
    end

    subgraph Path1["File Pre-population"]
        Draft["Write draft RTL + TB\ninto workspace"]
    end

    subgraph Path2["Prompt Injection"]
        SysPrompt["Inject full code\ninto system prompt\n(generate mode only)"]
    end

    subgraph Path3["SDK Skills Path"]
        Filtered["Filtered out\n(not passed to agents)"]
    end

    SkillFiles --> Select
    Select --> Draft
    Select --> SysPrompt

    SkillFiles -.->|"blocked"| Filtered

    style SkillFiles fill:#f5f3ff,stroke:#c4b5fd,color:#3b0764
    style MemoryStore fill:#eff6ff,stroke:#93c5fd,color:#1e3a5f
    style Path1 fill:#dcfce7,stroke:#4ade80,color:#14532d
    style Path2 fill:#dbeafe,stroke:#60a5fa,color:#1e3a5f
    style Path3 fill:#f1f5f9,stroke:#94a3b8,color:#334155
    style Filtered fill:#f1f5f9,stroke:#94a3b8,color:#334155
```

---

## 8. Executor Dispatch Chain

```mermaid
flowchart TB
    Agent["Agent calls\nrun_executor"] --> Dispatch["Dispatch by mode"]

    Dispatch -->|"Generate"| GenNode["Initialize Workspace\n+ pre-populate memory"]
    Dispatch -->|"Validate"| RunNode["Run Validation"]
    Dispatch -->|"Repair"| RecordRepair["Record + Verify\nRepair Edit"]
    Dispatch -->|"Integration"| RunInt["Integration\nRegression"]

    GenNode --> Validate["Compile + Simulate"]
    RunNode --> Validate

    Validate --> Result{"Pass?"}
    Result -->|"Yes"| Promote(["Promote\nWorkspace"])
    Result -->|"No"| RepairRec["Flag for Repair"]

    RunInt --> Campaigns["Run Campaigns\n(baseline, back-to-back,\nmid-reset)"]

    subgraph Verilator["Verilator Adapter"]
        CompSim["Compile + Simulate\nvia MCP server"]
    end

    Validate --> CompSim
    Campaigns --> CompSim

    style Verilator fill:#f1f5f9,stroke:#94a3b8,color:#334155
    style Agent fill:#f5f3ff,stroke:#c4b5fd,color:#3b0764
    style Promote fill:#dcfce7,stroke:#4ade80,color:#14532d
    style RepairRec fill:#fef3c7,stroke:#fbbf24,color:#78350f
```

---

## 9. Workflow Gate Decision Logic

```mermaid
flowchart TB
    Start["_evaluate_workflow_gate()"] --> CompSum["_autonomous_completion_summary()"]

    CompSum --> ClassifyModules["Classify each required module:\npromoted / blocked / cascade_blocked / pending"]
    ClassifyModules --> CheckInt["Check integration_status\nfrom deterministic_execution.json"]

    CheckInt --> Decision{"Decision Logic"}

    Decision -->|"protocol_violation\n!= None"| Blocked1["decision: blocked\nreason: protocol_violation"]
    Decision -->|"completion_status\n== success"| Success["decision: success"]
    Decision -->|"completion_status\n== blocked"| Blocked2["decision: blocked\nreason: required_module_blocked"]
    Decision -->|"next batch\navailable"| Continue["decision: continue\nnext_batch_ids: list"]
    Decision -->|"all promoted,\nintegration not passed,\nattempts <= 1"| ReadyInt["decision:\nready_for_integration"]
    Decision -->|"no eligible\nbatches remaining"| Blocked3["decision: blocked\nreason: no_remaining_batches"]

    Success --> WriteGate["Write workflow_gate.json"]
    Blocked1 --> WriteGate
    Blocked2 --> WriteGate
    Continue --> WriteGate
    ReadyInt --> WriteGate
    Blocked3 --> WriteGate

    style Success fill:#dcfce7,stroke:#4ade80,color:#14532d
    style Blocked1 fill:#fee2e2,stroke:#f87171,color:#7f1d1d
    style Blocked2 fill:#fee2e2,stroke:#f87171,color:#7f1d1d
    style Blocked3 fill:#fee2e2,stroke:#f87171,color:#7f1d1d
    style Continue fill:#dbeafe,stroke:#60a5fa,color:#1e3a5f
    style ReadyInt fill:#fef3c7,stroke:#fbbf24,color:#78350f
    style Decision fill:#fefce8,stroke:#fde047,color:#713f12
```

---

## 10. Prompt Composition Architecture

```mermaid
flowchart LR
    subgraph Contracts["BaseContract — Hard Constraints"]
        C1["AES_SCOPE_CONTRACT"]
        C2["STRUCTURED_IO_CONTRACT"]
        C3["NO_RAW_VERILATOR_CONTRACT"]
        C4["SKILLS_AS_AUTHORITY_CONTRACT"]
        C5["FRAMEWORK_OWNS_PROGRESS"]
    end

    subgraph Mixins["PhaseMixin — Soft Constraints"]
        M1["WORKER_LOCAL_SCOPE"]
        M2["WORKER_REQUEST_AUTHORITY"]
        M3["RUN_EXECUTOR_PHASE"]
        M4["GENERATE_PHASE"]
        M5["VALIDATE_PHASE"]
        M6["REPAIR_PHASE_ROUND_1/2+"]
        M7["L2_PHASE"]
        M8["MEMORY_CONSULTATION_DIRECTIVE"]
        M9["REPAIR_MEMORY_DIRECTIVE"]
    end

    subgraph Payload["InstancePayload"]
        P1["Per-task lines:\nwritable files,\nmodule-specific hints"]
    end

    subgraph SkillBlock["Skill References"]
        S1["build_skill_reference_block()\nORCHESTRATOR_CORE_SKILL_KEYS\nWORKER_FPGA_CORE_SKILL_KEYS\nREPAIR_CORE_SKILL_KEYS"]
    end

    subgraph MemBlock["Memory Block\n(generate mode only)"]
        MB["MemoryStore.build_prompt_block()"]
    end

    Contracts --> Compose["compose_prompt()"]
    Mixins --> Compose
    Payload --> Compose
    SkillBlock --> Compose
    MemBlock --> Compose
    Compose --> Final["Final System Prompt"]

    style Contracts fill:#fee2e2,stroke:#fca5a5,color:#7f1d1d
    style Mixins fill:#dbeafe,stroke:#93c5fd,color:#1e3a5f
    style Payload fill:#fef3c7,stroke:#fbbf24,color:#78350f
    style SkillBlock fill:#f0fdf4,stroke:#86efac,color:#14532d
    style MemBlock fill:#f5f3ff,stroke:#c4b5fd,color:#3b0764
    style Compose fill:#f1f5f9,stroke:#94a3b8,color:#334155
```

---

## 11. Batch Plan Structure (Typical 4-Module Run)

```mermaid
gantt
    title Batch Execution Order — Topological Layers + Repair Rounds
    dateFormat X
    axisFormat %s

    section Layer 1
    gen_layer_1_1_generate_validate (aes_sbox)        :a1, 0, 1
    gen_layer_1_1_aes_sbox_repair_1                    :a2, 1, 2
    gen_layer_1_1_aes_sbox_revalidate_1                :a3, 2, 3
    gen_layer_1_1_aes_sbox_repair_2                    :a4, 3, 4
    gen_layer_1_1_aes_sbox_revalidate_2                :a5, 4, 5

    section Layer 2
    gen_layer_2_1_generate_validate (ks + rt)           :b1, 5, 6
    gen_layer_2_1_ks_repair_1                           :b2, 6, 7
    gen_layer_2_1_ks_revalidate_1                       :b3, 7, 8
    gen_layer_2_1_rt_repair_1                           :b4, 6, 7
    gen_layer_2_1_rt_revalidate_1                       :b5, 7, 8
    gen_layer_2_1_ks_repair_2                           :b6, 8, 9
    gen_layer_2_1_ks_revalidate_2                       :b7, 9, 10
    gen_layer_2_1_rt_repair_2                           :b8, 8, 9
    gen_layer_2_1_rt_revalidate_2                       :b9, 9, 10

    section Layer 3
    gen_layer_3_1_generate_validate (core)              :c1, 10, 11
    gen_layer_3_1_core_repair_1                         :c2, 11, 12
    gen_layer_3_1_core_revalidate_1                     :c3, 12, 13
    gen_layer_3_1_core_repair_2                         :c4, 13, 14
    gen_layer_3_1_core_revalidate_2                     :c5, 14, 15

    section Integration
    integration                                         :d1, 15, 16
```

---

## 12. JSON Artifact Lifecycle

```mermaid
flowchart TB
    subgraph PlanTime["Plan Time — one-time"]
        SI["spec_ir.json"]
        PD["plan_dag.json"]
        GP["generation_plan.json"]
        BGS["brief_generation_summary.json"]
        BP["batch_plan.json"]
        DP["delegate_plan.json"]
        DR["delegate_requests/\nbatch__worker.json"]
    end

    subgraph PerIteration["Per Loop Iteration"]
        WG["workflow_gate.json\n(re-evaluated each loop)"]
        CBS["current_batch_snapshot.json"]
        BH["batch_history.json\n(appended each batch)"]
        AHD["autonomous_handoff_digest.json"]
        FM["fragility_memory.json\n(updated on L2 results)"]
    end

    subgraph PerNode["Per Node Workspace"]
        WS["workspace_state.json"]
        MC["contracts/module_contract.json"]
        TC["contracts/testbench_contract.json"]
        DB["contracts/design_brief.json"]
        GR["generation_result.json"]
        RR["repair_request.json"]
        ER["edit_receipt.json"]
        VS["validation/validation_summary.json"]
        L0R["validation/l0_result.json"]
        MRR["validation/sim/module_run_result.json"]
        PR["promotion/promotion_record.json"]
    end

    subgraph SessionEnd["Session End"]
        PE["promotion_events.json"]
        PF["promotion_failures.json"]
        IS["integration_summary.json"]
        DE["deterministic_execution.json"]
        DRes["delegate_results.json"]
        DFB["delegate_fallbacks.json"]
        FI["finalizer_input.json"]
        FAS["final_acceptance_summary.json"]
        SS["session_summary.json"]
        RT["report_tree.json"]
    end

    PlanTime --> PerIteration
    PerIteration --> PerNode
    PerNode --> SessionEnd

    style PlanTime fill:#eff6ff,stroke:#93c5fd,color:#1e3a5f
    style PerIteration fill:#fefce8,stroke:#fde047,color:#713f12
    style PerNode fill:#f5f3ff,stroke:#c4b5fd,color:#3b0764
    style SessionEnd fill:#f0fdf4,stroke:#86efac,color:#14532d
```

---

## 13. Error Recovery Flow (Provider Failure)

```mermaid
flowchart TB
    Run["session.run()"] --> TryBlock["try: execution_loop -> finalizer"]

    TryBlock -->|"Success"| HappyPath(["Write all artifacts\nReturn ExecutionSessionSummary"])

    TryBlock -->|"Exception"| ExceptBlock["except Exception as exc"]

    ExceptBlock --> CollectSummary["_collect_existing_generation_summary()\nRead whatever is on disk"]
    CollectSummary --> CollectFragility["_collect_fragility_memory()"]
    CollectFragility --> ExtractDelegates["_extract_delegate_results()"]

    ExtractDelegates --> CheckProvider{"_is_provider_failure(exc)?\nAND deterministic_summary?"}

    CheckProvider -->|"Yes"| Synthesize["_synthesize_final_acceptance_summary()\nLocal fallback with workflow_gate"]
    Synthesize --> WriteFallback["Write final_acceptance_summary.json\nWrite session_summary.json\nstatus: finished_with_fallback"]
    WriteFallback --> ReturnFallback(["Return ExecutionSessionSummary\n(no crash)"])

    CheckProvider -->|"No"| WriteFailure["Write final_acceptance_summary.json\n= status: not_available\nWrite session_summary.json with error"]
    WriteFailure --> Reraise(["raise  — crash"])

    ExceptBlock -.-> Finally["finally: conversation.close()"]

    style HappyPath fill:#dcfce7,stroke:#4ade80,color:#14532d
    style ReturnFallback fill:#dcfce7,stroke:#4ade80,color:#14532d
    style Reraise fill:#fee2e2,stroke:#f87171,color:#7f1d1d
    style CheckProvider fill:#fefce8,stroke:#fde047,color:#713f12
    style Synthesize fill:#dbeafe,stroke:#60a5fa,color:#1e3a5f
```

---

## 14. Orchestrator State Machine Transitions

```mermaid
stateDiagram-v2
    [*] --> SPEC_INTAKE
    SPEC_INTAKE --> ARCHITECTING: thinking profile
    ARCHITECTING --> PLANNING: thinking profile
    PLANNING --> MODULE_DESIGN: thinking profile

    MODULE_DESIGN --> MODULE_L0: fast profile
    MODULE_L0 --> MODULE_L1: fast profile

    MODULE_L1 --> MODULE_L2_OPTIONAL: requires_l2=true
    MODULE_L1 --> INTEGRATION_READY: requires_l2=false

    MODULE_L2_OPTIONAL --> INTEGRATION_READY: fast profile

    INTEGRATION_READY --> INTEGRATION_REGRESSION: thinking profile
    INTEGRATION_REGRESSION --> DONE: thinking profile

    DONE --> [*]

    note right of SPEC_INTAKE
        States SPEC_INTAKE through PLANNING\n
        use thinking LLM profile\n
        with subagent_policy = forbidden
    end note

    note right of MODULE_DESIGN
        States MODULE_DESIGN through MODULE_L1\n
        use fast LLM profile\n
        with subagent_policy = module_worker_allowed
    end note
```
