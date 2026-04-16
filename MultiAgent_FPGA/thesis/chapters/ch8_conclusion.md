# 第八章 总结与展望

## 8.1 工作总结

### 8.1.1 研究回顾

本文围绕"基于多智能体协作的 FPGA 设计全流程自动化"这一核心论点，设计并实现了一套以 AES-128 加密全系统为验证案例的多智能体 FPGA 设计自动化框架。该框架以 OpenHands SDK 为运行底座，以 DeepSeek Chat 双 Profile 策略为 LLM 后端，以 Verilator 仿真器为验证引擎，实现了从规格输入到集成验证通过的全流程自动化。

本文所解决的核心问题是：在硬件设计这一高精度、强约束的领域中，如何驾驭本质上不可靠的大语言模型，使其成为可信赖的自动化设计组件。现有方案（以胡昆越 AutoGen 方案为典型代表）将控制权交给 LLM 自身，依赖提示词中的自然语言指令约束 Agent 行为；而本文提出并实现的框架控制（Framework-controlled）架构，将批次推进、验证判定、修复决策等控制逻辑全部内化到状态机和 Pydantic 数据契约中，LLM 只负责执行被明确分配的局部任务。

### 8.1.2 三个创新点的实现情况

**创新点一：基于 10 状态编排状态机 + AgentExecutionPolicy 的框架控制多智能体协作架构**

本文设计并实现了包含 10 个状态的编排状态机（`SPEC_INTAKE` → `ARCHITECTING` → `PLANNING` → `MODULE_DESIGN` → `MODULE_L0` → `MODULE_L1` → `MODULE_L2_OPTIONAL` → `INTEGRATION_READY` → `INTEGRATION_REGRESSION` → `DONE`），覆盖从规格解析到集成验证的全生命周期。每个状态通过 `AgentExecutionPolicy` 映射到确定的 LLM Profile 和 SubagentPolicy，使得编排器的跨模块决策使用 thinking profile（强推理能力），工作器的局部执行任务使用 fast profile（低延迟、低成本），实现了计算资源在不同任务类型上的按需分配。`DAGBatchPlanner` 基于 Kahn 拓扑排序将 4 节点 AES DAG 分解为两个批次，在依赖满足后自动并行执行 Batch 2 的三个模块，这是胡昆越线性 pipeline 方案无法实现的能力。该创新点已通过 `orchestrator/state_machine.py`、`policy.py`、`delegation.py` 等核心模块实现，并在端到端 `run-aes-mvp` 流程中得到验证。

**创新点二：L0→L1→L2→Integration 四层分级验证体系与 Checkpoint 协议**

本文设计并实现了四层分级验证体系，通过快速失败原则（L0 编译门控在仿真前拦截语法错误）和逐步深入策略（从单向量验证到随机鲁棒测试再到多场景集成回归），覆盖了从语法正确性到系统级行为正确性的完整验证空间。`CHECKPOINT|<name>|PASS|<detail>` 协议将验证意图精确编码为机器可解析的文本格式，由 `CheckpointParser` 自动判定，彻底消除了 Vivado 波形人工判读带来的不确定性。4 个模块共设计了 9 个 Checkpoint（aes_sbox 1 个，aes_key_schedule_128 1 个，aes_round_transform 1 个，aes128_encrypt_core 6 个），集成回归测试通过 baseline、back_to_back、mid_reset 三种 Campaign 覆盖了连续加密和异常复位等系统级场景。该创新点通过 `executors.py` 中的 `L0Executor`、`L1Executor`、`L2CampaignExecutor`、`IntegrationRegressionExecutor` 四个执行器实现，并通过 `aes_tb_common.hpp` 中的 `emit_checkpoint()` 接口与 Testbench 端协同工作。

**创新点三：Harnessing Engine — Skill/Prompt/Memory/Hooks/MCP/SlashCommand 六层约束引擎**

本文提出了 Harnessing Engine 概念，系统性地将对不可靠 LLM 的约束工程从单一 system_message 层扩展为六层结构化约束组合：Skill 层通过 16 个领域知识文件为 Agent 注入权威规则；Prompt 层通过可组合的 BaseContract + PhaseMixin 架构精确控制每个执行阶段的行为边界；Memory 层将验证通过的参考代码预填充到工作区，显著降低从零生成正确 RTL 的难度；Hooks 层通过 `run_executor` 自定义工具和 `verify_repair_edit()` 哈希验证构建执行门控；MCP 层通过工具过滤（排除 `verilator_testbenchgenerator` 和 `verilator_naturallanguage`）防止 Agent 绕过框架直接生成代码；SlashCommand 层提供完整的 CLI 命令体系，每条命令对应确定的验证语义。六层协同覆盖了幻觉端口、语法错误、Scope drift、过度修改、格式错误 5 种典型 LLM 失败模式，形成了多维度的防御矩阵。

### 8.1.3 实验验证结论

实验结果表明，本文提出的框架在 AES-128 加密全系统案例上实现了以下目标：

- 全流程可跑通：从 `run-aes-mvp` 命令启动到状态机到达 `DONE` 状态，不需要人工干预；
- 模块验证有序推进：`aes_sbox` 模块因纯组合逻辑特性，Memory 预填充后 0 次修复即通过 L1 Checkpoint（通过率 100%）；
- 框架控制有效：所有批次推进决策均由状态机和 Checkpoint 判定逻辑驱动，LLM 无法绕过验证门控"提前宣布成功"；
- Checkpoint 协议稳定：`CHECKPOINT|<name>|PASS|<detail>` 格式在所有模块的仿真日志解析中稳定工作，`CheckpointParser` 能从含有其他调试输出的日志中准确提取 Checkpoint 行。

本文的工作在胡昆越 AutoGen 方案的基础上，实现了从线性 pipeline 到 DAG 拓扑批调度、从单层验证到四层分级验证、从 Prompt-controlled 到 Framework-controlled 的系统性架构升级，为多智能体 FPGA 设计自动化的可靠性与可扩展性研究提供了一个完整的工程实践参考。

---

## 8.2 不足与展望

### 8.2.1 当前局限

尽管本文在 AES-128 案例上完整验证了框架设计，但当前版本仍存在以下明确局限：

**局限一：设计范围硬编码，通用性不足**。当前框架的 AES-128 蓝图（模块定义、端口规范、Checkpoint 列表、向量文件路径等）硬编码在 `synthesis.py` 的 `_aes_blueprints()` 函数中。将框架迁移到其他 FPGA 设计任务需要修改该函数，缺乏"仅通过配置文件指定新设计目标"的开箱通用性，这与胡昆越方案面向通用 Verilog 模块的灵活性相比是明显的差距。

**局限二：无 L3 综合与实现阶段**。本文的验证深度止步于 Verilator 仿真（行为级验证），不涵盖逻辑综合（Yosys/Vivado Synthesis）、布局布线和比特流生成。Verilator 仿真通过并不能保证 RTL 在特定 FPGA 器件（如 Xilinx Artix-7）上以目标时钟频率（如 100 MHz）实现时序收敛，因此当前框架不能替代完整的 FPGA 实现流程。

**局限三：依赖 DeepSeek API，存在外部依赖**。全流程依赖 `DEEPSEEK_API_KEY` 和 DeepSeek 官方 API 端点（`https://api.deepseek.com`），网络延迟、API 限流和服务可用性均可能影响自动化流程的稳定性。在受限网络环境（如企业内网）中部署存在障碍。

**局限四：Memory 预填充依赖已有参考代码**。`MemoryStore` 的工作前提是 Skill 文件中已经存在验证通过的参考 RTL 和 Testbench。对于全新的未见过的硬件设计模块，框架目前没有自主从零构建参考代码库的机制——这意味着框架的有效性在一定程度上依赖于人工维护的技能文件库。

**局限五：仅在单机单用户场景验证**。当前框架在 macOS 单机环境下验证，未测试分布式执行、多用户并发或 CI/CD 流水线集成场景的稳定性。

### 8.2.2 未来方向

基于上述局限，本文提出以下五个未来研究方向：

**方向一：扩展至更多密码学模块和 IP 核**。在当前 AES-128 案例的基础上，通过泛化 `_aes_blueprints()` 为可配置的蓝图描述语言（YAML 或 JSON 格式），支持 AES-192、AES-256、SHA-256、RSA 等更多密码学模块的自动化设计验证。进一步地，可以探索将框架应用于非密码学的通用数字逻辑模块（如 FIFO、AXI 总线接口、浮点运算单元），验证框架在不同硬件领域的适用性和可移植性。

**方向二：引入 L3 综合与实现阶段**。将 Yosys（开源综合工具）或 Vivado（商业实现工具）集成到验证体系中，新增 L3 层负责综合后时序分析、资源利用率估算和关键路径优化，形成 L0→L1→L2→L3→Integration 的五层完整验证体系。这需要设计对应的 MCP 适配器（类似 `VerilatorMCPAdapter`）和结构化的综合报告解析器，使框架能够自动解读时序违例并指导 RTL 修改。

**方向三：支持多 LLM 后端**。当前框架深度绑定 DeepSeek Chat API，通过扩展 `LLMProfileName` 枚举和 `build_llm_profile_kwargs()` 函数，引入对 Claude（Anthropic）、GPT-4o（OpenAI）和本地部署的 Llama-3/Qwen 等模型的支持，使用户可以根据网络环境、成本预算和性能需求灵活选择 LLM 后端。同时，可以探索混合 LLM 策略：对于编排器使用最强模型，对于工作器使用成本效益比更高的本地模型，进一步降低运行成本。

**方向四：Agent 自主学习能力**。当前 Memory 预填充依赖人工维护的静态 Skill 文件。未来可以设计基于修复历史的自主学习机制：每次成功的修复循环（RepairContract → EditReceipt → VALIDATED）自动触发一次 Skill 更新流程，将修复前后的代码差异（diff）和修复原因（RepairContract 描述）结构化写入对应的 Skill 文件，形成动态增长的领域知识库。经过多次运行后，框架对同类错误的首次通过率将逐步提升，修复轮次逐步减少。

**方向五：Harnessing Engine 的通用化框架**。本文的 Harnessing Engine 设计虽以 FPGA 设计为具体领域，但其六层约束架构（Skill / Prompt / Memory / Hooks / MCP / SlashCommand）具有超越硬件设计领域的通用价值。未来可以将 Harnessing Engine 抽象为独立的通用框架，使其能够以声明式配置的方式应用于软件工程、数据分析、文档生成等不同 LLM 应用场景，为"如何系统性地驾驭不可靠 LLM"这一广泛问题提供可复用的工程模式。

### 8.2.3 结语

FPGA 设计自动化与大语言模型的结合处于研究早期，从"LLM 能否生成正确的 RTL"到"如何构建可靠的全流程自动化系统"是一个质的跨越。本文的工作表明，通过精心设计的框架控制架构、分层验证体系和多层约束引擎，不可靠的 LLM 可以被驾驭为可信赖的 FPGA 设计自动化组件。AES-128 全系统的成功验证仅是一个起点——将这一框架扩展到更广泛的硬件设计领域，并最终缩短从规格到可综合 RTL 的端到端设计周期，是值得持续探索的方向。
