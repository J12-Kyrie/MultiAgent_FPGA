# 第七章 系统测试与实验结果

本章以 AES-128 加密全系统作为验证案例，通过单模块验证、集成回归测试和全流程自动化执行三个维度，端到端地验证前述通用框架的有效性。实验数据证明框架的三个核心创新点（编排状态机、分层验证体系、Harnessing Engine）在 AES-128 实例化下均达到了设计预期。

## 7.1 实验环境

实验在 Apple Silicon M 系列 macOS 平台（16 GB 内存）上进行，软件环境包括 Python 3.12、Poetry >= 1.8、Verilator（Homebrew 安装）、Node.js >= 22.x 及 verilator-mcp MCP 服务，LLM 后端采用 DeepSeek Chat（deepseek-chat，API 端点 https://api.deepseek.com），其中编排器使用 thinking profile（reasoning_effort='medium'），模块工作器使用 fast profile（reasoning_effort='none'）。核心实验以 Verilator 仿真级验证为目标，全部 Checkpoint 协议解析、修复循环触发以及集成回归测试均在上述环境下完成。此外，本文编写了 Vivado 自动化脚本，将系统输出的 RTL/TB 代码自动调用 Xilinx Vivado 进行仿真生成波形图、综合、布局布线并编译出比特流（bitstream），作为生成代码在真实 FPGA 工具链上的端到端可实现性验证手段（详见 §7.6）。

---

## 7.2 单模块验证结果

本节汇报 AES-128 设计中 4 个模块的验证结果。每个模块依次经历领域设计知识注入（从技能文件提取领域设计知识写入工作区）、L0 编译门控（Verilator 编译检查）和 L1 仿真验证（Checkpoint 协议解析），未通过则触发修复循环。

**表 7-2: 单模块验证结果汇总**

| 模块 | L0 编译结果 | L1 仿真结果 | Checkpoint 通过数 / 总数 | Checkpoint 通过率 |
|------|-----------|-----------|----------------------|-----------------|
| aes_sbox | PASS | PASS | 1 / 1 | 100% |
| aes_key_schedule_128 | PASS | PASS | 1 / 1 | 100% |
| aes_round_transform | PASS | PASS | 1 / 1 | 100% |
| aes128_encrypt_core | PASS | PASS | 6 / 6 | 100% |

---

## 7.3 集成回归测试结果

集成回归测试在所有 4 个模块均处于 PROMOTED 状态后自动触发，执行三种 Campaign 分别验证端到端加密正确性、连续多帧无数据残留（back_to_back）和加密中途复位恢复能力（mid_reset）。

**表 7-3: 集成回归测试结果**

| Campaign | 验证目标 | 关键 Checkpoint | 状态 |
|----------|---------|---------------|------|
| baseline | NIST FIPS-197 已知答案测试向量端到端加密正确性 | CHK_RESET_CLEAR、CHK_START_ACCEPTED、CHK_BUSY_ASSERTED、CHK_DONE_PULSE、CHK_CIPHERTEXT_MATCH、CHK_BUSY_DEASSERTED（6/6 PASS） | PASS（仿真耗时 811ms） |
| back_to_back | 连续多帧加密无空闲间隔，验证 FSM 状态清理、无数据残留 | CHK_RESET_CLEAR、CHK_START_ACCEPTED、CHK_BUSY_ASSERTED、CHK_DONE_PULSE、CHK_CIPHERTEXT_MATCH、CHK_BUSY_DEASSERTED（6/6 PASS） | PASS（仿真耗时 3ms） |
| mid_reset | 加密过程中途断言 reset 信号，验证 FSM 恢复后可正常完成下一次加密 | CHK_RESET_CLEAR、CHK_START_ACCEPTED、CHK_BUSY_ASSERTED、CHK_DONE_PULSE、CHK_CIPHERTEXT_MATCH、CHK_BUSY_DEASSERTED（6/6 PASS） | PASS（仿真耗时 3ms） |

---

## 7.4 全流程自动化执行分析

本节分析从启动执行命令到状态机到达 DONE 状态的完整过程。全流程遵循 10 状态编排路径（SPEC_INTAKE → ARCHITECTING → PLANNING → MODULE_DESIGN → MODULE_L0 → MODULE_L1 → MODULE_L2_OPTIONAL → INTEGRATION_READY → INTEGRATION_REGRESSION → DONE）。

![图7-1: 工作区状态机](../fpga_flow/diagrams/04_workspace_state_machine.png)

**关键发现一：零 LLM 调用的框架控制阶段。** SPEC_INTAKE、ARCHITECTING 和 PLANNING 三个状态完全由框架 Synthesis 层代码执行，零 LLM 调用，耗时极短（< 1 秒），体现了框架控制架构的核心优势——规格综合、计划综合和集成清单综合均为确定性函数调用。

**关键发现二：领域设计知识注入的极高有效性。** 全部 16 个批次中，5 个实际执行（generate_validate 阶段），11 个修复相关批次（repair_edit 和 revalidate）均因首次验证已通过而被跳过。模块级执行阶段使用 fast profile，集成回归阶段使用 thinking profile 监督。

**关键发现三：零修复轮次。** 全部 4 个模块均在首次生成后直接通过 L0 编译和 L1 Checkpoint 验证，修复循环预算完全未被消耗。这是领域设计知识注入机制的最强实验证据——当领域设计知识质量足够高时，框架的修复循环机制成为冗余保障而非必需路径。

---

上述 AES-128 全流程实验从单模块验证、集成回归到端到端自动化执行，完整验证了框架在密码学设计场景下的有效性。为进一步验证框架对非密码学设计的端到端适用性，下一节以 LED Chaser 作为第二个验证案例。

## 7.5 LED Chaser 跨设计通用性验证

为验证框架对非密码学设计的端到端适用性，本节以 LED Chaser（4 位 LED 流水灯，带方向控制）作为第二个验证案例，通过 YAML 蓝图驱动机制在不修改任何框架代码的前提下完成全流程自动化执行。

### 7.5.1 验证目标与蓝图驱动执行

LED Chaser 案例的验证目标是：证明框架的编排状态机、Checkpoint 协议和分层验证体系能够直接复用于非 AES 设计，且仅需提供声明式蓝图文件即可完成适配。LED Chaser 设计通过 blueprint.yaml 蓝图文件定义，为单模块设计（4-bit LED 流水灯，带方向控制），配置 memory_required: false 以验证从零生成能力。与 AES-128 使用硬编码执行命令不同，LED Chaser 使用通用的蓝图驱动执行命令，由蓝图加载器从 YAML 文件自动生成规格中间表示、执行计划和集成回归清单。

### 7.5.2 状态机执行路径

LED Chaser 的状态机执行路径与 AES-128 案例完全一致，复用了相同的 10 状态架构。

### 7.5.3 验证结果

**表 7-6: LED Chaser 模块验证结果**

| 模块 | L0 编译结果 | L1 仿真结果 | Checkpoint 通过数 / 总数 | Checkpoint 通过率 |
|------|-----------|-----------|----------------------|-----------------|
| led_chaser | PASS | PASS | 4 / 4 | 100% |

**表 7-7: LED Chaser Checkpoint 详情**

| Checkpoint | 验证目标 | 结果 | 详情 |
|-----------|---------|------|------|
| CHK_RESET_CLEAR | 复位初始化 leds=0001 | PASS | Reset sets leds=0001 |
| CHK_SHIFT_LEFT | 左移三次得到 1000 | PASS | Shift left 3 times gives 1000 |
| CHK_SHIFT_RIGHT | 右移两次得到 0010 | PASS | Shift right 2 times gives 0010 |
| CHK_WRAP_AROUND | 环绕从最左回到 0001 | PASS | Wrap-around from leftmost gives 0001 |

LED Chaser 的 4 个 Checkpoint 完全由蓝图文件声明，框架通过 `CHECKPOINT|<name>|PASS|<detail>` 协议自动解析，无需修改检查点解析器或任何验证层代码。这证明了 Checkpoint 协议的设计无关性——任何硬件设计均可通过声明自定义 Checkpoint 列表接入框架的分层验证体系。

### 7.5.4 集成回归结果

**表 7-8: LED Chaser 集成回归测试结果**

| Campaign | 验证目标 | Checkpoint 通过 | 状态 |
|----------|---------|----------------|------|
| baseline (KAT) | 已知向量端到端功能正确性 | 4/4 PASS | PASS |

LED Chaser 为单模块设计，集成回归测试执行单个 baseline Campaign 验证端到端功能正确性。Workflow gate 判定为 success，模块状态由 VALIDATED 成功晋升为 PROMOTED。

### 7.5.5 通用性验证意义

LED Chaser 案例从五个维度验证了框架的跨设计通用性：（1）同一 10 状态编排状态机完整复用，无需修改；（2）4 个自定义 Checkpoint 由蓝图声明、Testbench 发射、框架自动解析，协议具有设计无关性；（3）YAML 蓝图驱动实现声明式零代码适配；（4）以 memory_required: false 配置运行，Agent 从零生成 RTL 和 Testbench 并通过验证；（5）全流程零修复通过。

LED Chaser 与 AES-128 形成互补：前者以单模块设计验证了声明式跨设计适配和无 Memory 场景下的从零生成能力，后者以 4 模块 DAG 验证了多模块协同、DAG 批调度和深度验证能力。两个案例共同构成了框架通用性的实证基础。

---

## 7.6 Vivado 自动化脚本与 FPGA 工具链验证

前述各节的实验验证均在 Verilator 仿真层面完成，验证了生成代码的功能正确性。然而，Verilator 属于行为级仿真器，其通过并不能保证 RTL 在真实 FPGA 器件上的可综合性与时序收敛性。为弥补这一验证缺口，本文编写了自动化脚本，将多智能体系统输出的 RTL 和 Testbench 代码自动调用 Xilinx Vivado Design Suite 进行完整的 FPGA 工具链验证，覆盖仿真波形生成、逻辑综合（Synthesis）、布局布线（Implementation）和比特流（Bitstream）编译四个阶段。

### 7.6.1 自动化脚本设计

自动化脚本的设计目标是：接收多智能体框架 promoted/ 目录下验证通过的 RTL 源文件，自动驱动 Vivado 完成从仿真到比特流的全流程，无需人工干预。脚本采用 TCL（Tool Command Language）脚本与 Shell 脚本组合的方式实现，核心流程如下：

1. **项目创建与源文件导入**：脚本自动创建 Vivado 工程，导入 promoted/ 目录下的 RTL 源文件（`.v`）和约束文件（`.xdc`），设置目标 FPGA 器件型号（如 Xilinx Artix-7 系列的 xc7a35tcpg236-1）；
2. **行为级仿真（Behavioral Simulation）**：调用 Vivado 内置的 xsim 仿真器执行行为级仿真，生成 VCD 波形文件并导出截图，用于与 Verilator 仿真结果进行交叉验证；
3. **逻辑综合（Synthesis）**：运行 Vivado 综合引擎（Vivado Synthesis），将 RTL 描述转换为门级网表，生成综合报告（资源利用率、时序摘要）；
4. **布局布线（Implementation）**：执行 Place & Route 流程，完成逻辑单元的物理布局和互连布线，生成时序报告（建立时间/保持时间违例检查）；
5. **比特流生成（Bitstream Generation）**：编译生成 .bit 比特流文件，可用于直接下载到目标 FPGA 开发板进行硬件验证。

### 7.6.2 AES-128 设计的 Vivado 验证结果

以 AES-128 加密核心为例，自动化脚本将 promoted/aes128_encrypt_core/ 目录下的全部 RTL 源文件（aes_sbox.v、aes_key_schedule_128.v、aes_round_transform.v、aes128_encrypt_core.v）导入 Vivado 工程，完成全流程验证。

**仿真波形验证**：Vivado xsim 仿真器生成的波形图如图 7-2 所示。波形清晰展示了 AES-128 加密核心的完整握手时序：`start` 信号触发后 `busy` 立即拉高，经过 11 个时钟周期的迭代运算后 `done` 产生单周期脉冲，`ciphertext` 输出密文 `69c4e0d86a7b0430d8cdb78070b4c55a`，与 NIST FIPS-197 标准测试向量完全一致。该波形与 Verilator 仿真结果交叉验证，确认了生成代码在两种仿真器下行为一致。

![图7-2: AES-128 加密核心 Vivado 仿真波形](../AES128.png)

**综合与实现报告**：逻辑综合阶段成功将 RTL 转换为门级网表，未报告任何综合错误或警告。布局布线阶段完成物理实现后，时序报告显示建立时间违例数为零（WNS ≥ 0），表明设计在目标器件上满足时序约束。比特流文件（.bit）成功生成，文件大小符合预期，可直接下载至 FPGA 开发板。

### 7.6.3 LED Chaser 设计的 Vivado 验证结果

LED Chaser 设计同样通过自动化脚本完成 Vivado 全流程验证。Vivado xsim 仿真波形如图 7-3 所示，波形展示了 4 位 LED 流水灯的循环移位行为：`led[3:0]` 按照 `0001 → 0010 → 0100 → 1000 → 0001` 的序列循环移位，`dir` 信号控制移位方向，复位后 `led` 初始化为 `0001`。移位严格对齐时钟上升沿，每位 LED 的持续时间一致，验证了分频器和状态机的稳定性。

![图7-3: LED Chaser Vivado 仿真波形](../LED.png)

综合与实现阶段同样无错误报告，比特流文件成功生成。

### 7.6.4 工具链验证的意义

Vivado 自动化脚本的引入为框架提供了以下验证价值：

1. **可综合性确认**：Verilator 仿真通过仅验证行为级正确性，Vivado 综合通过确认生成的 RTL 代码可被综合为目标 FPGA 器件的门级网表，排除了不可综合的 Verilog 结构（如 `initial` 块中的非综合操作）；
2. **时序收敛验证**：布局布线后的时序报告验证设计在目标时钟频率下无建立/保持时间违例，这是 Verilator 无法提供的物理层验证；
3. **端到端可实现性**：比特流文件的生成证明从多智能体系统输出的 RTL 代码到可下载至 FPGA 的最终产物之间不存在断链，实现了从"AI 生成代码"到"硬件可运行"的完整闭环；
4. **双仿真器交叉验证**：Vivado xsim 与 Verilator 两种仿真器的波形一致性验证，增强了对生成代码正确性的置信度——两种独立实现的仿真器均确认功能正确，排除了单一仿真器特有的假阳性风险。

需要说明的是，当前 Vivado 自动化脚本作为离线验证工具运行在多智能体框架的 DONE 状态之后，尚未集成到框架的状态机编排流程中。将 Vivado 工具链深度集成到框架的分层验证体系中（作为 L3 层），使其具备自动解读综合报告和时序违例并指导 RTL 修改的能力，是本文 §8.3.2 中规划的未来研究方向。
