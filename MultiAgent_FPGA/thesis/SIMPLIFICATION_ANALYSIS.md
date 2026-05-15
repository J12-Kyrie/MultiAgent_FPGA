# Thesis Simplification Analysis

## Summary

This analysis identifies content in the undergraduate thesis (chapters 1-8) that is excessively detailed, verbose, or structured more like technical documentation than academic writing. The thesis currently contains approximately 25+ tables, 48 code blocks, and over 300 inline code references -- far exceeding what is appropriate for an undergraduate thesis. The core problem is that the text reads as API-level documentation of the framework implementation rather than an academic argument about design decisions and their justification.

---

## 1. Excessive Tables

### Current Inventory (25+ tables across 8 chapters)

| # | Table | File:Lines | Rows x Cols | Verdict |
|---|-------|-----------|-------------|---------|
| 1 | [表2-1: DeepSeek双Profile参数对比] | ch2_background.md:26 | placeholder | KEEP (fill in or remove placeholder) |
| 2 | 表3-1: 与AutoGen方案的架构对比（10个维度） | ch3_system_design.md:44-57 | 10x3 | SIMPLIFY to 5-6 key dimensions |
| 3 | 表3-2: 4模块端口规范一览表 | ch3_system_design.md:88-106 | 16x5 | MOVE to appendix |
| 4 | 表3-3: Agent角色-LLM Profile-工具矩阵 | ch3_system_design.md:136-143 | 5x4 | KEEP |
| 5 | 表4-1: 每个状态的语义、执行者、输入/输出 | ch4_state_machine.md:76-88 | 10x5 | SIMPLIFY to 3-4 columns |
| 6 | 表4-2: OrchestratorState→Policy完整映射表 | ch4_state_machine.md:108-120 | 9x4 | REMOVE (redundant with 表4-1 and text) |
| 7 | [表5-1: 各层级验证目标、输入、输出、判定标准、典型耗时] | ch5_verification.md:21 | placeholder | KEEP (fill in) |
| 8 | 表5-2: 各模块Checkpoint一览表 | ch5_verification.md:122-133 | 9x3 | KEEP |
| 9 | [表5-3: 三种集成Campaign规格表] | ch5_verification.md:228 | placeholder | KEEP (fill in) |
| 10 | [表6-1: LLM失败模式-约束层级防御矩阵] | ch6_harnessing_engine.md:33 | placeholder reference | REMOVE placeholder (matrix is at 表6-3) |
| 11 | Skill键/名称/用途表 (Runtime Skills) | ch6_harnessing_engine.md:47-53 | 5x3 | SIMPLIFY to prose summary |
| 12 | Skill键/模块/内容表 (Memory Skills) | ch6_harnessing_engine.md:57-63 | 5x3 | SIMPLIFY to prose summary |
| 13 | [表6-2: 16个Skill文件分类表] | ch6_harnessing_engine.md:67 | placeholder | REMOVE (redundant with tables 11-12) |
| 14 | BaseContract约束维度表 | ch6_harnessing_engine.md:115-121 | 5x3 | KEEP (but reduce to 3 columns) |
| 15 | 表6-3: LLM失败模式-约束层级防御矩阵 | ch6_harnessing_engine.md:341-347 | 5x7 | MOVE to appendix (too wide) |
| 16 | 约束密度对比表 | ch6_harnessing_engine.md:366-373 | 6x3 | SIMPLIFY to 4 key rows |
| 17 | 表7-1: 实验环境配置表 | ch7_experiments.md:11-26 | 11x3 | SIMPLIFY to 5-6 key items |
| 18 | 表7-2: 单模块验证结果汇总 | ch7_experiments.md:77-83 | 4x6 | KEEP |
| 19 | 表7-3: 集成回归测试结果 | ch7_experiments.md:106-110 | 3x4 | KEEP |
| 20 | 表7-4: LLM API调用统计 | ch7_experiments.md:150-158 | 6x5 | REMOVE (all values are "—" or empty) |
| 21 | 表7-5: 能力维度对比表（10个维度） | ch7_experiments.md:180-191 | 10x4 | SIMPLIFY to 5-6 key dimensions |
| 22 | 表7-6: LED Chaser设计规格 | ch7_experiments.md:218-227 | 6x2 | KEEP |
| 23 | 表7-7: LED Chaser状态机执行轨迹 | ch7_experiments.md:244-253 | 8x4 | SIMPLIFY or merge with 表4-1 |
| 24 | 表7-8: LED Chaser模块验证结果 | ch7_experiments.md:260-263 | 1x6 | KEEP |
| 25 | 表7-9: LED Chaser Checkpoint详情 | ch7_experiments.md:267-272 | 4x4 | KEEP |
| 26 | 表7-10: LED Chaser集成回归测试结果 | ch7_experiments.md:280-282 | 1x4 | KEEP |
| 27 | Inline: 约束维度/本文方案/AutoGen方案对比 | ch6_harnessing_engine.md:366-373 | 6x3 | Duplicate of concept in 表3-1 |

### Recommendations

**Target: 10-12 tables total.** Current count is 25+. Proposed actions:

- **REMOVE entirely (4 tables):** 表4-2 (redundant with 表4-1), 表6-1 placeholder, 表6-2 placeholder, 表7-4 (all values are dashes/empty)
- **MOVE to appendix (3 tables):** 表3-2 (16-row port spec), 表6-3 (5x7 defense matrix), 表7-5 (10-dimension comparison, simplify to 5 dimensions in main text)
- **SIMPLIFY inline (6 tables):** 表3-1 (reduce from 10 to 5-6 dimensions), 表4-1 (reduce columns), Skill tables 11-12 (convert to prose), 表7-1 (reduce from 11 to 5-6 items), 表7-5 (reduce dimensions), 表7-7 (merge with existing state machine table)
- **KEEP as-is (8 tables):** 表3-3, 表5-1 (when filled), 表5-2, 表5-3 (when filled), 表7-2, 表7-3, 表7-6, 表7-8/9/10

---

## 2. Excessive Code/Programming Content

### Code Blocks (>10 lines, should be shortened or removed)

| # | Code Block | File:Lines | Language | Lines | Verdict |
|---|-----------|-----------|----------|-------|---------|
| 1 | `emit_checkpoint()` function | ch5_verification.md:57-63 | C++ | 7 | KEEP (short, illustrative) |
| 2 | `CheckpointParser` class | ch5_verification.md:87-100 | Python | 14 | SHORTEN to 5-line excerpt |
| 3 | `random_block()` function | ch5_verification.md:161-167 | C++ | 7 | KEEP (short) |
| 4 | `compose_prompt()` function signature | ch6_harnessing_engine.md:97-105 | Python | 9 | REMOVE (API detail) |
| 5 | `_MEMORY_REGISTRY` dict | ch6_harnessing_engine.md:179-185 | Python | 7 | REMOVE (implementation detail) |
| 6 | repair mode ValueError | ch6_harnessing_engine.md:142-147 | Python | 6 | REMOVE (implementation detail) |
| 7 | `should_escalate()` method | ch4_state_machine.md:150-164 | Python | 15 | SHORTEN to 3-line logic summary |
| 8 | `repair_budget_for_node()` function | ch4_state_machine.md:177-181 | Python | 5 | KEEP (short, illustrative) |
| 9 | `run_current_batch_until_gate()` signature | ch4_state_machine.md:234-242 | Python | 9 | REMOVE (API detail) |
| 10 | CLI command listing | ch6_harnessing_engine.md:313-322 | bash | 10 | SHORTEN to 3-4 key commands |
| 11 | CLI command listing | ch7_experiments.md:30-45 | bash | 16 | SHORTEN to 1 key command |
| 12 | State transition pseudocode | ch4_state_machine.md:59-70 | text | 12 | KEEP (essential) |
| 13 | Execution path pseudocode | ch5_verification.md:259-261 | text | 3 | KEEP |

### Sections That Read Like Software Manuals

1. **ch3_system_design.md lines 15-36 (Six-Layer Architecture):** This section lists every file name, class name, and function name in the framework. For a thesis, describe the *purpose and design rationale* of each layer in 2-3 sentences, not the file-by-file implementation inventory. Move the file listing to an appendix or remove entirely.

2. **ch4_state_machine.md lines 9-52 (10 State Definitions):** Each state description includes internal function names (`synthesize_spec_ir()`, `L0Executor`, `CheckpointParser`, etc.). Strip to: state name, semantic purpose (1 sentence), which agent type executes it. The internal implementation is not thesis-level content.

3. **ch5_verification.md lines 82-112 (CheckpointParser internals):** The full `CheckpointParser` class and `summarize_required_checkpoints()` function are implementation details. Replace with a 2-sentence description of the parsing algorithm.

4. **ch6_harnessing_engine.md lines 37-302 (Sections 6.2-6.7):** Nearly every paragraph includes function signatures with file paths and line numbers (e.g., `fpga_flow/skill_refs.py:22-51`). This is API documentation, not thesis prose. Remove all `file:line` references from the main text; move to footnotes only when absolutely necessary for verifiability.

5. **ch6_harnessing_engine.md lines 236-262 (run_executor and verify_repair_edit):** Detailed execution flow with 5 numbered steps listing internal function calls. Replace with a conceptual description of the proxy pattern and its verification guarantees.

6. **ch7_experiments.md lines 56-63 (Verification Flow):** Lists 4 steps with internal function names (`MemoryStore.populate_workspace()`, `L0Executor`, `L1Executor`, `CheckpointParser`). Replace with prose describing the verification pipeline conceptually.

---

## 3. Gray Code Blocks (Inline Code Overuse)

### Inline Code Statistics

| Chapter | Inline code occurrences | Assessment |
|---------|------------------------|------------|
| ch1_introduction.md | 5 | Acceptable |
| ch2_background.md | 13 | Acceptable |
| ch3_system_design.md | 48 | EXCESSIVE |
| ch4_state_machine.md | 49 | EXCESSIVE |
| ch5_verification.md | 49 | EXCESSIVE |
| ch6_harnessing_engine.md | 83 | CRITICALLY EXCESSIVE |
| ch7_experiments.md | 42 | EXCESSIVE |
| ch8_conclusion.md | 16 | Borderline |

**Total: 305 inline code references across 8 chapters.** For an undergraduate thesis, this should be under 100.

### Worst Offending Paragraphs

**ch6_harnessing_engine.md line 44-45:**
> 本框架构建了由16个Skill文件组成的三级注册体系，通过`skill_refs.py`统一管理。三级注册体系的分工严格区分了运行时注入与离线参考的职责：

Replace `skill_refs.py` with plain text "技能引用管理模块".

**ch6_harnessing_engine.md line 77:**
> `SKILLS_AS_AUTHORITY_CONTRACT`（`fpga_flow/prompt_contracts.py:72-77`）是Skill层的元约束：

Two inline code references in one sentence plus a file:line citation. Replace with: "技能权威性合约是Skill层的元约束："

**ch6_harnessing_engine.md lines 131-139:**
> `_select_phase_mixins(active_mode)`（`fpga_flow/prompts.py:91-114`）... `generate`模式：在基础混入（`WORKER_LOCAL_SCOPE`、`WORKER_REQUEST_AUTHORITY`、`RUN_EXECUTOR_PHASE`）之上加入`GENERATE_PHASE`和`MEMORY_CONSULTATION_DIRECTIVE`

Five inline code references in one sentence. Replace function names with descriptive Chinese terms.

**ch4_state_machine.md line 9:**
> 本框架的编排器状态机由 `policy.py` 中的 `OrchestratorState` 枚举完整定义，共包含 10 个状态。这 10 个状态不仅是系统执行阶段的语义标记，更是 `AgentExecutionPolicy` 映射的索引键

Replace with: "本框架的编排器状态机共定义10个状态，每个状态不仅标记执行阶段，更是执行策略映射的索引键。"

**ch3_system_design.md lines 17-36 (entire six-layer description):**
Every layer description is packed with class names, function names, and file paths. Example:
> `artifacts.py`（Pydantic 模型定义）、`policy.py`（执行策略枚举与映射）和 `executor_contracts.py`（执行器输入解析与 Checkpoint 汇总）

Replace all file names with descriptive Chinese terms. The reader does not need to know which Python file contains which class.

### Recommended Replacements

| Inline Code | Replace With |
|-------------|-------------|
| `SpecIR` | 规格中间表示（SpecIR） |
| `PlanDAG` | 执行计划有向无环图（PlanDAG） |
| `AgentExecutionPolicy` | 执行策略（首次出现时注明英文） |
| `MemoryStore` | 内存存储模块 |
| `CheckpointParser` | Checkpoint解析器 |
| `L0Executor` / `L1Executor` | L0执行器 / L1执行器 |
| `run_executor` | 执行工具（run_executor） |
| `verify_repair_edit()` | 修复编辑验证函数 |
| `fpga_flow/xxx.py:NNN` | 删除所有 file:line 引用 |
| `DEEPSEEK_OFFICIAL_THINKING` | 深度思考模式 |
| `DEEPSEEK_OFFICIAL_FAST` | 快速执行模式 |
| `MODULE_WORKER_ALLOWED` | 允许模块工作者 |
| `extra='forbid'` | "严格模式"或"禁止额外字段" |
| `reasoning_effort='medium'` | "中等推理深度" |
| `reasoning_effort='none'` | "无扩展推理" |

---

## 4. Overly Detailed Technical Passages

### 4.1 Repeated Concepts (explained 3+ times)

**Framework-controlled vs Prompt-controlled:**
- ch1_introduction.md:33 (不足一)
- ch3_system_design.md:8-11 (设计哲学)
- ch4_state_machine.md:203-261 (entire §4.4)
- ch6_harnessing_engine.md:360-375 (约束密度对比)
- ch7_experiments.md:175-204 (能力维度对比, dimension 4)
- ch8_conclusion.md:8-9 (研究回顾)

**Recommendation:** Define once in ch1 (briefly), elaborate in ch3 or ch4 (one dedicated section), reference in later chapters. Remove the redundant explanations from ch6, ch7, and ch8.

**Six-Layer Harnessing Engine:**
- ch1_introduction.md:51 (创新点三, full description)
- ch3_system_design.md:34-36 (§3.1.2 第六层)
- ch6_harnessing_engine.md:1-377 (entire chapter)
- ch8_conclusion.md:27-31 (创新点三 recap)

**Recommendation:** Brief overview in ch1, detailed treatment in ch6 only. ch3 should reference ch6, not re-explain. ch8 should summarize findings, not re-describe the architecture.

**AutoGen Comparison:**
- ch3_system_design.md:41-58 (表3-1, 10 dimensions)
- ch4_state_machine.md:255-261 (§4.4.4)
- ch6_harnessing_engine.md:360-375 (约束密度对比表)
- ch7_experiments.md:175-204 (表7-5, 10 dimensions)

**Recommendation:** One comprehensive comparison table in ch3 or ch7. Remove the other three instances.

**AES-128 Module DAG:**
- ch1_introduction.md:47 (brief mention)
- ch2_background.md:124-138 (§2.4.4, microarchitecture)
- ch3_system_design.md:66-107 (§3.2, full description with port table)
- ch5_verification.md:118-134 (checkpoint table)
- ch7_experiments.md:66-71 (checkpoint spec recap)

**Recommendation:** Full description in ch3. Brief reference elsewhere.

### 4.2 Passages That Should Be Appendices

1. **ch3_system_design.md lines 86-107 (表3-2: Port Specification):** A 16-row table listing every signal name, direction, width, and description. This is reference material, not thesis prose.

2. **ch5_verification.md lines 155-170 (Random Number Generation):** The xorshift algorithm implementation details (C++ code, seed values, state transitions) are implementation specifics that belong in an appendix.

3. **ch6_harnessing_engine.md lines 349-358 (Complete Constraint Chain for aes_sbox):** A 6-step walkthrough of every constraint layer for one module. This is a debugging/development artifact, not thesis content.

4. **ch7_experiments.md lines 240-254 (LED Chaser State Machine Trace):** An 8-row table repeating the state machine definition from ch4 with LED Chaser-specific values. One sentence saying "the state machine executed the same 10 states as AES-128" suffices.

### 4.3 Implementation-Heavy Sections to Condense

1. **ch3_system_design.md §3.1.2 (Six-Layer Architecture):** Currently 22 lines listing every file and class. Condense to 6 bullet points, one per layer, each 2 sentences describing purpose and key design choice.

2. **ch4_state_machine.md §4.1.1 (State Definitions):** 10 state descriptions averaging 5 lines each, totaling 50 lines. Each state includes internal function names and implementation details. Condense to a table (表4-1) with 3 columns: state name, semantic purpose, executing agent.

3. **ch5_verification.md §5.2.3-5.2.4 (CheckpointParser Internals):** Full Python class listing plus function description. Replace with: "Checkpoint解析器通过逐行扫描仿真日志，以CHECKPOINT|为前缀匹配提取验证结果，构建检查点名称到状态的映射字典。"

4. **ch6_harnessing_engine.md §6.5 (Hooks Layer):** 30+ lines describing `run_executor` internals with 5 numbered steps and function signatures. Replace with a conceptual description of the proxy pattern.

5. **ch6_harnessing_engine.md §6.4.1 (MemoryStore):** Includes Python dict literal and regex description. Replace with prose explaining the memory retrieval concept.

---

## 5. Missing Academic Flow

### 5.1 Abrupt Topic Transitions

**ch3_system_design.md line 63-64:**
> ---
> ## 3.2 验证案例：AES-128 全系统设计分解

The transition from the generic six-layer architecture (§3.1) to the AES-128 specific case (§3.2) lacks a bridging sentence. Add: "上述通用架构在具体硬件设计上的实例化方式，以下以AES-128加密全系统为例进行说明。"

**ch4_state_machine.md line 89:**
> ---
> ## 4.2 AgentExecutionPolicy 策略分层

The transition from state definitions to policy layering needs a sentence connecting the two: "状态机定义了'何时执行'，而策略分层决定了'如何执行'。"

**ch5_verification.md line 137:**
> ---
> ## 5.3 L2鲁棒性测试

Jump from Checkpoint protocol to L2 testing without transition. Add: "L0和L1验证覆盖了语法正确性和已知向量的功能正确性，但对于随机输入和边界条件下的行为鲁棒性尚未验证。L2鲁棒性测试正是为弥补这一验证缺口而设计。"

**ch6_harnessing_engine.md line 87:**
> ---
> ## 6.3 Prompt层：行为约束合成

Transition from Skill layer to Prompt layer needs connection: "Skill层解决了'Agent知道什么'的问题，而Prompt层解决'Agent被允许做什么'的问题。"

### 5.2 Sections Lacking Topic Sentences

**ch3_system_design.md lines 15-36:** The six-layer description begins immediately with "第一层：Contract 层" without a topic sentence establishing why a six-layer architecture was chosen over alternatives.

**ch4_state_machine.md lines 147-164 (§4.3.1):** The escalation trigger conditions section begins with a function signature rather than explaining the design motivation.

**ch5_verification.md lines 70-80 (§5.2.2):** The design decision analysis section begins with "选择简单文本协议而非结构化输出" -- this is good, but it should be preceded by a sentence explaining why the protocol format choice matters.

### 5.3 Arguments That Could Be Tightened

**ch1_introduction.md §1.3 (Five Deficiencies):** Each deficiency is 3-4 sentences. For an undergraduate thesis introduction, 2 sentences each would suffice. The detailed argumentation belongs in the respective chapter where each deficiency is addressed.

**ch6_harnessing_engine.md §6.1.2 (Design Philosophy):** The horse-harness metaphor paragraph (line 23) is evocative but adds 4 lines without advancing the technical argument. Consider a single sentence.

**ch7_experiments.md §7.2.4 (Memory Injection Analysis):** Three paragraphs explaining the same point (memory injection reduces generation difficulty). The third paragraph (line 90-92) restates what the first two already established. Remove the third.

**ch7_experiments.md §7.5 (10-Dimension Comparison):** The table already captures the comparison. The subsequent §7.5.1 "各维度分析" repeats every row of the table in prose form (5 paragraphs, 100+ lines). Either keep the table OR the prose, not both.

---

## 6. Summary of Recommended Changes

### Priority 1 (High Impact, Must Fix)

| Action | Files Affected | Impact |
|--------|---------------|--------|
| Remove 4 redundant/empty tables | ch4, ch6, ch7 | Reduces table count by 4 |
| Move 3 oversized tables to appendix | ch3, ch6, ch7 | Keeps reference material accessible |
| Strip all `file:line` references from main text | ch3, ch4, ch5, ch6 | Eliminates ~40 inline code refs |
| Remove duplicate AutoGen comparisons (keep 1) | ch4, ch6, ch8 | Removes ~100 lines of repetition |
| Remove duplicate Harnessing Engine descriptions (keep ch6 only) | ch1, ch3, ch8 | Removes ~50 lines of repetition |

### Priority 2 (Medium Impact, Should Fix)

| Action | Files Affected | Impact |
|--------|---------------|--------|
| Replace inline code with Chinese descriptions | All chapters | Reduces inline code from 305 to ~80 |
| Condense 6-layer architecture description | ch3 | Reduces from 22 lines to 12 |
| Condense 10 state descriptions to table | ch4 | Reduces from 50 lines to table |
| Remove code blocks >10 lines (keep only illustrative ones) | ch4, ch5, ch6 | Removes 5-6 code blocks |
| Add transition sentences between sections | ch3, ch4, ch5, ch6 | Improves academic flow |

### Priority 3 (Polish, Nice to Have)

| Action | Files Affected | Impact |
|--------|---------------|--------|
| Shorten ch1 §1.3 deficiency descriptions | ch1 | Tighter introduction |
| Remove horse-harness metaphor | ch6 | Removes 4 lines |
| Remove third Memory injection paragraph | ch7 | Removes redundant analysis |
| Choose table OR prose for ch7 §7.5 comparison | ch7 | Removes ~100 lines |

### Expected Outcome

After all changes:
- Tables: ~10-12 (down from 25+)
- Code blocks: ~6-8 (down from 48)
- Inline code references: ~80 (down from 305)
- Repeated concepts: 1 instance each (down from 3-6)
- Estimated page reduction: 15-25 pages
