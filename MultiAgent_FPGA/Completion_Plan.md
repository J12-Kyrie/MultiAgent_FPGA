# MultiAgent_FPGA AES Full-System 详细开发计划

## Summary

以 [Completion_Plan.md](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/Completion_Plan.md) 为最终目标，以当前 [aes_mvp](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp) 的已完成契约层为起点，分阶段把系统补完为“**真实可运行的 OpenHands SDK 多智能体 AES MVP**”。

当前可直接复用的基础已经存在：`SpecIR / PlanDAG / AgentExecutionPolicy / LLMConfig / prompt builders / skill refs / Verilator MCP adapter / state-machine skeleton`。开发重点不再是重新设计这些契约，而是把它们接成真实运行时，并补齐 AES RTL/TB、L0/L1/L2、integration regression、trace 和 CLI。

整个计划固定遵守以下不变约束：

- 请求模型名称始终是 `deepseek-v3.2`
- 记录当前解析后的 backend model 为 `deepseek-v3-2-251201`
- 推理提供方始终是 `https://api.chatfire.ai/v1`
- thinking 只通过 `completion_kwargs={"thinking": {"type": "enabled"}}`
- 主 Orchestrator 始终用 thinking profile
- `Module Worker` 和 `L2 Campaign SubAgent` 默认用 non-thinking profile
- Verilator 路径始终是 `verilator_compile -> verilator_simulate`
- 稳定测试路径始终是现成 `.cpp` self-checking TB
- MVP 范围始终是 `AES-128 / encrypt-only / block-handshake / iterative-10-round`
- 不进入 `L3`、不做 on-board、不断开当前 `aes_mvp` 子树另起一套实现

## Implementation Changes

1. **M0: 先把“知识层约束”补齐为可复用 skill 集合。**
   在现有 4 个 repo skills 之上，新增并冻结 5 个 OpenHands SDK skills：`openhands_sdk_bootstrap`、`openhands_sdk_skill_authoring`、`openhands_sdk_mcp_integration`、`openhands_sdk_subagent_delegation`、`openhands_sdk_observability`。它们只负责 OpenHands SDK 的稳定使用方法，不承载 AES 业务规则。完成标准是：所有 skill 可被 loader 解析、命名和职责边界稳定、能明确指挥后续 Codex App 任务，而不是停留在笔记层。

2. **M1: 把当前 `aes_mvp` 从 contract layer 升级为真正的 runtime composition root。**
   在 [MultiAgent_FPGA/aes_mvp](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp) 下增加真实运行时入口，固定实现 `RuntimeBootstrap`、`SdkAgentFactory`、`ConversationRunner`、`SdkImportShim` 四个职责。`RuntimeBootstrap` 负责加载 pinned Chatfire profiles、9 个 skills、policy、artifacts 和 Verilator MCP 配置；`SdkAgentFactory` 负责创建主 `Workflow Orchestrator`、`Module Worker SubAgent`、`L2 Campaign SubAgent`；`ConversationRunner` 负责把 agent step、tool call、observation 串成完整闭环；`SdkImportShim` 负责处理 `software_agent_sdk` 缺失时的 import guard 和测试替身模式。完成标准是：在 SDK 可用环境中可以真实创建 runtime；在 SDK 不可用环境中仍可跑 validate/smoke/unit tests，而不会把 contract layer 误报成 runtime。

3. **M2: 把现有 artifact/policy/prompt/skill refs 变成 runtime 的唯一真相源。**
   当前 [artifacts.py](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp/artifacts.py)、[policy.py](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp/policy.py)、[prompts.py](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp/prompts.py)、[skill_refs.py](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp/skill_refs.py)、[llm_profiles.py](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp/llm_profiles.py) 不需要重写，只需要被 runtime 真正消费。实现时固定要求：所有 agent 角色只能从 `AgentExecutionPolicy` 读取 profile 和 subagent policy；所有 prompt 只能基于 skill refs 生成；所有可写边界只能来自 `PlanDAGNode.rtl_files / tb_file / build_output_dir / sim_output_dir`；所有升级判断只能来自 `repair_attempt_threshold=2` 和 interface/state-machine/cross-module flags。完成标准是：planning 阶段绝不生成 subagent，module/L2 阶段的 spawn 行为与 `agent_execution_policy.json` 完全一致。

4. **M3: 完成 Verilator 执行服务和结果解析服务。**
   保留现有 [adapters/verilator.py](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp/adapters/verilator.py) 作为底层 MCP 适配器，在其上补 `L0Executor`、`L1Executor`、`L2CampaignExecutor`、`CheckpointParser`、`WaveformLocator`、`RunReportWriter`。`L0Executor` 只做 compile 和静态 gate；`L1Executor` 固定做 build reuse、simulate、checkpoint 解析；`L2CampaignExecutor` 只接受 `+vecfile / +seed / +cases / +profile` 四类 knob；`CheckpointParser` 只认 `simulation.log` 里的固定 `CHECKPOINT|...` 语法；`RunReportWriter` 统一生成 `ModuleRunResult / counterexample.json / fragility_summary.json`。完成标准是：Verilator 结果不再以自由文本在 runtime 内部流动，而是全部落到结构化运行结果对象和稳定文件路径。

5. **M4: 先打通顶层 vertical slice，再完成 4 节点拆解。**
   先实现 `aes128_encrypt_core` 顶层 RTL 和 `.cpp` testbench，优先跑通 `start/busy/done/ciphertext` 协议、11-cycle latency、KAT/zero/regress vectors 和 6 个固定 checkpoints。顶层 vertical slice 通过后，再按固定顺序实现并 reintegrate：`aes_sbox`、`aes_key_schedule_128`、`aes_round_transform`。这一阶段的硬规则是：模块 testbench 一律用 `.cpp`；不使用 `.sv`；不使用生成 testbench；顶层对外接口在整个阶段不再变化；抽子模块时不能改 `SpecIR`、不能改 `PlanDAG`、不能改 frozen checkpoint contract。完成标准是：4 个节点各自有真实 RTL/TB，且 reintegration 后顶层 regression 仍然全绿。

6. **M5: 补齐 conditional L2 和 integration regression。**
   L2 只在固定节点和固定 profile 上运行：`aes_sbox` 跳过，`aes_key_schedule_128` 和 `aes_round_transform` 走 `conditional`，`aes128_encrypt_core` 走 `required`。`back_to_back` 和 `mid_reset` 只允许顶层核使用。integration regression 固定以 `IntegrationRegressionManifest` 为唯一输入，始终验证 full vector corpus、11-cycle latency、ignore-while-busy、back-to-back、reset recovery。完成标准是：L2 的成功/失败都能输出结构化结果，integration regression 可以独立从 manifest 重放，不依赖人工解释。

7. **M6: 加入 observability、CLI 和端到端绿色路径。**
   为 runtime 增加 conversation-level trace、agent step trace、tool call trace、Verilator run trace，并把 raw observation 路径、`simulation.log`、`simulation.vcd`、checkpoint summaries、counterexample artifacts 统一挂到一个报告树中。把当前仅做 JSON 校验的 [__main__.py](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp/__main__.py) 升级为真正 CLI，固定提供 4 个子命令：`validate`、`smoke-sdk`、`run-node <module_id>`、`run-aes-mvp`。完成标准是：同一 CLI 既能做纯契约验证，也能在 SDK 存在时跑完整绿色路径，并且失败时能定位到具体阶段、模型 profile、subagent 角色和 Verilator 产物。

8. **M7: 用 Codex App 交付方式切分实施节奏，不跨 milestone 混做。**
   后续所有实现任务都按 milestone 切：每个 Codex 任务只负责一个 milestone 或一个 AES 节点；planning/runtime/policy 只在主线程做；`Module Worker` 和 `L2 Campaign` 才允许使用 subagent；每次任务必须写明可改文件、激活 skills、验收 gate 和“任务到此为止”。这条不是附加建议，而是开发纪律，否则后面 runtime、RTL、TB、L2、integration 会重新缠在一起。

## Important Interfaces

- `RuntimeBootstrap`：读取环境、skills、profiles、policy、artifacts、MCP，并产出完整运行时。
- `SdkAgentFactory`：只负责创建 3 个 runtime 角色，不承担编排逻辑。
- `ConversationRunner`：只负责 conversation 生命周期、delegate、tool dispatch、observation 回收。
- `AgentExecutionPolicy`：继续作为唯一状态路由规则，不允许再出现第二套 thinking/subagent 判断逻辑。
- `SpecIR / PlanDAGNode / ModuleRunResult / IntegrationRegressionManifest`：继续作为唯一数据契约，不允许新增平行 JSON 形状。
- `VerilatorMCPAdapter`：继续只暴露 `compile()` 和 `simulate()`，更高层的 L0/L1/L2 语义由 executor 层实现。
- CLI 命令面固定为：`validate`、`smoke-sdk`、`run-node`、`run-aes-mvp`。不要再保留只打印 summary JSON 的“伪运行入口”。

## Test Plan

- **Skill 层测试**：9 个 skills 都能被 loader 正确加载；职责边界明确；不会互相覆盖同一主题。
- **Runtime 层测试**：在无 SDK 包环境下，import guard、生成功能和单元测试可通过；在有 SDK 包环境下，真实 runtime 可以创建主 agent 和 2 类 subagent。
- **Policy/role 测试**：每个 active state 都映射到唯一 profile 和唯一 subagent policy；planning 阶段永远禁止 subagent；2 次失败升级规则被执行。
- **Verilator 层测试**：MCP 连接成功；`verilator_compile`/`verilator_simulate` 可发现；失败时解析器优先读取 `simulation.log` 和 `simulation.vcd`。
- **Node-level AES 测试**：`aes_sbox`、`aes_key_schedule_128`、`aes_round_transform`、`aes128_encrypt_core` 各自通过 L0/L1；对应 checkpoint 全部命中。
- **L2 测试**：允许的 4 类 knob 可用；forced failure 能生成 `counterexample.json`；顶层核能跑 `back_to_back` 和 `mid_reset`。
- **Integration 测试**：full vector corpus、11-cycle latency、ignore-while-busy、back-to-back、reset recovery 全部通过。
- **End-to-end 测试**：`SPEC_INTAKE -> ARCHITECTING -> PLANNING -> MODULE_DESIGN -> MODULE_L0 -> MODULE_L1 -> MODULE_L2_OPTIONAL -> INTEGRATION_READY -> INTEGRATION_REGRESSION -> DONE` 能在绿色路径下完整走通。
- **Quality gate**：每个 milestone 都跑对应单元测试和 `pre-commit`；最终再跑一次 `python -m pytest` 的框架专项集成测试和 CLI smoke tests。

## Assumptions

- 开发主线严格留在 [MultiAgent_FPGA/aes_mvp](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/aes_mvp) 下，不回去扩展 legacy `old_code_autogen` 脚本，也不把逻辑散到 `openhands/controller` 旧代码里。
- 外部 `software_agent_sdk` 仍然是目标 runtime，当前仓库只负责 bridge 和 framework；没有 SDK 时必须允许 validate/test-double 模式存在。
- 现有 contract layer 视为稳定基础，不重新发明第二套 artifacts、second policy、second prompt system。
- 当前详细计划默认“先补 runtime，再补 RTL/TB，再补 L2/integration，再做 observability/CLI 收口”，因为这是从现有实现到 Completion Plan 的最短闭环路径。
