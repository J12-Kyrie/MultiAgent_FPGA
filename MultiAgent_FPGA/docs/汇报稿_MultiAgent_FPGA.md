# 基于 OpenHands SDK 的 Multi-Agent FPGA 自动化设计系统 — 汇报稿

> **汇报人**：贾阔源 | **指导老师**：刘亚男 | **日期**：2026 年 4 月

---

## 一、演示文稿概述

本次毕业设计汇报共包含 22 页演示文稿，按照"研究背景及意义 — 关键技术框架 — 项目具体实施 — 总结与展望"四个章节依次展开。全文配有 46 张图片，其中包括 26 张核心技术图（架构图、流程图、状态机图、数学推导图等），其余为每页右上角重复出现的校徽标识。整个演示的核心论点围绕三大创新展开：框架控制的编排状态机、四层分级验证体系以及 Harnessing Engine 六层 LLM 约束引擎。以下按章节顺序对每页内容及其图片进行详细解读。

---

## 二、第一章：研究背景及意义（Slides 1-5）

### 2.1 封面与目录

演示文稿以一张简洁的封面页开篇，标题"基于 OpenHands SDK 的 Multi-Agent FPGA 自动化设计系统"居中排列，下方标注汇报人与指导老师信息，上方放置校徽标识。整体采用四角装饰矩形搭配圆角主框架的学术风格排版。

紧随其后的目录页将汇报内容划分为四个部分，以编号圆形图标配合文字说明的方式呈现，布局清晰直观，为听众建立了完整的汇报路线图。

### 2.2 大语言模型发展时间线（Slide 3）

第三页通过一条纵向时间线，梳理了大语言模型从 20 世纪至今的关键发展节点。时间线以垂直中轴线为主干，左右交替排列八个里程碑事件：从早期基于统计的 n-gram 模型出发，经过 2003 年 Bengio 团队提出的神经网络语言模型、2014 年 Seq2Seq 框架和 2015 年 Attention 机制，直到 2017 年 Google 提出 Transformer 架构——这被标注为"革命性突破"，也是后续所有大模型的基石。此后 2018 年 GPT 和 BERT 相继问世，2024 年国产大模型 DeepSeek 横空出世，2025 年则被标注为"智能体工程元年"。

这条时间线的叙事意图非常明确：通过回溯技术演进史，将本课题锚定在 2025 年 Agent 框架爆发的时代背景之中，说明课题立项既有深厚的技术积淀，又恰逢其时。

### 2.3 Harnessing Engineering — 驾驭工程（Slide 4）

第四页引入了本课题的一个核心概念——Harnessing Engineering（驾驭工程），并以一张极具说服力的对比图加以论证。这张图采用左右分栏布局，左侧展示了"Without Harness"的传统工作流，右侧展示了"With Harness"的优化工作流。

在左侧流程中，Agent 生成代码后需要经历三轮人工审查：第一轮发现类型错误，Agent 修复后第二轮又发现格式问题和引用错误，再次修复后第三轮才最终通过。整个过程消耗约 2000 个 token，且始终依赖人工介入，标注为"human blocked"。左侧各节点使用红色暖色调，视觉上暗示了人工审查带来的效率瓶颈。

右侧流程则截然不同：Agent 生成代码后，Hook 机制自动执行 Lint 和 TypeCheck，以结构化 JSON 格式一次性反馈所有错误，Agent 据此一轮修复完毕，再由 Hook 确认所有检查通过。整个过程仅消耗约 50 个 token，完全无需人工介入。右侧节点使用绿色冷色调，传达了自动化的高效感。图片底部的总结一语中的："Hooks compress multi-turn dialogue into automated signals — same result, 1/40 the context cost。"

这张对比图的深层含义在于揭示了本课题面临的根本挑战：大语言模型本质上是不可靠的，它会产生幻觉（生成不存在的端口名）、发生 scope drift（偏离指定任务范围）、还可能在验证未完成时提前宣布成功。Harnessing Engine 作为本课题提出的解决方案，通过六层结构化约束（Skill 层、Prompt 层、Memory 层、Hooks 层、MCP 层、SlashCommand 层），从外部工程化地约束 LLM 的行为，而非依赖模型的"自律性"。这也是本课题的第三个核心创新点。

### 2.4 LLM 在 EDA 领域的应用（Slide 5）

第五页聚焦文献综述，通过两张论文引用图和一段文字说明，完成了对当前研究前沿的定位。

第一张图来自 MCP4EDA 论文，展示了 MCP 协议在 EDA 领域的系统架构。图中采用三列布局：左侧是 MCP Host，包含多个 MCP Client 和 LLM；中间是 MCP Server，承载 Simulation、Synthesis 和 Backend 三个功能模块；右侧是具体的 EDA 工具链，涵盖 Icarus Verilog、GTKWave、Yosys、OpenLane、KLayout 等从仿真到物理实现的完整工具。各层之间通过 Post/Response 和 Call/Response 通信，LLM 通过发送上下文和工具请求与 Server 交互，实现了从 RTL 到 GDSII 的自动化流程。

第二张图来自 Spec2RTL-Agent 论文，展示了端到端的 RTL 自动生成流程。图中用三种颜色的色块划分了三个阶段：红色的 Understanding（理解设计规格并提取架构）、绿色的 Coding（生成 RTL 代码并通过 HLS 工具实现）、蓝色的 Reflection（对生成结果进行自我审查和修正）。图上方还特别标注了竞品对比：BetterV 和 CraftRTL 仅自动化了 Coding 阶段，AutoChip 和 VerilogCoder 仅自动化了 Reflection 阶段，而 Spec2RTL-Agent 实现了三个阶段的端到端全覆盖，并通过 Architecture Improvement 和 Code Fix 两条反馈路径形成迭代闭环。

页面下方列出了文字说明，将 LLM 在 EDA 领域的应用归纳为 Understanding、Coding、Reflection 三个维度，同时指出现有方案普遍存在模块间依赖处理不足、验证层级单一和 LLM 约束不够等问题——这恰好构成了本课题的创新切入点。

---

## 三、第二章：关键技术框架（Slides 6-11）

### 3.1 OpenHands 平台概览（Slide 7）

进入第二章后，第七页以一张占满全页的 OpenHands 平台全景架构图，介绍了本项目的运行底座。

这张图信息密度极高，涵盖了 OpenHands 的完整运行机制。左上角展示了三种用户交互入口——命令行、Web UI 和 IDE 插件，它们汇聚到"多轮用户-Agent 交互"中。图的核心区域是 Event Stream，即 Action-Observation 的追踪中心，通过编号 1 到 9 的序列完整演示了一个典型交互过程：用户提出请求后，Agent 依次创建 Python 文件、编写 Flask 服务器代码、运行命令启动服务、最后通过 Playwright 浏览器访问页面并获取输出结果。左下角定义了 Agent 的核心抽象——Event Stream 是 Action 和 Observation 的有序列表，Agent 根据 Event History 产生下一个 Action，Runtime 负责将 Action 转化为 Observation。右侧展示了 Agent Runtime 的组成：Docker Sandbox 提供隔离的执行环境，内含 Action Execution API，支持 Interactive Python Server、Bash Shell 和浏览器三种执行方式。

选择 OpenHands SDK 而非 AutoGen 等其他框架的核心原因在于：OpenHands 原生支持自定义工具注册和 MCP 集成，使得 Verilator 仿真器可以作为 Agent 可调用的工具无缝接入，从而实现"Agent 生成代码 → 框架自动编译仿真 → 解析结果 → 结构化反馈"的完整闭环。

### 3.2 OpenHands SDK 模块细节（Slide 8）

第八页进一步展开了 SDK 的内部结构，包含两张图。

第一张是 SDK 九大核心模块的功能对照表。Planning & Decision Engine 负责生成计划与决策，通过 Prompt 和自然语言反馈驱动，支持 CodeAct 和 ReAct 模式。Memory 模块存储对话历史、执行结果和外部知识，支持 RAG 检索和记忆压缩，解决了上下文窗口有限的难题。Planner 提供可配置的规则/动态/混合规划器。Tool Module 通过 function call 实现 LLM 输出到结构化工具调用的映射。Reflection Module 采用 ReAct 和 Reflexion 策略对模型行为进行检查与修正。Event Bus 是发布-订阅系统，实现模块间的解耦与异步通信。Runtime Sandbox 通过 Docker 创建隔离的工作空间，保证执行的安全性和可复现性。AgentController 是框架的"指挥官"，负责迭代循环、状态管理和子 Agent 调度。Server & Session 提供 WebSocket 接口，管理会话的创建、恢复和持久化。

第二张是后端架构图，清晰展示了从用户到运行时的完整数据通路：用户通过前端单页应用发起请求，经 HTTP/WebSocket 到达 OpenHands 后端，后端分别连接事件流、存储和大语言模型提供者。Runtime 区域以绿色背景标识，内部通过运行时接口分发到 Docker 运行时、本地运行时或远程运行时，最终到达动作执行服务器，支持 Bash 会话、Jupyter 插件和浏览器环境三种执行方式。

基于这些核心模块，本项目构建了五种 Agent 角色：Workflow Orchestrator 驾驭全局流程、Finalizer Orchestrator 负责终态总结、Module Worker 执行单模块的 RTL 生成、Repair Worker 处理结构化修复、L2 Campaign Agent 执行鲁棒性测试。这种分层委派设计使编排器专注于全局决策，工作器专注于局部执行。

### 3.3 DeepSeek 架构深度解析（Slides 9-11）

第九页是全部演示中信息密度最高的一页，包含多达 11 张技术图，完整剖析了 DeepSeek 大语言模型的架构特点。

首先是 DeepSeek 的整体架构图。左侧展示了标准的 Transformer Block 堆叠结构：输入经过 RMSNorm 进入 Attention 模块，再经 RMSNorm 进入 Feed-Forward Network，两处均有残差连接。右上角展示了 DeepSeekMoE 的核心设计：输入的 Hidden State 经过 Router 模块，由 TopK 机制动态选择要激活的专家网络。专家分为绿色标注的 Shared Experts（所有 token 共享）和蓝色标注的 Routed Experts（按需激活），各专家输出经加权求和后产生最终结果。右下角展示了 Multi-Head Latent Attention（MLA）机制的细节：输入被投影到低维潜在空间（分别得到 Latent Query 和 Latent KV），经过展开、RoPE 位置编码和拼接后参与多头注意力计算，其中 KV 的潜在表示在推理时被缓存。

接下来是 Dense 模型与 Sparse MoE 模型的对比图。Dense 模型的每个 Transformer Block 使用单一的 FFN 层，所有参数在每次推理中全部激活。而 Sparse MoE 模型则将 FFN 替换为 Gate 加多专家结构：Gate 根据输入动态路由，仅激活其中少量专家（蓝色高亮标识），Shared Expert 则始终参与计算。这种稀疏计算的本质可以用页面上另一张直观的概念图来概括："一个稠密大矩阵变成数百个稠密小矩阵，每次只激活 6 到 8 个。"

参数分布表进一步量化了这一架构的特点：DeepSeek 总共拥有 671.025B 参数，其中 MoE 模块占 98.02%（654.48B），Routed Expert 单独就占了 654.106B。相比之下，MLA 模块仅占 1.70%（11.4134B），Embedding 和 Output 层加起来不到 2%。这意味着模型的绝大部分容量存储在数百个专家网络中，但每次推理只激活其中极小一部分，从而在保持模型总能力的同时大幅降低计算成本。

MLA 的数学流程图和公式图则详细展示了 KV 压缩的数学原理。输入 x 分两路处理：一路通过 W_q 和 W_UK 的转置相乘得到 Query 的注意力分数，另一路通过 W_DKV 投影到低维空间后缓存。注意力计算完成后，通过 W_UV 和 W_o 输出最终结果。公式中明确标注了关键变量：c_t^KV 是压缩后的 KV 潜在表示，k_t^C 和 k_t^R 分别是从压缩空间恢复的 Key 和经过 RoPE 编码的位置 Key，两者拼接后参与注意力计算。这种设计的核心优势是：只需缓存低维的潜在表示而非完整的 Key-Value 矩阵，大幅降低了长上下文推理的显存占用。

第十和第十一页分别深入讲解了 DeepSeek 推理的两个阶段。Prefill 阶段处理完整的输入序列，所有 token 并行计算，张量维度从输入的 (b, s, 7168) 经 Q_down-proj 压缩到 (b, s, 1536)，再展开为 128 个注意力头。Decode 阶段则逐 token 自回归生成，序列维度从 s 缩减为 1，同时引入 KV Cache 机制，将当前步的 K/V 与历史缓存拼接。这两个阶段的分离对 Agent 系统有直接的工程意义：编排器的系统提示（包含长篇的合约文档和技能描述）主要消耗 Prefill 算力，而 Agent 在修复循环中的交互式推理主要消耗 Decode 算力。MLA 的 KV Cache 压缩机制使得这种长上下文、多轮对话的场景在算力和显存上都更加高效。

---

## 四、第三章：项目具体实施（Slides 12-19）

### 4.1 系统六层架构（Slide 13）

第十三页以一张全幅横向的架构图展示了系统的整体分层设计。图中采用自顶向下的布局，以浅黄色背景区分每一层的边界，淡紫色方框标注具体的文件和模块。

最顶层是 CLI Entry（main.py），提供 validate、smoke-sdk、smoke-provider、run-node 和 run-aes-mvp 五个命令入口。CLI 下方是 Runtime Layer，包含 sdk_shim.py（SDK 导入垫片）、bootstrap.py（运行时初始化）、factory.py（Agent 工厂）、runner.py（对话驱动器）、session.py（执行会话）、context_assembler.py（上下文组装）和 execution_tools.py（自定义工具注册）七个模块。Runtime Layer 向下分叉为三个平行的子层：Agent Layer 包含角色规格定义、提示词构建、提示词合约、技能引用和记忆存储五个组件；Execution Layer 包含执行器、适配器和 Verilator 集成三个组件；Synthesis Layer 包含综合引擎、数据契约、策略定义、执行器合约和工作区生成五个组件。

这种分层设计的核心优势在于关注点分离：每一层只负责一个维度的职责，层间通过 Pydantic 模型定义的严格数据契约通信，所有契约均使用 extra='forbid' 参数拒绝未定义字段，从数据层面保证了系统的正确性。

### 4.2 端到端工作流程（Slide 14）

第十四页通过两张互补的图详细展示了系统的运行流程。

第一张是六方参与者的时序图，完整呈现了一次批次执行的端到端交互过程。ExecutionSession 首先选择当前要执行的 batch，然后创建 SDK Conversation 并注入消息。Conversation 调用 run_until_gate 启动门控轮询。在对话过程中，Orchestrator Agent 调用 run_executor 自定义工具并传入任务 JSON 路径。run_executor 将请求派发到对应的 _run_node 执行流程，后者通过 Verilator MCP 依次执行 compile 和 simulate 操作。仿真结果以 JSON summary 的形式逐层回传，最终构建为结构化的 Observation 反馈给 Agent。ExecutionSession 在收到结果后，比对 expected_artifacts 并执行 hooks，决定是否进入下一个 gate。

第二张是完整的编排状态机 UML 图，展示了系统的十个状态和它们之间的转移关系。流程从 SPEC_INTAKE 开始，依次经过 ARCHITECTING 和 PLANNING（均使用 thinking 推理配置且禁止委派子 Agent），然后进入 MODULE_DESIGN、MODULE_L0 和 MODULE_L1（切换为 fast 执行配置并允许委派模块工作者）。如果模块需要 L2 鲁棒性测试，则进入 MODULE_L2_OPTIONAL 状态；否则直接进入 INTEGRATION_READY，随后执行 INTEGRATION_REGRESSION（回到 thinking 配置），最终到达 DONE 终态。

这两张图共同论证了本课题的第一个核心创新点：框架控制与提示词控制的根本区别。在 AutoGen 等传统方案中，执行进度由 LLM 的输出决定——模型说"验证通过了"系统就继续推进，这属于 Prompt-controlled 架构。而在本系统中，状态机拥有控制权，每一步状态转移必须满足框架定义的前置条件（如所有 Checkpoint 通过），LLM 无法绕过验证门控"提前宣布成功"。

### 4.3 任务规划与知识注入（Slide 15）

第十五页展示了两个关键机制：可组合的提示词架构和 DAG 拓扑规划。

第一张图以色彩编码的方式展示了提示词的组合架构。最上方红色边框的 BaseContract 定义了五条不可违反的硬约束：AES_SCOPE_CONTRACT 界定设计范围、STRUCTURED_IO_CONTRACT 约束输入输出格式、NO_RAW_VERILATOR_CONTRACT 禁止直接调用 Verilator、SKILLS_AS_AUTHORITY_CONTRACT 确立技能文件的权威性、FRAMEWORK_OWNS_PROGRESS 声明框架对进度的控制权。第二行蓝色边框的 PhaseMixin 定义了九条可按阶段组合的软约束，覆盖了从生成到验证到修复到 L2 测试的各个执行阶段。中间黄色边框的 InstancePayload 提供了每次任务的实例化信息，如可写文件列表和模块特有的 hints。下方绿色边框的 Skill References 和 Memory Block 分别注入领域知识和验证通过的参考代码。所有组件通过 compose_prompt() 函数聚合为最终的 System Prompt。

第二张图展示了 AES-128 的模块依赖 DAG。三层拓扑结构用不同颜色清晰区分：绿色的 Layer 1 只有 aes_sbox 一个叶子节点；蓝色的 Layer 2 包含 aes_key_schedule_128 和 aes_round_transform 两个互相独立的节点，它们都依赖 aes_sbox，可以并行执行；黄色的 Layer 3 是顶层汇聚节点 aes128_encrypt_core，依赖前面所有子模块，拥有六个 Checkpoint。

知识注入的核心在于 Memory 预填充机制：MemoryStore 从 Skill 文件中检索验证通过的参考 RTL 和 Testbench 代码，通过 populate_workspace() 写入 Agent 的工作区。这将 Agent 的任务从"从零生成正确的 RTL 代码"降级为"基于验证通过的参考代码进行适配"，显著降低了生成难度。实验结果也证实了这一策略的有效性：全部四个模块均在首次生成后直接通过验证，修复轮次为零。

### 4.4 批次调度机制（Slide 16）

第十六页通过两张流程图详细展示了 DAG 拓扑批调度的实现。

第一张是批次执行主循环的流程图。循环从收集当前状态（读取各模块的验证结果和晋升记录）开始，进入 Gate 评估环节。如果所有模块都已成功，则终止并输出 SUCCESS；如果有模块被阻塞且无法恢复，则终止并输出 BLOCKED；否则继续选择下一个可执行的 batch。选中 batch 后，首先检查其上游依赖是否已全部晋升：如果没有，则推迟到下一次迭代；如果已经具备条件，且所有单模块都已晋升但集成测试尚未通过，则构建集成回归批次。准备就绪的 batch 进入 gated conversation 执行，完成后进行后处理——验证产出文件和执行 hooks。如果 batch 执行失败，则级联阻塞其所有下游依赖模块；如果成功，则检查预算后回到循环起点。

第二张是 Workflow Gate 评估的完整决策树。_evaluate_workflow_gate() 函数首先调用 _autonomous_completion_summary() 收集所有必需模块的状态，将每个模块分类为 promoted（已晋升）、blocked（被阻塞）、cascade_blocked（级联阻塞）或 pending（待处理）。然后从 deterministic_execution.json 中读取集成测试状态，最后进入六条分支的决策逻辑：成功完成、协议违规阻塞、必需模块阻塞、继续执行下一批次、就绪进入集成测试、无可用批次阻塞。决策结果被写入 workflow_gate.json 文件。

这里体现了一个重要的设计原则：文件系统门控。每个 batch 的"通过"条件不是 LLM 说通过就通过，而是框架检查 promoted 目录下是否存在对应模块的验证通过文件。这是框架控制的具体体现——由文件系统事实而非 LLM 输出决定批次推进。

### 4.5 子功能模块实现（Slide 17）

第十七页展示了 AES-128 验证案例中四个子模块的具体实现细节。aes_sbox 实现了 FIPS-197 规范的 S-box 替换表，将 8 位输入映射到 8 位输出，是纯组合逻辑，通过 CHK_SBOX_MATCH 检查点验证。aes_key_schedule_128 实现了 128 位密钥的 10 轮轮密钥扩展，通过 CHK_ROUNDKEY_MATCH 与 NIST 已知答案测试向量对比验证。aes_round_transform 实现了 AES 单轮变换的四个步骤——SubBytes、ShiftRows、MixColumns 和 AddRoundKey，通过 CHK_ROUND_STATE_MATCH 验证变换结果。顶层模块 aes128_encrypt_core 实例化以上三个子模块，采用迭代微架构实现完整的 10 轮 AES-128 加密，11 个时钟周期完成一次加密并产生单周期 done 脉冲，拥有六个 Checkpoint 覆盖 FSM 的完整生命周期。

### 4.6 MCP Tool 仿真（Slide 18）

第十八页说明了 Agent 如何与 Verilator 仿真器交互。核心组件是 VerilatorMCPAdapter——一个异步 MCP 适配器，负责将框架的验证请求转换为 Verilator 的编译和仿真操作。Agent 通过调用 run_executor 自定义工具发起请求（这是唯一合法入口），run_executor 根据任务类型分发到对应的执行器，执行器通过 Adapter 发起 MCP 调用。Adapter 负责预处理工作——过滤非 Verilog 文件、自动生成 -I 包含路径标志、添加 C++17 编译标志，然后通过 stdio 管道与 Node.js MCP Server 通信，调用 verilator_compile 和 verilator_simulate 两个工具。仿真完成后，从 simulation.log 中解析 Checkpoint 行，生成结构化的验证结果。

MCP 层还实施了工具白名单过滤：只允许 verilator_compile 和 verilator_simulate 两个工具，屏蔽了 testbenchgenerator 和 naturallanguage 等存在风险的工具入口，防止 Agent 绕过框架的结构化流程。

### 4.7 四层执行器与修复循环（Slide 19）

第十九页是项目实施部分的收尾，通过两张流程图展示了四层分级验证执行器和结构化修复循环。

第一张图展示了修复循环的完整流程。当验证失败后，系统首先选择修复目标（RTL 文件或 Testbench），然后生成修复请求（包含基线哈希和约束条件），派发给 Repair Agent。Repair Agent 读取请求后编辑目标文件，编辑完成后框架进行验证——检查文件哈希是否发生变化以及必需的 token 是否存在。如果验证通过，记录 Edit Receipt 并重新运行 L0+L1 验证；如果重新验证也通过，则晋升工作区；如果任何一步失败，检查修复预算是否耗尽——有余量则继续循环，耗尽则标记为 BLOCKED。图中 Repair Agent 用黄色背景突出标识，表示这是 LLM 操作的区域；Framework Verify 用蓝色边框标识，表示这是框架控制的验证节点。SHA-256 哈希验证的设计确保了修复编辑确实修改了目标文件，防止 Agent 声称"已修复"但实际未做任何更改。

第二张图展示了 run_executor 工具的完整分发流程。Agent 调用 run_executor 后，系统根据模式分发到四条不同的路径：Generate 模式初始化工作区并预填充 Memory，然后编译仿真；Validate 模式直接运行验证；Repair 模式记录并验证修复编辑；Integration 模式执行集成回归，运行 baseline、back-to-back 和 mid-reset 三个 Campaign。所有涉及编译和仿真的路径最终都通过 Verilator Adapter 经 MCP Server 执行，验证通过则晋升工作区，失败则标记待修复。

四层执行器形成了逐级递进的验证体系：L0 编译门控在秒级时间内快速拦截语法错误和类型不匹配；L1 在编译成功后执行仿真并解析 Checkpoint，验证功能正确性；L2 使用随机向量和边界条件进行鲁棒性测试；Integration 在所有模块晋升后运行三种 Campaign 验证全系统的正确性和可靠性。

---

## 五、第四章：总结与展望（Slides 20-22）

### 5.1 LED 流水灯案例（Slide 21）

为了验证框架的通用性，汇报首先展示了一个简单案例——LED 流水灯。这是一个单模块设计，DAG 仅有一个节点，没有模块间依赖。通过编写 led_chaser/blueprint.yaml，框架无需修改核心代码即可适配这个新设计，验证了蓝图驱动机制的通用性、状态机的基本流转以及 L0+L1 验证链路的端到端工作能力。这个"最小可验证设计"证明了框架的核心流程不依赖于 AES-128 的特定实现。

### 5.2 AES-128 全系统案例（Slide 22）

AES-128 加密全系统是本课题的核心验证案例。实验结果全面而有力：在单模块验证方面，全部四个模块均在首次生成后直接通过 L0 编译与 L1 Checkpoint 验证，修复轮次为零，首次通过率达到 100%。在集成回归测试方面，baseline（NIST 标准 KAT 向量）、back_to_back（连续多帧加密）和 mid_reset（加密过程中异步复位）三个 Campaign 全部通过，顶层模块六个 Checkpoint 无一遗漏。在框架控制有效性方面，16 个执行批次中有 11 个修复批次因 condition_false（首次已通过）被自动跳过，所有推进决策均由状态机和 Checkpoint 判定驱动，LLM 始终无法绕过验证门控。

---

## 六、核心创新点与整体评价

### 6.1 三大创新点

本课题针对现有 LLM+EDA 方案的五个不足（Prompt 控制不可靠、线性 pipeline 无法处理依赖、缺乏结构化修复、验证层级单一、LLM 约束工程不足），提出了三个核心创新点。

第一个创新是框架控制的编排状态机。通过将控制权从 LLM 转移到十状态的编排状态机，配合 AgentExecutionPolicy 实现精确的行为边界控制，每个状态映射到确定的 LLM 配置和子 Agent 委派策略。全局决策阶段使用 thinking 推理配置以获得更强的推理能力，局部执行阶段使用 fast 配置以获得更快的响应速度。

第二个创新是 L0 到 L1 到 L2 再到 Integration 的四层分级验证体系。从编译门控到功能仿真到鲁棒性测试再到集成回归，层层门控递进，Checkpoint 协议实现了机器自动判定，消除了对人工审查的依赖。

第三个创新是 Harnessing Engine 六层 LLM 约束引擎。Skill 层注入领域知识、Prompt 层通过可组合架构控制行为边界、Memory 层将生成任务降级为适配任务、Hooks 层通过 SHA-256 哈希验证修复编辑、MCP 层通过工具白名单过滤危险入口、SlashCommand 层提供带 dry-run 预览的 CLI 命令。六层协同覆盖了幻觉端口、语法错误、Scope Drift、过度修改和格式错误五种典型 LLM 失败模式，相比仅依赖单一 system_message 的传统方案实现了质的飞跃。

### 6.2 整体评价

从演示文稿的质量来看，内容完整性和逻辑连贯性方面表现优秀，四章结构从背景到技术到实施到结果形成了严密的叙事闭环。技术深度方面，对 DeepSeek MoE/MLA 架构、MCP 协议集成和状态机设计等核心技术均有深入到数学公式和张量维度层面的分析。创新展示方面，三大创新点均有明确的图示支撑和实验数据验证。

建议可进一步优化的方面包括：Slide 20 中存在"总结与总结"的文字笔误应修正为"总结与展望"；Slides 10-11 的 Prefill/Decode 数据流目前主要为文字描述，建议补充完整的数据流图；Slide 22 的实验结果建议补充全流程执行时间和 Token 消耗量等量化指标；此外，presentation_script.md 中提到的三张 Mermaid 补充架构图（MCP Adapter 数据流、Harnessing Engine 六层架构、核心创新点循环关系）建议实际插入到演示文稿中，以进一步增强技术表达的完整性。

### 6.3 关键数据汇总

整个项目涉及四个 AES-128 功能模块、三层 DAG 拓扑结构、十个状态机状态、九个验证 Checkpoint、五种 Agent 角色、十六个技能文件、四层验证执行器、三种集成回归 Campaign 和六层约束引擎。在 AES-128 全系统验证中实现了 100% 的首次通过率和零修复轮次，三个集成回归 Campaign 全部通过。DeepSeek 模型总参数量为 671.025B，其中 MoE 模块占比 98.02%。这些数据共同证明了本课题所提出的多 Agent FPGA 自动化设计框架在正确性、可靠性和通用性方面的有效性。
