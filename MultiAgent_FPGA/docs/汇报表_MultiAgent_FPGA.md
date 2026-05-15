# 毕业设计汇报表

> **题目**：基于 OpenHands SDK 的 Multi-Agent FPGA 自动化设计系统
> **汇报人**：贾阔源 | **指导老师**：刘亚男
> **日期**：2026 年 4 月

---

## 一、演示文稿总览

| 属性 | 说明 |
|------|------|
| 总页数 | 22 页（含 4 页目录过渡页） |
| 章节划分 | ① 研究背景及意义（Slides 3-5）② 关键技术框架（Slides 7-11）③ 项目具体实施（Slides 13-19）④ 总结与展望（Slides 21-22） |
| 图片总量 | 46 张（含重复出现的校徽/Logo 约 20 次，核心技术图 26 张） |
| 核心创新点 | 3 个：框架控制的编排状态机、L0→L1→L2→Integration 四层分级验证、Harnessing Engine 六层 LLM 约束引擎 |

---

## 二、逐页详细分析

### Slide 1 — 封面页

| 项目 | 内容 |
|------|------|
| **页面类型** | 标题幻灯片 |
| **标题** | 基于 OpenHands SDK 的 Multi-Agent FPGA 自动化设计系统 |
| **副标题** | 汇报人：贾阔源 指导老师：刘亚男 |
| **图片** | 1 张校徽/Logo（PNG，18KB），居中放置于标题上方 |
| **视觉布局** | 四角装饰矩形 + 圆角矩形主框架，居中文本排版，简洁学术风格 |

**要点**: 封面页遵循标准学术汇报模板，清晰呈现课题名称、汇报人与指导老师信息。

---

### Slide 2 — 目录页

| 项目 | 内容 |
|------|------|
| **页面类型** | 目录导航 |
| **章节** | 01 研究背景及意义 / 02 关键技术框架 / 03 项目具体实施 / 04 总结与展望 |
| **图片** | 无 |
| **视觉布局** | 四个圆形编号（01-04）配对文字说明，2×2 网格布局 |

**要点**: 四章结构清晰，从背景→技术→实施→总结形成完整叙事闭环。

---

### Slide 3 — 大语言模型发展的关键节点

| 项目 | 内容 |
|------|------|
| **页面类型** | 时间线图 |
| **图片** | 1 张校徽 + 页面内由形状元素（椭圆节点、连接线、矩形文本框）构建的时间线 |
| **时间节点** | 20世纪 → 2003 → 2014 → 2015 → **2017**（Transformer）→ 2018 → 2024 → 2025 |
| **关键里程碑** | n-gram 统计模型 → 神经网络语言模型（Bengio）→ Seq2Seq → Attention 机制 → **Transformer 架构**（革命性突破）→ GPT/BERT → DeepSeek → 智能体工程元年 |

**图片深度分析**:
- 时间线以垂直中轴线为主干，左右交替排列 8 个关键节点
- 每个节点由圆形标记 + 箭头连接 + 矩形文本框组成
- 2017 年 Transformer 节点被特别强调（"革命性突破"），这是后续所有大模型的基石
- 2025 年标注为"智能体工程元年"，直接引出本课题的立项背景

**汇报意义**: 通过回溯 LLM 发展史，建立了课题的时代背景——2025 年 Agent 框架爆发为本课题提供了技术基础和时代机遇。

---

### Slide 4 — Harnessing Engineering（驾驭工程）

| 项目 | 内容 |
|------|------|
| **页面类型** | 对比图 + 概念引入 |
| **图片** | 1 张校徽 + 1 张核心对比图（JPG，74KB）："Validation Without Harness vs. With Harness" |

**图片深度分析 — "Validation Without Harness vs. With Harness"**:

这是本课题最具说服力的概念图之一，采用左右对比布局：

| 维度 | Without Harness（左侧） | With Harness（右侧） |
|------|-------------------------|---------------------|
| **流程** | Agent写代码 → Human Review（发现错误）→ Agent修复 → Human Review Again（又有问题）→ Agent再修复 → Human确认OK | Agent写代码 → Hook自动Lint+TypeCheck（结构化JSON反馈）→ Agent一次性修复 → Hook验证通过 |
| **交互轮次** | 3 轮 | 1 轮 |
| **Token消耗** | ~2,000 tokens | ~50 tokens |
| **人工介入** | 需要人工反复审查 | 零人工介入 |
| **底部结论** | "3 rounds · ~2,000 tokens of dialogue · human blocked" | "1 round · ~50 tokens · zero human involvement" |

- 左侧流程用**红色/暖色调**标注 Human Review 节点，暗示人工瓶颈
- 右侧流程用**绿色/冷色调**标注 Hook 自动化节点，暗示高效自动化
- 底部总结："Hooks compress multi-turn dialogue into automated signals — **same result, 1/40 the context cost**"

**汇报意义**: 以直观的视觉对比论证了 Harnessing Engineering 的核心价值——通过六层结构化约束框架，将 LLM 的不可靠行为（幻觉、scope drift、虚假成功声明）从外部工程化地约束，而非依赖 LLM 的"自律性"。这是本课题的**第三个核心创新点**。

---

### Slide 5 — 大语言模型在 EDA 领域的应用

| 项目 | 内容 |
|------|------|
| **页面类型** | 文献综述 + 研究定位 |
| **图片** | 1 张校徽 + 2 张核心图 |

**图片 1 — MCP-EDA Workflow（252KB）**:
- 展示了 MCP4EDA 论文的系统架构
- 三列布局：**MCP Host**（多个 MCP Client + LLM）→ **MCP Server**（Simulation / Synthesis / Backend）→ **Tools**（Icarus Verilog / GTKWave / Yosys / OpenLane / KLayout 等）
- 通信模式：Post/Response（Client↔Server），Call/Response（Server↔Tools），Send context/Tool Request/Feedback（LLM↔Server）
- 这展示了 MCP 协议在 EDA 领域的端到端自动化能力——从 RTL 到 GDSII

**图片 2 — Spec2RTL-Agent Pipeline（239KB）**:
- 展示了 Spec2RTL-Agent 论文的端到端 RTL 生成流程
- 三阶段色块划分：**Understanding**（红色）→ **Coding**（绿色）→ **Reflection**（蓝色）
- 流程节点：Design Specifications → Understanding and Architecting → Proposed Arch → Coding → Function-wise Implementation → HLS Tool → Design Reflection → Final Implementation
- 上方标注对比：BetterV & CraftRTL 仅自动化 Coding 阶段，AutoChip & VerilogCoder 仅自动化 Reflection 阶段
- **Spec2RTL-Agent 的定位**：端到端自动化 Understanding + Coding + Reflection 全部三个阶段
- 底部两条反馈箭头：Architecture Improvement 和 Code Fix，形成迭代闭环

**汇报意义**: 通过两篇代表性论文定位了当前 LLM+EDA 的研究前沿，同时指出了它们的不足（模块间依赖处理不足、验证层级单一、LLM 约束不够），为本课题的创新空间做了铺垫。

---

### Slide 6 — 目录页（过渡到第二章）

| 项目 | 内容 |
|------|------|
| **页面类型** | 过渡页 |
| **高亮** | "02 关键技术框架" |

---

### Slide 7 — OpenHands 平台概览

| 项目 | 内容 |
|------|------|
| **页面类型** | 平台架构介绍 |
| **图片** | 1 张校徽 + 1 张 OpenHands 平台全景架构图（730KB，全页占满） |

**图片深度分析 — OpenHands Event Stream 架构**:

这是一张信息密度极高的全景架构图，展示了 OpenHands 的核心运行机制：

- **左侧 — 用户交互入口**：User Interface（Command Line / Web UI / IDE Plugins）→ Multi-turn User-Agent Interaction
- **中央 — Event Stream**：所有 Action-Observation 的追踪中心，编号展示了完整的交互序列：
  - `[1] Message (source=user)` — 用户发出请求
  - `[2] IPythonRunCellAction` — Agent 创建文件
  - `[3] IPythonRunCellObservation` — 文件创建结果
  - `[4] IPythonRunCellAction` — Agent 编写服务器代码
  - `[5] IPythonRunCellObservation` — 代码执行结果
  - `[6] CmdRunAction` — Agent 运行命令
  - `[7] CmdRunObservation` — Flask 服务器启动
  - `[8] BrowseInteractiveAction` — Agent 浏览器访问
  - `[9] BrowserOutputObservation` — 页面输出结果
- **左下 — Agent 抽象**：Event History → Agent (produce new action) → Action → Abstraction 定义
- **右侧 — Agent Runtime**：Docker Sandbox 内含 Action Execution API → Interactive Python Server / Bash Shell / Browser (Playwright Chromium)

**汇报意义**: 展示了选择 OpenHands SDK 的核心原因——其原生支持自定义工具注册和 MCP 集成，使得 Verilator 仿真器可以作为 Agent 可调用的工具接入，实现"Agent 写代码 → 框架自动编译仿真 → 解析结果 → 反馈 Agent"的闭环。

---

### Slide 8 — OpenHands SDK 细节

| 项目 | 内容 |
|------|------|
| **页面类型** | SDK 模块详解 |
| **图片** | 1 张校徽 + 2 张架构图 |

**图片 1 — OpenHands SDK 模块功能表（152KB）**:

| 模块 | 作用与接口 | 关键特点 |
|------|----------|---------|
| Planning & Decision Engine | 生成计划与决策，决定调用工具或子 Agent | Prompt + 自然语言反馈，支持 CodeAct/ReAct |
| Memory | 对话历史、执行结果、外部知识存储 | RAG 检索、记忆压缩、层级存储 |
| Planner | 规则/动态/混合规划器 | 规则模板或 LLM 动态生成计划 |
| Tool Module | 对接外部工具，function call 映射 | 工具调用标准化，闭环反馈 |
| Reflection Module | 模型行为检查与修正 | ReAct、Reflexion 策略 |
| Event Bus (EventStream) | 发布-订阅系统 | 模块解耦、异步运行 |
| Runtime Sandbox | Docker 隔离工作空间 | 安全、稳定、可复现 |
| AgentController | 框架"指挥官"，迭代循环管理 | 独立状态、心跳、异常处理 |
| Server & Session | WebSocket 接口，会话管理 | 会话创建、恢复、持久化 |

**图片 2 — OpenHands 后端架构图（232KB）**:
- 数据流：用户 → 前端(单页应用) → HTTP/WS → OpenHands 后端
- 后端分支：事件流 / 存储 / 大语言模型提供者
- Runtime 区域（绿色背景）：运行时接口 → Docker运行时 / 本地运行时 / 远程运行时 → 动作执行服务器 → Bash会话 / Jupyter插件 / 浏览器环境

**汇报意义**: 详细展示了 OpenHands SDK 的 9 大核心模块，说明了 5 种 Agent 角色（Workflow Orchestrator / Finalizer Orchestrator / Module Worker / Repair Worker / L2 Campaign Agent）的分层委派设计基础。

---

### Slide 9 — DeepSeek MoE 架构

| 项目 | 内容 |
|------|------|
| **页面类型** | 技术深入解析（信息密度最高的一页） |
| **图片** | 1 张校徽 + **11 张技术图**（含架构图、对比图、参数表、数学公式图等） |

**图片 1 — DeepSeek 完整架构图（266KB）**:
- **左侧 — Transformer Block × L**：标准堆叠结构 RMSNorm → Attention → RMSNorm → Feed-Forward Network，带残差连接
- **右上 — DeepSeekMoE**：Input Hidden u_t → Router（TopK_r 选择）→ Shared Experts (1...N_s, 绿色) + Routed Experts (1...N_r, 蓝色) → 加权求和 → Output Hidden h'_t
- **右下 — Multi-Head Latent Attention (MLA)**：Input Hidden h_t → Latent c_t^Q（Q 压缩）+ Latent c_t^KV（KV 压缩，**Cached During Inference**）→ 各自展开为多头 → RoPE 位置编码 → concatenate → Multi-Head Attention → Output

**图片 2 — Dense vs Sparse MoE 对比（134KB）**:
- **(a) Dense model**：Norm → Attention → Norm → FFN（残差连接），所有参数全部激活
- **(b) Sparse MoE model**：Norm → Attention → Norm → Gate → 路由到 Shared + 部分 Routed Experts (a-f, 蓝色高亮表示被激活)，仅部分参数激活

**图片 3 — DeepSeek 参数分布表**:

| 模块/子组件 | 总参数(B) | 参数占比 |
|------------|----------|---------|
| Embedding | 0.904 | 0.14% |
| MLA | 11.4134 | 1.70% |
| MoE (模块合计) | 654.480 | **98.02%** |
| ├── Shared Expert | 0.267 | - |
| ├── Routed Expert | 654.106 | - |
| └── Router | 0.106 | - |
| Output | 0.927 | 1.83% |
| **总计** | **671.025** | **100%** |

**图片 4 — MoE 核心思想图示**:
- "一个稠密大矩阵 ⇒ 数百个稠密小矩阵 + 每次只激活 6~8 个"
- 直观概括了 MoE 的稀疏计算核心理念

**图片 5 — MLA 数学流程图（237KB）**:
- 从输入 x 分两路：W_q·W_UK^T（Query 路径）和 W_DKV（KV 压缩路径+Cache）
- 计算注意力分数：q'' = x^T·W_q·W_k^T，与 X^T·W_DKV 做点积 → softmax → 加权求和 → W_UV·W_o 输出
- 底部公式：W_k' = W_DKV·W_UK，W_v' = W_DKV·W_UV（吸收分解）

**图片 6 — MLA 数学公式**:
- c_t^KV = W^DKV · h_t（KV 压缩到低维潜在空间）
- k_t^C = W^UK · c_t^KV（从潜在空间恢复 K）
- k_t^R = RoPE(W^KR · h_t)（位置编码分支）
- k_{t,i} = [k_{t,i}^C ; k_t^R]（拼接）
- v_t^C = W^UV · c_t^KV（从潜在空间恢复 V）

**汇报意义**: 这是技术深度最大的一页，完整展示了 DeepSeek 的 MoE + MLA 双核心创新。MoE 通过稀疏激活实现高性价比推理（671B 总参数但每次仅激活少量专家），MLA 通过 KV 压缩大幅降低长上下文的显存占用，两者共同使 DeepSeek 成为 Agent 自动化流水线的理想 LLM 后端。

---

### Slide 10 — DeepSeek Prefill 阶段数据流

| 项目 | 内容 |
|------|------|
| **页面类型** | 数据流详解（Prefill） |
| **图片** | 1 张校徽（本页主要为文本描述+形状构建的数据流） |

**关键内容**:
- Prefill 阶段处理完整输入序列，所有 token 并行处理
- 张量维度变化：输入 (b, s, 7168) → Q_down-proj 压缩到 (b, s, 1536) → Q_up-proj 扩展为 128 头 × 192 维
- MLA 中 KV 投影到低维空间：512 维的 kv_nope + 64 维的 k_rope
- MoE 层中 TopK Router 选择活跃专家后，gate/up 分支经 SiLU 激活 + down_Linear

---

### Slide 11 — DeepSeek Decode 阶段数据流

| 项目 | 内容 |
|------|------|
| **页面类型** | 数据流详解（Decode） |
| **图片** | 1 张校徽 |

**关键内容**:
- Decode 阶段逐个生成 token，与 Prefill 的两个关键区别：
  1. 序列维度从 s 变为 1：(b, s, 7168) → (b, 1, 7168)
  2. 引入 KV Cache：K_cat + K_Cache，V + V_Cache，注意力 KV 序列长度为 s+1
- **对 Agent 系统的意义**：编排器的系统提示（合约+技能文档）消耗 Prefill 算力，Agent 交互式推理消耗 Decode 算力；MLA 的 KV Cache 压缩使多轮修复对话更高效

---

### Slide 12 — 目录页（过渡到第三章）

| 项目 | 内容 |
|------|------|
| **页面类型** | 过渡页 |
| **高亮** | "03 项目具体实施" |

---

### Slide 13 — 项目架构

| 项目 | 内容 |
|------|------|
| **页面类型** | 系统全景架构 |
| **图片** | 1 张校徽 + 1 张六层架构全景图（113KB，全幅横向排列） |

**图片深度分析 — 六层系统架构图**:

采用自顶向下的层次布局：

```
CLI Entry (main.py)
  ├── validate / smoke-sdk / smoke-provider / run-node / run-aes-mvp
  │
  ▼
Runtime Layer (runtime/)
  ├── sdk_shim.py    ├── bootstrap.py   ├── factory.py
  ├── runner.py      ├── session.py     ├── context_assembler.py
  └── execution_tools.py
  │
  ├────────────────────┼─────────────────────┐
  ▼                    ▼                     ▼
Agent Layer          Execution Layer       Synthesis Layer
├── agents/specs.py  ├── executors/        ├── synthesis.py
├── prompts.py       ├── adapters/         ├── artifacts.py
├── prompt_contracts/ ├── verilator/       ├── policy.py
├── skill_refs.py                          ├── executor_contracts.py
└── memory.py                              └── generation.py
```

- 浅黄色背景标识每一层的边界
- 淡紫色方框标识每个具体文件/模块
- 箭头明确展示了层间依赖关系：CLI → Runtime → (Agent + Execution + Synthesis)

**汇报意义**: 展示了清晰的关注点分离——每层只负责一个维度的职责，层间通过 Pydantic 数据契约通信，这是工程质量的保证。

---

### Slide 14 — 项目工作流程

| 项目 | 内容 |
|------|------|
| **页面类型** | 流程图 + 状态机 |
| **图片** | 1 张校徽 + 2 张核心图 |

**图片 1 — 端到端序列图（83KB）**:

六个参与者的时序交互：
```
ExecutionSession → SDK Conversation → Orchestrator Agent → run_executor → _run_node/L0+L1 → Verilator MCP
```
- ExecutionSession 选择 batch，创建 Conversation + 消息
- SDK Conversation 调用 run_until_gate
- Orchestrator Agent 调用 run_executor(task JSON path)
- run_executor 派发到 _run_node / L0+L1
- L0+L1 通过 Verilator MCP 执行 compile / simulate
- JSON summary 逐层返回 → Observation 回到 Agent
- ExecutionSession 比对 expected_artifacts、执行 hooks、进入下一 gate

**图片 2 — 编排状态机（95KB）**:

完整的 10 状态 UML 状态图：
```
● → SPEC_INTAKE [thinking profile]
     → ARCHITECTING [thinking profile]
       → PLANNING [thinking profile]
         → MODULE_DESIGN [fast profile]
           → MODULE_L0 [fast profile]
             → MODULE_L1 [fast profile]
               ├─ requires_l2=true → MODULE_L2_OPTIONAL [fast profile]
               └─ requires_l2=false ─┐
                                      ▼
                    INTEGRATION_READY [thinking profile]
                      → INTEGRATION_REGRESSION [thinking profile]
                        → DONE ◎
```
- 左侧黄色注释框说明：SPEC_INTAKE ~ PLANNING 使用 thinking profile + subagent_policy=forbidden
- 右侧黄色注释框说明：MODULE_DESIGN ~ MODULE_L1 使用 fast profile + subagent_policy=module_worker_allowed

**汇报意义**: 核心论证了"**框架控制 vs. 提示词控制**"的根本区别——状态转移由框架定义的前置条件决定，LLM 无法绕过验证门控"提前宣布成功"。

---

### Slide 15 — 任务规划和知识注入

| 项目 | 内容 |
|------|------|
| **页面类型** | DAG + Prompt 组合架构 |
| **图片** | 1 张校徽 + 2 张核心图 |

**图片 1 — 提示词组合架构图（70KB）**:

六层组件汇聚到最终系统提示：

| 层级 | 组件 | 颜色 |
|------|------|------|
| **BaseContract — Hard Constraints**（红色边框） | AES_SCOPE_CONTRACT / STRUCTURED_IO_CONTRACT / NO_RAW_VERILATOR_CONTRACT / SKILLS_AS_AUTHORITY_CONTRACT / FRAMEWORK_OWNS_PROGRESS | 红色 |
| **PhaseMixin — Soft Constraints**（蓝色边框） | WORKER_LOCAL_SCOPE / WORKER_REQUEST_AUTHORITY / RUN_EXECUTOR_PHASE / GENERATE_PHASE / VALIDATE_PHASE / REPAIR_PHASE_ROUND_1/2+ / L2_PHASE / MEMORY_CONSULTATION_DIRECTIVE / REPAIR_MEMORY_DIRECTIVE | 蓝色 |
| **InstancePayload**（黄色边框） | Per-task lines: writable files, module-specific hints | 黄色 |
| **Skill References**（绿色边框） | build_skill_reference_block() + ORCHESTRATOR/WORKER/REPAIR_CORE_SKILL_KEYS | 绿色 |
| **Memory Block**（绿色边框） | MemoryStore.build_prompt_block() (generate mode only) | 绿色 |

所有组件通过 `compose_prompt()` 聚合为 **Final System Prompt**。

**图片 2 — AES-128 DAG 层次图（40KB）**:

三层拓扑结构，用颜色区分：
- **Layer 1**（绿色）：`aes_sbox` — CHK_SBOX_MATCH, L2: skip
- **Layer 2**（蓝色）：`aes_key_schedule_128` — CHK_ROUNDKEY_MATCH, L2: conditional + `aes_round_transform` — CHK_ROUND_STATE_MATCH, L2: conditional（**并行执行**）
- **Layer 3 — Top/Sink**（黄色）：`aes128_encrypt_core` — 6 checkpoints, L2: required

箭头表示依赖关系：Layer 1 → Layer 2 → Layer 3。

**汇报意义**: 展示了两个关键机制：(1) 可组合的提示词架构实现了精确的行为边界控制；(2) Memory 预填充将"从零生成"降级为"适配修改"，实现了 100% 首次通过率。

---

### Slide 16 — 批次调度

| 项目 | 内容 |
|------|------|
| **页面类型** | 流程图（双图） |
| **图片** | 1 张校徽 + 2 张流程图 |

**图片 1 — 批次执行主循环流程图（96KB）**:

完整的调度循环：
```
Loop Start → Collect State (Read results + promotions)
  → Evaluate Gate
    ├── success → SUCCESS ✓（绿色）
    ├── blocked → BLOCKED ✗（红色）
    └── continue → Select Next Batch
         → Upstream deps promoted?
           ├── No → Defer to next iteration
           └── Yes ─┐
                     ├── ready for integration → Build Integration Batch
                     └── Prepare Batch → Run Batch (gated conversation)
                         → Post-Process (Verify artifacts + hooks)
                           → Batch failed?
                             ├── No → [loop back]
                             └── Yes → Cascade-block dependents（红色）
                         → Check budget → [loop back]
```

**图片 2 — Workflow Gate 评估决策图（122KB）**:

`_evaluate_workflow_gate()` 的完整决策树：
1. `_autonomous_completion_summary()` 收集状态
2. 对每个必需模块分类：promoted / blocked / cascade_blocked / pending
3. 从 `deterministic_execution.json` 检查 integration_status
4. **Decision Logic** 六条分支：
   - `completion_status == success` → **decision: success**（绿色）
   - `protocol_violation != None` → **decision: blocked, reason: protocol_violation**（红色）
   - `completion_status == blocked` → **decision: blocked, reason: required_module_blocked**（红色）
   - `next batch available` → **decision: continue, next_batch_ids: list**（蓝色）
   - `all promoted, integration not passed, attempts <= 1` → **decision: ready_for_integration**（黄色）
   - `no eligible batches remaining` → **decision: blocked, reason: no_remaining_batches**（红色）
5. 写入 `workflow_gate.json`

**汇报意义**: 展示了**文件系统门控（Batch Gate）**的具体实现——批次推进由框架检查 promoted 目录下的验证通过文件决定，而非由 LLM 输出决定。

---

### Slide 17 — 子功能模块实现

| 项目 | 内容 |
|------|------|
| **页面类型** | 模块规格 |
| **图片** | 1 张校徽 + 1 张 DAG 层次图（与 Slide 15 相同，40KB） |

**模块详情**:

| 模块 | 功能 | Checkpoint | L2 策略 |
|------|------|-----------|---------|
| `aes_sbox` | FIPS-197 S-box 查找表，8bit→8bit 纯组合逻辑 | CHK_SBOX_MATCH | skip |
| `aes_key_schedule_128` | 128 位密钥的 10 轮轮密钥扩展 | CHK_ROUNDKEY_MATCH | conditional |
| `aes_round_transform` | AES 单轮变换：SubBytes+ShiftRows+MixColumns+AddRoundKey | CHK_ROUND_STATE_MATCH | conditional |
| `aes128_encrypt_core` | 顶层模块，迭代微架构，11 周期完成加密，单周期 done 脉冲 | 6 个 CHK_* | required |

---

### Slide 18 — MCP Tool 仿真

| 项目 | 内容 |
|------|------|
| **页面类型** | 技术架构说明 |
| **图片** | 1 张校徽（本页主要为文本描述） |

**关键内容**:
- **VerilatorMCPAdapter** 是核心组件：异步 MCP 适配器，将框架请求转换为 Verilator 操作
- `run_executor` 是 Agent 的**唯一合法执行入口**，Agent 不能直接调用 Verilator
- 预处理：过滤非 Verilog 文件、自动 `-I` 包含路径、C++17 编译标志
- 通过 stdio 管道与 Node.js MCP Server 通信
- **工具白名单**：仅允许 `verilator_compile` 和 `verilator_simulate`，屏蔽 `testbenchgenerator` 和 `naturallanguage`

---

### Slide 19 — Executor 执行器

| 项目 | 内容 |
|------|------|
| **页面类型** | 四层执行器 + 修复循环 |
| **图片** | 1 张校徽 + 2 张核心流程图 |

**图片 1 — 结构化修复循环流程图（69KB）**:

```
Validation Failed
  → Select Repair Target (RTL or testbench)
    → Write Repair Request (baseline hashes + constraints)
      → Dispatch to Repair Agent
        → [Repair Agent] Read request + edit target file
          → Framework Verify (hash changed? tokens present?)
            ├── Pass → Record Edit Receipt → Revalidate (L0+L1 re-run)
            │          ├── Pass → Promote Workspace ✓（绿色）
            │          └── Fail ──┐
            └── Fail ──────────────┤
                                   ▼
                           Budget remaining?
                             ├── Yes → [循环回 Dispatch]
                             └── No → BLOCKED ✗（红色）
```
- Repair Agent 用黄色背景突出，表示 LLM 操作区域
- Framework Verify 用蓝色边框，表示框架控制的验证节点
- SHA-256 哈希验证确保修复编辑确实修改了目标文件

**图片 2 — run_executor 工具分发流程图（75KB）**:

```
Agent calls run_executor
  → Dispatch by mode
    ├── Generate → Initialize Workspace + pre-populate memory → Compile + Simulate
    ├── Validate → Run Validation → Compile + Simulate
    ├── Repair → Record + Verify Repair Edit
    └── Integration → Integration Regression → Run Campaigns (baseline, back-to-back, mid-reset)
                                                   ↓
                                            Verilator Adapter
                                         Compile + Simulate via MCP server

  Compile + Simulate → Pass?
    ├── Yes → Promote Workspace（绿色）
    └── No → Flag for Repair（黄色）
```

**四层执行器总结**:

| 层级 | 名称 | 功能 | 速度 |
|------|------|------|------|
| L0 | 编译门控 | Verilator 编译检查，捕获语法/类型错误 | 秒级快速失败 |
| L1 | 仿真+Checkpoint | 编译+仿真+解析 CHECKPOINT 行 | 分钟级 |
| L2 | 鲁棒性测试 | 随机向量+边界条件，生成 counterexample.json | 分钟级 |
| Integration | 集成回归 | baseline + back_to_back + mid_reset 三 Campaign | 分钟级 |

**汇报意义**: 展示了"所有验证操作都经过框架统一管控"的核心设计——`run_executor` 是唯一入口，修复循环有明确的预算限制和哈希验证。

---

### Slide 20 — 目录页（过渡到第四章）

| 项目 | 内容 |
|------|------|
| **页面类型** | 过渡页 |
| **高亮** | "04 总结与展望"（注：页面文本有笔误"总结与总结"，应修正） |

---

### Slide 21 — 实验案例 1：LED 流水灯（简单案例）

| 项目 | 内容 |
|------|------|
| **页面类型** | 实验验证 |
| **图片** | 1 张校徽 |

**验证内容**:
- 单模块设计，DAG 仅一个节点，无模块间依赖
- 验证目标：蓝图驱动的通用性、状态机基本流转、L0+L1 验证链路
- **结论**：证明了框架核心流程不依赖于 AES-128 的特定实现

---

### Slide 22 — 实验案例 2：AES-128 加密算法（核心案例）

| 项目 | 内容 |
|------|------|
| **页面类型** | 核心实验结果 |
| **图片** | 1 张校徽 |

**实验结果汇总**:

| 验证维度 | 结果 | 详情 |
|---------|------|------|
| **单模块验证** | **100% 首次通过** | 4/4 模块首次生成即通过 L0 编译 + L1 Checkpoint，修复轮次 = 0 |
| **集成回归** | **3/3 Campaign PASS** | baseline（NIST KAT）、back_to_back（连续多帧）、mid_reset（异步复位）全部通过 |
| **顶层 Checkpoint** | **6/6 通过** | CHK_RESET_CLEAR / CHK_START_ACCEPTED / CHK_BUSY_ASSERTED / CHK_DONE_PULSE / CHK_CIPHERTEXT_MATCH / CHK_BUSY_DEASSERTED |
| **框架控制有效性** | **11/16 批次自动跳过** | 因 condition_false（首次已通过）被跳过，所有推进决策由状态机+Checkpoint 驱动 |

---

## 三、图片类型统计

| 图片类型 | 数量 | 代表页面 |
|---------|------|---------|
| 校徽/Logo（重复） | ~20 张 | 几乎每页右上角 |
| 系统架构图 | 5 张 | Slides 7, 8, 13, 15(prompt), 19(run_executor) |
| 流程图/状态机 | 6 张 | Slides 14(序列图+状态机), 16(批次循环+gate), 19(修复循环) |
| 对比图 | 2 张 | Slides 4(Harness对比), 9(Dense vs MoE) |
| 论文引用图 | 2 张 | Slide 5(MCP-EDA + Spec2RTL-Agent) |
| DAG 依赖图 | 2 张 | Slides 15, 17 |
| 模型架构图 | 4 张 | Slide 9(DeepSeek架构+MLA流程+参数表+MoE思想) |
| 数学公式图 | 2 张 | Slide 9(MLA公式+KV分解) |
| 功能表格图 | 2 张 | Slides 8(SDK模块表), 9(参数分布表) |
| 概念示意图 | 1 张 | Slide 9(稠密→稀疏) |
| **合计（去重后）** | **~46 张** | |

---

## 四、三大核心创新点总结

### 创新点 1：框架控制的编排状态机

| 维度 | 说明 |
|------|------|
| **问题** | 传统方案（如 AutoGen）中 LLM 输出决定执行进度（Prompt-controlled），LLM 可能虚假声明"验证通过" |
| **方案** | 10 状态编排状态机 + AgentExecutionPolicy 策略层 |
| **核心图** | Slide 14 状态机图、Slide 16 Gate 评估图 |
| **关键特征** | 状态转移必须满足框架定义的前置条件；thinking/fast profile 自动切换；subagent policy 精确控制委派权限 |

### 创新点 2：L0→L1→L2→Integration 四层分级验证

| 维度 | 说明 |
|------|------|
| **问题** | 现有方案验证层级单一，缺乏逐级门控 |
| **方案** | 四层递进验证 + Checkpoint 协议（`CHECKPOINT|<name>|PASS|<detail>`） |
| **核心图** | Slide 19 run_executor 流程图、Slide 19 修复循环图 |
| **关键特征** | L0 秒级快速失败；L1 仿真 Checkpoint 验证；L2 鲁棒性随机测试；Integration 三 Campaign 集成回归 |

### 创新点 3：Harnessing Engine 六层 LLM 约束引擎

| 维度 | 说明 |
|------|------|
| **问题** | LLM 本质不可靠（幻觉、scope drift、过度修改等），单一 system_message 约束不足 |
| **方案** | 六层深度防御：Skill / Prompt / Memory / Hooks / MCP / SlashCommand |
| **核心图** | Slide 4 Harness 对比图、Slide 15 Prompt 组合架构图 |
| **关键特征** | 覆盖 5 种典型失败模式；相比 AutoGen 的"1 层约束"，实现"6 层深度防御" |

---

## 五、演示文稿质量评估

| 维度 | 评分 | 说明 |
|------|------|------|
| **内容完整性** | ★★★★★ | 从背景到技术到实施到结果，叙事完整 |
| **技术深度** | ★★★★★ | DeepSeek MoE/MLA、MCP 协议、状态机设计等均有深入分析 |
| **图片质量** | ★★★★☆ | 核心架构图清晰，但 Slides 10-11 缺少 Prefill/Decode 数据流图 |
| **视觉一致性** | ★★★★☆ | 整体风格统一，但部分图片为外部论文截图，风格略有差异 |
| **逻辑连贯性** | ★★★★★ | 章节间过渡自然，每张 slide 都为结论服务 |
| **创新展示** | ★★★★★ | 三大创新点有明确图示支撑，实验数据有力 |

### 建议改进项

1. **Slide 20 文字修正**：将"总结与总结"修正为"总结与展望"
2. **Slides 10-11**：建议补充 Prefill/Decode 阶段的完整数据流图（当前主要为文字描述）
3. **Slide 22**：建议补充执行时间数据（如全流程耗时、Token 消耗量等量化指标）
4. **附录图**：presentation_script.md 提到 3 张 Mermaid 补充架构图（MCP Adapter、Harnessing Engine、核心创新点），建议实际插入 PPT

---

## 六、关键数据一览

| 指标 | 数据 |
|------|------|
| AES-128 模块数 | 4 个 |
| DAG 拓扑层数 | 3 层 |
| 状态机状态数 | 10 个 |
| Checkpoint 总数 | 9 个（sbox:1 + key_sched:1 + round_trans:1 + encrypt_core:6） |
| Agent 角色数 | 5 种 |
| 技能文件数 | 16 个（5 runtime + 5 memory + 6 doc-only） |
| 验证执行器层级 | 4 层（L0/L1/L2/Integration） |
| 集成回归 Campaign | 3 种（baseline / back_to_back / mid_reset） |
| 约束引擎层数 | 6 层 |
| 首次通过率 | 100%（4/4 模块） |
| 修复轮次 | 0 |
| DeepSeek 总参数 | 671.025B |
| MoE 参数占比 | 98.02% |
