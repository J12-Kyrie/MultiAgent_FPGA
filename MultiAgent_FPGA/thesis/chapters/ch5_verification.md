# 第五章 四层验证体系与Checkpoint协议

## 5.1 分层验证架构

### 5.1.1 设计动机

在多智能体FPGA设计自动化系统中，验证是保证生成代码正确性的核心环节。传统单层验证方案（仿真通过/失败）存在以下问题：其一，语法错误只有在仿真阶段才被发现，浪费了编译资源；其二，仿真通过并不能保证边界行为的正确性；其三，子模块的独立验证通过并不意味着顶层集成的正确性。

本文提出四层分级验证体系，遵循"快速失败（fail fast）"原则，通过逐步深入的验证策略将问题发现尽可能提前，并将验证结果与框架控制流深度集成。

[图5-1: 四层验证体系架构图（L0→L1→L2→Integration 金字塔）]

四层验证体系的核心设计理念是：**时间成本与问题发现深度呈正比递增**。L0编译门控仅需秒级时间即可捕获语法级错误；L1仿真验证需要数十秒，但可验证功能正确性；L2鲁棒性测试需要分钟级时间，但能发现边界条件下的脆弱性；集成回归测试最为耗时，但能捕获模块间接口和时序问题。这一设计使系统能够在不同阶段以匹配的代价发现相应类型的问题。

### 5.1.2 四层架构总览

各层验证的职责、输入输出与判定标准如下：

[表5-1: 各层级验证目标、输入、输出、判定标准、典型耗时]

**L0编译门控（L0Executor）**：接收RTL Verilog源文件和C++ Testbench，调用Verilator编译器，输出编译日志。判定标准为编译返回码为零且无错误输出。L0是最轻量的门控，能捕获未声明信号、端口宽度不匹配、语法错误、非法Verilog结构等问题。

**L1仿真验证（L1Executor）**：在L0编译成功的前提下执行仿真，通过解析`simulation.log`中的Checkpoint协议行判定功能正确性。L1采用已知向量（KAT，Known-Answer Test），要求所有必需Checkpoint均出现且状态为PASS。

**L2鲁棒性测试（L2CampaignExecutor）**：对已通过L1的模块施加随机向量或边界向量的压力测试，验证在非KAT条件下的行为一致性。L2的判定不仅包含Checkpoint通过率，还会输出`counterexample.json`和`fragility_summary.json`，供`L2AdaptivePlanner`用于后续Profile选择决策。

**集成回归测试（IntegrationRegressionExecutor）**：在所有模块全部PROMOTED后触发，以`IntegrationRegressionManifest`为规格驱动，对顶层模块`aes128_encrypt_core`执行三种Campaign（baseline、back_to_back、mid_reset），验证完整系统在不同使用场景下的正确性。

### 5.1.3 分层验证与框架控制流的集成

四层验证不是孤立存在的，而是与编排状态机深度集成。编排状态`MODULE_L0`对应L0执行，`MODULE_L1`对应L1执行，`MODULE_L2_OPTIONAL`对应L2鲁棒性测试，`INTEGRATION_REGRESSION`对应集成回归测试。每层验证的判定结果直接影响工作区状态机的转移：L0失败则工作区保持REPAIRING状态，L1 Checkpoint全部通过则状态跃迁至VALIDATED，PROMOTED后触发集成回归。这一设计确保了验证结果的机器可判定性，消除了对LLM主观判断的依赖。

---

## 5.2 Checkpoint协议设计

### 5.2.1 协议格式规范

Checkpoint协议是本系统验证体系的核心通信机制，定义了Testbench与框架之间的结构化结果汇报接口。协议格式为：

```
CHECKPOINT|<name>|PASS|<detail>
```

其中：
- `CHECKPOINT` 为固定前缀，作为日志行过滤的识别标记
- `<name>` 为Checkpoint名称，与`pass_criteria.l1.coverage_checkpoints`中定义的名称精确对应
- `PASS` 为当前唯一合法的状态值，表示该检查点已验证通过
- `<detail>` 为人类可读的补充说明，不参与机器判定逻辑

该协议通过`aes_tb_common.hpp`中的`emit_checkpoint()`函数在C++ Testbench端发射：

```cpp
inline void emit_checkpoint(
    const std::string& checkpoint,
    const std::string& detail
) {
    std::cout << "CHECKPOINT|" << checkpoint << "|PASS|" << detail << std::endl;
}
```

（`aes_mvp/tb/aes_tb_common.hpp:603-608`）

这一设计实现了Testbench端的极简接入：Testbench开发者只需在正确性验证通过后调用`emit_checkpoint("CHK_XXX", "描述")`一行代码，无需了解协议解析细节。

### 5.2.2 设计决策分析

选择简单文本协议而非结构化输出（如JSON）的决策基于以下考量：

**对日志噪声的鲁棒性**：Verilator仿真过程中会产生大量警告、调试输出和波形信息。文本协议通过逐行扫描和前缀匹配实现解析，不受日志噪声干扰；而JSON格式需要完整解析仿真输出流，对格式错误极为敏感。

**Testbench端实现简单**：`emit_checkpoint()`是单行调用，Testbench开发者和LLM Agent均能可靠地生成该调用，不会因JSON转义、嵌套结构等问题引入格式错误。

**框架端解析简单**：`CheckpointParser`（`aes_mvp/executors.py:71-90`）的实现仅需30行代码，通过`CHECKPOINT_PREFIX = 'CHECKPOINT|'`前缀过滤和`split('|', 3)`分割即可完成解析，维护成本极低。

与胡昆越AutoGen方案的对比：该方案使用Vivado xsim仿真，验证结果依赖波形图（.vcd）的人工判读，无法实现机器自动判定。本文的Checkpoint协议使验证结果完全机器可判定，且与文件系统通信机制（Batch Gate回调）无缝集成。

### 5.2.3 CheckpointParser解析逻辑

框架端的`CheckpointParser`类（`aes_mvp/executors.py:71-90`）负责从`simulation.log`文件中提取Checkpoint信息，构建`name→status|detail`字典：

```python
class CheckpointParser:
    def parse_text(self, text: str) -> dict[str, str]:
        summary: dict[str, str] = {}
        for raw_line in text.splitlines():
            line = raw_line.strip()
            if not line.startswith(CHECKPOINT_PREFIX):
                continue
            parts = line.split('|', 3)
            if len(parts) < 4:
                continue
            _, name, status, detail = parts
            summary[name] = f'{status}|{detail}'
        return summary
```

解析器扫描`simulation.log`全文，对每一行检查是否以`CHECKPOINT|`开头，然后以`|`为分隔符切分（最多3次，保留detail中可能存在的`|`字符），构建名称到状态字符串的映射。

### 5.2.4 Checkpoint汇总与判定

`summarize_required_checkpoints()`函数（`aes_mvp/executor_contracts.py:329-353`）接收解析后的Checkpoint字典和required_checkpoints元组，输出三类分类结果：

- **missing**：未在仿真日志中出现的必需Checkpoint（Testbench未执行到该路径）
- **failed**：出现但状态字段不为`PASS`的Checkpoint
- **passed**：出现且状态为`PASS`的Checkpoint

只有当`missing`和`failed`均为空时，验证才判定为通过。这一逻辑同时捕获了"Testbench未运行到验证点"和"Testbench运行到验证点但判定失败"两种失败模式。

[图5-2: Checkpoint协议工作流程（TB emit → simulation.log → CheckpointParser → summarize → Decision）]

### 5.2.5 各模块Checkpoint一览

[表5-2: 各模块Checkpoint一览表]

| 模块 | Checkpoint名称 | 验证内容 |
|------|--------------|---------|
| aes_sbox | CHK_SBOX_MATCH | S-box查找表输出与已知向量匹配 |
| aes_key_schedule_128 | CHK_ROUNDKEY_MATCH | 11轮密钥扩展输出与标准参考值匹配 |
| aes_round_transform | CHK_ROUND_STATE_MATCH | 单轮SubBytes+ShiftRows+MixColumns+AddRoundKey输出匹配 |
| aes128_encrypt_core | CHK_RESET_CLEAR | 复位后所有状态寄存器清零 |
| aes128_encrypt_core | CHK_START_ACCEPTED | start信号在IDLE状态被正确采样 |
| aes128_encrypt_core | CHK_BUSY_ASSERTED | 加密启动后busy信号在首个时钟上升沿置位 |
| aes128_encrypt_core | CHK_DONE_PULSE | done信号为单周期脉冲（仅持续1个时钟） |
| aes128_encrypt_core | CHK_CIPHERTEXT_MATCH | 11周期后输出密文与NIST标准向量精确匹配 |
| aes128_encrypt_core | CHK_BUSY_DEASSERTED | done脉冲后busy信号随即去断言 |

`aes128_encrypt_core`模块包含6个Checkpoint，覆盖了完整的FSM行为验证路径：从复位清零、握手协议、busy信号时序、延迟精度到密文正确性，构成了对11周期迭代微架构的全面行为规约。

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

Profile的种子固定（`_CAMPAIGN_PROFILE_SEEDS`字典，`aes_mvp/executors.py:206-211`），保证测试结果的完全可复现性。

### 5.3.3 随机数生成与可复现性

随机块生成使用xorshift算法，C++实现在`aes_tb_common.hpp:488-501`，Python实现在`_BaseExecutor`类中（`aes_mvp/executors.py:219-234`）。两端实现保持严格一致，使Python生成的oracle密文（用于端到端验证）与C++ Testbench生成的随机向量完全对应。

C++端`random_block()`函数：
```cpp
inline Block random_block(uint64_t& state) {
    Block out{};
    for (std::size_t i = 0; i < 16; ++i) {
        out[i] = static_cast<uint8_t>(next_rng(state) >> 56);
    }
    return out;
}
```

其中`next_rng()`为xorshift64变体（state ^= state << 13; state ^= state >> 7; state ^= state << 17），每次取64位状态的最高字节作为随机字节输出。固定seed与确定性RNG的组合确保了L2测试的完全可复现性：任意时刻以相同seed执行相同profile，必然得到相同的测试向量序列。

### 5.3.4 顶层模块的Oracle生成机制

对于`aes128_encrypt_core`（顶层模块），L2测试采用额外的端到端正确性验证机制。框架在仿真前调用`_write_campaign_oracle_file()`（`aes_mvp/executors.py:239-291`），使用OpenSSL的`aes-128-ecb`命令行接口生成每个随机测试向量对应的标准密文，写入oracle文件：

```
label=rand_small_case_0|key=<32位hex>|plaintext=<32位hex>|ciphertext=<32位hex>
```

Testbench读取oracle文件中的密文进行比对，实现了以OpenSSL为参考实现的端到端验证。这一设计的优势在于：oracle生成完全独立于被测模块，避免了"用自身验证自身"的循环逻辑。

### 5.3.5 L2AdaptivePlanner自适应策略

`L2AdaptivePlanner`（`aes_mvp/synthesis.py:930-976`）根据历史脆弱性记录自适应选择L2 Profile：

- 若模块无历史记录，选择第一个Profile（rand_small）
- 若上一次Profile测试失败，选择列表中的下一个Profile（更严格的测试）
- 若上一次Profile测试通过，保持当前Profile

这一机制实现了测试强度与历史脆弱性的自适应匹配，避免了对所有模块施加同等力度的测试造成的资源浪费。

[图5-3: L2 Campaign执行流程（Profile选择 → 向量生成/Oracle → 仿真 → Checkpoint解析 → counterexample/fragility输出）]

### 5.3.6 L2测试输出物

L2执行完成后输出两个关键文件：

**`counterexample.json`**：记录失败向量详情，包含profile、vecfile、cases、seed、checkpoint_summary、missing_checkpoints、failed_checkpoints等字段，供框架和Agent分析失败原因。

**`fragility_summary.json`**：记录脆弱性统计指标，包含observed_checkpoints（实际出现的Checkpoint）、checkpoint_count等信息，供`L2AdaptivePlanner`用于下一轮Profile决策。

---

## 5.4 集成回归测试

### 5.4.1 触发条件与规格定义

集成回归测试的触发条件是：AES-128全系统的所有4个模块（aes_sbox、aes_key_schedule_128、aes_round_transform、aes128_encrypt_core）全部达到PROMOTED状态，且`IntegrationReadinessResolver`确认所有依赖已满足。

集成测试规格通过`IntegrationRegressionManifest`（`aes_mvp/artifacts.py:270-294`）定义，采用Pydantic模型并强制`extra='forbid'`，包含：

- `top_module`：集成测试的顶层模块（aes128_encrypt_core）
- `rtl_files`：全部4个模块的RTL文件列表（含依赖关系顺序）
- `tb_file`：顶层模块的C++ Testbench
- `required_modules`：必需模块列表，与rtl_files的stem顺序严格一致（由`model_validator`验证）
- `regression_checkpoints`：需要在所有Campaign中通过的Checkpoint集合
- `latency_target_cycles`：11周期延迟目标
- `back_to_back_required`：是否需要执行back_to_back Campaign
- `mid_reset_scenarios`：mid_reset Campaign的场景列表
- `interface_freeze_hash`：接口冻结标识（`aes-128-block_handshake-iterative_10_round-autonomous-v1`）

`synthesize_integration_manifest()`函数（`aes_mvp/synthesis.py:612-658`）在框架初始化阶段从SpecIR和PlanDAG自动生成IntegrationRegressionManifest，无需人工配置。

### 5.4.2 三种Campaign规格

[表5-3: 三种集成Campaign规格表]

**baseline Campaign**：使用NIST FIPS-197标准向量执行端到端加密正确性验证。验证目标是确认顶层模块在标准测试条件下的功能完全正确。包含全部6个aes128_encrypt_core Checkpoint：CHK_RESET_CLEAR、CHK_START_ACCEPTED、CHK_BUSY_ASSERTED、CHK_DONE_PULSE、CHK_CIPHERTEXT_MATCH、CHK_BUSY_DEASSERTED。

**back_to_back Campaign**：连续发起多次加密请求，两次加密之间无空闲间隔（前一次done脉冲后立即送入新的start信号）。验证目标是FSM在连续工作模式下不存在状态残留：BUSY信号在done后正确去断言，IDLE状态正确恢复，下次start能被正常采样。通过`plusargs: {profile: 'back_to_back'}`传递给Testbench。

**mid_reset Campaign**：在加密进行到第5轮（约中间位置）时断言reset信号，验证FSM能够从任意中间状态正确复位，之后能够接受新的加密请求并产生正确密文。通过`plusargs: {profile: 'mid_reset'}`传递给Testbench。

集成测试捕获的典型缺陷类型包括：子模块接口时序错位（如busy信号延迟一个周期）、FSM状态寄存器复位不完全（如round计数器在reset后未清零）、back_to_back场景下的状态污染（如前次加密的key未清除影响后次加密）。这些缺陷在子模块独立L1验证中无法被发现，只有在系统级集成测试中才会暴露。

### 5.4.3 集成测试执行机制

`IntegrationRegressionExecutor`（`aes_mvp/executors.py:552-693`）按以下流程执行集成回归：

1. 调用`resolve_integration_regression_inputs()`解析manifest，验证rtl_files顺序与required_modules一致，验证vector_set文件存在
2. 执行一次编译（将全部4个模块的RTL和顶层TB一同编译为可执行模型）
3. 依次执行baseline、back_to_back（如`back_to_back_required`为True）、mid_reset（如`mid_reset_scenarios`非空）三种Campaign
4. 每种Campaign独立调用`simulate()`，使用独立的output_dir，解析独立的simulation.log
5. 使用`summarize_required_checkpoints()`对每种Campaign的Checkpoint进行汇总，生成aggregate_missing和aggregate_failed
6. 当aggregate_missing和aggregate_failed均为空时，写入status: 'passed'的`integration_regression_result.json`

[图5-4: 集成回归测试执行流程（manifest解析 → 统一编译 → 三种Campaign → Checkpoint聚合 → 最终判定）]

### 5.4.4 集成测试与子模块验证的层次关系

集成回归测试在四层验证体系中处于顶层，与子模块L0/L1/L2验证形成层次关系：子模块验证关注局部行为正确性，集成验证关注系统级行为正确性和模块间交互。

本系统的设计原则是：每个模块在进入集成测试前必须经过独立的L0+L1验证（可选L2），PROMOTED状态是集成测试的前提条件。这一"先分后合"的验证策略减少了集成测试阶段的调试负担，提高了系统整体的验证效率。

四层验证体系的完整执行路径为：

```
L0编译门控 → L1仿真+Checkpoint → (L2鲁棒性测试) → 所有模块PROMOTED → 集成回归测试 → DONE
```

每一层都是下一层的前提，每一层的验证结果都直接驱动框架控制流的状态转移，形成了一套机器自动判定、无需人工干预的完整验证体系。
