# Thesis Simplification Report

**Date:** 2026-05-11
**Scope:** ch1_introduction.md through ch8_conclusion.md + ch_references.md (9 files)
**Goal:** Identify specific content that can be removed, condensed, or restructured to make the thesis read as academic prose rather than API documentation.

---

## Executive Summary

The thesis has three structural problems that inflate its length and weaken its academic quality:

1. **Massive cross-chapter repetition** -- the same concepts (framework-controlled vs prompt-controlled, AutoGen comparison, Harnessing Engine six layers, Memory injection, DAG scheduling) are explained 3-6 times across different chapters with nearly identical wording.
2. **Implementation-documentation style** -- 215 inline code references, 48 code blocks, and pervasive use of Python/Verilog class names, function names, file paths, and line numbers make the text read like a software manual.
3. **Redundant figures** -- 5 diagram files are each used 2-3 times across different chapters under different figure numbers, creating the illusion of more visual content than actually exists.

Estimated page reduction after all changes: **20-30 pages**.

---

## 1. Redundant/Repeated Content Across Chapters

### 1.1 Framework-controlled vs Prompt-controlled (explained 6 times)

This is the thesis's central architectural argument, but it is restated nearly verbatim in every chapter:

| Occurrence | File | Lines | Context |
|-----------|------|-------|---------|
| 1 | ch1_introduction.md | 33-41 | "不足一" and "不足五" |
| 2 | ch3_system_design.md | 8-11 | "设计哲学" section |
| 3 | ch3_system_design.md | 39-44 | "与AutoGen方案的架构对比" |
| 4 | ch4_state_machine.md | 170-233 | Entire §4.4 (4 subsections) |
| 5 | ch6_harnessing_engine.md | 358-375 | "约束密度对比" |
| 6 | ch7_experiments.md | 161-193 | §7.5 "能力维度对比" dimension 4 |
| 7 | ch8_conclusion.md | 8-9 | "研究回顾" |

**Recommendation:** Define the concept once in ch1 (2-3 sentences). Elaborate in ch4 §4.4 (the dedicated section). In all other chapters, use a single clause like "在框架控制架构下" and cross-reference ch4. Remove the full re-explanation from ch6 §6.8.3, ch7 §7.5 dimension 4, and ch8 §8.1.1.

**Estimated savings:** ~80 lines across 4 files.

### 1.2 AutoGen Comparison (4 separate tables/sections)

The comparison between this framework and the AutoGen-based prior work appears in four distinct locations with overlapping content:

| Occurrence | File | Lines | Format |
|-----------|------|-------|--------|
| 1 | ch3_system_design.md | 39-44 | Prose paragraph (3 dimensions) |
| 2 | ch4_state_machine.md | 226-233 | §4.4.4 prose (control reliability) |
| 3 | ch6_harnessing_engine.md | 358-375 | Table (6 constraint dimensions) |
| 4 | ch7_experiments.md | 161-193 | Table 7-5 (10 capability dimensions) + §7.5.1 prose (10 paragraphs) |

**Recommendation:** Keep ONE comprehensive comparison in ch7 (the experimental chapter, where comparison has evidentiary weight). Replace the ch3, ch4, and ch6 instances with single-sentence cross-references: "与AutoGen方案的详细对比见第七章表7-5". The ch4 §4.4.4 prose (8 lines about `TERMINATE` keyword) can be folded into the ch7 table row on "控制可靠性".

**Estimated savings:** ~60 lines across 3 files.

### 1.3 Harnessing Engine Six-Layer Description (4 times)

| Occurrence | File | Lines | Content |
|-----------|------|-------|---------|
| 1 | ch1_introduction.md | 51 | 创新点三, full 6-layer enumeration |
| 2 | ch3_system_design.md | 34-36 | §3.1.2 第六层 description |
| 3 | ch6_harnessing_engine.md | 1-377 | Entire chapter (correct location) |
| 4 | ch8_conclusion.md | 27-31 | 创新点三 recap |

**Recommendation:** ch1 should give a 2-sentence overview ("六层约束引擎，详见第六章"). ch3 should reference ch6 ("Agent/Prompt层的详细约束机制见第六章"). ch8 should summarize experimental findings, not re-describe the architecture. Only ch6 should contain the full six-layer description.

**Estimated savings:** ~40 lines across 3 files.

### 1.4 AES-128 Module DAG Description (5 times)

| Occurrence | File | Lines | Content |
|-----------|------|-------|---------|
| 1 | ch1_introduction.md | 47, 53 | Brief mentions |
| 2 | ch2_background.md | 124-138 | §2.4.4 microarchitecture + FSM |
| 3 | ch3_system_design.md | 49-92 | §3.2 full description + port table |
| 4 | ch5_verification.md | 114-131 | Checkpoint table per module |
| 5 | ch7_experiments.md | 66-71 | Checkpoint spec recap |

**Recommendation:** Full DAG description belongs in ch3 §3.2. ch2 should only cover AES algorithm background (not the specific framework modules). ch5 checkpoint table can stay (it adds new information). ch7 should not recap checkpoint specs -- reference ch5 instead.

**Estimated savings:** ~25 lines.

### 1.5 Memory Injection / "Task Degradation" (explained 5+ times)

The concept that Memory injection "degrades" the agent's task from "generate from scratch" to "confirm and adapt" is repeated in:

| Occurrence | File | Lines |
|-----------|------|-------|
| 1 | ch6_harnessing_engine.md | 173, 202 | §6.4.1, §6.4.2 |
| 2 | ch7_experiments.md | 84, 88-90, 92 | §7.2.3 note, §7.2.4 (3 paragraphs) |
| 3 | ch7_experiments.md | 149, 157 | §7.4.2, §7.4.3 |
| 4 | ch8_conclusion.md | 31, 61, 75 | 创新点三, 局限四, 方向四 |

**Recommendation:** Define the concept once in ch6 §6.4. ch7 §7.2.4 should present experimental evidence (1 paragraph), not re-explain the concept. ch8 should reference it in the context of limitations/future work, not re-define it.

**Estimated savings:** ~30 lines.

### 1.6 Repetition of "16 Skill Files" and "三级注册体系"

The 16 Skill files and their three-tier registration (runtime/memory/documentation) are described in:

| Occurrence | File | Lines |
|-----------|------|-------|
| 1 | ch3_system_design.md | 35-36 |
| 2 | ch6_harnessing_engine.md | 39-67 | Full tables |
| 3 | ch8_conclusion.md | 29-31 |

**Recommendation:** Full description only in ch6. ch3 and ch8 should reference ch6.

**Estimated savings:** ~15 lines.

---

## 2. Overly Detailed Implementation Content

### 2.1 Sections That Read Like API Documentation

The following sections list internal file names, class names, function names, and implementation details that do not belong in a thesis:

| File | Lines | Content | Recommendation |
|------|-------|---------|----------------|
| ch3_system_design.md | 17-36 | Six-layer architecture with file names (`artifacts.py`, `policy.py`, `executor_contracts.py`, etc.) | Replace file names with descriptive Chinese terms. Each layer: 2 sentences on purpose + key design choice. |
| ch4_state_machine.md | 9-52 | 10 state definitions with function names (`synthesize_spec_ir()`, `L0Executor`, `CheckpointParser`, etc.) | Condense to a table: state name, semantic purpose (1 sentence), executing agent type. Remove all function names. |
| ch5_verification.md | 78-108 | Full `CheckpointParser` Python class + `summarize_required_checkpoints()` description | Replace with: "Checkpoint解析器通过逐行扫描仿真日志，以前缀匹配提取验证结果，构建检查点名称到状态的映射。" (2 sentences) |
| ch5_verification.md | 150-166 | xorshift RNG C++ implementation | Move to appendix or replace with 1-sentence description. |
| ch6_harnessing_engine.md | 96-105 | `compose_prompt()` Python function signature | Remove. Describe the four-layer composition in prose. |
| ch6_harnessing_engine.md | 139-145 | repair mode `ValueError` Python code | Remove entirely. This is a unit test concern, not thesis content. |
| ch6_harnessing_engine.md | 177-184 | `_MEMORY_REGISTRY` Python dict literal | Remove. Describe the mapping concept in prose. |
| ch6_harnessing_engine.md | 236-262 | `run_executor` 5-step execution flow with function names | Replace with conceptual description of the proxy pattern (3 sentences). |
| ch7_experiments.md | 56-63 | Verification flow with internal function names | Replace with prose describing the pipeline conceptually. |

### 2.2 File Path and Line Number References

The thesis contains approximately 40 references to specific source files and line numbers (e.g., `fpga_flow/prompt_contracts.py:72-77`, `fpga_flow/skill_refs.py:22-51`). These are appropriate for a technical manual but not for a thesis.

**Recommendation:** Remove ALL `file:line` references from the main text. If verifiability is needed, add a single footnote per chapter pointing to the source repository.

**Affected files:** ch3 (8 occurrences), ch4 (3), ch5 (2), ch6 (15+), ch7 (3).

---

## 3. Tables Analysis

### 3.1 Current Inventory: 22+ tables across 8 chapters

| # | Table | File:Line | Rows | Verdict |
|---|-------|-----------|------|---------|
| 1 | 表2-1: DeepSeek双Profile参数对比 | ch2:26 | placeholder | KEEP (fill in) |
| 2 | 表3-2: 4模块端口规范一览表 | ch3:72-91 | 16x5 | MOVE to appendix |
| 3 | 表3-3: Agent角色-LLM Profile-工具矩阵 | ch3:119-128 | 5x4 | KEEP |
| 4 | Skill Runtime表 | ch6:47-53 | 5x3 | CONVERT to prose |
| 5 | Skill Memory表 | ch6:57-63 | 5x3 | CONVERT to prose |
| 6 | BaseContract约束维度表 | ch6:113-119 | 5x3 | KEEP |
| 7 | 表6-3: LLM失败模式-约束层级防御矩阵 | ch6:337-345 | 5x7 | MOVE to appendix |
| 8 | 约束密度对比表 | ch6:366-373 | 6x3 | MERGE with ch7 表7-5 |
| 9 | 表7-1: 实验环境配置表 | ch7:11-26 | 11x3 | SIMPLIFY to 5-6 items |
| 10 | 表7-2: 单模块验证结果汇总 | ch7:77-83 | 4x6 | KEEP |
| 11 | 表7-3: 集成回归测试结果 | ch7:106-110 | 3x4 | KEEP |
| 12 | 表7-5: 能力维度对比表 | ch7:169-181 | 10x4 | SIMPLIFY to 6 key dimensions |
| 13 | 表7-6: LED Chaser设计规格 | ch7:206-216 | 6x2 | KEEP |
| 14 | 表7-7: LED Chaser状态机执行轨迹 | ch7:232-243 | 8x4 | REMOVE (redundant with ch4 state machine) |
| 15 | 表7-8: LED Chaser模块验证结果 | ch7:250-253 | 1x6 | KEEP |
| 16 | 表7-9: LED Chaser Checkpoint详情 | ch7:256-261 | 4x4 | KEEP |
| 17 | 表7-10: LED Chaser集成回归测试结果 | ch7:268-272 | 1x4 | KEEP |

### 3.2 Recommendations

| Action | Tables | Savings |
|--------|--------|---------|
| REMOVE (redundant) | 表7-7 (LED Chaser state trace, repeats ch4) | -1 table |
| MOVE to appendix | 表3-2 (16-row port spec), 表6-3 (5x7 defense matrix) | -2 tables from main text |
| CONVERT to prose | Skill Runtime/Memory tables (ch6:47-63) | -2 tables, +4 lines prose |
| MERGE | 约束密度对比表 (ch6) into 表7-5 (ch7) | -1 table |
| SIMPLIFY | 表7-1 (11 rows to 5-6), 表7-5 (10 dims to 6) | smaller tables |
| KEEP as-is | 表2-1, 表3-3, BaseContract表, 表7-2, 表7-3, 表7-6, 表7-8/9/10 | 8 tables |

**Target:** 10-12 tables in main text (down from 22+).

---

## 4. Code Blocks Analysis

### 4.1 Inventory: 24 code blocks across 4 files

| # | Code Block | File:Lines | Language | Lines | Verdict |
|---|-----------|-----------|----------|-------|---------|
| 1 | State transition map | ch4:59-70 | text | 12 | KEEP (essential) |
| 2 | `should_escalate()` | ch4:120-135 | Python | 15 | SHORTEN to 3-line logic |
| 3 | `repair_budget_for_node()` | ch4:147-152 | Python | 5 | KEEP |
| 4 | `FRAMEWORK_OWNS_PROGRESS_CONTRACT` | ch4:188-190 | text | 3 | KEEP |
| 5 | `run_current_batch_until_gate()` signature | ch4:204-214 | Python | 10 | REMOVE (API detail) |
| 6 | Checkpoint protocol format | ch5:43-45 | text | 3 | KEEP |
| 7 | `emit_checkpoint()` C++ | ch5:55-62 | C++ | 7 | KEEP |
| 8 | `CheckpointParser` class | ch5:82-96 | Python | 14 | REMOVE or shorten to 3 lines |
| 9 | `random_block()` C++ | ch5:156-164 | C++ | 8 | MOVE to appendix |
| 10 | Oracle format | ch5:172-174 | text | 3 | KEEP |
| 11 | Execution path | ch5:251-253 | text | 3 | KEEP |
| 12 | `SKILLS_AS_AUTHORITY_CONTRACT` | ch6:79-82 | text | 3 | KEEP |
| 13 | `compose_prompt()` signature | ch6:96-105 | Python | 9 | REMOVE |
| 14 | repair `ValueError` | ch6:139-145 | Python | 6 | REMOVE |
| 15 | `_MEMORY_REGISTRY` dict | ch6:177-184 | Python | 7 | REMOVE |
| 16 | MEMORY block format | ch6:196-200 | text | 5 | KEEP |
| 17 | `MEMORY_CONSULTATION_DIRECTIVE` | ch6:210-215 | text | 5 | KEEP |
| 18 | `REPAIR_MEMORY_DIRECTIVE` | ch6:219-224 | text | 5 | KEEP |
| 19 | CLI commands (ch6) | ch6:311-321 | bash | 10 | SHORTEN to 3-4 commands |
| 20 | CLI commands (ch7) | ch7:30-45 | bash | 16 | SHORTEN to 1 command |
| 21 | State machine path (ch7) | ch7:132-136 | text | 5 | KEEP |
| 22 | LED Chaser run command | ch7:220-223 | bash | 3 | KEEP |

### 4.2 Recommendations

| Action | Blocks | Count |
|--------|--------|-------|
| REMOVE entirely | `compose_prompt()` signature, repair `ValueError`, `_MEMORY_REGISTRY` dict, `run_current_batch_until_gate()` signature | 4 blocks |
| SHORTEN | `should_escalate()` (15 to 3 lines), `CheckpointParser` (14 to 3 lines), CLI commands ch6 (10 to 4 lines), CLI commands ch7 (16 to 3 lines) | 4 blocks |
| MOVE to appendix | `random_block()` C++ implementation | 1 block |
| KEEP | All remaining | 13 blocks |

**Target:** 17 code blocks (down from 24), with 4 removed entirely and 4 shortened.

---

## 5. Inline Code Reference Analysis

### 5.1 Statistics by Chapter

| Chapter | Inline code (`backtick`) count | Assessment |
|---------|-------------------------------|------------|
| ch1_introduction.md | 4 | Acceptable |
| ch2_background.md | 9 | Acceptable |
| ch3_system_design.md | 42 | EXCESSIVE |
| ch4_state_machine.md | 39 | EXCESSIVE |
| ch5_verification.md | 25 | EXCESSIVE |
| ch6_harnessing_engine.md | 54 | CRITICALLY EXCESSIVE |
| ch7_experiments.md | 28 | EXCESSIVE |
| ch8_conclusion.md | 14 | Borderline |
| **Total** | **215** | **Target: <80** |

### 5.2 Worst Offending Patterns

**Pattern A: File names as code** (~30 occurrences)
- `artifacts.py`, `policy.py`, `executor_contracts.py`, `skill_refs.py`, `prompts.py`, `prompt_contracts.py`, `generation.py`, `memory.py`, `executors.py`, `agents/specs.py`, `runtime/bootstrap.py`, `runtime/factory.py`, `runtime/runner.py`, `runtime/session.py`, `adapters/verilator.py`
- **Replace with:** Chinese descriptive terms (e.g., "合约模型定义文件", "执行策略模块")

**Pattern B: Class/function names as code** (~80 occurrences)
- `SpecIR`, `PlanDAG`, `ModuleContract`, `NodeWorkspaceRecord`, `RepairContract`, `EditReceipt`, `AgentExecutionPolicy`, `DAGBatchPlanner`, `L0Executor`, `L1Executor`, `L2CampaignExecutor`, `IntegrationRegressionExecutor`, `CheckpointParser`, `MemoryStore`, `BlueprintLoader`, `ContractCompiler`, `NodePolicyEngine`, `L2AdaptivePlanner`, `IntegrationReadinessResolver`, `ConversationRunner`, `ExecutionSession`, `SdkAgentFactory`, `RuntimeBootstrap`
- **Replace with:** Descriptive Chinese terms on first use, with English in parentheses. Subsequent uses should be plain Chinese.

**Pattern C: Enum/constant names as code** (~40 occurrences)
- `DEEPSEEK_OFFICIAL_THINKING`, `DEEPSEEK_OFFICIAL_FAST`, `MODULE_WORKER_ALLOWED`, `L2_CAMPAIGN_ALLOWED`, `FORBIDDEN`, `MISSING`, `DRAFT_READY`, `VALIDATED`, `PROMOTED`, `REPAIRING`, `BLOCKED`, `FAILED`
- **Replace with:** Chinese translations (e.g., "深度思考模式", "快速执行模式", "允许模块工作者")

**Pattern D: Pydantic/config references** (~15 occurrences)
- `extra='forbid'`, `@model_validator`, `ConfigDict`, `reasoning_effort='medium'`, `reasoning_effort='none'`
- **Replace with:** "严格模式（禁止额外字段）", "模型验证器", "中等推理深度", "无扩展推理"

### 5.3 Specific Paragraphs Requiring Rewrite

**ch6_harnessing_engine.md:44-45:**
> 本框架构建了由16个Skill文件组成的三级注册体系，通过`skill_refs.py`统一管理。
Replace: "本框架构建了由16个技能文件组成的三级注册体系，通过统一的技能引用管理模块进行管理。"

**ch4_state_machine.md:9:**
> 本框架的编排器状态机由 `policy.py` 中的 `OrchestratorState` 枚举完整定义，共包含 10 个状态。这 10 个状态不仅是系统执行阶段的语义标记，更是 `AgentExecutionPolicy` 映射的索引键
Replace: "本框架的编排器状态机共定义10个状态，每个状态不仅标记执行阶段，更是执行策略映射的索引键。"

**ch3_system_design.md:17-20:**
> 合约层是整个系统的数据类型基础。其核心文件包括 `artifacts.py`（Pydantic 模型定义）、`policy.py`（执行策略枚举与映射）和 `executor_contracts.py`（执行器输入解析与 Checkpoint 汇总）。
Replace: "合约层是整个系统的数据类型基础，定义了规格中间表示、执行计划、工作区记录、修复合约等核心数据模型，所有模型均采用严格模式配置。"

---

## 6. Figure Duplication Analysis

### 6.1 Duplicate Figures (same image file, different figure numbers)

5 diagram files are reused across multiple chapters under different figure numbers:

| Image File | Used As | Chapters |
|-----------|---------|----------|
| `08_executor_dispatch.png` | 图2-2, 图5-1, 图6-4 | ch2, ch5, ch6 |
| `02_aes_node_dag.png` | 图2-3, 图3-2 | ch2, ch3 |
| `03_batch_execution_loop.png` | 图3-3, 图5-2 | ch3, ch5 |
| `05_sdk_agent_hierarchy.png` | 图2-1, 图4-2 | ch2, ch4 |
| `14_orchestrator_states.png` | 图2-4, 图4-1 | ch2, ch4 |

### 6.2 Recommendations

**Remove duplicates from ch2 (background chapter):**
- ch2 图2-1 (SDK Agent hierarchy) -- this is a framework-specific diagram, not background material. Remove from ch2, keep in ch4.
- ch2 图2-2 (executor dispatch) -- framework-specific. Remove from ch2, keep in ch5 or ch6.
- ch2 图2-3 (AES node DAG) -- framework-specific decomposition. Remove from ch2, keep in ch3.
- ch2 图2-4 (orchestrator states) -- framework-specific. Remove from ch2, keep in ch4.

ch2 should only contain generic background diagrams (AES algorithm flow, Transformer architecture), not framework-specific diagrams. The four framework diagrams currently in ch2 belong in their respective detailed chapters (ch3, ch4, ch5).

**Remove duplicates from ch5 and ch6:**
- ch5 图5-1 (executor dispatch) -- already in ch6 as 图6-4. Keep in ch6 only.
- ch5 图5-2 (batch execution loop) -- already in ch3 as 图3-3. Keep in ch3 only.

**Net result:** Remove 6 duplicate figure placements. Each unique diagram appears exactly once.

### 6.3 Missing Figure: 图6-3

The text references 图6-1, 图6-2, 图6-4, 图6-5 but skips 图6-3. Either add a figure at that position or renumber subsequent figures.

---

## 7. Content That Should Move to Appendices

| Content | Current Location | Reason |
|---------|-----------------|--------|
| 表3-2: 16-row port specification | ch3:72-91 | Reference material, not argument |
| 表6-3: 5x7 failure-mode defense matrix | ch6:337-345 | Too wide for main text |
| xorshift RNG implementation (C++) | ch5:156-164 | Implementation detail |
| ch6 §6.8.2 complete constraint chain walkthrough | ch6:349-356 | Debugging artifact |
| LED Chaser state machine trace table | ch7:232-243 | Redundant with ch4 |

---

## 8. Missing Academic Transitions

Several chapter/section transitions lack bridging sentences:

| Location | Issue | Suggested Bridge |
|----------|-------|-----------------|
| ch3:63 (§3.1 to §3.2) | Jump from generic architecture to AES-128 case | "上述通用架构在具体硬件设计上的实例化方式，以下以AES-128为例说明。" |
| ch4:89 (§4.1 to §4.2) | Jump from state definitions to policy | "状态机定义了'何时执行'，而策略分层决定了'如何执行'。" |
| ch5:137 (§5.2 to §5.3) | Jump from Checkpoint protocol to L2 testing | "L0和L1覆盖了语法和已知向量验证，但对随机输入的鲁棒性尚未验证。" |
| ch6:87 (§6.2 to §6.3) | Jump from Skill to Prompt layer | "Skill层解决了'Agent知道什么'，Prompt层解决'Agent被允许做什么'。" |

---

## 9. Reference Issues

### 9.1 Citation Number Inconsistencies

The references file (ch_references.md) has 20 entries numbered [1]-[20], but the chapter text uses citation numbers that do not always match. For example:
- ch1:11 cites "[1]" for VeriGen, but ch_references.md [1] is indeed VeriGen -- this is consistent.
- ch2:78 cites "[18]" for Verilator, but ch_references.md [18] is AgentBench, not Verilator.
- ch2:78 also cites "[8]" for Vivado, but ch_references.md [8] is Vivado -- consistent.

**Recommendation:** Verify all citation-number mappings between chapter text and ch_references.md. At minimum, ch2:78's Verilator citation [18] needs correction.

### 9.2 Missing Figures Check

All figure references in the text point to existing files:
- `fpga_flow/diagrams/` contains 17 PNG files
- `AES128.png` and `LED.png` exist in the thesis root directory
- No dangling figure references found

---

## 10. Prioritized Action Plan

### Priority 1: High Impact, Must Fix

| # | Action | Files | Estimated Savings |
|---|--------|-------|-------------------|
| 1 | Remove 6 duplicate figure placements from ch2 | ch2 | ~20 lines + cleaner background chapter |
| 2 | Consolidate AutoGen comparison to ch7 only | ch3, ch4, ch6 | ~60 lines |
| 3 | Remove Harnessing Engine re-descriptions from ch1, ch3, ch8 | ch1, ch3, ch8 | ~40 lines |
| 4 | Strip all `file:line` references | ch3, ch4, ch5, ch6, ch7 | ~40 inline code refs |
| 5 | Remove 4 implementation-detail code blocks | ch4, ch6 | ~30 lines |
| 6 | Convert inline code to Chinese descriptive terms | All | 215 to ~80 refs |

### Priority 2: Medium Impact, Should Fix

| # | Action | Files | Estimated Savings |
|---|--------|-------|-------------------|
| 7 | Condense 10 state descriptions to table | ch4 | ~30 lines |
| 8 | Condense six-layer architecture description | ch3 | ~15 lines |
| 9 | Move 3 oversized tables to appendix | ch3, ch6 | cleaner main text |
| 10 | Convert Skill tables to prose | ch6 | ~20 lines |
| 11 | Add transition sentences | ch3, ch4, ch5, ch6 | +8 lines (improves flow) |
| 12 | Fix citation [18] for Verilator | ch2, ch_references | correctness |

### Priority 3: Polish

| # | Action | Files | Estimated Savings |
|---|--------|-------|-------------------|
| 13 | Shorten ch1 §1.3 deficiency descriptions | ch1 | ~15 lines |
| 14 | Remove ch7 §7.2.4 third paragraph (redundant) | ch7 | ~5 lines |
| 15 | Choose table OR prose for ch7 §7.5 analysis | ch7 | ~50 lines |
| 16 | Remove ch7 表7-7 (LED Chaser state trace) | ch7 | ~15 lines |
| 17 | Fix missing 图6-3 numbering | ch6 | correctness |

### Expected Outcome After All Changes

| Metric | Before | After |
|--------|--------|-------|
| Tables (main text) | 22+ | 10-12 |
| Code blocks | 24 | 17 |
| Inline code references | 215 | ~80 |
| Duplicate figures | 6 placements | 0 |
| Repeated concepts (3+ occurrences) | 6 topics | 0 |
| Estimated page reduction | -- | 20-30 pages |
