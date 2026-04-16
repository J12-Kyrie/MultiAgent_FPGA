# 第三章 系统总体设计

## 3.1 系统架构概述

### 3.1.1 整体设计哲学

本系统的核心设计哲学可概括为"框架控制"（Framework-controlled）原则，即批次推进决策、验证通过判定和状态机转移均由框架代码而非 LLM 本身掌握。这一原则与传统"提示词控制"（Prompt-controlled）方案形成根本性的对立：在提示词控制方案中，Agent 通过自然语言指令自行决定何时宣告完成、何时推进阶段，这不可避免地引入 LLM 幻觉和不收敛风险；而在本系统中，LLM 的角色严格限定为局部执行者——它生成或修复代码，但无权声明验证已通过或批次已完成。

框架控制的另一个维度体现在数据流的单向性：`SpecIR`（规格中间表示）→ `PlanDAG`（有向无环图执行计划）→ Workspace（工作区草稿）→ L0/L1 验证 → Promote（晋升）→ Integration（集成回归）。每个阶段的进入条件由框架在文件系统层面检查，Agent 通过写文件向框架传递信息，框架通过门控回调决定是否推进。

### 3.1.2 六层架构

本系统采用六层分层架构，自底层向上依次为：

**第一层：Contract 层（合约层）**
合约层是整个系统的数据类型基础。其核心文件包括 `artifacts.py`（Pydantic 模型定义）、`policy.py`（执行策略枚举与映射）和 `executor_contracts.py`（执行器输入解析与 Checkpoint 汇总）。该层所有模型均采用 Pydantic 的 `extra='forbid'` 配置，即任何未声明字段的出现将立即触发验证异常。这一设计是系统的第一道反幻觉屏障：LLM 若在输出中添加了不在规格中的字段，系统将拒绝该输出而非静默接受。

关键数据模型包括：`SpecIR`（规格中间表示，含 `system_goal`、`algorithm`、`variant`、`operation`、`microarchitecture`、`latency_target_cycles` 等字段，并通过 `@model_validator` 强制校验 AES 范围约束）、`PlanDAG`（包含 `PlanDAGNode` 列表，内置 DFS 无环验证）、`ModuleContract`（每模块端口和 Checkpoint 合约）、`NodeWorkspaceRecord`（工作区状态记录）、`RepairContract`（结构化修复指令）、`EditReceipt`（编辑收据）及 `IntegrationRegressionManifest`（集成回归清单）。

**第二层：Synthesis 层（合成层）**
合成层负责从硬编码的 AES 蓝图生成所有核心构件。`synthesis.py` 中的 `_aes_blueprints()` 函数是节点分类学的唯一事实来源，它定义了 4 个节点的模块标识符、依赖关系、RTL 文件路径、测试台路径、L2 策略、关键度、集成角色、端口规范、Checkpoint 名称及向量集路径。在此基础上，`synthesize_spec_ir()` 生成 `SpecIR`，`synthesize_plan_dag()` 生成 `PlanDAG`，`synthesize_integration_manifest()` 生成集成清单。`ContractCompiler` 进一步为每个节点编译 `ModuleContract`、`TestbenchContract` 和 `ModuleDesignBrief`。

**第三层：Execution 层（执行层）**
执行层封装了全部 Verilator 操作。`executors.py` 实现了 `L0Executor`（编译门控）、`L1Executor`（编译+仿真+Checkpoint 解析）、`L2CampaignExecutor`（鲁棒性测试，支持 `+profile`/`+vecfile`/`+seed`/`+cases` plusarg）和 `IntegrationRegressionExecutor`（三种集成 campaign）。`adapters/verilator.py` 中的 `VerilatorMCPAdapter` 通过 Model Context Protocol（MCP）向底层 Node.js 服务发送编译/仿真请求，自动推断 include 标志、过滤输入文件、附加 C++17 编译标准。所有执行器继承自 `_BaseExecutor`，其中的 `CheckpointParser` 负责从 `simulation.log` 中解析 `CHECKPOINT|<name>|PASS|<detail>` 协议行。

**第四层：Runtime 层（运行时层）**
运行时层是系统的骨干，负责 SDK 集成与会话编排。`runtime/bootstrap.py` 中的 `RuntimeBootstrap.build()` 负责完整的启动初始化：加载 SDK 模块、校验 13 个 Skill 文件、构建 LLM Profile 参数、合成 `SpecIR`/`PlanDAG`/`IntegrationManifest`、配置 Verilator MCP 服务器。`runtime/factory.py` 中的 `SdkAgentFactory` 按角色创建 Agent 实例。`runtime/runner.py` 中的 `ConversationRunner` 驱动 SDK 对话，其核心方法 `run_current_batch_until_gate()` 实现了门控驱动的批次执行：在独立线程中运行对话，主线程以 0.2 秒间隔轮询门控回调，当门控满足或超时（默认 180 秒）时暂停对话。`runtime/session.py` 中的 `ExecutionSession` 是最顶层的编排驱动器，负责规划批次、执行批次、写报告树、跟踪晋升事件、处理集成回归并产生最终汇总。

**第五层：Generation 层（生成层）**
生成层管理工作区的完整生命周期。`generation.py` 中的 `initialize_node_workspace()` 负责创建工作区目录结构、写入合约 JSON 并通过 `MemoryStore.populate_workspace()` 预填充草稿文件。修复循环的完整流程为：`write_repair_request()` 写出结构化修复合约 → Agent 执行编辑 → `verify_repair_edit()` 通过 SHA-256 哈希验证文件确实发生了变化且包含必要的修复令牌 → `write_edit_receipt()` 写出编辑收据 → 触发重新验证。`promote_workspace()` 在验证通过后将草稿文件复制到 `promoted/<module_id>/` 目录。`NodeWorkspaceState` 枚举定义了工作区的完整生命周期：`MISSING` → `DRAFT_READY` → `VALIDATED` → `PROMOTED`（或经由 `REPAIRING` → `BLOCKED`/`FAILED`）。

**第六层：Agent/Prompt 层（智能体/提示词层）**
该层定义 Agent 角色规范、提示词合成和 Skill 注入策略。`agents/specs.py` 为每个角色提供 `AgentSpawnSpec` 构建函数，封装了角色类型、LLM Profile、系统提示词、Skill 键集合、允许状态集合和可写路径约束。`prompt_contracts.py` 定义了可组合的 `BaseContract` 和 `PhaseMixin` 常量，通过 `compose_prompt()` 四层组合（角色引言 → 基础合约 → 阶段混入 → 实例负载 → Skill 块）生成最终提示词。`skill_refs.py` 管理 16 个 Skill 文件的三级注册体系。

[图 3-1: 系统六层架构图（从底层 Contract 到顶层 Agent/Prompt）]

### 3.1.3 与胡昆越 AutoGen 方案的架构对比

表 3-1 从 10 个维度对本系统与胡昆越基于 AutoGen 实现的 FPGA 设计自动化方案进行架构层面的对比分析。

**表 3-1: 与胡昆越 AutoGen 方案的架构对比（10 个维度）**

| 维度 | 胡昆越方案（AutoGen） | 本文方案（OpenHands SDK） |
|------|----------------------|--------------------------|
| Agent 框架 | AutoGen ConversableAgent 链式调用 | OpenHands SDK（状态机 + 层级委派） |
| LLM 后端 | DeepSeek-reasoner + 本地微调 codegen-2B | DeepSeek-chat（thinking/fast 双 Profile） |
| 代码生成策略 | 微调模型直接生成 Verilog | Memory 预填充参考代码 + Agent 修复循环 |
| 验证工具链 | Vivado（TCL 脚本驱动，商业许可） | Verilator（MCP 协议 + Checkpoint 自动解析，开源） |
| Agent 协作模式 | 线性 6 步 pipeline（串行执行） | 分层拓扑批调度 + Orchestrator-Worker 委派 |
| 验证层级 | 单层（Vivado 仿真通过/失败） | 4 层（L0 编译门控 → L1 仿真 → L2 鲁棒性 → 集成回归） |
| 控制模式 | Prompt-controlled（LLM 自主决定推进） | Framework-controlled（状态机拥有控制权） |
| 修复机制 | Debug Agent 读日志后重写代码，无收敛保证 | 结构化 RepairContract + SHA-256 哈希验证 + 2 次升级阈值 |
| 并行执行能力 | 无（严格线性执行） | DAG 拓扑分层：同层节点可并行委派 |
| 约束工程密度 | 单层约束（system_message 纯文本） | 6 层约束引擎（Skill/Prompt/Memory/Hooks/MCP/SlashCommand） |

两种方案在出发点上各有侧重。胡昆越方案以模型能力为核心，通过微调提升单次代码生成的正确率；本文方案以系统架构为核心，通过框架结构和约束工程降低 LLM 不可靠性对系统正确性的影响。这一根本性的设计选择差异决定了两种方案在可扩展性、可维护性和可靠性方面的不同取向。

---

## 3.2 AES-128 全系统设计分解

### 3.2.1 模块依赖 DAG

本系统以 AES-128 加密全系统为案例，共包含 4 个硬件模块，其依赖关系构成一个有向无环图（DAG）。该 DAG 结构在 `synthesis.py` 的 `_aes_blueprints()` 函数中以硬编码方式定义，并在 `PlanDAG` 的 `@model_validator` 中通过深度优先搜索（DFS）进行无环验证。

[图 3-2: AES-128 模块依赖 DAG 图（4 节点，含依赖箭头）]

4 个模块的角色与依赖关系如下：

**aes_sbox（S-box 替换模块）**：实现 AES 标准中的字节替换操作，为纯组合逻辑，无上游依赖。该模块是 DAG 的叶节点（`integration_role: leaf`），被 `aes_key_schedule_128`、`aes_round_transform` 和 `aes128_encrypt_core` 三个模块依赖。由于其功能单一且无依赖，`l2_policy` 设置为 `skip`（跳过鲁棒性测试）。

**aes_key_schedule_128（密钥扩展模块）**：实现 AES-128 的密钥扩展算法，生成 11 组轮密钥（含初始密钥在内）。该模块依赖 `aes_sbox`（用于 SubWord 操作），`l2_policy` 为 `conditional`，`criticality` 为 `high`。

**aes_round_transform（轮变换模块）**：实现 AES 单轮的 4 步变换：SubBytes（字节替换）、ShiftRows（行移位）、MixColumns（列混合，基于 GF(2^8) 有限域运算）和 AddRoundKey（轮密钥异或）。该模块依赖 `aes_sbox`，`l2_policy` 为 `conditional`，`criticality` 为 `high`。

**aes128_encrypt_core（顶层加密核心）**：实现 AES-128 加密的顶层有限状态机（FSM），集成上述全部子模块，实现 11 周期延迟（初始 AddRoundKey 1 周期 + 10 轮迭代各 1 周期）的 block-level handshake 接口。该模块是 DAG 的 sink 节点（`integration_role: sink`），`l2_policy` 为 `required`，`criticality` 为 `high`，是集成回归测试的顶层目标。

### 3.2.2 模块端口规范

**表 3-2: 4 模块端口规范一览表**

| 模块 | 信号名 | 方向 | 宽度 | 说明 |
|------|--------|------|------|------|
| aes_sbox | in_byte | input | 8 | 待替换的输入字节 |
| aes_sbox | out_byte | output | 8 | 替换后的输出字节 |
| aes_key_schedule_128 | key | input | 128 | AES-128 原始密钥 |
| aes_key_schedule_128 | round_keys | output | 1408 | 11 组轮密钥（11×128 bit） |
| aes_round_transform | state_in | input | 128 | 轮变换输入状态 |
| aes_round_transform | round_key | input | 128 | 本轮密钥 |
| aes_round_transform | is_last_round | input | 1 | 末轮标志（跳过 MixColumns） |
| aes_round_transform | state_out | output | 128 | 轮变换输出状态 |
| aes128_encrypt_core | clk | input | 1 | 时钟信号 |
| aes128_encrypt_core | rst | input | 1 | 同步复位（高有效） |
| aes128_encrypt_core | start | input | 1 | 加密启动握手信号 |
| aes128_encrypt_core | plaintext | input | 128 | 明文输入 |
| aes128_encrypt_core | key | input | 128 | 加密密钥 |
| aes128_encrypt_core | ciphertext | output | 128 | 密文输出 |
| aes128_encrypt_core | done | output | 1 | 完成单周期脉冲 |
| aes128_encrypt_core | busy | output | 1 | 运算进行中标志 |

上述接口规范在 `synthesis.py` 的 `_aes_blueprints()` 中以 `PortSpec` 字典形式定义，经 `ContractCompiler.compile_module_contract()` 转换为 `ModuleContract` 模型，并写入各模块工作区的 `module_contract.json` 文件，成为 Agent 在生成和修复过程中不得更改的冻结接口约束。

---

## 3.3 Agent 角色与 LLM 配置

### 3.3.1 Agent 角色体系

本系统共定义 4 种 Agent 角色，由 `policy.py` 中的 `AgentRole` 枚举列出：`WORKFLOW_ORCHESTRATOR`（工作流编排器）、`MODULE_WORKER_SUBAGENT`（模块工作者子代理）和 `L2_CAMPAIGN_SUBAGENT`（L2 测试活动子代理）。各角色由 `agents/specs.py` 中对应的 `AgentSpawnSpec` 构建函数创建，每个规范包含角色类型、LLM Profile、系统提示词、Skill 键集合、允许的编排器状态集合及可写路径约束。

具体来看，本系统设计了 5 个 Agent 构建函数：

- `build_workflow_orchestrator_spec()`：构建执行编排器，使用 `DEEPSEEK_OFFICIAL_FAST` profile，持有 `run_executor` 自定义工具，允许在除 `DONE` 之外的全部 9 个状态下活动，不持有任何可写路径（编排器不直接写文件）。
- `build_finalizer_orchestrator_spec()`：构建终态汇总编排器，使用 `DEEPSEEK_OFFICIAL_THINKING` profile，持有 `FinishTool`，仅允许在 `INTEGRATION_READY`、`INTEGRATION_REGRESSION`、`DONE` 三个状态下活动，负责生成最终工作流报告后调用 `finish()`。
- `build_module_worker_spec(node)`：构建单模块工作者，使用 `DEEPSEEK_OFFICIAL_FAST` profile，持有 `run_executor` 工具，可写路径严格限定为该节点的 RTL 文件和测试台文件，仅允许在 `MODULE_DESIGN`、`MODULE_L0`、`MODULE_L1` 三个状态下活动。
- `build_repair_worker_spec()`：构建专用修复工作者，使用 `DEEPSEEK_OFFICIAL_FAST` profile，不持有 `run_executor`（修复阶段不允许触发执行），遵循"编辑优先"协议。
- `build_l2_campaign_spec(node, ...)`：构建 L2 测试活动代理，使用 `DEEPSEEK_OFFICIAL_FAST` profile，持有 `run_executor` 工具，仅允许在 `MODULE_L2_OPTIONAL` 状态下活动，不允许 RTL 或测试台编辑。

### 3.3.2 双 LLM Profile 策略

系统采用 `LLMProfileName` 枚举定义两种 DeepSeek API 调用配置：

- `DEEPSEEK_OFFICIAL_THINKING`（深度思考模式，`reasoning_effort='medium'`）：计算成本较高但推理能力强，用于需要跨模块推理的编排器（规格分析、架构设计、集成回归阶段）以及最终汇总编排器。
- `DEEPSEEK_OFFICIAL_FAST`（快速执行模式，`reasoning_effort='none'`）：响应快速、成本低，用于局部任务执行的工作者（模块生成、验证、修复、L2 测试）。

这一双 Profile 设计的核心逻辑是：跨模块决策（如判断模块间接口是否一致、决定是否升级）需要深度推理能力，而节点本地任务（如基于已有参考代码修复一个编译错误）不需要耗费推理资源，使用快速模式即可完成。通过在正确的任务上使用正确的 Profile，系统在保证决策质量的同时控制了 API 调用成本。

**表 3-3: Agent 角色-LLM Profile-工具矩阵**

| Agent 角色 | LLM Profile | 持有工具 | 典型活动状态 |
|-----------|-------------|---------|------------|
| 执行编排器（Workflow Orchestrator） | FAST | run_executor | MODULE_DESIGN / L0 / L1 |
| 终态编排器（Finalizer Orchestrator） | THINKING | FinishTool | INTEGRATION_READY / DONE |
| 模块工作者（Module Worker） | FAST | run_executor | MODULE_DESIGN / L0 / L1 |
| 修复工作者（Repair Worker） | FAST | 无 | MODULE_DESIGN / L0 / L1 |
| L2 测试代理（L2 Campaign） | FAST | run_executor | MODULE_L2_OPTIONAL |

---

## 3.4 DAG 拓扑批调度与并行执行

### 3.4.1 拓扑分层算法

`synthesis.py` 中的 `DAGBatchPlanner` 类实现了基于 Kahn 算法变体的拓扑分层调度。`_topological_layers()` 方法计算每个节点的入度（依赖数量），将入度为 0 的节点放入初始就绪集合，按批次执行并在每次执行后将新满足依赖的节点加入下一批次。

对于 AES-128 的 4 节点 DAG，拓扑分层的结果为：

- **第一批次（Layer 1）**：`[aes_sbox]`——无依赖，单独执行。
- **第二批次（Layer 2）**：`[aes_key_schedule_128, aes_round_transform, aes128_encrypt_core]`——在 `aes_sbox` 完成后，三个模块的依赖均已满足，理论上可并行委派执行。

节点在同层内按优先级排序：首先按 `integration_role`（`top` > `sink` > `leaf` > `support`），其次按 `criticality`（`high` > `medium` > `low`），最后按 `module_id` 字母序。这一排序策略确保顶层/关键模块优先处理。

批次任务被封装为 `DelegateBatchPlan`，包含 `batch_id`、`stage`（对应 `OrchestratorState`）、`max_children`（最大子代理数，默认 5）和 `tasks` 列表。`max_children` 限制了单批次并行子代理数量，防止对 LLM API 造成过大并发压力。

[图 3-3: 拓扑批调度执行时序图（Batch 1 串行 → Batch 2 并行委派）]

### 3.4.2 工作区生命周期状态机

每个节点的工作区存在独立的状态机，由 `NodeWorkspaceState` 枚举定义 7 个状态：

- `MISSING`：工作区尚未初始化
- `DRAFT_READY`：工作区已初始化、草稿文件已由 Memory 预填充
- `VALIDATED`：L0 编译和 L1 仿真均通过，所有必需 Checkpoint 均为 PASS
- `PROMOTED`：已从草稿工作区晋升至规范 RTL/TB 路径
- `REPAIRING`：验证失败，正在修复循环中（未超出预算）
- `BLOCKED`：修复预算耗尽，需要人工介入或升级至思考型编排器
- `FAILED`：发生不可恢复的错误

`NodePolicyEngine.decide_next_mode()` 根据当前 `NodeWorkspaceRecord` 状态和验证结果决定下一个 `SubagentWorkMode`（`GENERATE`、`VALIDATE`、`REPAIR`、`L2_EXECUTE` 或 `INTEGRATION`）。这一决策逻辑完全在框架侧执行，LLM 无法直接影响工作区状态的推进。

---

## 3.5 关键支撑机制概述

### 3.5.1 结构化修复循环

当 L0 编译或 L1 仿真失败时，系统启动结构化修复循环。修复循环的完整流程为：

1. `write_repair_request()` 生成 `RepairContract` 并写入工作区，其中包含失败阶段（`failure_phase`）、主要目标文件（`primary_target_file`）、文件片段（`primary_file_excerpt`）、错误摘要（`error_excerpt`）、仿真日志摘要（`simulation_log_excerpt`）及第一步编辑指令（`first_edit_steps`）。
2. 修复工作者 Agent 读取 `RepairContract`，按照 `REPAIR_PHASE_ROUND_1` 或 `REPAIR_PHASE_ROUND_2_PLUS` 阶段混入的约束执行精确编辑。第一轮修复的硬性要求是：**第一个工具调用必须是对 `primary_target_file` 的文件编辑**，防止 Agent 偏离修复范围。
3. `verify_repair_edit()` 通过 SHA-256 哈希比对验证文件确实发生了实质性变化，并检查 `must_add_tokens` 列表中的必要令牌是否已被添加。哈希验证失败意味着 Agent 未实际修改文件，系统将拒绝该修复并记录失败。
4. `write_edit_receipt()` 写出 `EditReceipt`，记录已编辑的文件列表和第一步编辑摘要。
5. 重新触发 L0/L1 验证。

### 3.5.2 升级策略

`AgentExecutionPolicy.should_escalate()` 是升级决策的唯一入口，当下列任一条件满足时返回 `True`：

- `repair_attempts >= repair_attempt_threshold`（修复次数达到阈值，默认 2 次）
- `cross_module_issue=True`（问题跨越模块边界）
- `state_machine_issue=True`（涉及状态机逻辑错误）
- `interface_issue=True`（涉及接口信号不兼容）

升级后，控制权从快速模式的工作者 Agent 返回至深度思考模式的编排器，携带完整的失败上下文（失败阶段、错误日志、已尝试的修复历史），由编排器决定后续策略（继续修复、放弃该节点或重新规划）。

### 3.5.3 Pydantic 反幻觉机制

所有合约模型均使用 `ConfigDict(extra='forbid')`，这意味着任何 JSON 响应中出现的多余字段都会在反序列化时立即触发 `ValidationError`。结合 `@model_validator` 中的范围约束（如 `SpecIR` 强制 `algorithm='AES'`、`variant='AES-128'`、`latency_target_cycles=11`），系统构建了一个机器可检查的约束体系，有效防止 LLM 幻觉污染核心数据结构。

---

本章从整体层面描述了系统的六层架构、AES-128 模块分解、Agent 角色配置、DAG 批调度机制及三项关键支撑机制。这一架构设计的核心优势在于：关注点分离（每层职责单一）、控制权内聚（框架而非 LLM 掌握进度判断）以及可验证性（文件系统 artifact 作为 Agent 与框架之间的唯一通信通道）。后续各章将对状态机编排（第四章）、分层验证体系（第五章）和 LLM 约束引擎（第六章）三个核心创新点进行深入展开。
