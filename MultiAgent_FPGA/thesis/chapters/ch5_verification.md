# 第五章 四层验证体系与Checkpoint协议

## 5.1 分层验证架构

### 5.1.1 设计动机

在任何多智能体 FPGA 设计自动化框架中，验证是保证生成代码正确性的核心环节。本框架提出的四层分级验证体系是一种通用的硬件验证方法论，适用于任何具备 Verilator 可编译 RTL 和自检 C++ Testbench 的多模块设计。

四层验证体系的核心设计理念是：**时间成本与问题发现深度呈正比递增**。L0编译门控仅需秒级时间即可捕获语法级错误；L1仿真验证需要数十秒，但可验证功能正确性；L2鲁棒性测试需要分钟级时间，但能发现边界条件下的脆弱性；集成回归测试最为耗时，但能捕获模块间接口和时序问题。遵循"快速失败（fail fast）"原则，系统在不同阶段以匹配的代价发现相应类型的问题，并将验证结果与框架控制流深度集成。

### 5.1.2 四层架构总览

四层验证架构的设计不依赖于特定的硬件设计——L0 编译门控对任何 Verilog RTL 有效，L1 Checkpoint 验证对任何实现了 Checkpoint 协议的 Testbench 有效，L2 鲁棒性测试对任何可参数化的 Testbench 有效，集成回归对任何 DAG 结构的多模块设计有效。以下以 AES-128 验证案例说明各层的具体运作。各层的职责与判定标准如表5-1所示，具体实现细节在5.2--5.4节中展开。

| 层级 | 验证目标 | 判定标准 | 典型时间开销 |
|------|---------|---------|-------------|
| L0 编译门控 | 语法与结构正确性 | Verilator编译返回码为零 | 秒级 |
| L1 仿真验证 | 功能正确性 | 所有必需Checkpoint出现且为PASS | 数十秒 |
| L2 鲁棒性测试 | 边界条件行为一致性 | Checkpoint通过率 + counterexample记录 | 分钟级 |
| 集成回归测试 | 系统级接口与时序正确性 | 三种Campaign全部Checkpoint通过 | 数分钟 |

### 5.1.3 分层验证与框架控制流的集成

四层验证与编排状态机的深度集成详见第四章：编排状态MODULE\_L0、MODULE\_L1、MODULE\_L2\_OPTIONAL、INTEGRATION\_REGRESSION分别对应四层验证执行，每层验证的判定结果直接驱动工作区状态机的转移。

---

## 5.2 Checkpoint协议设计

### 5.2.1 协议格式规范

Checkpoint 协议的格式设计是完全通用的——任何硬件设计的 Testbench 均可通过调用检查点发射函数发射自定义的 Checkpoint 标记，框架的 检查点解析器 无需修改即可解析。协议的通用性使得框架支持新设计时无需更改验证基础设施，只需定义新的 Checkpoint 名称集合。

Checkpoint协议是本框架验证体系的核心通信机制，定义了Testbench与框架之间的结构化结果汇报接口。每条协议行由四个以竖线分隔的字段组成：固定前缀"CHECKPOINT"作为日志行过滤的识别标记；Checkpoint名称与蓝图中定义的必需检查点集合精确对应；状态字段当前唯一合法值为"PASS"，表示该检查点已验证通过；末尾字段为人类可读的补充说明，不参与机器判定逻辑。在C++ Testbench端，该协议通过共享头文件中的一行辅助函数调用实现——Testbench开发者只需在正确性验证通过后调用该函数，将协议行发射至标准输出，无需了解协议解析细节。框架端通过逐行前缀匹配解析协议行，再以竖线为分隔符进行切分，构建从Checkpoint名称到状态字符串的映射字典。

### 5.2.2 设计决策分析

选择简单文本协议而非结构化输出（如JSON）的决策基于以下考量：

**对日志噪声的鲁棒性**：Verilator仿真过程中会产生大量警告、调试输出和波形信息。文本协议通过逐行扫描和前缀匹配实现解析，不受日志噪声干扰；而JSON格式需要完整解析仿真输出流，对格式错误极为敏感。

**Testbench端实现简单**：检查点发射函数是单行调用，Testbench开发者和LLM Agent均能可靠地生成该调用，不会因JSON转义、嵌套结构等问题引入格式错误。

**框架端解析简单**：检查点解析器的实现仅需30行代码，通过CHECKPOINT_PREFIX前缀过滤和split('|', 3)分割即可完成解析，维护成本极低。

与AutoGen等技术路线方案的对比：该方案使用Vivado xsim仿真，验证结果依赖波形图（.vcd）的人工判读，无法实现机器自动判定。本文的Checkpoint协议使验证结果完全机器可判定，且与文件系统通信机制（Batch Gate回调）无缝集成。

### 5.2.3 Checkpoint汇总与判定

检查点汇总函数接收解析后的Checkpoint字典和required_checkpoints元组，输出三类分类结果：

- **missing**：未在仿真日志中出现的必需Checkpoint（Testbench未执行到该路径）
- **failed**：出现但状态字段不为`PASS`的Checkpoint
- **passed**：出现且状态为`PASS`的Checkpoint

只有当missing和failed均为空时，验证才判定为通过。这一逻辑同时捕获了"Testbench未运行到验证点"和"Testbench运行到验证点但判定失败"两种失败模式。

### 5.2.4 各模块Checkpoint一览

以下 AES-128 验证案例的 9 个 Checkpoint 展示了 Checkpoint 协议在具体设计中的实例化方式。对于其他硬件设计（如 SHA-256 哈希模块或 FIFO 控制器），可按照相同的协议定义不同的 Checkpoint 集合。

在AES-128验证案例中，协议共定义了9个检查点。aes_sbox模块的CHK_SBOX_MATCH验证查找表输出与已知向量的匹配；aes_key_schedule_128模块的CHK_ROUNDKEY_MATCH验证11轮密钥扩展输出与标准参考值的一致性；aes_round_transform模块的CHK_ROUND_STATE_MATCH验证单轮状态变换的正确性。aes128_encrypt_core作为顶层模块，包含6个检查点：CHK_RESET_CLEAR验证复位后状态寄存器清零；CHK_START_ACCEPTED验证握手采样；CHK_BUSY_ASSERTED验证加密启动后的忙信号置位；CHK_DONE_PULSE验证完成脉冲的单周期特性；CHK_CIPHERTEXT_MATCH验证11周期延迟后的密文正确性；CHK_BUSY_DEASSERTED验证完成后的忙信号去断言。这6个检查点覆盖了完整的有限状态机行为路径，构成了对11周期迭代微架构的全面行为规约。

---

## 5.3 L2鲁棒性测试

### 5.3.1 设计动机

L1验证使用已知向量（KAT），这些向量来自NIST FIPS-197标准，数量有限且确定性强。KAT通过并不能证明模块在随机输入、边界输入、重复模式输入等条件下行为正确。L2鲁棒性测试的目标是在L1的功能正确性验证之上，进一步探测模块的边界脆弱性。

### 5.3.2 L2 Profile体系

L2测试通过Profile机制对测试强度进行分级控制：

- **rand_small**（种子1001）：少量随机向量（默认8个case），快速探测随机条件下的基本正确性
- **rand_medium**（种子2001）：中等数量随机向量，深度随机测试
- **back_to_back**（种子3001）：连续加密场景，无空闲间隔，验证FSM状态清理正确性（仅顶层模块适用）
- **mid_reset**（种子4001）：加密过程中断言reset，验证复位恢复行为（仅顶层模块适用）

Profile的种子固定（_CAMPAIGN_PROFILE_SEEDS字典），保证测试结果的完全可复现性。

### 5.3.3 随机数生成与可复现性

随机块生成使用确定性RNG算法，C++端和Python端保持严格一致的实现，使Python生成的oracle密文与C++ Testbench生成的随机向量完全对应。**固定种子 + 确定性RNG = 完全可复现**：任意时刻以相同种子执行相同Profile，必然得到相同的测试向量序列。

### 5.3.4 顶层模块的Oracle生成机制

框架使用标准密码学工具链为每个随机测试向量生成参考密文，实现以独立参考实现为基准的端到端验证，避免了"用自身验证自身"的循环逻辑。

### 5.3.5 L2AdaptivePlanner自适应策略

L2AdaptivePlanner根据历史脆弱性记录自适应选择L2 Profile：

- 若模块无历史记录，选择第一个Profile（rand_small）
- 若上一次Profile测试失败，选择列表中的下一个Profile（更严格的测试）
- 若上一次Profile测试通过，保持当前Profile

这一机制实现了测试强度与历史脆弱性的自适应匹配，避免了对所有模块施加同等力度的测试造成的资源浪费。

![图5-3: 错误恢复流程](../fpga_flow/diagrams/13_error_recovery.png)

### 5.3.6 L2测试输出物

L2执行完成后输出两个关键文件：

**counterexample.json**：记录失败向量详情，供框架和Agent分析失败原因。

**fragility_summary.json**：记录脆弱性统计指标，供L2AdaptivePlanner用于下一轮Profile决策。

---

## 5.4 集成回归测试

集成回归测试的三种 Campaign 模式（baseline、back_to_back、mid_reset）是面向时序状态机硬件设计的通用测试策略，适用于任何包含 FSM 的多模块设计。

### 5.4.1 触发条件与规格定义

集成回归测试的触发条件是：AES-128全系统的所有4个模块（aes_sbox、aes_key_schedule_128、aes_round_transform、aes128_encrypt_core）全部达到PROMOTED状态，且IntegrationReadinessResolver确认所有依赖已满足。

集成测试规格通过IntegrationRegressionManifest定义，采用Pydantic模型并强制extra='forbid'，关键字段包括：

- top\_module：集成测试的顶层模块（aes128\_encrypt\_core）
- rtl\_files：全部4个模块的RTL文件列表（含依赖关系顺序）
- regression\_checkpoints：需要在所有Campaign中通过的Checkpoint集合
- latency\_target\_cycles：11周期延迟目标

synthesize_integration_manifest()函数在框架初始化阶段从SpecIR和PlanDAG自动生成IntegrationRegressionManifest，无需人工配置。

### 5.4.2 三种Campaign规格

**baseline Campaign**：使用NIST FIPS-197标准向量执行端到端加密正确性验证。验证目标是确认顶层模块在标准测试条件下的功能完全正确。包含全部6个aes128_encrypt_core Checkpoint：CHK_RESET_CLEAR、CHK_START_ACCEPTED、CHK_BUSY_ASSERTED、CHK_DONE_PULSE、CHK_CIPHERTEXT_MATCH、CHK_BUSY_DEASSERTED。

**back_to_back Campaign**：连续发起多次加密请求，两次加密之间无空闲间隔（前一次done脉冲后立即送入新的start信号）。验证目标是FSM在连续工作模式下不存在状态残留：BUSY信号在done后正确去断言，IDLE状态正确恢复，下次start能被正常采样。通过`plusargs: {profile: 'back_to_back'}`传递给Testbench。

**mid_reset Campaign**：在加密进行到第5轮（约中间位置）时断言reset信号，验证FSM能够从任意中间状态正确复位，之后能够接受新的加密请求并产生正确密文。通过`plusargs: {profile: 'mid_reset'}`传递给Testbench。

集成测试捕获的典型缺陷类型包括：子模块接口时序错位（如busy信号延迟一个周期）、FSM状态寄存器复位不完全（如round计数器在reset后未清零）、back_to_back场景下的状态污染（如前次加密的key未清除影响后次加密）。这些缺陷在子模块独立L1验证中无法被发现，只有在系统级集成测试中才会暴露。

### 5.4.3 集成测试执行机制

集成回归执行器按以下流程执行集成回归：

1. **编译**：将全部4个模块的RTL和顶层TB一同编译为可执行模型
2. **执行三种Campaign**：依次执行baseline、back\_to\_back、mid\_reset，每种Campaign独立调用simulate()并解析独立的仿真日志
3. **汇总判定**：对每种Campaign的Checkpoint进行汇总，当aggregate\_missing和aggregate\_failed均为空时判定集成回归通过
