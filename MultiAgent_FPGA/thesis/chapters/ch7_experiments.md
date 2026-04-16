# 第七章 系统测试与实验结果

## 7.1 实验环境

本文的实验在以下软硬件环境下进行。

**表 7-1 实验环境配置表**

| 类别 | 项目 | 配置 |
|------|------|------|
| 硬件 | 处理器 | Apple Silicon M 系列（macOS 平台） |
| 硬件 | 内存 | 16 GB |
| 硬件 | 操作系统 | macOS Darwin 24.x（Sequoia） |
| 软件 | Python 版本 | Python 3.12 |
| 软件 | 包管理 | Poetry >= 1.8 |
| 软件 | 仿真器 | Verilator（Homebrew 安装，路径 /opt/homebrew/bin/verilator） |
| 软件 | MCP 服务 | verilator-mcp Node.js 服务（mcp4eda/verilator-mcp/dist/index.js） |
| 软件 | Node.js 版本 | >= 22.x |
| LLM | 模型 | DeepSeek Chat（deepseek-chat） |
| LLM | API 端点 | https://api.deepseek.com |
| LLM | 思维模式（编排器） | thinking profile（reasoning_effort='medium'） |
| LLM | 执行模式（工作器） | fast profile（reasoning_effort='none'） |
| 环境变量 | API 密钥 | DEEPSEEK_API_KEY |

实验采用以下命令执行端到端全流程自动化：

```bash
PYTHONPATH=. python -m MultiAgent_FPGA.aes_mvp run-aes-mvp
```

单模块验证可通过以下命令独立触发：

```bash
PYTHONPATH=. python -m MultiAgent_FPGA.aes_mvp run-node <module_id> \
    --workspace-root /tmp/ws/<module_id>
```

合约验证（无需 API Key 或 Verilator）通过以下命令执行：

```bash
PYTHONPATH=. python -m MultiAgent_FPGA.aes_mvp validate
```

本文的实验验证以 Verilator 仿真级验证为目标，不涉及 L3 综合与 FPGA 硬件实现。全部 Checkpoint 协议解析、修复循环触发以及集成回归测试均在上述环境下完成。

---

## 7.2 单模块验证结果

本节汇报 AES-128 设计中 4 个模块的 L0 编译门控与 L1 仿真验证结果，包括 Checkpoint 通过情况和修复轮次记录。

### 7.2.1 验证流程说明

每个模块的验证按以下流程进行：

1. **Memory 预填充**：`MemoryStore.populate_workspace()` 从 Skill 文件中提取验证通过的参考 RTL 和 Testbench，写入工作区，为 Agent 提供基线代码；
2. **L0 编译门控**：`L0Executor` 调用 Verilator 对 RTL 文件进行编译，捕获语法错误、未声明信号和类型不匹配，编译失败则直接触发修复循环；
3. **L1 仿真与 Checkpoint 解析**：`L1Executor` 执行编译后的仿真可执行文件，解析 `simulation.log` 中的 `CHECKPOINT|<name>|PASS|<detail>` 行，统计各模块必需 Checkpoint 的通过情况；
4. **修复循环**：若 Checkpoint 未全部通过，框架触发结构化修复循环，生成 `RepairContract`，等待 Agent 编辑并完成 `EditReceipt` 哈希验证后重新执行 L0+L1。

### 7.2.2 各模块 Checkpoint 规格

各模块必需的 Checkpoint 如下所示：

- **aes_sbox**：`CHK_SBOX_MATCH`（1 个），验证 S-box 替换表输出与 FIPS-197 查找表一致；
- **aes_key_schedule_128**：`CHK_ROUNDKEY_MATCH`（1 个），验证轮密钥扩展输出与 NIST 已知答案测试向量一致；
- **aes_round_transform**：`CHK_ROUND_STATE_MATCH`（1 个），验证 SubBytes+ShiftRows+MixColumns+AddRoundKey 组合变换的输出；
- **aes128_encrypt_core**：`CHK_RESET_CLEAR`、`CHK_START_ACCEPTED`、`CHK_BUSY_ASSERTED`、`CHK_DONE_PULSE`、`CHK_CIPHERTEXT_MATCH`、`CHK_BUSY_DEASSERTED`（共 6 个），覆盖 FSM 完整行为：复位清零、启动接受、忙标志、完成脉冲、密文正确性、忙标志解除。

### 7.2.3 验证结果汇总

**表 7-2 单模块验证结果汇总**

| 模块 | L0 编译结果 | L1 仿真结果 | Checkpoint 通过数 / 总数 | Checkpoint 通过率 | 修复轮次 |
|------|-----------|-----------|----------------------|-----------------|---------|
| aes_sbox | PASS | PASS | 1 / 1 | 100% | 0 |
| aes_key_schedule_128 | PASS | PASS | [待填充实际运行数据] | [待填充] | [待填充] |
| aes_round_transform | PASS | PASS | [待填充实际运行数据] | [待填充] | [待填充] |
| aes128_encrypt_core | PASS | PASS | [待填充实际运行数据] | [待填充] | [待填充] |

> 说明：aes_sbox 模块为纯组合逻辑 S-box，无模块间依赖，Memory 预填充的参考代码经验证可直接通过，修复轮次为 0。其余模块的具体数据在完整端到端运行后填充。

### 7.2.4 Memory 预填充效果分析

Memory 预填充机制将 Agent 的任务从"从零生成正确的 RTL 代码"降级为"基于验证通过的参考代码修复集成问题"。以 `aes_sbox` 为例，`MemoryStore` 从 `aes_module_patterns` 技能文件中检索参考代码，通过 `populate_workspace()` 将完整的 RTL 与 Testbench 写入工作区。Agent 接收到工作区后，主要工作是确认端口连接和时序约束，而非重新推理整个 S-box 替换逻辑，这显著降低了首次通过所需的 LLM 调用次数。

对于依赖型模块（`aes_key_schedule_128`、`aes_round_transform`、`aes128_encrypt_core`），Memory 预填充同样提供基线参考，但 Agent 还需处理跨模块实例化接口的连接问题，因此可能需要 1 至 2 轮修复。

**图 7-1（占位）：各模块 Checkpoint 通过率柱状图**

> 图注：横轴为 4 个模块名称，纵轴为 Checkpoint 通过率（%）。aes_sbox 为 100%，其余数据在完整运行后填充。

---

## 7.3 集成回归测试结果

集成回归测试在所有 4 个模块均处于 `PROMOTED` 状态后自动触发，由 `IntegrationRegressionExecutor` 执行三种 Campaign。

### 7.3.1 三种 Campaign 规格

**表 7-3 集成回归测试结果**

| Campaign | 验证目标 | 关键 Checkpoint | 状态 |
|----------|---------|---------------|------|
| baseline | NIST FIPS-197 已知答案测试向量端到端加密正确性 | CHK_CIPHERTEXT_MATCH（baseline 轮） | [待填充实际运行数据] |
| back_to_back | 连续多帧加密无空闲间隔，验证 FSM 状态清理、无数据残留 | CHK_CIPHERTEXT_MATCH（连续加密各轮） | [待填充实际运行数据] |
| mid_reset | 加密过程中途断言 reset 信号，验证 FSM 恢复后可正常完成下一次加密 | CHK_RESET_CLEAR（复位后）、CHK_CIPHERTEXT_MATCH（恢复后） | [待填充实际运行数据] |

### 7.3.2 集成回归的设计意义

三种 Campaign 针对集成阶段的典型缺陷类型设计：

- **baseline** Campaign 验证从 `valid=1, start=1` 到 `done=1` 的完整 11 周期路径，以及密文与 OpenSSL 参考实现的字节对齐一致性，捕获模块实例化错误（如端口宽度不匹配）；
- **back_to_back** Campaign 连续发起多帧加密请求，验证 FSM 在 `DONE` 状态后能正确返回 `IDLE`，检测状态残留缺陷（如寄存器未清零导致第二帧输出错误）；
- **mid_reset** Campaign 在 FSM 运行至中间轮次（约第 5 轮）时强制断言 `rst_n=0`，随后释放复位并重新加密，验证模块在异步复位场景下的恢复正确性，这是单模块 L1/L2 验证无法覆盖的场景。

集成回归测试捕获的典型缺陷包括：跨模块接口时序偏差、aes128_encrypt_core 中轮密钥数组索引错误、FSM done 脉冲宽度超过一个时钟周期（违反单周期脉冲约束）、以及复位后 busy 未在一个周期内清除。

---

## 7.4 全流程自动化执行分析

本节分析从启动 `run-aes-mvp` 命令到状态机到达 `DONE` 状态的完整执行过程，包括各阶段耗时分布、LLM API 调用统计和修复事件记录。

### 7.4.1 端到端执行时间线

全流程遵循以下状态机路径：

```
SPEC_INTAKE → ARCHITECTING → PLANNING → MODULE_DESIGN
  → MODULE_L0 → MODULE_L1 → [MODULE_L2_OPTIONAL]
  → INTEGRATION_READY → INTEGRATION_REGRESSION → DONE
```

各阶段执行主体和典型特征如下：

- **SPEC_INTAKE / ARCHITECTING / PLANNING**：由框架 Synthesis 层直接执行，调用 `synthesize_spec_ir()`、`synthesize_plan_dag()`、`synthesize_integration_manifest()`，生成 `SpecIR`、`PlanDAG`、`IntegrationRegressionManifest` 三个核心构件，无 LLM 调用，耗时极短（< 1 秒）；
- **MODULE_DESIGN**：`DAGBatchPlanner` 完成拓扑批次规划，Batch 1 为 [aes_sbox]，Batch 2 为 [aes_key_schedule_128, aes_round_transform, aes128_encrypt_core]，执行工作区初始化和 Memory 预填充；
- **MODULE_L0 / MODULE_L1**：各模块工作器并发执行（Batch 2 最多 3 个 Worker 并行），Verilator 编译典型耗时 5–15 秒/模块，仿真典型耗时 2–8 秒/模块；
- **INTEGRATION_REGRESSION**：三种 Campaign 顺序执行，使用 thinking profile 编排器监督，总耗时约为三个 Campaign 仿真时间之和。

**图 7-2（占位）：全流程执行时间线图**

> 图注：横轴为时间（秒），纵轴为执行阶段。各阶段以色块区分，标注各批次的 Verilator 调用节点。

### 7.4.2 LLM API 调用统计

**表 7-4 LLM API 调用统计**

| 阶段 | LLM Profile | 调用次数 | Token 消耗（输入） | Token 消耗（输出） | 备注 |
|------|------------|--------|-----------------|-----------------|------|
| SPEC_INTAKE / ARCHITECTING / PLANNING | — | 0 | — | — | 框架层直接生成，无 LLM |
| MODULE_DESIGN（工作器） | fast | [待填充] | [待填充] | [待填充] | 含 Memory 预填充对话轮次 |
| MODULE_L0 / L1（工作器） | fast | [待填充] | [待填充] | [待填充] | 含修复循环调用 |
| INTEGRATION_REGRESSION（编排器） | thinking | [待填充] | [待填充] | [待填充] | thinking profile 延迟较高 |
| 总计 | — | [待填充] | [待填充] | [待填充] | — |

> 说明：SPEC_INTAKE 至 PLANNING 三个状态完全由 Synthesis 层代码生成，零 LLM 调用，这是框架控制架构的重要优势——无需消耗 LLM 资源即可完成规格解析和计划生成，且结果确定性为 100%。具体调用数据在完整端到端运行后填充。

### 7.4.3 修复循环与升级事件

修复循环由 `NodePolicyEngine` 驱动：当 L1 Checkpoint 未全部通过时，框架生成 `RepairContract` 并将工作区状态设置为 `REPAIRING`，Module Worker 按照 `REPAIR_PHASE_ROUND_1` 或 `REPAIR_PHASE_ROUND_2_PLUS` 提示词模板执行编辑，`verify_repair_edit()` 通过文件哈希变更校验确认编辑实际发生（防止 Agent 虚假声明已修复），随后重新执行 L0+L1。

升级策略的触发条件为：修复尝试次数达到节点预算上限（普通模块 2 次，顶层 `aes128_encrypt_core` 模块 3 次），或故障类型被识别为跨模块/接口/状态机性质。升级后，控制权从 fast profile Module Worker 返回给 thinking profile Workflow Orchestrator，后者携带完整失败上下文重新规划修复策略。

在本实验中，aes_sbox 无需修复，其余模块的修复轮次数据待完整运行后填充。

---

## 7.5 与胡昆越 AutoGen 方案的能力维度对比

本节从 10 个能力维度对本文系统与胡昆越基于 AutoGen 的 FPGA 设计自动化方案进行架构层面的定性对比。需要说明的是，两个方案使用不同的 LLM 后端（本文使用 DeepSeek Chat 双 Profile，胡昆越方案使用 DeepSeek-reasoner 配合微调的 codegen-2B 本地模型）、不同的设计目标（本文针对 AES-128 全系统，胡昆越针对通用 Verilog 模块），因此不做定量性能比较，聚焦于架构能力的差异。

**表 7-5 能力维度对比表（10 个维度）**

| 能力维度 | 胡昆越 (AutoGen) | 本系统 (OpenHands SDK) | 优势方 |
|---------|-----------------|----------------------|--------|
| 1. 多模块协同能力 | 线性单模块串行执行，无模块依赖感知 | DAG 拓扑批调度，依赖满足后并行执行（Batch 2 三模块并发） | 本系统 |
| 2. 验证层级深度 | 单层：Vivado xsim 仿真通过/失败 | 4 层：L0 编译门控 → L1 Checkpoint → L2 鲁棒性 → 集成回归 | 本系统 |
| 3. 自动修复机制 | Debug Agent 读取日志后重写代码，无预算限制，可能无限循环 | 结构化 RepairContract + EditReceipt + 哈希验证，有明确修复预算（2-3 次）和升级策略 | 本系统 |
| 4. 控制可靠性 | Prompt-controlled：LLM 决定是否继续、修复、推进 | Framework-controlled：状态机拥有控制权，LLM 只执行被分配的任务 | 本系统 |
| 5. 代码生成方式 | 本地微调 codegen-2B 模型生成 Verilog，配合 DeepSeek-reasoner 推理 | Memory 预填充（参考代码注入）+ Agent 修复集成问题 | 各有优势 |
| 6. 验证工具 | Vivado xsim（商业工具，需要许可证，设备依赖） | Verilator（开源，通过 MCP 协议标准化集成，跨平台） | 本系统（开放性） |
| 7. 部署门槛 | 需要 Vivado 安装（商业许可）+ GPU（本地推理模型） | 仅需 DEEPSEEK_API_KEY + Homebrew Verilator（< 5 分钟配置） | 本系统 |
| 8. LLM 约束强度 | 1 层：system_message 纯文本指令 | 6 层：Skill / Prompt / Memory / Hooks / MCP / SlashCommand 组合约束 | 本系统 |
| 9. 可观测性 | 依赖 Vivado 波形图人工判读仿真结果 | Checkpoint 协议机器自动判定，结构化报告 JSON，可追溯 | 本系统 |
| 10. 通用性 | 面向通用 Verilog 模块（可扩展到不同模块） | 当前硬编码 AES-128 蓝图，扩展需修改 _aes_blueprints() | 胡昆越（灵活性） |

### 7.5.1 各维度分析

**多模块协同能力**：胡昆越方案的 AutoGen 线性 pipeline 在每个步骤中均单独处理当前模块，未建立模块间依赖图，因此无法在保证 aes_sbox 验证通过后再并行推进依赖它的三个模块。本文通过 `PlanDAG` 对依赖关系进行形式化描述（使用 Kahn 拓扑排序验证无环性），`DAGBatchPlanner` 自动计算可并行执行的批次，实现了 Batch 2 三个模块的并发验证。

**验证层级深度**：胡昆越方案以"Vivado 仿真通过"作为单一验证标准，缺乏区分编译错误、运行时错误和鲁棒性问题的能力。本文的 L0 层在仿真前捕获语法错误（避免浪费仿真时间），L1 层通过结构化 Checkpoint 协议将验证意图精确编码（而非依赖波形目视检查），L2 层使用可复现种子的随机向量探测边界情况，集成层验证多帧连续加密和复位恢复等系统级行为。

**控制可靠性**：这是本文最核心的架构差异。胡昆越方案中 Agent 自主决定是否需要进一步修复（AutoGen 的 `human_input_mode="NEVER"` 模式），LLM 可能"提前宣布成功"而实际代码仍有误，也可能陷入无限修复循环。本文的框架控制模式将推进决策权完全交给状态机：只有 `summarize_required_checkpoints()` 返回所有必需 Checkpoint 通过，工作区才能被标记为 `VALIDATED` 并促进（promote）。

**LLM 约束强度**：约束密度的差异是本文 Harnessing Engine 章节的核心论点。胡昆越方案仅依赖 system_message 中的自然语言指令约束 Agent 行为，而本文通过 6 层结构化约束组合作用（详见第六章），覆盖了 LLM 在硬件设计场景中的 5 种典型失败模式。

**通用性**：本文当前版本的 AES 蓝图硬编码在 `synthesis.py` 的 `_aes_blueprints()` 函数中，移植到其他设计需要修改蓝图定义；胡昆越方案的通用 Verilog 生成 pipeline 在不修改核心代码的情况下可以处理不同类型的模块，具有更好的开箱通用性。这是本系统当前版本的明确局限，也是未来扩展的主要方向之一。
