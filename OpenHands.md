## <font style="color:rgb(13, 13, 13);">OpenHands 框架概览</font>
<!-- 这是一张图片，ocr 内容为：USER INTERFACE EVENT STREAM AGENT RUNTIME COMMAND LINE WHERE ALL ACTION-OBSERVATION(S)ARE TRACKED WHERE EACH ACTION EXECUTION LEADS TO AN OBSERVATION WEB UI MULTI-TURN [1]MESSAGE(SOURCE-USER) [6]CMDRUNACTION(SOURCEAGENT) IDE PLUGINS CAN YOU CREATE A LIST OF NUMBERS FROM 1 TO 10,AND I HAVE CREATED A PYTHON FILE APP.PY THAT WILL USER-AGENT [30] DOCKER SANDBOX CREATE A WEB PAGE TO DISPLAY THEM AT PORT 5000? DISPLAY A LIST OF NUMBERS FROM 1 TO 10 WHEN YOU RUN INTERACTION IT.LET ME RUN THE SERVER FOR YOU: OPENHANDS AUTOMATICALLY INSTALL <EXECUTE_BASH> [2]IPYTHONRUNCELLACTION(SOURCEAGENT) "ACTION EXECUTION API"INTO USER- PYTHON3 APP.PY >SERVER.LOG 2>&1 & SUREL LET ME CREATE A FILE FIRST: PROVIDED ARBITRARY DOCKER IMAGES CAT SERVER.10G EVENTHISTORY <EXECUTE_IPYTHON> </EXECUTE_BASH> [PAST ACTION(S)&OBSERVATION(S)] CREATE_FILE('APP.PY) ACTION </EXECUTE_IPYTHON> [7]CMDRUNOBSERVATION OPENHANDS-MAINTAINED [3]IPYTHONRUNCELLOBSERVATION [1] 124 AGENT ACTION EXECUTION API [FILE://WORKSPACE/APP.PY (1 LINES TOTAL)] SERVING FLASK APP ' APP' *DEBUQ MODE:OFF [FILE APP.PY CREATED.] WARNING:THIS IS A DEVELOPMENT SERVER.DO NOT PRODUCE NEW ACTION INTERACTIVE PYTHON JUPYTER USE IT IN A PRODUCTION DEPIOYMENT.USE A (IPYTHON)SERVER PRODUCTION WSGI SERVER INSTEAD. [4]IPYTHONRUNCELLACTION(SOURCEAGENT) RUNNING ON HTTP://127.0.0.1:5000 PRESS CTRL+C TO QUIT I WILL WRITE THE PYTHON CODE FOR STARTING A SERVER. ACTION <EXECUTE_IPYTHON> BASH SHELL EDITED_CODE-\"I"L'[OMITTED FOR BREVITY]"L")"L" [8]BROWSELNTERACTIVEACTION(SOURCEAGENT) EDIT_FILE(START'L,END'1,CONTENTENT EDITED_CODE) THE SERVER IS RUNNING ON PORT 5000 WITH PID 124.LET </EXECUTE_IPYTHON> ME BROWSE TO THE PAGE AT HTTP://127.0.0.1:5000 ABSTRACTION <EXECUTE_BROWSE> [5]IPYTHONRUNCELLOBSERVATION BROWSER GOTO("HTTP://127.0.0.1:5000") [...OMITTED FOR BREVITY...] PLAYWRIGHT CHROMIUM 4LEAPP.ROUTE('/) EVENT STREAM:LIST[ACTION_1, </EXECUTE_BROWSE> 5|DEF INDEX(): OBSERVATION_1,ACTION_2,.....] 19 NUMBERS  LIST(RANGE(1.11)) 71 AGENT:EVENT HISTORY->ACTION [9]BROWSEROUTPUTOBSERVATION RETURN STR(NUMBERS) OBSERVATION .OMITTED FOR BREVITY....][FILE UPDATED.] [1,2,3,4,5,6,7,8,9,10] [...0 RUNTIME:ACTION->OBSERVATION -->
![](https://cdn.nlark.com/yuque/0/2026/png/62574793/1774353270655-71e2dea3-e251-4825-8236-01b0ba7766aa.png)

前端
<!-- 这是一张图片，ocr 内容为：RUNTIME BASH会话 DOCKER运行时 动作执行服务器 本地运行时 JUPYTER插件 运行时接口 远程运行时 浏览器环境 事件流 用户 前端(单页应用) OPENHANDS 后端 HTTP/WS 存储 大语言模型提供者 -->
![](https://cdn.nlark.com/yuque/0/2026/png/62574793/1774353332796-fb06e0aa-4bed-4ac6-8779-e0361eddc140.png)

后端

<!-- 这是一张图片，ocr 内容为：&ABSTRACT> AGENT ACTION +SANDBOX_PLUGINS:LIST[PLUGINREQUIREMENT] RUNTIME CODEACTAGENT OBSERVATION EVENTSTREAM +TOOLS +CONNECT() +SEND_ACTION_FOR_EXECUTION() REST ACTIONEXECUTIONSERVER ACTIONEXECUTIONCLIENT +EXECUTE_ACTION() +_SEND_ACTION_SERVER_REQUEST() +ALIVE() JUPYTERPLUGIN LOCALRUNTIME BASHSESSION REMOTERUNTIME BROWSERENV DOCKERRUNTIME -->
![](https://cdn.nlark.com/yuque/0/2026/png/62574793/1774353340161-6c0bf809-8bb4-464f-a565-6fb41d4b69b8.png)

<font style="color:rgb(13, 13, 13);">OpenHands 是开源 Agent 框架，采用</font><font style="color:rgb(13, 13, 13);"> </font>**<font style="color:rgb(13, 13, 13);">事件驱动 + 模块化架构</font>**<font style="color:rgb(13, 13, 13);">，将 Agent 操作拆解为多个可复用的组件。其核心设计如下：</font>

### <font style="color:rgb(13, 13, 13);">1 核心模块与交互</font>
OpenHands 的架构分为四个包：

| 组成 | 说明 | 引用 |
| --- | --- | --- |
| **SDK (**`**openhands.sdk**`<br/>**)** | 核心框架，定义 Agent、Conversation、LLM、工具系统、事件、工作区、技能、凝缩器和安全等组件。 | |
| **Tools (**`**openhands.tools**`<br/>**)** | 内置工具包，实现 Bash、文件编辑、浏览器等工具，按照 Action/Observation/Executor 模式设计，工具与工作区解耦。 | |
| **Workspace (**`**openhands.workspace**`<br/>**)** | 定义 DockerRuntime、RemoteRuntime 等沙箱工作区，提供统一的文件系统和命令执行环境。 | |
| **Agent Server (**`**openhands.agent_server**`<br/>**)** | 基于 FastAPI/WebSocket 的远程服务，使代理能够通过 HTTP 或 WebSocket 在生产环境中运行。 | |


OpenHands 的模块如下：

| **<font style="color:rgb(13, 13, 13);">模块</font>** | **<font style="color:rgb(13, 13, 13);">作用与接口</font>** | **<font style="color:rgb(13, 13, 13);">关键特点</font>** |
| --- | --- | --- |
| **<font style="color:rgb(13, 13, 13);">Planning & Decision Engine</font>** | <font style="color:rgb(13, 13, 13);">为每一步生成计划与决策，决定调用哪个工具或子 Agent。</font> | <font style="color:rgb(13, 13, 13);">通过</font><font style="color:rgb(13, 13, 13);"> </font>_<font style="color:rgb(13, 13, 13);">prompt + 自然语言反馈</font>_<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">产生决策，支持 CodeAct (生成代码) 或 ReAct 模式。</font> |
| **<font style="color:rgb(13, 13, 13);">Memory</font>** | <font style="color:rgb(13, 13, 13);">存储对话历史、执行结果及外部知识；分为短期、工作记忆和长期记忆</font><font style="color:rgb(13, 13, 13);">。</font> | <font style="color:rgb(13, 13, 13);">支持 RAG 检索、记忆压缩、层级存储。解决上下文窗口有限、信息散乱的难题。</font> |
| **<font style="color:rgb(13, 13, 13);">Planner</font>** | <font style="color:rgb(13, 13, 13);">可配置规则/动态/混合规划器，帮助 Agent 划分任务，确定工具调用顺序。</font> | <font style="color:rgb(13, 13, 13);">通过规则模板或 LLM 动态生成计划。</font> |
| **<font style="color:rgb(13, 13, 13);">Tool Module</font>** | <font style="color:rgb(13, 13, 13);">对接外部工具；OpenHands 使用</font><font style="color:rgb(13, 13, 13);"> </font>_<font style="color:rgb(13, 13, 13);">function call</font>_<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">把 LLM 输出映射为结构化工具调用</font><font style="color:rgb(13, 13, 13);">。</font> | <font style="color:rgb(13, 13, 13);">工具调用标准化、与 LLM 解耦，支持闭环反馈。</font> |
| **<font style="color:rgb(13, 13, 13);">Reflection Module</font>** | <font style="color:rgb(13, 13, 13);">对模型行为进行检查，修正错误或总结经验。</font> | <font style="color:rgb(13, 13, 13);">采用 ReAct、Reflexion 等策略。</font> |
| **<font style="color:rgb(13, 13, 13);">Event Bus (EventStream)</font>** | <font style="color:rgb(13, 13, 13);">发布–订阅系统，各组件通过事件流传递消息和观察结果</font><font style="color:rgb(13, 13, 13);">。</font> | <font style="color:rgb(13, 13, 13);">使各模块解耦、异步运行，可挂载多个订阅者。</font> |
| **<font style="color:rgb(13, 13, 13);">Runtime Sandbox</font>** | <font style="color:rgb(13, 13, 13);">使用 Docker 创建隔离的工作空间，执行代码、运行命令、浏览网页等</font><font style="color:rgb(13, 13, 13);">。</font> | <font style="color:rgb(13, 13, 13);">保证安全、稳定和可复现。</font> |
| **<font style="color:rgb(13, 13, 13);">AgentController</font>** | <font style="color:rgb(13, 13, 13);">框架的“指挥官”，负责迭代循环、状态管理、限制预算，调度子 Agent 等</font><font style="color:rgb(13, 13, 13);">。</font> | <font style="color:rgb(13, 13, 13);">为每个 Agent 或子 Agent 维护独立状态，提供心跳、异常处理与迭代控制。</font> |
| **<font style="color:rgb(13, 13, 13);">Server & Session</font>** | <font style="color:rgb(13, 13, 13);">提供 WebSocket 接口，管理对话会话、保存历史并恢复上下文</font><font style="color:rgb(13, 13, 13);">。</font> | <font style="color:rgb(13, 13, 13);">支持会话创建、恢复、列举和清理，确保任务过程持久化。</font> |


### <font style="color:rgb(13, 13, 13);">2 CodeAct Paradigm</font>
<font style="color:rgb(13, 13, 13);">CodeAct 是 OpenHands 的核心设计：将 Agent 的</font><font style="color:rgb(13, 13, 13);"> </font>_<font style="color:rgb(13, 13, 13);">action space</font>_<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">统一为“写代码并执行”，通过 Python sandbox 执行用户任务</font><font style="color:rgb(13, 13, 13);">。流程如下：</font>

1. **<font style="color:rgb(13, 13, 13);">Think:</font>**<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">LLM 阅读指令及上下文，思考步骤；</font>
2. **<font style="color:rgb(13, 13, 13);">Generate Code:</font>**<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">LLM 生成 Python/Bash 代码实现当前步骤；</font>
3. **<font style="color:rgb(13, 13, 13);">Execute:</font>**<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">在沙箱中运行代码，获取执行结果；</font>
4. **<font style="color:rgb(13, 13, 13);">Observe & Reflect:</font>**<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">将执行结果反馈给 LLM，更新计划。</font>

<font style="color:rgb(13, 13, 13);">相较于传统的 ReAct，通过代码统一动作空间带来多项优势：</font>

+ **<font style="color:rgb(13, 13, 13);">行动空间统一</font>**<font style="color:rgb(13, 13, 13);">：无需为每个工具定义 JSON schema，只需提供 Python 环境及常用库</font><font style="color:rgb(13, 13, 13);">；</font>
+ **<font style="color:rgb(13, 13, 13);">组合性强</font>**<font style="color:rgb(13, 13, 13);">：可以编写复杂逻辑并调用系统工具或第三方库；</font>
+ **<font style="color:rgb(13, 13, 13);">自我调试能力</font>**<font style="color:rgb(13, 13, 13);">：代码执行失败时 LLM 可以调整代码重新运行；</font>
+ **<font style="color:rgb(13, 13, 13);">开箱即用</font>**<font style="color:rgb(13, 13, 13);">：复用既有生态，如 pandas、matplotlib、git 等。</font>

### <font style="color:rgb(13, 13, 13);">3 多智能体与微型代理</font>
#### <font style="color:rgb(13, 13, 13);">3.1 多智能体与 Sub‑Agent 架构</font>
<font style="color:rgb(13, 13, 13);">随着任务复杂度提高，单一 Agent 容易出现</font><font style="color:rgb(13, 13, 13);"> </font>**<font style="color:rgb(13, 13, 13);">上下文污染、工具选择困难、性能下滑</font>**<font style="color:rgb(13, 13, 13);">。多智能体系统将复杂任务拆成子任务，由多个专业 Agent 协作完成</font><font style="color:rgb(13, 13, 13);">。主要模式有：</font>

+ **<font style="color:rgb(13, 13, 13);">Multi‑Agent System</font>**<font style="color:rgb(13, 13, 13);">：多个 Agent 相对独立，各自拥有状态和上下文，通过通信协议协作，控制权分布式</font><font style="color:rgb(13, 13, 13);">。</font>
+ **<font style="color:rgb(13, 13, 13);">Sub‑Agent (委派式子代理)</font>**<font style="color:rgb(13, 13, 13);">：主代理可以使用 </font>`<font style="color:rgb(13, 13, 13);">spawn</font>`<font style="color:rgb(13, 13, 13);"> 命令创建多个子代理，每个子代理继承相同的 LLM 配置，在同一工作区内运行独立的会话，并拥有自己的上下文。随后通过 </font>`<font style="color:rgb(13, 13, 13);">delegate</font>`<font style="color:rgb(13, 13, 13);"> 命令并行分配任务，主代理会阻塞等待所有子代理完成后合并结果，处理异常和超时。这种模式适用于需要并行处理的独立子任务，例如同时分析多个文件或独立执行多步操作。</font>

Agent 的**决策循环**可简述为：

1. <font style="color:rgb(13, 13, 13);"> 用户发送指令，Agent 将其与当前对话上下文交给 LLM。 </font>
2. <font style="color:rgb(13, 13, 13);"> LLM 生成行动计划（如运行 Bash 命令或编写代码），通过工具系统封装为 </font>**Action**<font style="color:rgb(13, 13, 13);">。 </font>
3. <font style="color:rgb(13, 13, 13);"> Action 发布到 </font>**事件流**<font style="color:rgb(13, 13, 13);">（Event Stream），交由工作区运行时执行。 </font>
4. <font style="color:rgb(13, 13, 13);"> 执行结果作为 </font>**Observation**<font style="color:rgb(13, 13, 13);"> 通过事件流返回 Agent，Agent 更新记忆并再次决定下一步，直到任务结束。 </font>
5. <font style="color:rgb(13, 13, 13);"> Agent 在认为任务完成时发送 </font>`<font style="color:rgb(13, 13, 13);">finish</font>`<font style="color:rgb(13, 13, 13);"> 或 </font>`<font style="color:rgb(13, 13, 13);">reject</font>`<font style="color:rgb(13, 13, 13);"> 类型的 Action</font>

#### <font style="color:rgb(13, 13, 13);">3.2 Microagent 的分类与触发机制</font>
<font style="color:rgb(13, 13, 13);">OpenHands 的 microagents 属于 </font>**<font style="color:rgb(13, 13, 13);">Agent as Tool（工具式子代理）</font>**<font style="color:rgb(13, 13, 13);">，属于 “封装好的任务专家”，被动响应明确输入并返回输出，无需共享主 Agent 上下文。相比 Sub‑Agent，microagent 无状态、隔离，可跨项目复用。</font>

+ **<font style="color:rgb(13, 13, 13);">Knowledge Microagent（知识型微代理）</font>**<font style="color:rgb(13, 13, 13);">：用于注入领域知识、最佳实践、框架指南等。通过 frontmatter 中的</font><font style="color:rgb(13, 13, 13);"> </font>**<font style="color:rgb(13, 13, 13);">triggers</font>**<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">字段，匹配用户输入中的关键词触发</font><font style="color:rgb(13, 13, 13);">。例如出现 “docker” 时自动注入 Docker 指南。</font>
+ **<font style="color:rgb(13, 13, 13);">Repo Microagent（仓库型微代理）</font>**<font style="color:rgb(13, 13, 13);">：提供仓库特定的开发规范和流程指南；始终处于激活状态，在当前仓库上下文中自动加载</font><font style="color:rgb(13, 13, 13);">。</font>
+ **<font style="color:rgb(13, 13, 13);">Task Microagent</font>**<font style="color:rgb(13, 13, 13);">：KnowledgeMicroagent 的子类，用于需要用户输入参数的任务。触发方式可由</font><font style="color:rgb(13, 13, 13);"> </font>`**<font style="color:rgb(13, 13, 13);background-color:rgb(236, 236, 236);">/agent_name</font>**`<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">命令激活，并通过变量提取模板获得参数</font><font style="color:rgb(13, 13, 13);">。</font>

<font style="color:rgb(13, 13, 13);">微代理可以存放在</font><font style="color:rgb(13, 13, 13);"> </font>**<font style="color:rgb(13, 13, 13);">OpenHands/microagents</font>**<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">公共目录中，也可以在项目的</font><font style="color:rgb(13, 13, 13);"> </font>`**<font style="color:rgb(13, 13, 13);background-color:rgb(236, 236, 236);">.openhands/microagents</font>**`<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">中存放私有知识库。系统加载仓库时会自动扫描并注册这些微代理</font><font style="color:rgb(13, 13, 13);">。</font>

#### <font style="color:rgb(13, 13, 13);">3.3 微代理的执行与委托机制</font>
<font style="color:rgb(13, 13, 13);">当 LLM 在决策时认为某个子任务需要交给专用代理完成，就会调用</font><font style="color:rgb(13, 13, 13);"> </font>`**<font style="color:rgb(13, 13, 13);background-color:rgb(236, 236, 236);">delegate_to_xxx_agent</font>**`<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">工具，生成</font><font style="color:rgb(13, 13, 13);"> </font>**<font style="color:rgb(13, 13, 13);">AgentDelegateAction</font>**<font style="color:rgb(13, 13, 13);">。AgentController 通过</font><font style="color:rgb(13, 13, 13);"> </font>`**<font style="color:rgb(13, 13, 13);background-color:rgb(236, 236, 236);">start_delegate()</font>**`<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">创建子 Agent 的控制器，独立维护其状态、预算与事件流，执行完毕后封装</font><font style="color:rgb(13, 13, 13);"> </font>**<font style="color:rgb(13, 13, 13);">AgentDelegateObservation</font>**<font style="color:rgb(13, 13, 13);"> </font><font style="color:rgb(13, 13, 13);">返回主 Agent</font><font style="color:rgb(13, 13, 13);">。</font>

<font style="color:rgb(13, 13, 13);">这种委托机制具有以下特征：</font>

+ **<font style="color:rgb(13, 13, 13);">资源隔离</font>**<font style="color:rgb(13, 13, 13);">：父子 Agent 共享文件存储和事件流，但状态独立，避免互相污染</font><font style="color:rgb(13, 13, 13);">；</font>
+ **<font style="color:rgb(13, 13, 13);">容错性</font>**<font style="color:rgb(13, 13, 13);">：子 Agent 异常不会阻塞主 Agent；异常通过 AgentDelegateObservation 上报</font><font style="color:rgb(13, 13, 13);">；</font>
+ **<font style="color:rgb(13, 13, 13);">层级协作</font>**<font style="color:rgb(13, 13, 13);">：主 Agent 可以嵌套调用多级子 Agent，各自有自己的 Controller 实例，支持树状任务拆分</font><font style="color:rgb(13, 13, 13);">。</font>

### <font style="color:rgb(13, 13, 13);">4 内存系统</font>
<font style="color:rgb(13, 13, 13);">记忆对长任务极为关键，OpenHands 采用</font><font style="color:rgb(13, 13, 13);"> </font>**<font style="color:rgb(13, 13, 13);">分层记忆与检索机制</font>**<font style="color:rgb(13, 13, 13);">：</font>

1. **<font style="color:rgb(13, 13, 13);">短期记忆</font>**<font style="color:rgb(13, 13, 13);">：保存当前会话中的对话历史、工具结果；</font>
2. **<font style="color:rgb(13, 13, 13);">工作记忆（Working Memory）</font>**<font style="color:rgb(13, 13, 13);">：缓存最近几轮重要信息，用于生成 prompts；</font>
3. **<font style="color:rgb(13, 13, 13);">长期记忆</font>**<font style="color:rgb(13, 13, 13);">：通过向量数据库存储经验总结与外部知识，支持语义检索</font><font style="color:rgb(13, 13, 13);">。</font>

<font style="color:rgb(13, 13, 13);">系统还提供 </font>**<font style="color:rgb(13, 13, 13);">记忆压缩</font>**<font style="color:rgb(13, 13, 13);">（condenser）对长历史进行摘要；提供查询接口根据关键词、时间或相似度检索；并通过治理策略定期清理冗余内容。</font>

### <font style="color:rgb(13, 13, 13);">5 工具系统</font>
<font style="color:rgb(13, 13, 13);">工具定义了 Agent 可以执行的操作。SDK 的工具系统围绕 </font>**Action**<font style="color:rgb(13, 13, 13);">、</font>**Observation**<font style="color:rgb(13, 13, 13);"> 和 </font>**Executor**<font style="color:rgb(13, 13, 13);"> 三个核心组件</font><font style="color:rgb(13, 13, 13);">：</font>

+ **Action**<font style="color:rgb(13, 13, 13);">：描述工具接受的输入参数，例如 </font>`<font style="color:rgb(13, 13, 13);">BashAction</font>`<font style="color:rgb(13, 13, 13);"> 包含要执行的命令。 </font>
+ **Observation**<font style="color:rgb(13, 13, 13);">：描述工具返回的数据和要显示给 LLM 的格式，例如 </font>`<font style="color:rgb(13, 13, 13);">FileReadObservation</font>`<font style="color:rgb(13, 13, 13);"> 返回文件内容。 </font>
+ **Executor**<font style="color:rgb(13, 13, 13);">：实现工具逻辑，实际调用外部程序、脚本或服务。 </font>

<font style="color:rgb(13, 13, 13);">工具通过 </font>`<font style="color:rgb(13, 13, 13);">ToolDefinition</font>`<font style="color:rgb(13, 13, 13);"> 将三者绑定并注册到 Agent。预置工具包括 Bash、文件编辑器、浏览器（用于网页交互）和 MCP 远程工具等。文档强调工具与工作区解耦，工具的执行由运行时控制，开发者可根据需求创建自定义工具。</font>

<font style="color:rgb(13, 13, 13);">工具调用采用 function call 设计：LLM 通过规范化 schema 决定何时调用哪个工具，框架将调用结果封装为 Observation，并返回给 LLM 做进一步推理。该设计保证了工具接口的标准化、与 LLM 解耦以及闭环反馈。</font>

### <font style="color:rgb(13, 13, 13);">6 运行时与插件系统</font>
**运行时（Runtime）**<font style="color:rgb(13, 13, 13);"> 是连接决策与执行的关键。OpenHands 采用 </font>**客户端—服务器模型**<font style="color:rgb(13, 13, 13);">：</font>

1. <font style="color:rgb(13, 13, 13);"> 用户提供一个基础 Docker 镜像，OpenHands 构建带有运行时客户端的 </font>**OH Runtime 镜像**<font style="color:rgb(13, 13, 13);">。 </font>
2. <font style="color:rgb(13, 13, 13);"> 平台启动 Docker 容器并初始化 </font>`<font style="color:rgb(13, 13, 13);">ActionExecutor</font>`<font style="color:rgb(13, 13, 13);">，加载 Bash、Python 等执行环境和指定插件</font><font style="color:rgb(13, 13, 13);">。 </font>
3. <font style="color:rgb(13, 13, 13);"> 后端通过 REST API 与容器通信，发送 Action、接收 Observation，容器在安全的沙箱中执行命令并返回结果</font><font style="color:rgb(13, 13, 13);">。 </font>
4. <font style="color:rgb(13, 13, 13);"> 运行时管理环境变量、插件和工作目录，并可集成浏览器环境或自定义插件。 </font>

<font style="color:rgb(13, 13, 13);">运行时采用 </font>**插件系统**<font style="color:rgb(13, 13, 13);"> 扩展能力，例如 </font>`<font style="color:rgb(13, 13, 13);">JupyterRequirement</font>`<font style="color:rgb(13, 13, 13);"> 提供交互式 Python 执行，</font>`<font style="color:rgb(13, 13, 13);">AgentSkillsRequirement</font>`<font style="color:rgb(13, 13, 13);"> 注册文件系统操作等。插件按照声明式结构打包，在启动时由运行时加载，从而统一工具在沙箱中的调用方式。构建镜像时会使用三种标签（versioned、lock、source）保证 reproducibility。</font>

<font style="color:rgb(13, 13, 13);">OpenHands 使用 </font>**<font style="color:rgb(13, 13, 13);">Docker 或本地环境</font>**<font style="color:rgb(13, 13, 13);">构建工作目录，确保代码执行环境安全隔离，并提供 </font>**<font style="color:rgb(13, 13, 13);">ActionExecutor</font>**<font style="color:rgb(13, 13, 13);">、</font>**<font style="color:rgb(13, 13, 13);">AgentSkillsPlugin</font>**<font style="color:rgb(13, 13, 13);">、</font>**<font style="color:rgb(13, 13, 13);">BrowserEnv</font>**<font style="color:rgb(13, 13, 13);"> 三大运行时组件。ActionExecutor 根据工具类型选择执行方法，插件提供文件读写、代码执行等功能，BrowserEnv 封装浏览器环境，支持网页交互。</font>

## OpenHands 工作组件
OpenHands = Conversation 驱动 Agent，Agent 通过 Tool 调 Workspace；Skills 改输入，Condenser 缩历史，MCP 扩能力，TaskToolSet / DelegateTool 扩子代理协作模式

### 模块对应表
+ **Conversation**：会话编排与状态机。
+ **Agent**：单步推理-行动循环。
+ **Tool**：动作契约层。
+ **Workspace**：执行环境抽象层。
+ **TaskToolSet**：顺序专家委派。
+ **DelegateTool**：并行子代理委派。
+ **Skills**：上下文知识注入层。
+ **MCP**：外部工具接入层。
+ **Condenser**：上下文压缩层。

| name | OpenHands 官方抽象 / 入口 | 它真正负责什么 | 不该把它误解成什么 |
| --- | --- | --- | --- |
| **Agent** | `Agent`<br/>, `AgentBase`<br/>, `AgentContext` | 执行核心 reasoning-action loop；查询 LLM；编排工具；应用 skills / condenser；做安全检查。 | 不是总状态仓库；它官方强调是 **stateless, event-driven** 的 step 执行器。 |
| **Conversation** | `Conversation`<br/>, `LocalConversation`<br/>, `RemoteConversation`<br/>, `ConversationState`<br/>, `EventLog` | 是与 Agent 交互的主入口；管理生命周期、历史、执行状态、workspace 协调、持久化与监控。 | 不是“另一个 Agent”；它更像 orchestrator / session manager。 |
| **Tool** | Tool System（Action / Observation / Executor / ToolDefinition） | 给 Agent 提供“能做什么”的统一接口，输入输出都是类型化的。 | 不是裸函数调用堆；OpenHands 把它做成严格的 action-observation 契约。 |
| **Workspace** | `BaseWorkspace`<br/>, `LocalWorkspace`<br/>, `RemoteWorkspace` | 抽象执行环境，统一命令执行、文件操作、资源管理与隔离。 | 不是单纯目录路径；它是 execution environment abstraction。 |
| **TaskToolSet** | `TaskToolSet` | 让父 Agent 把复杂任务交给一个子代理顺序执行；支持持久化和 `resume`<br/>。 | 不是并行 fan-out 工具；它是 sequential blocking delegation。 |
| **DelegateTool** | `DelegateTool` | 先 spawn 多个子代理，再 delegate 多个任务，并行运行后返回合并结果。 | 不是多轮可恢复专家对话的首选；它更适合 parallel fan-out / fan-in。 |
| **Skills** | `Skill`<br/>, `AgentContext`<br/>, `AGENTS.md`<br/>, triggered skills, `SKILL.md` | 给 Agent 注入长期规则、领域知识和按需上下文。 | 不是执行器；它们主要影响 prompt/context，而不是直接跑动作。 |
| **MCP** | `mcp_config`<br/>, MCP-provided tools | 从外部 server 动态发现并接入工具与资源。 | 不是单独的 Agent；它是外部能力接入协议。 |
| **Condenser** | `Condenser`<br/>, `LLMSummarizingCondenser` | 当历史过长时保留近端消息、摘要旧消息，减少 token 成本并保持连续性。 | 不是向量数据库式长期记忆；它首先是 context compression 机制。 |




<font style="color:rgb(17, 17, 17);">OpenHands 的关键类包括：</font>

+ **<font style="color:rgb(17, 17, 17);">LLM</font>**<font style="color:rgb(17, 17, 17);">：负责与大型语言模型的所有交互。由于 LiteLLM 的支持，它可以与任何底层完成模型一起工作。</font>
+ **<font style="color:rgb(17, 17, 17);">Agent</font>**<font style="color:rgb(17, 17, 17);">：负责查看当前状态，并产生一个动作，使目标更进一步接近最终目标。</font>
+ **<font style="color:rgb(17, 17, 17);">AgentController</font>**<font style="color:rgb(17, 17, 17);">：初始化 Agent，管理状态，并驱动主要循环，一步步推动 Agent 前进。</font>
+ **<font style="color:rgb(17, 17, 17);">State</font>**<font style="color:rgb(17, 17, 17);">：代表 Agent 任务的当前状态。包括当前步骤、最近事件的历史记录、Agent的长期计划等。State 模块就像 Agent 的 “记忆大脑”，不仅能记下任务执行中的各种状态数据，还支持断点恢复，长周期任务就算中断了，也能接着之前的进度继续做，不用从头再来。</font>
+ **<font style="color:rgb(17, 17, 17);">EventStream</font>**<font style="color:rgb(17, 17, 17);">：事件的中心枢纽，任何组件都可以发布事件，或监听其他组件发布的事件。</font>
    - **<font style="color:rgb(17, 17, 17);">Event</font>**<font style="color:rgb(17, 17, 17);">：动作或观察</font>
        * **<font style="color:rgb(17, 17, 17);">Action</font>**<font style="color:rgb(17, 17, 17);">：代表一个请求，例如编辑文件、运行命令或发送消息。</font>
        * **<font style="color:rgb(17, 17, 17);">Observation</font>**<font style="color:rgb(17, 17, 17);">：代表从环境中收集的信息，例如文件内容或命令输出。</font>
    - <font style="color:rgb(17, 17, 17);">Action 和 Observation 相当于组件间的 “通用语言”——Action 带着要执行的指令，Observation 传回执行的结果，俩者配合到位，信息传递才顺畅不卡壳。这些模块不是各干各的，而是靠 Event Stream 这个 “核心枢纽” 连在一起协同工作 —— 各种事件都在这里汇聚、分发，推着任务按计划一步步走，最终让 AI Agent有能力处理复杂任务。</font>
    - <font style="color:rgb(17, 17, 17);">ReAct 范式就像是 Agent 的 “行为准则”，定下了 “先思考、再行动、收反馈” 的核心逻辑，确保它做决策时有条理、不混乱。事件驱动模型则搭起了系统的 “骨架”，所有交互都靠事件流转来推进，各个模块不用硬绑在一起，能灵活应对各种情况。</font>
+ **<font style="color:rgb(17, 17, 17);">Runtime</font>**<font style="color:rgb(17, 17, 17);">：负责执行动作，并发送回观察结果。</font>
    - **<font style="color:rgb(17, 17, 17);">Sandbox</font>**<font style="color:rgb(17, 17, 17);">：运行命令的运行时环境部分，例如在 Docker 内部。</font>
    - <font style="color:rgb(17, 17, 17);">Runtime 和 Memory 这些组件是系统的关键 “器官”：Runtime 会提供一个隔离的执行环境，保证代码运行时安全又稳定，不会搞乱其他部分；Memory 则把历史数据管得明明白白，给 Agent 做决策提供过往经验。</font>
+ **<font style="color:rgb(17, 17, 17);">Server</font>**<font style="color:rgb(17, 17, 17);">：通过 HTTP 管理 OpenHands 会话，例如驱动前端。</font>
    - **<font style="color:rgb(17, 17, 17);">Session</font>**<font style="color:rgb(17, 17, 17);">：保存单个 EventStream、单个 AgentController 和单个 Runtime。通常代表一个单一任务（但可能包括几个用户提示）。</font>
    - **<font style="color:rgb(17, 17, 17);">ConversationManager</font>**<font style="color:rgb(17, 17, 17);">：维护一个活动会话列表，并确保请求被路由到正确的会话。</font>

<!-- 这是一张图片，ocr 内容为：用户交互 AGENT控制器 服务器层 AGENT实现 执行环境层 核心服务层 记忆与知识层 安全与监控层 第三方集成层 -->
![](https://cdn.nlark.com/yuque/0/2026/png/62574793/1774353774523-92d31587-68bb-4067-9aa4-7cba30ba8749.png)

<font style="color:rgb(17, 17, 17);">这个流程展示了 OpenHands 作为一个 AI 软件开发Agent平台的完整架构，从用户交互到核心执行的完整数据流和组件关系。</font>

1. <font style="color:rgb(17, 17, 17);">用户输入阶段</font>
    1. <font style="color:rgb(17, 17, 17);">用户通过 Web 界面、CLI 或 API 发起请求</font>
    2. <font style="color:rgb(17, 17, 17);">服务器接收请求并创建会话</font>
    3. <font style="color:rgb(17, 17, 17);">事件通过事件流系统传递</font>
2. <font style="color:rgb(17, 17, 17);">Agent 处理阶段</font>
    1. <font style="color:rgb(17, 17, 17);">Controller 根据配置初始化相应 Agent</font>
    2. <font style="color:rgb(17, 17, 17);">Agent 基于当前状态和历史生成决策</font>
    3. <font style="color:rgb(17, 17, 17);">通过工具系统执行具体操作</font>
3. <font style="color:rgb(17, 17, 17);">执行阶段</font>
    1. <font style="color:rgb(17, 17, 17);">Runtime 环境执行具体命令或代码</font>
    2. <font style="color:rgb(17, 17, 17);">插件系统提供额外功能支持</font>
    3. <font style="color:rgb(17, 17, 17);">安全系统监控执行过程</font>
4. <font style="color:rgb(17, 17, 17);">反馈阶段</font>
    1. <font style="color:rgb(17, 17, 17);">执行结果作为 Observation 返回</font>
    2. <font style="color:rgb(17, 17, 17);">更新 Agent 状态和记忆</font>
    3. <font style="color:rgb(17, 17, 17);">将结果返回给用户</font>

## OpenHands 代码库
<font style="color:rgb(17, 17, 17);">OpenHands的代码库组织清晰，以下是最主要的目录：</font>

1. **<font style="color:rgb(17, 17, 17);">Agent中心（agenthub）</font>**<font style="color:rgb(17, 17, 17);">：这是Agent的核心区域，负责代码生成和执行相关的逻辑，是平台的核心能力载体。它包含专注于代码生成与执行的Agent逻辑，是平台的核心能力所在。此外，还包括负责浏览器交互的Agent实现。</font>
2. **<font style="color:rgb(17, 17, 17);">事件系统（events）</font>**<font style="color:rgb(17, 17, 17);">：这是事件驱动架构的核心目录，定义了系统的“通信语言”。它包含封装任务执行结果等反馈类事件的</font>`<font style="color:rgb(192, 52, 29);background-color:rgba(0, 0, 0, 0.04);">observation/</font>`<font style="color:rgb(17, 17, 17);">，以及定义Agent可执行的各类动作指令的</font>`<font style="color:rgb(192, 52, 29);background-color:rgba(0, 0, 0, 0.04);">action/</font>`<font style="color:rgb(17, 17, 17);">。</font>`<font style="color:rgb(192, 52, 29);background-color:rgba(0, 0, 0, 0.04);">stream.py</font>`<font style="color:rgb(17, 17, 17);">实现了事件流的管理机制，负责事件的分发、存储与订阅，是组件协同工作的关键枢纽。</font>
3. **<font style="color:rgb(17, 17, 17);">运行时环境（runtime/）</font>**<font style="color:rgb(17, 17, 17);">：提供Agent执行的底层环境支持。</font>`<font style="color:rgb(192, 52, 29);background-color:rgba(0, 0, 0, 0.04);">impl/</font>`<font style="color:rgb(17, 17, 17);">目录包含Docker容器、本地环境等不同运行时的具体实现；</font>`<font style="color:rgb(192, 52, 29);background-color:rgba(0, 0, 0, 0.04);">plugins/</font>`<font style="color:rgb(17, 17, 17);">支持通过插件扩展运行时功能，提升系统的灵活性。</font>
4. **<font style="color:rgb(17, 17, 17);">记忆管理（memory/）</font>**<font style="color:rgb(17, 17, 17);">：负责管理Agent的历史数据与记忆。</font>`<font style="color:rgb(192, 52, 29);background-color:rgba(0, 0, 0, 0.04);">conversation_memory.py</font>`<font style="color:rgb(17, 17, 17);">处理对话历史的存储与检索；</font>`<font style="color:rgb(192, 52, 29);background-color:rgba(0, 0, 0, 0.04);">condenser/</font>`<font style="color:rgb(17, 17, 17);">实现历史记录的压缩逻辑，解决LLM上下文窗口有限的问题，保障长周期任务的连贯性。</font>
5. **<font style="color:rgb(17, 17, 17);">语言模型集成（llm/）</font>**<font style="color:rgb(17, 17, 17);">：实现与各类大型语言模型的集成。</font>
6. **<font style="color:rgb(17, 17, 17);">控制器（controller/）</font>**<font style="color:rgb(17, 17, 17);">：系统的“指挥中心”，负责Agent的调度与管理。</font>

<!-- 这是一张图片，ocr 内容为：用户交互层 API调用(无头 CLI命令行 WOB前端界面 (CLI模式) 模式) (TRONTEND/) 服务器层(SERVER/) 会活管理器 事件路由 WEB服务器 (SESSION/) (STREAM) AGENTCONTROLLER(CONTROLLER/) AGENT控制器 状态管理器 (AGENT_CTRL.PY) (STATE/) 要托管理器 停滞检测器 (STUCK.PY) (DELEGETE) AGENT(AGENTHUB/) PLANNERAGENT (PLANNER_*) (CODEACT ) 计划管理器 工具系统(TOOLS/) (TASK_TRACKER) 函数调用处理 (FUNCTION_CALLING) 核心服务层(CORE/) 事件系统 (EVENTS/) 配置管理(CONFIG/) LLM接口层(LLM/) LLM注册表 AGON配置 (LIM_ REGISTRY) (AGONT_CONFIG) 执行环境(RUNTIME/) 本地执行器 DOCKER少箱 SSH执行器(SSH/) (LOCAL/) 插件系统(PLUGINS/) AGONTSKILLS(基础工 JUPYTER支持(PYTHON交互环境) 具) 记忆与知识层(MEMORY/) 历史压缩器 对话记忆 微AGENT(MICRO*) (CONDENSER) (CONVERSATION) 安全与监控层(SECURITY) 安全分析器 权限控制 审计日志(AUDIT) (ANALYZER/) 第三方华成层(INTEGRATION) 浏览器自动化 GITHUB集成 MCP协议(MOP/) (GITHUB/) (BROWSER) -->
![](https://cdn.nlark.com/yuque/0/2026/png/62574793/1774353755330-1c82d2a9-07e7-4bff-bc3f-357f7bc86166.png)



## OpenHands 工作机制
<font style="color:black;">OpenHands Agent 的交互逻辑可提炼为 “初始化 - 事件注入 - 协同处理 - 等待” 的极简流程，核心围绕 EventStream 实现模块联动：</font>

1. <font style="color:rgb(1, 1, 1);">初始化就绪：用户创建会话时，系统自动完成 Agent、AgentController、Runtime、Memory 有核心模块的初始化，且每个模块都会自动订阅 EventStream，确保能捕获相关事件；</font>
2. <font style="color:rgb(1, 1, 1);">任务发起：用户发送消息本质是向 EventStream 中注入一条事件，这条事件会触发所有订阅相关回调函数的模块，启动协同处理；</font>
3. <font style="color:rgb(1, 1, 1);">多模块协同响应：</font>
    1. <font style="color:rgb(1, 1, 1);">Session 模块持续上报事件流中的各类状态事件，保障全局可观测；</font>
    2. <font style="color:rgb(1, 1, 1);">若用户开启 Security Analyzer，该模块会通过安全分析，自动确认低风险任务，减少用户手动干预；</font>
    3. <font style="color:rgb(1, 1, 1);">AgentController 向事件流注入 RecallAction，Memory 模块判断是否为首次接收的用户信息，据此补充相关记忆并返回 RecallObservation 事件；</font>
4. <font style="color:rgb(1, 1, 1);">状态同步：AgentController 更新任务当前状态，并将相关信息传递给 Agent。即AgentController 调用 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Agent.step</font>`<font style="color:rgb(1, 1, 1);"> 方法处理当前事件，生成 Action 并注入事件流。</font>
5. <font style="color:rgb(1, 1, 1);">行动决策：Agent 基于接收的状态信息，向</font><font style="color:rgb(1, 1, 1);"> </font>LLM<font style="color:rgb(1, 1, 1);"> </font><font style="color:rgb(1, 1, 1);">发起请求，生成下一步具体行动方案；</font>
6. <font style="color:rgb(1, 1, 1);">行动输出：Agent 明确输出行动指令，可能是运行系统命令、读取文件、调用工具等具体操作；</font>
7. <font style="color:rgb(1, 1, 1);">行动分发：该行动指令通过 EventStream 传递至 Runtime 组件，等待执行；</font>
8. <font style="color:rgb(1, 1, 1);">执行与反馈：Runtime 执行行动指令，生成包含执行结果、错误信息等内容的观察结果；</font>
9. <font style="color:rgb(1, 1, 1);">结果回传：观察结果通过 EventStream 回传给 AgentController，完成一次执行闭环；</font>
10. <font style="color:rgb(1, 1, 1);">循环或终止：AgentController 根据观察结果判断任务是否完成，若未完成则重复上述流程；若需协同，则委派给其他 Agent，直至任务结束。</font>

### <font style="color:rgb(1, 1, 1);">启动</font>
1. 创建Agent, 默认生成CodeActAgent, 可配置沙盒环境和沙盒环境所需的插件
2. 构建Runtime `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Runtime</font>`<font style="color:rgb(0, 0, 0);">只处理可运行的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Action</font>`<font style="color:rgb(0, 0, 0);">事件，执行动作拿到输出</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Observation</font>`<font style="color:rgb(0, 0, 0);">发送回事件流中</font>
3. <font style="color:rgb(0, 0, 0);">构建Memory </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Memory</font>`<font style="color:rgb(0, 0, 0);">只处理</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RecallAction</font>`<font style="color:rgb(0, 0, 0);">，对于用户首次输入信息则将一些额外的工作空间上下文信息添加到</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RecallObservation</font>`<font style="color:rgb(0, 0, 0);">发送回事件流中，对于其他非用户首次的输入信息则加入</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">microagent knowledge(领域强化提示词)</font>`<font style="color:rgb(0, 0, 0);">到</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RecallObservation</font>`<font style="color:rgb(0, 0, 0);">发送回事件流中。</font>
4. <font style="color:rgb(0, 0, 0);">创建Microagent </font><font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Microagent </font><font style="color:rgb(0, 0, 0);">同样基于大型语言模型构建，比如，其独特之处可以是其内置的专业提示词（Prompt）。</font>
5. <font style="color:rgb(0, 0, 0);">创建MCP Add MCP tools to the agent</font>
6. <font style="color:rgb(0, 0, 0);">创建Controller AgentController 是 OpenHands 系统中的核心控制器组件，负责管理代理（Agent）的整个生命周期和行为</font>

`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentController</font>`<font style="color:black;">作为主要状态管理模块，</font>

    - <font style="color:rgb(1, 1, 1);">根据</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Observation</font>`<font style="color:rgb(1, 1, 1);">事件进行状态变换</font>
    - <font style="color:rgb(1, 1, 1);">根据</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Action</font>`<font style="color:rgb(1, 1, 1);">进行状态变换和以下处理：</font>
        * <font style="color:rgb(1, 1, 1);">对于</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">MessageAction</font>`<font style="color:rgb(1, 1, 1);">发送</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RecallAction</font>`<font style="color:rgb(1, 1, 1);">到事件流中</font>
        * <font style="color:rgb(1, 1, 1);">对于</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateAction</font>`<font style="color:rgb(1, 1, 1);">做Agent路由（后续机制解读中再详细介绍）</font>
    - <font style="color:rgb(1, 1, 1);">根据当前的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">event</font>`<font style="color:rgb(1, 1, 1);">判断进行调用</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">agent.step</font>`
7. 发送启动事件 <font style="color:rgb(0, 0, 0);">发送一个启动事件MessageAction</font>
8. <font style="color:rgb(0, 0, 0);">订阅事件流</font>
    - <font style="color:rgb(1, 1, 1);">Runtime 在事件流中订阅 EventStreamSubscriber.RUNTIME，事件回调函数会处理需要runtine处理的action，比如mcp/tool等等。</font>
    - <font style="color:rgb(1, 1, 1);">Memory 在事件流中订阅 EventStreamSubscriber.MEMORY。事件回调函数根据当前的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">event</font>`<font style="color:rgb(1, 1, 1);">生成一个带</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">microagent_knowledge</font>`<font style="color:rgb(1, 1, 1);">的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Observation</font>`<font style="color:rgb(1, 1, 1);">并以</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ENVIRONMENT</font>`<font style="color:rgb(1, 1, 1);">作为源添加回事件流中，这里的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">microagent_knowledge</font>`<font style="color:rgb(1, 1, 1);">是一种特定提示词增强的方法。</font>
    - <font style="color:rgb(1, 1, 1);">AgentController 在事件流中订阅 EventStreamSubscriber.AGENT_CONTROLLER。</font>
    - <font style="color:rgb(1, 1, 1);">run_controller 在事件流中订阅 EventStreamSubscriber.MAIN。</font>
9. 运行代理 <font style="color:rgb(0, 0, 0);">运行代理直到进入结束状态</font>



### 服务
##### 1.1 API模式
<font style="color:black;">可以发送或从服务器接收两种类型的消息：</font>

    - **<font style="color:rgb(1, 1, 1);">Actions</font>**
    - **<font style="color:rgb(1, 1, 1);">Observations</font>**

###### **<font style="color:rgb(1, 1, 1);">  1.11 Actions</font>**
<font style="color:black;">一个action 包含三个部分：</font>

    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">action</font>`<font style="color:rgb(1, 1, 1);">：要采取的动作</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">args</font>`<font style="color:rgb(1, 1, 1);">：动作的参数</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">message</font>`<font style="color:rgb(1, 1, 1);">：可以放在聊天记录中的友好消息</font>

<font style="color:black;">有几种action 。它们的参数列在下面。 随着时间的推移，这个列表可能会增长。</font>

    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">initialize</font>`<font style="color:black;"> - 初始化代理。仅由客户端发送。</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">model</font>`<font style="color:rgb(1, 1, 1);"> - 要使用的模型名称</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">directory</font>`<font style="color:rgb(1, 1, 1);"> - 工作空间的路径</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">agent_cls</font>`<font style="color:rgb(1, 1, 1);"> - 要使用的代理类</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">start</font>`<font style="color:black;"> - 开始一个新的开发任务。仅由客户端发送。</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">task</font>`<font style="color:rgb(1, 1, 1);"> - 要开始的任务</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">read</font>`<font style="color:black;"> - 读取文件内容。</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">path</font>`<font style="color:rgb(1, 1, 1);"> - 要读取的文件路径</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">write</font>`<font style="color:black;"> - 写入内容到文件。</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">path</font>`<font style="color:rgb(1, 1, 1);"> - 要写入的文件路径</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">content</font>`<font style="color:rgb(1, 1, 1);"> - 写入文件的内容</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">run</font>`<font style="color:black;"> - 运行命令。</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">command</font>`<font style="color:rgb(1, 1, 1);"> - 要运行的命令</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">browse</font>`<font style="color:rgb(1, 1, 1);"> - 打开网页。</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">url</font>`<font style="color:rgb(1, 1, 1);"> - 要打开的URL</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">think</font>`<font style="color:rgb(1, 1, 1);"> - 允许代理制定计划、设定目标或记录想法</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">thought</font>`<font style="color:rgb(1, 1, 1);"> - 要记录的想法</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">finish</font>`<font style="color:rgb(1, 1, 1);"> - 代理发出任务完成的信号</font>

###### **<font style="color:rgb(1, 1, 1);">  1.12 Observation</font>**
<font style="color:black;">一个observation 包含四个部分：</font>

    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">observation</font>`<font style="color:rgb(1, 1, 1);">：观察类型</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">content</font>`<font style="color:rgb(1, 1, 1);">：表示观察数据的字符串</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">extras</font>`<font style="color:rgb(1, 1, 1);">：额外的结构化数据</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">message</font>`<font style="color:rgb(1, 1, 1);">：可以放在聊天记录中的友好消息</font>

<font style="color:black;">有几种observation 。它们的额外信息列在下面。 随着时间的推移，这个列表可能会增长。</font>

    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">read</font>`<font style="color:rgb(1, 1, 1);"> - 文件内容</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">path</font>`<font style="color:rgb(1, 1, 1);"> - 读取的文件路径</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">browse</font>`<font style="color:rgb(1, 1, 1);"> - URL的HTML内容</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">url</font>`<font style="color:rgb(1, 1, 1);"> - 打开的URL</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">run</font>`<font style="color:rgb(1, 1, 1);"> - 命令的输出</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">command</font>`<font style="color:rgb(1, 1, 1);"> - 运行的命令</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">exit_code</font>`<font style="color:rgb(1, 1, 1);"> - 命令的退出代码</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">chat</font>`<font style="color:rgb(1, 1, 1);"> - 用户的消息</font>

##### <font style="color:rgb(1, 1, 1);">1.2 服务器组件</font>
<font style="color:black;">以下部分描述了OpenHands项目的服务器端组件。</font>

###### <font style="color:black;">session.py</font>
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">session.py</font>`<font style="color:black;"> 文件定义了</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:black;">类，它代表与客户端的WebSocket会话。关键特性包括：</font>

    - <font style="color:rgb(1, 1, 1);">处理WebSocket连接和断开</font>
    - <font style="color:rgb(1, 1, 1);">初始化和管理代理会话</font>
    - <font style="color:rgb(1, 1, 1);">在客户端和代理之间分发事件</font>
    - <font style="color:rgb(1, 1, 1);">向客户端发送消息和错误</font>

###### <font style="color:black;">session/agent_session.py</font>
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">agent_session.py</font>`<font style="color:black;"> 文件包含</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentSession</font>`<font style="color:black;">类，它管理会话内代理的生命周期。关键特性包括：</font>

    - <font style="color:rgb(1, 1, 1);">创建和管理运行时环境</font>
    - <font style="color:rgb(1, 1, 1);">初始化代理控制器</font>
    - <font style="color:rgb(1, 1, 1);">处理安全分析</font>
    - <font style="color:rgb(1, 1, 1);">管理事件流</font>

###### <font style="color:black;">session/conversation_manager/conversation_manager.py</font>
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">conversation_manager.py</font>`<font style="color:black;"> 文件定义了</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ConversationManager</font>`<font style="color:black;">类，它负责管理多个客户端会话。关键特性包括：</font>

    - <font style="color:rgb(1, 1, 1);">添加和重启会话</font>
    - <font style="color:rgb(1, 1, 1);">向特定会话发送消息</font>
    - <font style="color:rgb(1, 1, 1);">清理非活动会话</font>

###### <font style="color:black;">listen.py</font>
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">listen.py</font>`<font style="color:black;"> 文件是主服务器文件，它设置FastAPI应用程序并定义各种API端点。关键特性包括：</font>

    - <font style="color:rgb(1, 1, 1);">设置CORS中间件</font>
    - <font style="color:rgb(1, 1, 1);">处理WebSocket连接</font>
    - <font style="color:rgb(1, 1, 1);">管理文件上传</font>
    - <font style="color:rgb(1, 1, 1);">提供代理交互、文件操作和安全分析的API端点</font>
    - <font style="color:rgb(1, 1, 1);">为前端提供静态文件服务</font>

<font style="color:black;">该脚本定义了服务接口，主要分为两个部分：</font>

    - <font style="color:rgb(1, 1, 1);">一部分是通过</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">FastAPI</font>`<font style="color:rgb(1, 1, 1);">库实现的HTTP接口，其具体实现位于</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">openhands/server/routes</font>`<font style="color:rgb(1, 1, 1);">目录中；</font>
    - <font style="color:rgb(1, 1, 1);">另一部分是利用</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">socketio</font>`<font style="color:rgb(1, 1, 1);">库实现的WebSocket接口，其代码实现在</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">openhands/server/listen_socket.py</font>`<font style="color:rgb(1, 1, 1);">文件中。用户与代理的交互通过WebSocket进行，连接初始化时会触发</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">connect</font>`<font style="color:rgb(1, 1, 1);">事件，用户发送消息时会触发</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">oh_user_action</font>`<font style="color:rgb(1, 1, 1);">事件，连接断开时会触发</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">disconnect</font>`<font style="color:rgb(1, 1, 1);">事件。因此，梳理代理交互逻辑的核心在于对这三个事件的处理流程进行整理。</font>

<font style="color:rgb(51, 51, 51);background-color:rgba(0, 0, 0, 0.03);">
</font>

##### 1.3 服务工作流程描述
<font style="color:black;">服务的工作流程如下：</font>

    1. <font style="color:black;">服务器初始化</font><font style="color:rgb(1, 1, 1);">：</font>
        * <font style="color:rgb(1, 1, 1);">FastAPI应用程序在</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">listen.py</font>`<font style="color:rgb(1, 1, 1);">中创建和配置。</font>
        * <font style="color:rgb(1, 1, 1);">设置CORS中间件和静态文件服务。</font>
        * <font style="color:rgb(1, 1, 1);">初始化</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ConversationManager</font>`<font style="color:rgb(1, 1, 1);">。</font>
    2. <font style="color:black;">客户端连接</font><font style="color:rgb(1, 1, 1);">：</font>
        * <font style="color:rgb(1, 1, 1);">当客户端通过WebSocket连接时，创建新的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);">或重启现有一个。</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);">初始化</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentSession</font>`<font style="color:rgb(1, 1, 1);">，设置运行时环境和代理控制器。</font>
    3. <font style="color:black;">代理初始化</font><font style="color:rgb(1, 1, 1);">：</font>
        * <font style="color:rgb(1, 1, 1);">客户端发送初始化请求。</font>
        * <font style="color:rgb(1, 1, 1);">服务器根据提供的参数创建和配置代理。</font>
        * <font style="color:rgb(1, 1, 1);">设置运行时环境，初始化代理控制器。</font>
    4. <font style="color:black;">事件处理</font><font style="color:rgb(1, 1, 1);">：</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);">管理客户端和代理之间的事件流。</font>
        * <font style="color:rgb(1, 1, 1);">客户端的事件分发到代理。</font>
        * <font style="color:rgb(1, 1, 1);">代理的观察结果发送回客户端。</font>
    5. <font style="color:black;">文件操作</font><font style="color:rgb(1, 1, 1);">：</font>
        * <font style="color:rgb(1, 1, 1);">服务器处理文件上传，确保它们符合大小和类型限制。</font>
        * <font style="color:rgb(1, 1, 1);">通过运行时环境执行文件读取和写入操作。</font>
    6. <font style="color:black;">安全分析</font><font style="color:rgb(1, 1, 1);">：</font>
        * <font style="color:rgb(1, 1, 1);">如果配置了，每个会话初始化安全分析器。</font>
        * <font style="color:rgb(1, 1, 1);">安全相关的API请求转发到安全分析器。</font>
    7. <font style="color:black;">会话管理</font><font style="color:rgb(1, 1, 1);">：</font>
        * `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ConversationManager</font>`<font style="color:rgb(1, 1, 1);">定期清理非活动会话。</font>
        * <font style="color:rgb(1, 1, 1);">它还在需要时处理向特定会话发送消息。</font>
    8. <font style="color:black;">API端点</font><font style="color:rgb(1, 1, 1);">：</font>
        * <font style="color:rgb(1, 1, 1);">提供各种API端点，用于代理交互、文件操作和获取配置默认值。</font>

<font style="color:black;">这种服务器架构允许管理多个客户端会话，每个会话都有自己的代理实例、运行时环境和安全分析器。事件驱动设计促进了客户端和代理之间的实时通信，而模块化结构允许轻松扩展和维护不同组件。</font>

<font style="color:black;"></font>

##### 流程图
<!-- 这是一张图片，ocr 内容为：客户端连接流程(CONNECT事件) 1.连接建立与参数解析 解析QUERY-PARAMS:LATEST-EVENT_ID,CONVERSATION_ID. PROVIDERS_SET 校验CONVERSATION_ID是否存在 校验API密钥有效性 2.用户身份验证 提取COOKIE和AUTHORIZATION头 通过CONVERSATION_VALIDATOR校验用户身份,获取USER_ID 3.事件存储初始化 创建EVENTSTORE实例,关联会话事件数据 若事件存储不存在,拒绝连接 4.历史事件回放 创建ASYNCEVENTSTOREWRAPPER,从 UR,从LATEST_EVENT_ID+1开始回放 跳过无效事件,暂存代理状态变更事件 向客户端推送历史事件,最后推送代理状态变更事件 5.会话初始化与加入 调用SETUP_INIT_CONVERSATION_SETTINGS初始化会话配置 调用JOIN_CONVERSATION关联连接与会话,启动代理循环 若加入失败,拒绝连接 6.连接成功/失败处理 成功;客户端与服务器建立实时通信,等待用户行动 失败:触发CONNECTIONREFUSEDERROR,断开客户端连接 其他核心事件流程 OH_USER_ACTION OH_ACTION DISCONNECT (用户行动) (兼容旧版) (连接断开) 转发至事件流 断开会话关联 转发至事件流 (会话管理器处理) (会话管理器处理) 公众号西的思考 -->
![](https://cdn.nlark.com/yuque/0/2026/png/62574793/1774525948472-683a2525-43aa-436f-a9be-f38bbd6e655d.png)

### 交互与会话
##### 1.1 会话
<font style="color:black;">常见的Agent系统会通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:black;">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:black;"> 和 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Memory</font>`<font style="color:black;"> 提供了结构化的上下文管理方式。</font>

    1. `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);">：当前对话线程（可以将你与智能体的不同对话实例视为独立的</font><font style="color:black;">对话线程</font><font style="color:rgb(1, 1, 1);">，它们可能会利用</font><font style="color:black;">长期知识</font><font style="color:rgb(1, 1, 1);">）</font>
        * <font style="color:rgb(1, 1, 1);">表示用户与你的智能体系统之间</font>_<font style="color:black;">单次、持续的交互</font>_<font style="color:rgb(1, 1, 1);">。</font>
        * <font style="color:rgb(1, 1, 1);">包含该特定交互期间，智能体采取的消息和动作（称为 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Events</font>`<font style="color:rgb(1, 1, 1);">）的时间顺序序列。</font>
        * <font style="color:rgb(1, 1, 1);">一个 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);"> 还可以保存仅在</font>_<font style="color:black;">本次对话</font>_<font style="color:rgb(1, 1, 1);">期间相关的临时数据（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:rgb(1, 1, 1);">）。</font>
    2. `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:rgb(1, 1, 1);">：当前对话中的数据</font>
        * <font style="color:rgb(1, 1, 1);">存储在特定 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);"> 内的数据。</font>
        * <font style="color:rgb(1, 1, 1);">用于管理</font>_<font style="color:black;">仅</font>_<font style="color:rgb(1, 1, 1);">与</font>_<font style="color:black;">当前（单次）、活跃</font>_<font style="color:rgb(1, 1, 1);">对话线程相关的信息（例如，</font>_<font style="color:black;">本次对话</font>_<font style="color:rgb(1, 1, 1);">中的购物车商品，</font>_<font style="color:black;">本 Session</font>_<font style="color:rgb(1, 1, 1);"> 中提到的用户偏好）。</font>
        * <font style="color:rgb(1, 1, 1);">关注如何高效地读取、写入和管理 session 专属数据。</font>
    3. `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Memory</font>`<font style="color:rgb(1, 1, 1);">：可检索的跨 Session 信息</font>
        * <font style="color:rgb(1, 1, 1);">表示可能跨越</font>_<font style="color:black;">多个过去 Session</font>_<font style="color:rgb(1, 1, 1);">或包含外部数据源的信息存储。</font>
        * <font style="color:rgb(1, 1, 1);">它作为一个知识库，智能体可以</font>_<font style="color:black;">检索</font>_<font style="color:rgb(1, 1, 1);">以回忆超出当前对话的信息或上下文。</font>

<font style="color:black;">因此，Agent系统一般有如下两套组件或者服务：</font>

    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:rgb(1, 1, 1);">：管理不同的对话线程（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);"> 对象）负责生命周期管理：创建、检索、更新（追加 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Events</font>`<font style="color:rgb(1, 1, 1);">、修改 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:rgb(1, 1, 1);">）和删除单个 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);">。</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">MemoryService</font>`<font style="color:rgb(1, 1, 1);">：管理长期知识存储（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Memory</font>`<font style="color:rgb(1, 1, 1);">），负责将信息（通常来自已完成的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);">）导入长期存储。提供基于查询检索已存储知识的方法。</font>

<font style="color:rgb(1, 1, 1);"></font>

<font style="color:black;"></font>

##### 1.2 会话系统的常见功能
<font style="color:black;">用户通常不会直接创建或管理 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:black;"> 对象，而是通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:black;">。该服务作为会话生命周期的中央管理者。其核心职责包括：</font>

    - <font style="color:black;">开启新对话：</font><font style="color:rgb(1, 1, 1);"> 当用户开始交互时，创建新的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);"> 对象。</font>
    - <font style="color:black;">恢复已有对话：</font><font style="color:rgb(1, 1, 1);"> 通过 ID 检索特定 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);">，让智能体可以从上次中断处继续。</font>
    - <font style="color:black;">保存进度：</font><font style="color:rgb(1, 1, 1);"> 将新的交互（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event</font>`<font style="color:rgb(1, 1, 1);"> 对象）追加到 session 历史。这也是 session </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">state</font>`<font style="color:rgb(1, 1, 1);"> 更新的机制（详见 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:rgb(1, 1, 1);"> 章节）。</font>
    - <font style="color:black;">列出对话：</font><font style="color:rgb(1, 1, 1);"> 查找特定用户和应用的活跃会话线程。</font>
    - <font style="color:black;">清理：</font><font style="color:rgb(1, 1, 1);"> 当对话结束或不再需要时，删除 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);"> 及其相关数据。</font>

<font style="color:black;">选择合适的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:black;"> 是决定智能体对话历史和临时数据如何存储与持久化的关键。</font>

##### 1.3 Session常见内容
<font style="color:black;">一般来说，当用户开始与智能体交互时，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:black;"> 会创建一个 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:black;"> 对象。该对象作为</font>_<font style="color:black;">单个对话线程</font>_<font style="color:black;">相关所有内容的容器。其主要属性如下：</font>

    1. <font style="color:rgb(1, 1, 1);">标识信息（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">id</font>`<font style="color:rgb(1, 1, 1);">, </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">appName</font>`<font style="color:rgb(1, 1, 1);">, </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">userId</font>`<font style="color:rgb(1, 1, 1);">）：</font>

<font style="color:black;">用于唯一标记对话的核心字段，具体说明如下：</font>

    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">id</font>`<font style="color:rgb(1, 1, 1);">：当前对话线程的唯一标识符，是后续检索该对话的关键依据。一个 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:rgb(1, 1, 1);"> 对象可管理多个 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);">（会话）实例，此字段用于明确当前操作对应的具体会话对象。示例值："test_id_modification"。</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">app_name</font>`<font style="color:rgb(1, 1, 1);">：标识当前对话所属的智能体应用。示例值："id_modifier_workflow"。</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">userId</font>`<font style="color:rgb(1, 1, 1);">：将对话与特定用户关联的关联字段，用于用户维度的对话管理与权限控制。</font>
    2. <font style="color:rgb(1, 1, 1);">对话历史（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">events</font>`<font style="color:rgb(1, 1, 1);">）：</font>

<font style="color:black;">按时间顺序排列的交互序列，包含当前对话线程中发生的所有交互行为（以 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event</font>`<font style="color:black;"> 对象形式存储），涵盖用户消息、智能体响应、工具调用动作等全量交互记录。</font>

    3. <font style="color:rgb(1, 1, 1);">会话状态（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">state</font>`<font style="color:rgb(1, 1, 1);">）：</font>

<font style="color:black;">用于存储</font><font style="color:black;">仅与当前活跃对话相关的临时数据</font><font style="color:black;">，相当于智能体在交互过程中的 “临时草稿本”。下一节将详细介绍 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">state</font>`<font style="color:black;"> 的具体使用与管理方式。</font>

    4. <font style="color:rgb(1, 1, 1);">活动追踪（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">lastUpdateTime</font>`<font style="color:rgb(1, 1, 1);">）：</font>

<font style="color:black;">时间戳字段，记录当前对话线程中最后一次交互事件的发生时间，用于会话活跃度判断与过期管理。</font>

##### 1.4 会话生命周期
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:black;"> 与 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:black;"> 在一次对话轮次中协作的简化流程：</font>

1. <font style="color:black;">开始或恢复：</font><font style="color:rgb(1, 1, 1);"> 应用程序需要使用 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:rgb(1, 1, 1);"> 要么 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">create_session</font>`<font style="color:rgb(1, 1, 1);">（用于新聊天），要么使用现有的 session id。</font>
2. <font style="color:black;">提供上下文：</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Runner</font>`<font style="color:rgb(1, 1, 1);"> 从适当的服务方法获取相应的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);"> 对象，为智能体提供对相应 Session 的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">state</font>`<font style="color:rgb(1, 1, 1);"> 和 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">events</font>`<font style="color:rgb(1, 1, 1);"> 的访问权限。</font>
3. <font style="color:black;">智能体处理：</font><font style="color:rgb(1, 1, 1);"> 用户用查询提示智能体。智能体分析查询以及可能的 session </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">state</font>`<font style="color:rgb(1, 1, 1);"> 和 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">events</font>`<font style="color:rgb(1, 1, 1);"> 历史来确定响应。</font>
4. <font style="color:black;">响应和状态更新：</font><font style="color:rgb(1, 1, 1);"> 智能体生成响应（并可能标记要在 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">state</font>`<font style="color:rgb(1, 1, 1);"> 中更新的数据）。</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Runner</font>`<font style="color:rgb(1, 1, 1);"> 将其打包为 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event</font>`<font style="color:rgb(1, 1, 1);">。</font>
5. <font style="color:black;">保存交互：</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Runner</font>`<font style="color:rgb(1, 1, 1);"> 调用 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">sessionService.append_event(session, event)</font>`<font style="color:rgb(1, 1, 1);">，将 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">session</font>`<font style="color:rgb(1, 1, 1);"> 和新的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">event</font>`<font style="color:rgb(1, 1, 1);"> 作为参数。服务将 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event</font>`<font style="color:rgb(1, 1, 1);"> 添加到历史记录中，并根据事件中的信息更新存储中的 session </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">state</font>`<font style="color:rgb(1, 1, 1);">。session 的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">last_update_time</font>`<font style="color:rgb(1, 1, 1);"> 也会得到更新。</font>
6. <font style="color:black;">准备下一次：</font><font style="color:rgb(1, 1, 1);"> 智能体的响应发送给用户。更新后的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:rgb(1, 1, 1);"> 现在由 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:rgb(1, 1, 1);"> 存储，准备进行下一轮（这通常会在当前会话中继续对话，从步骤 1 重新开始循环）。</font>
7. <font style="color:black;">结束对话：</font><font style="color:rgb(1, 1, 1);"> 当对话结束时，你的应用程序调用 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">sessionService.delete_session(...)</font>`<font style="color:rgb(1, 1, 1);"> 来清理存储的会话数据（如果不再需要的话）。</font>

<font style="color:rgb(1, 1, 1);"></font>

#### 2 会话系统
<font style="color:black;">在OpenHands中：</font>

+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">WebSession</font>`<font style="color:rgb(1, 1, 1);"> 是一个 Web 服务器绑定的会话包装器，</font><font style="color:black;">负责管理单个 Web 客户端连接并协调 AgentSession 生命周期</font><font style="color:rgb(1, 1, 1);">。是 OpenHands 系统中连接前端用户界面和后端Agent执行的核心桥梁，负责协调整个交互流程。</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentSession</font>`<font style="color:rgb(1, 1, 1);"> 是 OpenHands 框架中 </font><font style="color:black;">Agent运行的 “上下文容器”</font><font style="color:rgb(1, 1, 1);">，核心作用是封装Agent执行所需的所有组件（Agent、控制器、运行时、内存、事件流），统一管理它们的生命周期（初始化、启动、通信、关闭），并提供会话级的配置隔离、数据持久化和状态管理，是Agent能够独立、稳定执行任务的基础。</font>

### 事件系统
<font style="color:black;">如果说 ReAct 范式是代理的 “大脑思维模式”，那么事件驱动架构就是Agent系统的 “神经网络”，它使用了发布-订阅模式，以去中心化的方式协调各组件高效运作，允许组件之间的松耦合通信。整个系统的核心并非僵硬的同步调用，而是一条承载所有关键活动的 “事件流”，系统中的各类核心操作都会被抽象为标准化的 “事件”。</font>

<font style="color:black;">OpenHands 中，EventStream 负责管理session中的触发的事件，以及事件注册函数的回调项目中注册事件回调函数，比如：</font>

+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Runtime</font>`<font style="color:rgb(1, 1, 1);">注册：只接收</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Action</font>`<font style="color:rgb(1, 1, 1);">的事件与runtime进行交互</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentController</font>`<font style="color:rgb(1, 1, 1);">注册，根据事件更新Agent状态</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">main</font>`<font style="color:rgb(1, 1, 1);">：命令行方式执行agent效果评估时使用，接收agent状态变更事件</font>

#### <font style="color:rgb(1, 1, 1);">EventStream</font>
<font style="color:rgb(0, 0, 0);">OpenHands 事件系统的核心是</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">EventStream</font>`<font style="color:rgb(0, 0, 0);">类（事件流系统），这是一个专门处理事件的系统，它的核心作用是维护了事件队列并支持事件的发布和订阅，管理和分发事件。这种事件驱动的架构使OpenHands能够处理异步操作，并支持多Agent之间的协作。</font>

<font style="color:black;">主要步骤包括：</font>

+ <font style="color:rgb(1, 1, 1);">启动一个循环运行的线程，这个线程负责从事件队列中读取事件，并将它们逐一发送到各个订阅模块的处理队列中。</font>
+ <font style="color:rgb(1, 1, 1);">当模块需要订阅事件时，它会调用一个订阅函数</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">subscribe</font>`<font style="color:rgb(1, 1, 1);">，这样事件流就会为该模块维护一个线程池，所有发送到该模块的事件都会被相应的回调函数处理。</font>
+ <font style="color:rgb(1, 1, 1);">任何地方需要向事件流中添加事件时，都会调用一个添加事件的函数</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">add_event</font>`<font style="color:rgb(1, 1, 1);">。</font>

<font style="color:black;">事件流的逻辑虽然简单，但确保了程序各部分之间的独立性和通信的一致性。这里的消息都是事件，分为两种类型：</font>

+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Action</font>`<font style="color:rgb(1, 1, 1);">：指需要执行的任务。</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Observation</font>`<font style="color:rgb(1, 1, 1);">：指环境对任务执行结果的回应。</font>

<font style="color:black;">下图展示了 OpenHands 中 Agent 与环境交互的核心机制：Agent 通过执行动作影响环境，环境通过观察结果反馈给 Agent，Agent 基于这些反馈做出下一步决策。：</font>

+ <font style="color:rgb(1, 1, 1);">Agent 决定执行一个动作，通过AgentController和EventStream传到了Runtime。</font>
+ <font style="color:rgb(1, 1, 1);">Runtime 在环境中执行该动作</font>
+ <font style="color:rgb(1, 1, 1);">环境产生一个观察结果作为执行结果</font>
+ <font style="color:rgb(1, 1, 1);">Runtime 捕获这个观察结果并发送到 EventStream（事件流）</font>
+ <font style="color:rgb(1, 1, 1);">EventStream 存储观察结果，然后通过AgentController通知Agent</font>
+ <font style="color:rgb(1, 1, 1);">Agent 获取更新后的历史记录（包括新的观察结果）</font>
+ <font style="color:rgb(1, 1, 1);">Agent 使用观察结果做出下一个决策</font>
+ <font style="color:rgb(1, 1, 1);">循环重复进行</font>

<!-- 这是一张图片，ocr 内容为：ACTIONS ACTIONS AGENTCONTROLLER AGENT RUNTIME EVENTSTREAM OBSERVATIONS ACTIONS STATE OBSERVATIONS 公众号.罗西的思考 FRONTEND ACTIONS -->
![](https://cdn.nlark.com/yuque/0/2026/png/62574793/1774530795069-1f3074f3-a1d4-4820-b04a-93b4c5bfc843.png)

##### <font style="color:rgb(0, 0, 0);">功能</font>
<font style="color:black;">EventStream 的功能如下：</font>

+ <font style="color:rgb(1, 1, 1);">事件订阅与通知机制。</font>
    - <font style="color:rgb(1, 1, 1);">多订阅者支持：通过EventStreamSubscriber枚举定义了多种订阅者类型。</font>
    - <font style="color:rgb(1, 1, 1);">灵活订阅机制：使用 subscribe 和 unscribe 方法管理订阅关系。</font>
    - <font style="color:rgb(1, 1, 1);">多回调支持：每个订阅者可以注册多个回调函数，通过callback_id进行区分。</font>
+ <font style="color:rgb(1, 1, 1);">事件处理与分发</font>
    - <font style="color:rgb(1, 1, 1);">异步队列处理：使用 queue.Queue和独立线程处理事件队列。</font>
    - <font style="color:rgb(1, 1, 1);">线程池执行：为每个订阅者的回调函数创建独立的线程池，避免阻塞。</font>
    - <font style="color:rgb(1, 1, 1);">顺序分发：按照订阅者ID的排序顺序将事件分发给订阅者。</font>
+ <font style="color:rgb(1, 1, 1);">事件存储与持久化</font>
    - <font style="color:rgb(1, 1, 1);">事件ID管理：为每个事件分配唯一ID并维护递增计数器。</font>
    - <font style="color:rgb(1, 1, 1);">时间戳记录：自动为事件添加时间戳。</font>
    - <font style="color:rgb(1, 1, 1);">文件存储：将事件以JSON格式持久化到文件系统。</font>
    - <font style="color:rgb(1, 1, 1);">缓存页面机制：使用页面缓存提高大量事件的读写性能。</font>
+ <font style="color:rgb(1, 1, 1);">工作流程：</font>
    - <font style="color:rgb(1, 1, 1);">组件通过subscribe方法注册为事件订阅者。</font>
    - <font style="color:rgb(1, 1, 1);">当有事件发生时，通过add_event方法添加到事件流。</font>
    - <font style="color:rgb(1, 1, 1);">add_event方法处理事件ID分配，时间戳设置、持久化存储。</font>
    - <font style="color:rgb(1, 1, 1);">事件被放入处理队列，由独立线程异步分发。</font>
    - <font style="color:rgb(1, 1, 1);">_process_queue 分发按照顺序将事件分发给所有订阅者的回调函数。</font>

##### <font style="color:rgb(0, 0, 0);">订阅</font>
<font style="color:black;">系统将任务拆解为一系列可监控的 "状态节点"，每个节点都配备专属的观察者实例。当某一节点的状态发生变更（例如从 "待执行" 转为 "执行中"，或从 "成功" 转为 "失败"），观察者会立即触发预设的回调逻辑，通知调度中心进行下一步处理。这种设计带来了两大核心优势：</font>

+ <font style="color:black;">实现了任务调度的 "松耦合"。调度中心无需主动查询每个任务的状态，而是被动接收状态变更通知，这大幅降低了系统各模块间的依赖关系，使得新增任务类型或修改调度逻辑时，无需重构整个框架。</font>
+ <font style="color:black;">支持动态优先级调整。当高紧急度的任务插入时，观察者可实时捕获这一事件，触发调度中心的优先级重排机制，暂停低优先级任务的资源分配，确保关键任务优先执行。这种灵活性在多项目并行的场景中尤为重要。</font>

<font style="color:rgb(0, 0, 0);">在这一架构中，所有组件都扮演着 “生产者” 或 “消费者” 的角色。生产者负责生成事件：代理决策后产生 “动作事件”，运行时环境执行任务后生成 “反馈事件”。消费者则通过订阅特定事件获取信息并响应：运行时订阅 “动作事件” 以执行具体任务，控制器订阅全量事件以维护系统状态。这种基于事件的交互模式，彻底打破了组件间的直接依赖。</font>

###### <font style="color:rgb(0, 0, 0);">订阅者</font>
<font style="color:black;">_subscribers 和 subscriber_id 起到如下作用。</font>

<font style="color:black;">subscriber_id 会唯一标识一个订阅者，每个订阅者代表系统的不同组件或者服务。不同的订阅者会处理事件，比如：</font>

+ <font style="color:black;">EventStreamSubscriber.SERVER: 服务器处理</font>
+ <font style="color:black;">EventStreamSubscriber.RUNTIME: 运行时处理</font>
+ <font style="color:black;">EventStreamSubscriber.AGENT_CONTROLLER: 代理控制器处理</font>

```python
class EventStreamSubscriber(str, Enum):
    AGENT_CONTROLLER = 'agent_controller'
    RESOLVER = 'openhands_resolver'
    SERVER = 'server'
    RUNTIME = 'runtime'
    MEMORY = 'memory'
    MAIN = 'main'
    TEST = 'test'
```

<font style="color:black;">几个大模块都是在</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">__init__</font>`<font style="color:black;">函数中完成模块的初始化准备工作，并且向事件流中订阅消息并注册各自模块的消息处理函数。事件回调函数会根据当前的事件进行状态机的状态转移。</font>

+ <font style="color:rgb(1, 1, 1);">Runtime 在事件流中订阅 EventStreamSubscriber.RUNTIME，事件回调函数会处理需要runtine处理的action，比如mcp/tool等等。</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Runtime</font>`<font style="color:rgb(1, 1, 1);">只处理可运行的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Action</font>`<font style="color:rgb(1, 1, 1);">事件，执行动作拿到输出</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Observation</font>`<font style="color:rgb(1, 1, 1);">发送回事件流中</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">isinstance(event, MCPAction)</font>`<font style="color:rgb(1, 1, 1);">执行MCP获取结果其他runtime支持的action则执行获取结果。</font>
+ <font style="color:rgb(1, 1, 1);">Memory 在事件流中订阅 EventStreamSubscriber.MEMORY。事件回调函数根据当前的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">event</font>`<font style="color:rgb(1, 1, 1);">生成一个带</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">microagent_knowledge</font>`<font style="color:rgb(1, 1, 1);">的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RecallObservation</font>`<font style="color:rgb(1, 1, 1);">并以</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ENVIRONMENT</font>`<font style="color:rgb(1, 1, 1);">作为源添加回事件流中，这里的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">microagent_knowledge</font>`<font style="color:rgb(1, 1, 1);">是一种特定提示词增强的方法。</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Memory</font>`<font style="color:rgb(1, 1, 1);">只处理</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RecallAction</font>`<font style="color:rgb(1, 1, 1);">，对于用户首次输入信息则将一些额外的工作空间上下文信息添加到</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RecallObservation</font>`<font style="color:rgb(1, 1, 1);">发送回事件流中，对于其他非用户首次的输入信息则加入microagent_knowledge到</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RecallObservation</font>`<font style="color:rgb(1, 1, 1);">发送回事件流中。</font>
+ <font style="color:rgb(1, 1, 1);">AgentController 在事件流中订阅 EventStreamSubscriber.AGENT_CONTROLLER。</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentController</font>`<font style="color:rgb(1, 1, 1);">作为主要状态管理模块，</font>
    - <font style="color:rgb(1, 1, 1);">对于</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">MessageAction</font>`<font style="color:rgb(1, 1, 1);">发送</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RecallAction</font>`<font style="color:rgb(1, 1, 1);">到事件流中</font>
    - <font style="color:rgb(1, 1, 1);">对于</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateAction</font>`<font style="color:rgb(1, 1, 1);">做Agent路由</font>
    - <font style="color:rgb(1, 1, 1);">根据</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Observation</font>`<font style="color:rgb(1, 1, 1);">事件进行状态变换</font>
    - <font style="color:rgb(1, 1, 1);">根据</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Action</font>`<font style="color:rgb(1, 1, 1);">进行状态变换和以下处理：</font>
    - <font style="color:rgb(1, 1, 1);">根据当前的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">event</font>`<font style="color:rgb(1, 1, 1);">判断进行调用</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">agent.step</font>`
+ <font style="color:rgb(1, 1, 1);">run_controller 在事件流中订阅 EventStreamSubscriber.MAIN。</font>
+ <font style="color:rgb(1, 1, 1);">WebSession、ConversationManager 会订阅 EventStreamSubscriber.SERVER。</font>

###### <font style="color:rgb(0, 0, 0);">分发</font>
<font style="color:rgb(0, 0, 0);">用户发送消息添加了一条消息到消息流中，系统会依据 subscriber_id 来决定哪些订阅者应该接收该类事件。这条消息会被广播到每一个消息通道中，通过注册的回调函数可以分析哪些模块对消息进行了处理。</font>

```python
    async def _process_queue(self) -> None:
        while should_continue() and not self._stop_flag.is_set():
            event = None
            try:
                event = self._queue.get(timeout=0.1)
            except queue.Empty:
                continue

            # pass each event to each callback in order
            for key in sorted(self._subscribers.keys()): # 此处会决定分发到哪里
                callbacks = self._subscribers[key]
                # Create a copy of the keys to avoid "dictionary changed size during iteration" error
                callback_ids = list(callbacks.keys())
                for callback_id in callback_ids:
                    # Check if callback_id still exists (might have been removed during iteration)
                    if callback_id in callbacks:
                        callback = callbacks[callback_id]
                        pool = self._thread_pools[key][callback_id]
                        future = pool.submit(callback, event)
                        future.add_done_callback(
                            self._make_error_handler(callback_id, key)
                        )
```

###### <font style="color:rgb(0, 0, 0);">资源管理</font>
<font style="color:rgb(0, 0, 0);">subscriber_id 帮助系统管理每个订阅者的资源。</font>

```python
    def _clean_up_subscriber(self, subscriber_id: str, callback_id: str) -> None:
        if subscriber_id not in self._subscribers:
            logger.warning(f'Subscriber not found during cleanup: {subscriber_id}')
            return
        if callback_id not in self._subscribers[subscriber_id]:
            logger.warning(f'Callback not found during cleanup: {callback_id}')
            return
        if (
            subscriber_id in self._thread_loops
            and callback_id in self._thread_loops[subscriber_id]
        ):
            loop = self._thread_loops[subscriber_id][callback_id]
            current_task = asyncio.current_task(loop)
            pending = [
                task for task in asyncio.all_tasks(loop) if task is not current_task
            ]
            for task in pending:
                task.cancel()
            try:
                loop.stop()
                loop.close()
            except Exception as e:
                logger.warning(
                    f'Error closing loop for {subscriber_id}/{callback_id}: {e}'
                )
            del self._thread_loops[subscriber_id][callback_id]

        if (
            subscriber_id in self._thread_pools
            and callback_id in self._thread_pools[subscriber_id]
        ):
            pool = self._thread_pools[subscriber_id][callback_id]
            pool.shutdown()
            del self._thread_pools[subscriber_id][callback_id]

        del self._subscribers[subscriber_id][callback_id]
```

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

#### Event
<font style="color:black;">在 OpenHands 系统中，Event 是系统中最基本的数据单元，代表系统中发生的各种动作和观察结果（用户输入、智能体文本、工具调用/结果、状态变更请求、控制信号）。所有事件都继承自 Event 基类。表示一个原子性事件。</font>

<font style="color:black;">想象一下，如果我们把</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event Stream</font>`<font style="color:black;">比作一个信息传递的“邮政系统”，那么</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event</font>`<font style="color:black;">就是这个系统中传递的“信件”。在OpenHands中，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event</font>`<font style="color:black;">是最基本的信息单位，它是一个标准化的数据结构，用来记录系统中发生的任何重要事件。</font>

<font style="color:black;">通过将Agent的思考（由LLM生成的自然语言输出）与系统的实际执行（结构化的Action/Observation）分开，我们解决了意图与执行之间的隔离。LLM负责决定“要做什么”，而Action/Observation则详细说明了“怎样去做”和“结果如何”，这确保了系统的稳定性和可预测性。</font>

##### <font style="color:black;">Event</font>
###### 定义
<font style="color:black;">每一个 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event</font>`<font style="color:black;"> 对象都携带了一些元数据，就像信封上的信息：</font>

+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">id</font>`<font style="color:rgb(1, 1, 1);">: 事件的唯一标识符。</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">source</font>`<font style="color:rgb(1, 1, 1);">: 事件的来源，可以是 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AGENT</font>`<font style="color:rgb(1, 1, 1);">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">USER</font>`<font style="color:rgb(1, 1, 1);"> 或 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ENVIRONMENT</font>`<font style="color:rgb(1, 1, 1);">。</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">timestamp</font>`<font style="color:rgb(1, 1, 1);">: 事件发生的时间戳。</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">cause</font>`<font style="color:rgb(1, 1, 1);">: 触发此事件的另一个事件的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">id</font>`<font style="color:rgb(1, 1, 1);">。</font>

<font style="color:black;">将系统中的所有互动都抽象为</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event</font>`<font style="color:black;">，我们得到了一种通用的语言。无论是Agent的决策、用户的消息还是环境的反馈，都可以统一处理、存储和分发。特别是</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">cause</font>`<font style="color:black;">字段，它像一条看不见的线，将Action和它引起的Observation紧密联系起来，形成了ReAct循环的因果链，这对于理解和调试Agent的行为至关重要。</font>

<font style="color:black;">EventStream 对Event的处理过程为：</font>

+ <font style="color:black;">事件通过 add_event 方法添加到流中</font>
+ <font style="color:black;">系统自动分配 ID 和时间戳</font>
+ <font style="color:black;">事件被存储到文件系统</font>
+ <font style="color:black;">事件被放入处理队列</font>

<font style="color:black;">系统通过 event_to_dict 和 event_from_dict 函数处理事件的序列化和反序列化，确保事件可以在不同组件间传输和存储。</font>

###### <font style="color:black;">分类</font>
<font style="color:black;">按照功能分类，事件主要分为两类：</font>

+ <font style="color:rgb(1, 1, 1);">第一种是Action（行动），它代表了智能代理想要对环境执行的具体操作。这并不是模糊不清的自然语言描述，而是一个明确的指令。例如，如果代理想要列出某个目录下的所有文件，它会发送一个清晰的指令，如“执行命令'ls -l'”。这样的指令让系统能够准确无误地理解代理的意图并执行相应的操作。</font>
+ <font style="color:rgb(1, 1, 1);">第二种是Observation（观察），它代表了智能代理从环境中收集到的信息。这通常是在执行了某个行动之后，系统给予的反馈。例如，如果代理执行了一个列出文件的命令，观察就会包含执行结果的详细信息，如“输出内容为'...'，退出代码为0”。这些信息帮助代理了解其行动的结果，并为下一步行动提供依据。</font>

<font style="color:black;">按来源，事件分类如下：</font>

+ <font style="color:rgb(1, 1, 1);">EventSource.AGENT 来自代理的操作和观察结果</font>
+ <font style="color:rgb(1, 1, 1);">EventSource.USER 来自用户的操作</font>
+ <font style="color:rgb(1, 1, 1);">EventSource.ENVIRONMENT 来自环境的操作和观察结果，这些事件可能包括：</font>
    - <font style="color:rgb(1, 1, 1);">系统状态变化</font>
    - <font style="color:rgb(1, 1, 1);">环境初始化完成通知</font>
    - <font style="color:rgb(1, 1, 1);">运行时状态更新</font>
    - <font style="color:rgb(1, 1, 1);">系统级的观察结果</font>

##### <font style="color:rgb(1, 1, 1);">Action</font>
###### 类型
<font style="color:black;">总共有 13 种不同的 Action 类型。这些 Action 涵盖了代理执行的各种操作，包括文件操作、命令执行、消息传递、状态管理、代理委托等核心功能。</font>

+ <font style="color:black;">基础 Action 类型：</font>
    - <font style="color:rgb(1, 1, 1);">Action – 抽象基类</font>
+ <font style="color:black;">具体 Action 实现：</font>
    - <font style="color:rgb(1, 1, 1);">AgentDelegateAction – 委托代理执行任务</font>
    - <font style="color:rgb(1, 1, 1);">AgentThinkAction：允许 Agent 添加纯文本到历史记录中的无操作。</font>
    - <font style="color:rgb(1, 1, 1);">AgentFinishAction – 代理完成任务，停止控制循环，允许用户输入新任务。</font>
    - <font style="color:rgb(1, 1, 1);">AgentRejectAction – 代理拒绝任务</font>
    - <font style="color:rgb(1, 1, 1);">AgentRecallAction：搜索记忆（例如向量数据库）。</font>
    - <font style="color:rgb(1, 1, 1);">BrowseInteractiveAction – 交互式浏览</font>
    - <font style="color:rgb(1, 1, 1);">ChangeAgentStateAction – 更改代理状态</font>
    - <font style="color:rgb(1, 1, 1);">CmdRunAction – 在沙盒终端中运行命令</font>
    - <font style="color:rgb(1, 1, 1);">CmdKillAction：杀死后台命令。</font>
    - <font style="color:rgb(1, 1, 1);">FileEditAction – 编辑文件</font>
    - <font style="color:rgb(1, 1, 1);">FileReadAction – 读取文件</font>
    - <font style="color:rgb(1, 1, 1);">IPythonRunCellAction – 交互式执行Python代码块（在Jupyter笔记本中）并接收</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">CmdOutputObservation</font>`<font style="color:rgb(1, 1, 1);">。</font>
    - <font style="color:rgb(1, 1, 1);">MessageAction – 消息操作，表示来自代理或用户的消息</font>
    - <font style="color:rgb(1, 1, 1);">AddTaskAction：向计划中添加子任务。</font>
    - <font style="color:rgb(1, 1, 1);">ModifyTaskAction：更改子任务的状态。</font>
    - <font style="color:rgb(1, 1, 1);">NullAction – 空操作</font>
    - <font style="color:rgb(1, 1, 1);">SystemMessageAction – 系统消息操作</font>
+ <font style="color:black;">特殊 Agent 相关 Action：</font>
    - <font style="color:rgb(1, 1, 1);">CondensationAction – 历史压缩操作</font>
    - <font style="color:rgb(1, 1, 1);">CondensationRequestAction – 请求历史压缩操作</font>
    - <font style="color:rgb(1, 1, 1);">RecallAction – 回忆操作</font>

###### <font style="color:rgb(1, 1, 1);">流程</font>
<font style="color:black;">在 OpenHands 的架构中，总体的事件流如下：Agent -> Action -> Runtime-> Observation -> Agent</font>

+ <font style="color:rgb(1, 1, 1);">Agent生成Action事件并发送到环境</font>
+ <font style="color:rgb(1, 1, 1);">事件通过EventStream传递给Runtime执行</font>
+ <font style="color:rgb(1, 1, 1);">Runtime执行相应操作</font>
+ <font style="color:rgb(1, 1, 1);">Environment 执行 Action 并生成 Observation 作为响应</font>
+ <font style="color:rgb(1, 1, 1);">Observation 被发送回 Agent 作为下一步决策的输入</font>

![画板](https://cdn.nlark.com/yuque/0/2026/jpeg/62574793/1774592664035-f3ced1f7-dc19-475a-a96c-64fff258845d.jpeg)

<font style="color:rgb(0, 0, 0);">为了解决线性工作流的脆弱性，引入了</font>**<font style="color:black;">闭环反馈</font>**<font style="color:rgb(0, 0, 0);">机制。现在，任务的每一步不再是一次性的调用，而是一个</font>**<font style="color:black;">可以自我纠错的 Agent</font>**<font style="color:rgb(0, 0, 0);">。这种 Agent 循环极大地提升了系统的鲁棒性和最终结果的质量，因为模型有机会从自己的错误中学习和恢复。</font>

##### <font style="color:rgb(1, 1, 1);">Observation</font>
<font style="color:rgb(0, 0, 0);">Action是Agent对环境（Runtime）发出的指令或者操作，Observation是环境对这些操作的响应或者反馈。它代表了环境对 Agent 执行的 Action 的响应，包含了操作结果、环境状态变化等信息，供 Agent 进行下一步决策使用。这种设计符合典型的强化学习和智能体系统的模式，其中 Agent 通过与环境交互（执行 Action 并接收 Observation）来完成任务。</font>

###### <font style="color:rgb(0, 0, 0);">类型</font>
<font style="color:black;">外部来源的 Observations，大部分 Observation 对象是从外部环境或运行时系统构建并传入的，这些 Observation 类型都代表了环境的不同状态，例如：</font>

<font style="color:black;">这些通常由运行时系统创建并通过事件流传递给控制器。</font>

+ <font style="color:rgb(1, 1, 1);">命令执行结果（CmdRunObservation）</font>
+ <font style="color:rgb(1, 1, 1);">文件读取结果（FileReadObservation）</font>
+ <font style="color:rgb(1, 1, 1);">IPython 执行结果（IPythonRunCellObservation）</font>
+ <font style="color:rgb(1, 1, 1);">浏览器交互结果（BrowserOutputObservation）</font>
+ <font style="color:rgb(1, 1, 1);">RecallObservation: 记忆检索结果</font>
+ <font style="color:rgb(1, 1, 1);">CmdOutputObservation：命令执行的输出。</font>
+ <font style="color:rgb(1, 1, 1);">BrowserOutputObservation：浏览 URL 后的输出。</font>
+ <font style="color:rgb(1, 1, 1);">FileReadObservation：文件读取操作的输出。</font>
+ <font style="color:rgb(1, 1, 1);">AgentRecallObservation：Agent 回忆操作的输出。</font>
+ <font style="color:rgb(1, 1, 1);">AgentErrorObservation：Agent 执行操作时发生错误的输出。</font>

<font style="color:black;">AgentController 内部构建的 Observations。在 AgentController 类中，有几处会直接构建 Observation 对象：</font>

+ <font style="color:rgb(1, 1, 1);">NullObservation：表示无操作或忽略的观察结果，用于过滤不需要处理的事件。</font>
+ <font style="color:rgb(1, 1, 1);">ErrorObservation：表示执行过程中发生的错误，包含错误信息供代理处理。</font>
+ <font style="color:rgb(1, 1, 1);">AgentStateChangedObservation：表示代理状态的变更，如加载、运行、错误等状态。比如，在AgentController的set_agent_state_to函数中，当agent状态发生改变时会创建一个AgentStateChangedObservation事件，并将其来源设置为 EventSource.ENVIRONMENT。</font>

###### 流程
<font style="color:rgb(0, 0, 0);">Observation 在 Agent 中的处理流程如下：</font>

```python
Runtime 执行 Action --> 产生 Observation --> EventStream 发布事件 --> AgentController.on_event 接收 --> 判断是否需要 step --> AgentController._step 处理 --> 调用 Agent.step --> Agent 基于历史事件（包括 Observation）决策
```

<font style="color:black;">具体流程如下：</font>

+ <font style="color:rgb(1, 1, 1);">Runtime执行完action之后，生成observation事件。</font>
+ <font style="color:rgb(1, 1, 1);">事件通过EventStream.add_event() 传回Agent，这些 Observations 通过事件流传递，用于更新代理的状态和历史记录。</font>
+ <font style="color:rgb(1, 1, 1);">AgentController 订阅 EventStream，在 on_event() 方法中处理这些事件。</font>
+ <font style="color:rgb(1, 1, 1);">Agent基于observation决定下一步动作。</font>

<font style="color:black;">Observation 在 Agent 决策中的作用如下：</font>

+ <font style="color:rgb(1, 1, 1);">Agent 状态更新：AgentStateChangedObservation 会更新 Agent 的内部状态；错误 Observation 会触发错误处理流程。</font>
+ <font style="color:rgb(1, 1, 1);">历史记录：所有 Observations 都被存储在 State.history 中；Agent 在决策时会回顾整个历史记录，包括所有的 Actions 和 Observations。</font>
+ <font style="color:rgb(1, 1, 1);">决策依据：Agent（LLM）通过分析历史中的 Observations 来理解环境状态；例如 CmdOutputObservation 提供了命令执行结果，Agent 据此决定下一步行动。</font>

###### <font style="color:rgb(1, 1, 1);">细节</font>
<font style="color:black;">主要的 Observation 构建位置包括：</font>

+ <font style="color:rgb(1, 1, 1);">运行时环境（执行命令、文件操作等）</font>
+ <font style="color:rgb(1, 1, 1);">AgentController._reset () 方法（构建 ErrorObservation）</font>
+ <font style="color:rgb(1, 1, 1);">AgentController.set_agent_state_to () 方法（构建 AgentStateChangedObservation）</font>
+ <font style="color:rgb(1, 1, 1);">AgentController.end_delegate () 方法（构建 AgentDelegateObservation）</font>

##### <font style="color:rgb(1, 1, 1);">Environment</font>
<font style="color:black;">针对 EventSource.ENVIRONMENT，本小节做特殊说明。</font>

<font style="color:black;">EventSource.ENVIRONMENT 通常表示由系统环境或者基础设施生成的事件，可能包括：</font>

+ <font style="color:rgb(1, 1, 1);">系统状态变化。</font>
+ <font style="color:rgb(1, 1, 1);">环境初始化完成通知。</font>
+ <font style="color:rgb(1, 1, 1);">运行时状态更新。</font>
+ <font style="color:rgb(1, 1, 1);">系统级的观察结果。</font>

```python
def handle_exit_command(
    config: OpenHandsConfig,
    event_stream: EventStream,
    usage_metrics: UsageMetrics,
    sid: str,
) -> bool:
    if confirm_exit:
        event_stream.add_event(
            ChangeAgentStateAction(AgentState.STOPPED),
            EventSource.ENVIRONMENT,
        )

# 在 Runtime 中
    def maybe_run_setup_script(self):
        # setup scripts time out after 10 minutes
        action = CmdRunAction(
            f'chmod +x {setup_script} && source {setup_script}',
            blocking=True,
            hidden=True,
        )
        # Add the action to the event stream as an ENVIRONMENT event
        source = EventSource.ENVIRONMENT
        self.event_stream.add_event(action, source)

# 在Memory类 _on_event 方法中，我们可以看到环境返回的 Observation 被重新标记为 Agent 事件发送到 UI:python
async def _on_event(self, event: Event):
    self.event_stream.add_event(workspace_obs, EventSource.ENVIRONMENT)

# 在 AgentSession 中
                    self.event_stream.add_event(
                        ChangeAgentStateAction(AgentState.RUNNING),
                        EventSource.ENVIRONMENT,
                    )

# 在 WebSession 中
        self.agent_session.event_stream.add_event(
            AgentStateChangedObservation('', AgentState.LOADING),
            EventSource.ENVIRONMENT,
        )

# AgentController 中
    async def set_agent_state_to(self, new_state: AgentState) -> None:
        self.event_stream.add_event(
            AgentStateChangedObservation('', self.state.agent_state, reason),
            EventSource.ENVIRONMENT,
        )
```

<font style="color:rgb(0, 0, 0);">虽然Runtime也会产生一些观察结果，但具体是 EventSource.ENVIRONMENT 或者 EventSource.AGENT，取决于上下文。</font>

##### <font style="color:rgb(0, 0, 0);">AgentThinkAction</font>
<font style="color:rgb(0, 0, 0);"> AgentThinkAction，该Action允许 Agent 添加纯文本到历史记录中的无操作。</font>

```python

            # ================================================
            # AgentThinkAction
            # ================================================
            elif tool_call.function.name == ThinkTool['function']['name']:
                action = AgentThinkAction(thought=arguments.get('thought', ''))

```

<font style="color:rgb(0, 0, 0);">ThinkTool 是对Anthropic  Think Tool设计理念的模仿或再实现。</font>

<font style="color:black;">Anthropic Think Tool在执行复杂任务时为其创建专门用于结构化思考的空间。Think Tool发生在AI开始响应之后，像是在工作过程中主动停下来整理思路。通过“think”工具，Anthropic  赋予 Claude 在得出最终答案的过程中插入一个额外思考步骤的能力——该步骤拥有自己专属的思考空间，用以判断当前是否已掌握继续推进所需的全部信息。这一机制在执行长链条的工具调用或与用户进行多轮复杂对话时尤为有用。</font>

<font style="color:black;">尽管听起来与延伸思考（extended thinking）类似，但二者概念不同：延伸思考发生在 Claude 开始生成回复</font>**<font style="color:black;">之前</font>**<font style="color:black;">，让模型深度思考并迭代方案；而“思考”工具用于 Claude</font>**<font style="color:black;">已开始生成回复后</font>**<font style="color:black;">，在遇到长链条工具调用或长对话时，主动暂停并思考是否已掌握足够信息。它尤其适用于模型无法仅凭用户查询获得全部信息，而需处理外部信息（如工具返回结果）的场景。</font>

<font style="color:black;">相比延伸思考，“思考”工具所进行的推理范围更窄，更聚焦于新发现的信息。</font>

<font style="color:black;">Anthropic  推荐：</font>

+ <font style="color:rgb(1, 1, 1);">对于非顺序工具调用或简单指令遵循，优先使用延伸思考；</font>
+ <font style="color:rgb(1, 1, 1);">对于复杂工具链、需仔细分析工具输出、策略密集型环境或代价高昂的序列决策，使用“思考”工具。</font>

###### <font style="color:black;">何时使用“思考”工具</font>
<font style="color:black;">适用场景：</font>

+ <font style="color:rgb(1, 1, 1);">需深度分析前序工具输出，可能回溯方案；</font>
+ <font style="color:rgb(1, 1, 1);">策略密集型环境，需验证合规性；</font>
+ <font style="color:rgb(1, 1, 1);">序列决策，每步依赖前序结果且错误代价高。</font>

<font style="color:black;">不适用场景</font><font style="color:black;">：</font>

+ <font style="color:rgb(1, 1, 1);">单次或并行工具调用即可完成任务；</font>
+ <font style="color:rgb(1, 1, 1);">约束简单，默认行为已足够。</font>

###### <font style="color:black;">最佳实践</font>
1. <font style="color:black;">领域示例驱动的提示</font><font style="color:rgb(1, 1, 1);">给出何时、如何调用思考工具，并提供贴合业务的推理示例（见原文航空域提示）。</font>
2. <font style="color:black;">将复杂指令放入系统提示</font><font style="color:rgb(1, 1, 1);">长且复杂的思考指南放在系统提示而非工具描述中，效果更佳。</font>
3. <font style="color:black;">持续监控与迭代</font><font style="color:rgb(1, 1, 1);">观察 Claude 实际调用模式，针对性调整提示，以强化有效思考路径。</font>

```python
_THINK_DESCRIPTION = """Use the tool to think about something. It will not obtain new information or make any changes to the repository, but just log the thought. Use it when complex reasoning or brainstorming is needed.

Common use cases:
1. When exploring a repository and discovering the source of a bug, call this tool to brainstorm several unique ways of fixing the bug, and assess which change(s) are likely to be simplest and most effective.
2. After receiving test results, use this tool to brainstorm ways to fix failing tests.
3. When planning a complex refactoring, use this tool to outline different approaches and their tradeoffs.
4. When designing a new feature, use this tool to think through architecture decisions and implementation details.
5. When debugging a complex issue, use this tool to organize your thoughts and hypotheses.

The tool simply logs your thought process for better transparency and does not execute any code or make changes."""

ThinkTool = ChatCompletionToolParam(
    type='function',
    function=ChatCompletionToolParamFunctionChunk(
        name='think',
        description=_THINK_DESCRIPTION,
        parameters={
            'type': 'object',
            'properties': {
                'thought': {'type': 'string', 'description': 'The thought to log.'},
            },
            'required': ['thought'],
        },
    ),
)

class ThinkExecutor(ToolExecutor):
    def __call__(
        self,
        _: ThinkAction,
        conversation: "BaseConversation | None" = None,  # noqa: ARG002
    ) -> ThinkObservation:
        return ThinkObservation.from_text(text="Your thought has been logged.")


class ThinkTool(ToolDefinition[ThinkAction, ThinkObservation]):
    """Tool for logging thoughts without making changes."""

    @classmethod
    def create(
        cls,
        conv_state: "ConversationState | None" = None,  # noqa: ARG003
        **params,
    ) -> Sequence[Self]:
        """Create ThinkTool instance.

        Args:
            conv_state: Optional conversation state (not used by ThinkTool).
            **params: Additional parameters (none supported).

        Returns:
            A sequence containing a single ThinkTool instance.

        Raises:
            ValueError: If any parameters are provided.
        """
        if params:
            raise ValueError("ThinkTool doesn't accept parameters")
        return [
            cls(
                description=THINK_DESCRIPTION,
                action_type=ThinkAction,
                observation_type=ThinkObservation,
                executor=ThinkExecutor(),
                annotations=ToolAnnotations(
                    readOnlyHint=True,
                    destructiveHint=False,
                    idempotentHint=True,
                    openWorldHint=False,
                ),
            )
        ]
```

<font style="color:rgb(1, 1, 1);"></font>

<font style="color:rgb(1, 1, 1);"></font>

<font style="color:rgb(1, 1, 1);"></font>

<font style="color:rgb(1, 1, 1);"></font>

<font style="color:rgb(1, 1, 1);"></font>

<font style="color:rgb(1, 1, 1);"></font>

<font style="color:rgb(1, 1, 1);"></font>

### Agent
<font style="color:black;">智能体（Agent）是一种能够感知和理解环境，并使用工具来实现目标的应用程序。LLM能够动态指导自己的过程和工具使用，保持对任务完成方式的控制。Agent的设计旨在更灵活地处理某些任务，其决策由模型决定，而非预定义的规则。</font>

<font style="color:black;">借助 CodeAct 的 LLM 智能体，OpenHands 通过交互式的多轮流程，展现出显著的优势：</font>

+ <font style="color:rgb(1, 1, 1);">智能体能够接收新的观察数据，并据此优化先前的行动方案。这类似于人类在任务执行中，依据新信息灵活调整策略的过程。</font>
+ <font style="color:rgb(1, 1, 1);">依托记忆与反馈机制，智能体可随时间提升自身性能。它能将过往经验铭记于心，并在后续任务中加以运用，不断进步，恰似一名持续学习成长的学生。</font>
+ <font style="color:rgb(1, 1, 1);">此外，智能体还能胜任复杂的流程任务，涵盖模型训练、数据可视化以及自动化决策等。这表明 CodeAct 不仅能处理基础任务，更能驾驭高级且复杂的作业，例如训练机器学习模型、绘制图表以及实施自动决策等。</font>

#### <font style="color:rgb(1, 1, 1);">状态管理</font>
##### 设计要点
<font style="color:black;">多任务并发执行时，任务状态易出现冲突；长流程任务的中间状态（如已完成子任务、待处理步骤）易丢失；异常中断后难以精准恢复到中断前的状态。因此，需要有一个数据结构来维护Agent的状态，这就是State。</font>

<font style="color:black;">在每个 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Session</font>`<font style="color:black;">（我们的对话线程）中，</font>`**<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">state</font>**`<font style="color:black;"> 属性就像智能体专用于该特定交互的草稿板，是智能体存储和更新对话期间所需动态细节的地方。</font>

<font style="color:black;">状态管理的价值在于</font>**<font style="color:black;">可追溯与可恢复</font>**<font style="color:black;">：任何时刻都能回答”当前在哪一步、为什么这样做、结果如何、接下来做什么”。在出现错误或需要人工介入时，可以精确定位问题并从断点恢复。状态设计最佳实践如下：</font>

+ <font style="color:black;">最小主义：</font><font style="color:rgb(1, 1, 1);"> 仅存储必要的、动态的数据。</font>
+ <font style="color:black;">序列化：</font><font style="color:rgb(1, 1, 1);"> 使用基本的、可序列化的类型。</font>
+ <font style="color:black;">描述性键和前缀：</font><font style="color:rgb(1, 1, 1);"> 使用清晰的名称和适当的前缀（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">user:</font>`<font style="color:rgb(1, 1, 1);">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">app:</font>`<font style="color:rgb(1, 1, 1);">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">temp:</font>`<font style="color:rgb(1, 1, 1);"> 或无前缀）。</font>
+ <font style="color:black;">浅层结构：</font><font style="color:rgb(1, 1, 1);"> 尽可能避免深层嵌套。</font>
+ <font style="color:black;">标准更新流程：</font><font style="color:rgb(1, 1, 1);"> 依赖 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">append_event</font>`<font style="color:rgb(1, 1, 1);">。</font>

##### State类
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:black;">类作为全面的数据容器，用于跟踪 OpenHands 系统中智能体的运行状态。它维护智能体运行、演进和从会话中恢复所需的所有关键信息，包括对话历史、运行指标、迭代控制和错误记录。</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">save_to_session</font>`<font style="color:black;">方法支持智能体状态的持久化存储，允许在不同的执行实例之间恢复会话和保持连续性。</font>

<font style="color:black;">对于需要长时间运行且状态不断变化的 Agent 任务来说，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:black;">的作用至关重要。</font>

+ <font style="color:rgb(1, 1, 1);">首先，它是 Agent 决策的核心依据，尤其是完整的历史事件记录，为 Agent 提供了不可或缺的上下文信息，让决策不再盲目；</font>
+ <font style="color:rgb(1, 1, 1);">其次，外部系统（比如用户界面或控制器）可以通过调整</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:rgb(1, 1, 1);">来管理 Agent 的生命周期，实现暂停、恢复、终止等操作；</font>
+ <font style="color:rgb(1, 1, 1);">更重要的是，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:rgb(1, 1, 1);">可以被序列化存储，当任务因意外中断时，系统能通过加载存储的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:rgb(1, 1, 1);">，让任务从断点处精确恢复，完美解决了长周期任务的连续性问题。</font>

#### Agent系统
##### Base Class
<font style="color:black;">实际上，我们要实现一个 AI Agent，最简单的就是以 ReAct 为基础，去构建一个不断循环的推理（Reason），行动（Act）和观察（Observe）。</font>

<font style="color:black;">而在 OpenHands 的技术体系中，Agent 系统凭借高度灵活的模块化架构，实现了多样化专业 Agent 的开发与适配。这一设计的根基，是一个名为</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Agent</font>`<font style="color:black;">的抽象基类 —— 它就像所有 Agent 的 “通用模板”，不仅规定了必须实现的核心接口，还封装了各类 Agent 都需要的基础功能，确保了不同 Agent 在系统中的兼容性。</font>

<font style="color:black;">所有 Agent 都必须遵循</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Agent</font>`<font style="color:black;">基类的规范，其中最核心的就是</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">step()</font>`<font style="color:black;">方法。这个方法如同 Agent 的 “决策入口”，接收</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:black;">作为输入，经过内部逻辑处理后输出</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Action</font>`<font style="color:black;">。这种清晰简洁的接口设计，让系统能轻松接入新的 Agent 实现，或是在不同 Agent 之间切换，大大提升了扩展性。</font>

```python
class Agent(ABC):
    DEPRECATED = False
    """
    This abstract base class is an general interface for an agent dedicated to
    executing a specific instruction and allowing human interaction with the
    agent during execution.
    It tracks the execution status and maintains a history of interactions.
    """

    _registry: dict[str, type['Agent']] = {}
    sandbox_plugins: list[PluginRequirement] = []

    config_model: type[AgentConfig] = AgentConfig
    """Class field that specifies the config model to use for the agent. Subclasses may override with a derived config model if needed."""

    def __init__(
        self,
        config: AgentConfig,
        llm_registry: LLMRegistry,
    ):
        self.llm = llm_registry.get_llm_from_agent_config('agent', config)
        self.llm_registry = llm_registry
        self.config = config
        self._complete = False
        self._prompt_manager: 'PromptManager' | None = None
        self.mcp_tools: dict[str, ChatCompletionToolParam] = {}
        self.tools: list = []

    @abstractmethod
    def step(self, state: 'State') -> 'Action':
        """Starts the execution of the assigned instruction. This method should
        be implemented by subclasses to define the specific execution logic.
        """
        pass

```

##### Agent类型
<font style="color:black;">在 OpenHands 的智能体系中，针对不同任务场景设计了多种专业化 Agent，它们如同分工明确的 “岗位专员”，各自承载着独特的功能使命，共同支撑起系统的多样化能力。</font>

1. <font style="color:rgb(1, 1, 1);">CodeActAgent。作为系统的核心力量，CodeActAgent 践行了 CodeAct 的核心理念，将所有行动统一到代码层面，具备极强的通用性。它主要负责处理各类代码相关任务，既能执行 bash 命令，也能运行 Python 代码。其工作原理很巧妙：先向大语言模型提供文件读写、命令执行等 “工具” 的详细定义，再借助模型的函数调用或工具调用能力，让模型根据任务需求自主选择合适的工具完成操作，堪称系统中无所不能的 “技术骨干”。</font>
2. <font style="color:rgb(1, 1, 1);">BrowsingAgent。专注于网页交互任务的 BrowsingAgent，就像一位专业的网页操作专员。它会把网页的无障碍树作为上下文信息传递给大语言模型，帮助模型理解网页的结构布局。同时，它还提供了点击、填写表单、滚动页面等一系列网页交互动作，模型通过分析无障碍树制定操作策略，由它来精准执行，高效完成网页相关的任务。</font>
3. <font style="color:rgb(1, 1, 1);">ReadOnlyAgent。这是一位坚守 “不修改原则” 的特殊 Agent。它的核心特点是只读不写，只能进行查看类操作，不会执行任何可能改变系统状态或修改数据的动作，在需要保障系统安全、避免数据被误改的场景中发挥着重要作用。</font>
4. <font style="color:rgb(1, 1, 1);">VisualBrowsingAgent。作为 BrowsingAgent 的 “视觉增强版”，VisualBrowsingAgent 具备处理视觉信息的能力。它不仅能理解网页的结构，还能识别网页中的图像等视觉内容，针对需要分析视觉元素的网页任务，比如识别图片中的信息、基于视觉布局进行操作等，它能展现出独特的优势。</font>
5. <font style="color:rgb(1, 1, 1);">DummyAgent。DummyAgent 是一个结构简单的 Agent，主要承担测试任务。它就像系统的 “测试道具”，开发者可以通过它验证系统的基础功能和交互逻辑，为其他 Agent 的开发和调试提供支持，是保障系统稳定性的重要辅助角色。</font>
6. <font style="color:rgb(1, 1, 1);">LocAgent。LocAgent 实现了LocAgent: Graph-Guided LLM Agents for Code Localization 的Agent。LocAgent 首先将代码库解析为一个异构图表示，其中包含了多种类型的代码实体及其依赖关系。在此基础上，系统构建了分层稀疏索引，这不仅支持了高效的内容检索，还使得结构化的探索成为可能。借助这些索引，LocAgent 能够结合图结构与工具接口，执行由 Agent 驱动的逐步搜索过程，从而精准地完成代码定位任务。这种多跳推理的方式，使得 LocAgent 能够逐步接近目标代码，实现高效的代码定位。</font>

<font style="color:black;">作为系统的 “智能决策者”，每个 Agent 的核心动力都来自大型语言模型（LLM）。它的工作目标十分明确：基于当前任务的完整上下文信息（也就是</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:black;">对象），判断并输出下一步该执行的具体操作（即</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Action</font>`<font style="color:black;">）。这种将决策逻辑完全 “打包” 在 Agent 内部的设计，是实现系统模块化的关键 —— 就像不同的专业工具各司其职，Agent 只需专注于自己的决策任务，无需干扰其他组件。而</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">agenthub</font>`<font style="color:black;">的存在更让这套体系如虎添翼，它如同一个 “Agent 人才库”，汇集了具备不同专业技能的 Agent，系统可根据具体任务需求灵活选择或委托相应的 Agent 来处理。</font>

<font style="color:black;">每个 Agent 被设计成一个循环，在每次迭代中，通过调用 agent.step() 方法，以状态 （State）作为输入，输出动作 （Actions）来执行操作或命令，在执行动作的后可能接收到的观察 （Observations）结果。</font>

<font style="color:black;">在实现的过程中，每个 Agent 类都必须实现 step 和 search_memory 方法，以便执行指令和从记忆中查询信息。该抽象类还提供了一些辅助方法，如 reset、register、get_cls、list_agents，帮助管理 Agent 的状态及其注册信息。</font>

<font style="color:rgb(0, 0, 0);">而一个Agent最简驱动流程如下。</font>

```python
while True:
  prompt = agent.generate_prompt(state)
  response = llm.completion(prompt)
  action = agent.parse_response(response)
  observation = runtime.run(action)
  state = state.update(action, observation)
```



































#### State
<font style="color:black;">State 对象是 Agent 执行任务时所依赖的关键信息的集合。它包括以下内容：</font>

+ <font style="color:rgb(1, 1, 1);">Agent 采取的动作的历史记录，以及这些动作产生的观察结果（例如文件内容、命令输出）。</font>
+ <font style="color:rgb(1, 1, 1);">自最近一步以来发生的一系列动作和观察的轨迹。</font>
+ <font style="color:rgb(1, 1, 1);">一个 plan 对象，包含主要目标。Agent 可以通过 AddTaskAction 和 ModifyTaskAction 来添加和修改子任务。</font>

##### 特色
<font style="color:black;">OpenHands State的主要特色如下：</font>

1. <font style="color:black;">全面的状态跟踪</font><font style="color:rgb(1, 1, 1);">：捕获智能体操作的所有方面，从当前状态和对话历史到性能指标和错误记录。</font>
2. <font style="color:black;">多智能体支持</font><font style="color:rgb(1, 1, 1);">：通过</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">delegate_level</font>`<font style="color:rgb(1, 1, 1);">和父指标快照包含委托层级跟踪，用于协调多智能体操作。</font>
3. <font style="color:black;">持久化机制</font><font style="color:rgb(1, 1, 1);">：通过 pickle 序列化和 base64 编码提供可靠的会话保存，并处理遗留状态文件的向后兼容性。</font>
4. <font style="color:black;">运行控制</font><font style="color:rgb(1, 1, 1);">：整合迭代和预算控制标志，管理资源使用并防止无限循环。</font>
5. <font style="color:black;">可扩展性</font><font style="color:rgb(1, 1, 1);">：包含</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">extra_data</font>`<font style="color:rgb(1, 1, 1);">字段用于特定任务信息，使类适用于不同的使用场景。</font>
6. <font style="color:black;">状态转换</font><font style="color:rgb(1, 1, 1);">：跟踪当前状态和恢复状态，管理智能体生命周期（LOADING、RUNNING、PAUSED 等）。</font>
7. <font style="color:black;">历史管理</font><font style="color:rgb(1, 1, 1);">：通过起始 / 结束索引维护事件历史，跟踪相关对话片段。</font>

##### State 定义
###### OpenHands State
<font style="color:black;">State表示 OpenHands 系统中代理的运行状态，保存其操作和记忆的数据，实际上聚合了Agent做出决策所需要的所有信息：</font>

+ <font style="color:rgb(1, 1, 1);">多代理/委托状态：</font>
    - <font style="color:rgb(1, 1, 1);">存储任务（代理与用户之间的对话）</font>
    - <font style="color:rgb(1, 1, 1);">子任务（代理与用户或其他代理之间的对话）</font>
    - <font style="color:rgb(1, 1, 1);">全局和局部迭代次数</font>
    - <font style="color:rgb(1, 1, 1);">多代理交互的委托层级数</font>
    - <font style="color:rgb(1, 1, 1);">几乎卡住的状态</font>
+ <font style="color:rgb(1, 1, 1);">代理的运行状态：</font>
    - <font style="color:rgb(1, 1, 1);">当前代理状态（例如，加载中、运行中、已暂停）</font>
    - <font style="color:rgb(1, 1, 1);">流量控制状态，用于速率限制</font>
    - <font style="color:rgb(1, 1, 1);">确认模式</font>
    - <font style="color:rgb(1, 1, 1);">遇到的最新错误</font>
+ <font style="color:rgb(1, 1, 1);">保存和恢复代理的数据：</font>
    - <font style="color:rgb(1, 1, 1);">保存和从会话中恢复</font>
    - <font style="color:rgb(1, 1, 1);">使用 pickle 和 base64 序列化</font>
+ <font style="color:rgb(1, 1, 1);">保存/恢复关于消息历史的数据：</font>
    - <font style="color:rgb(1, 1, 1);">代理历史中事件的开始和结束 ID</font>
    - <font style="color:rgb(1, 1, 1);">摘要和委托摘要</font>
+ <font style="color:rgb(1, 1, 1);">指标：</font>
    - <font style="color:rgb(1, 1, 1);">当前任务的全局指标</font>
    - <font style="color:rgb(1, 1, 1);">当前子任务的局部指标</font>
+ <font style="color:rgb(1, 1, 1);">额外数据：</font>
    - <font style="color:rgb(1, 1, 1);">额外的任务特定数据"</font>

```python
@dataclass
class State:
    """表示OpenHands系统中智能体的运行状态，保存其操作和内存数据。"""

    session_id: str = ''  # 当前会话的唯一标识符
    user_id: Optional[str] = None  # 与会话相关联的用户标识符
    iteration_flag: IterationControlFlag = field(  # 控制迭代限制和进度
        default_factory=lambda: IterationControlFlag(
            limit_increase_amount=100, current_value=0, max_value=100
        )
    )
    conversation_stats: Optional[ConversationStats] = None  # 关于对话历史的统计信息
    budget_flag: Optional[BudgetControlFlag] = None  # 控制资源预算限制
    confirmation_mode: bool = False  # 智能体在执行操作前是否需要确认
    history: List[Event] = field(default_factory=list)  # 智能体操作中的事件记录
    inputs: Dict = field(default_factory=dict)  # 存储智能体的输入参数
    outputs: Dict = field(default_factory=dict)  # 存储智能体生成的输出结果
    agent_state: AgentState = AgentState.LOADING  # 智能体当前的运行状态
    resume_state: Optional[AgentState] = None  # 暂停后要返回的状态

    # 根智能体的层级为0，每个委托层级增加1
    delegate_level: int = 0  # 多智能体委托中的层级结构
    # start_id和end_id跟踪历史中事件的范围
    start_id: int = -1  # 历史中相关事件的起始索引
    end_id: int = -1  # 历史中相关事件的结束索引

    parent_metrics_snapshot: Optional[Metrics] = None  # 父智能体指标的快照
    parent_iteration: int = 100  # 来自父智能体的迭代计数

    # 注意：控制器使用此字段跟踪委托前父级的指标快照
    # 评估任务存储跟踪任务进度/状态所需的额外数据
    extra_data: Dict[str, Any] = field(default_factory=dict)  # 特定于任务的附加数据
    last_error: str = ''  # 最近遇到的错误记录

    # 注意：已弃用的参数，暂时保留以确保向后兼容性
    # 将在30天后移除
    iteration: Optional[int] = None  # 已弃用：使用iteration_flag替代
    local_iteration: Optional[int] = None  # 已弃用：本地迭代计数器
    max_iterations: Optional[int] = None  # 已弃用：最大迭代限制
    traffic_control_state: Optional[TrafficControlState] = None  # 已弃用：速率限制状态
    local_metrics: Optional[Metrics] = None  # 已弃用：使用metrics替代
    delegates: Optional[Dict[Tuple[int, int], Tuple[str, str]]] = None  # 已弃用：委托跟踪

    metrics: Metrics = field(default_factory=Metrics)  # 当前任务的性能指标

    def save_to_session(
        self, sid: str, file_store: FileStore, user_id: Optional[str]
    ) -> None:
        """将当前状态保存到持久存储中，以便以后检索。

        参数：
            sid: 与此状态相关联的会话ID
            file_store: 用于保存的存储系统
            user_id: 与此会话相关联的用户ID
        """
        # 暂时移除对话统计信息，因为它们自行处理持久性
        conversation_stats = self.conversation_stats
        self.conversation_stats = None

        # 序列化状态对象
        pickled = pickle.dumps(self)
        logger.debug(f'Saving state to session {sid}:{self.agent_state}')
        encoded = base64.b64encode(pickled).decode('utf-8')

        try:
            # 将编码后的状态写入文件存储
            file_store.write(
                get_conversation_agent_state_filename(sid, user_id), encoded
            )

            # 在SaaS/远程环境中清理旧的状态文件
            if user_id:
                old_filename = get_conversation_agent_state_filename(sid)
                try:
                    file_store.delete(old_filename)
                except Exception:
                    pass  # 删除旧文件时忽略错误
        except Exception as e:
            logger.error(f'Failed to save state to session: {e}')
            raise e
        finally:
            # 恢复对话统计信息引用
            self.conversation_stats = conversation_stats

```



###### 其他实现
<font style="color:black;">在其他的Agent系统中，也可以用一个保存键值对的集合（字典或 Map）来实现state。它用于存放智能体为让当前对话顺利进行需要记住或追踪的信息：</font>

+ <font style="color:black;">个性化交互：</font><font style="color:rgb(1, 1, 1);"> 记住之前提到的用户偏好（例如，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">'user_preference_theme': 'dark'</font>`<font style="color:rgb(1, 1, 1);">）。</font>
+ <font style="color:black;">跟踪任务进度：</font><font style="color:rgb(1, 1, 1);"> 在多轮过程中跟踪步骤（例如，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">'booking_step': 'confirm_payment'</font>`<font style="color:rgb(1, 1, 1);">）。</font>
+ <font style="color:black;">积累信息：</font><font style="color:rgb(1, 1, 1);"> 构建列表或摘要（例如，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">'shopping_cart_items': ['book', 'pen']</font>`<font style="color:rgb(1, 1, 1);">）。</font>
+ <font style="color:black;">做出明智决策：</font><font style="color:rgb(1, 1, 1);"> 存储影响下一个响应的标志或值（例如，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">'user_is_authenticated': True</font>`<font style="color:rgb(1, 1, 1);">）。</font>

<font style="color:black;">状态键上的前缀定义了它们的作用域和持久性行为，特别是对于持久性服务：</font>

+ <font style="color:black;">无前缀（会话状态）：</font>
    - <font style="color:black;">作用域：</font><font style="color:rgb(1, 1, 1);"> 特定于</font><font style="color:black;">当前</font><font style="color:rgb(1, 1, 1);">会话（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">id</font>`<font style="color:rgb(1, 1, 1);">）。</font>
    - <font style="color:black;">持久性：</font><font style="color:rgb(1, 1, 1);"> 仅在 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:rgb(1, 1, 1);"> 是持久性的（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Database</font>`<font style="color:rgb(1, 1, 1);">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">VertexAI</font>`<font style="color:rgb(1, 1, 1);">）时才持久化。</font>
    - <font style="color:black;">使用案例：</font><font style="color:rgb(1, 1, 1);"> 跟踪当前任务中的进度（例如，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">'current_booking_step'</font>`<font style="color:rgb(1, 1, 1);">）、此次交互的临时标志（例如，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">'needs_clarification'</font>`<font style="color:rgb(1, 1, 1);">）。</font>
    - <font style="color:black;">示例：</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">session.state['current_intent'] = 'book_flight'</font>`
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">user:</font>`<font style="color:black;"> 前缀（用户状态）：</font>
    - <font style="color:black;">作用域：</font><font style="color:rgb(1, 1, 1);"> 绑定到 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">user_id</font>`<font style="color:rgb(1, 1, 1);">，在该用户的</font><font style="color:black;">所有</font><font style="color:rgb(1, 1, 1);">会话中共享（在同一个 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">app_name</font>`<font style="color:rgb(1, 1, 1);"> 内）。</font>
    - <font style="color:black;">持久性：</font><font style="color:rgb(1, 1, 1);"> 在 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Database</font>`<font style="color:rgb(1, 1, 1);"> 或 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">VertexAI</font>`<font style="color:rgb(1, 1, 1);"> 中持久化。（由 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">InMemory</font>`<font style="color:rgb(1, 1, 1);"> 存储但在重启时丢失）。</font>
    - <font style="color:black;">使用案例：</font><font style="color:rgb(1, 1, 1);"> 用户偏好（例如，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">'user:theme'</font>`<font style="color:rgb(1, 1, 1);">）、个人资料详情（例如，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">'user:name'</font>`<font style="color:rgb(1, 1, 1);">）。</font>
    - <font style="color:black;">示例：</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">session.state['user:preferred_language'] = 'fr'</font>`
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">app:</font>`<font style="color:black;"> 前缀（应用状态）：</font>
    - <font style="color:black;">作用域：</font><font style="color:rgb(1, 1, 1);"> 绑定到 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">app_name</font>`<font style="color:rgb(1, 1, 1);">，在该应用程序的</font><font style="color:black;">所有</font><font style="color:rgb(1, 1, 1);">用户和会话中共享。</font>
    - <font style="color:black;">持久性：</font><font style="color:rgb(1, 1, 1);"> 在 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Database</font>`<font style="color:rgb(1, 1, 1);"> 或 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">VertexAI</font>`<font style="color:rgb(1, 1, 1);"> 中持久化。（由 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">InMemory</font>`<font style="color:rgb(1, 1, 1);"> 存储但在重启时丢失）。</font>
    - <font style="color:black;">使用案例：</font><font style="color:rgb(1, 1, 1);"> 全局设置（例如，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">'app:api_endpoint'</font>`<font style="color:rgb(1, 1, 1);">）、共享模板。</font>
    - <font style="color:black;">示例：</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">session.state['app:global_discount_code'] = 'SAVE10'</font>`
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">temp:</font>`<font style="color:black;"> 前缀（临时会话状态）：</font>
    - <font style="color:black;">作用域：</font><font style="color:rgb(1, 1, 1);"> 特定于</font><font style="color:black;">当前</font><font style="color:rgb(1, 1, 1);">会话处理轮次。</font>
    - <font style="color:black;">持久性：</font><font style="color:black;">从不持久化。</font><font style="color:rgb(1, 1, 1);"> 保证被丢弃，即使使用持久性服务。</font>
    - <font style="color:black;">使用案例：</font><font style="color:rgb(1, 1, 1);"> 仅在立即需要的中间结果、你明确不想存储的数据。</font>
    - <font style="color:black;">示例：</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">session.state['temp:raw_api_response'] = {...}</font>`

<font style="color:black;">智能体代码通过单一的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">session.state</font>`<font style="color:black;"> 集合（dict/Map）与</font>_<font style="color:black;">合并后的</font>_<font style="color:black;">状态交互。</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">SessionService</font>`<font style="color:black;"> 会根据前缀从正确的底层存储获取/合并状态。</font>

##### 生命周期
<font style="color:rgb(0, 0, 0);">State类的生命周期如下：</font>

![画板](https://cdn.nlark.com/yuque/0/2026/jpeg/62574793/1774594919714-530a960d-325d-4ee0-a891-6dd1da3ab99f.jpeg)

##### 联系
<font style="color:rgb(0, 0, 0);">state和其他组件或者数据结构的联系如下</font>

###### <font style="color:rgb(0, 0, 0);">Stat与AgentController的联系</font>
<font style="color:rgb(0, 0, 0);">在AgentController._step()中，Agent通过State获取信息。</font>

```python
    async def _step(self) -> None:
        """Executes a single step of the parent or delegate agent. Detects stuck agents and limits on the number of iterations and the task budget."""
        if self.get_agent_state() != AgentState.RUNNING:
            self.log(
                'debug',
                f'Agent not stepping because state is {self.get_agent_state()} (not RUNNING)',
                extra={'msg_type': 'STEP_BLOCKED_STATE'},
            )
            return
```

###### State与Observation/Action 的关系
<font style="color:rgb(0, 0, 0);">Observation 更新 State。当 Environment 返回 Observation 时，Observation 被添加到 State 历史中。</font>

```python
    def add_history(self, event: Event):
        # if the event is not filtered out, add it to the history
        if self.agent_history_filter.include(event):
            self.state.history.append(event)
```

<font style="color:rgb(0, 0, 0);">Agent 基于当前 State 生成 Action。</font>

```python
action = self.agent.step(self.state)
```

<font style="color:rgb(0, 0, 0);">另外，虽然前端的 FooterContent 组件不直接使用 State，但整个前端界面的状态管理依赖于后端 State 的同步Backend State -> WebSocket -> Frontend State -> UI Updates。前端组件根据接收到的 State 信息更新界面状态和可用操作。</font>

###### <font style="color:rgb(0, 0, 0);">State 的共享</font>
<font style="color:rgb(0, 0, 0);">State 分为全局状态和局部状态。全局指标在委托间共享，比如。</font>

```python
   async def start_delegate(self, action: AgentDelegateAction) -> None:
        """启动一个委托智能体来处理子任务。

        OpenHands 是一个多智能体系统。`任务（task）` 指 OpenHands（整个系统）与用户之间的对话，
        可能包含用户的一个或多个输入。它始于用户的初始输入（通常是任务说明），结束于以下三种情况：
        智能体发起的 `AgentFinishAction`、用户发起的停止操作，或出现错误。

        `子任务（subtask）` 指智能体与用户之间，或智能体与其他智能体之间的对话。如果一个 `任务`
        由单个智能体执行，那么它同时也是一个 `子任务`。否则，一个 `任务` 由多个 `子任务` 组成，
        每个子任务由一个智能体执行。

        参数：
            action (AgentDelegateAction)：包含要启动的委托智能体信息的动作对象
        """
        # 根据动作中指定的智能体类型获取对应的智能体类
        agent_cls: type[Agent] = Agent.get_cls(action.agent)
        # 获取该智能体的配置（优先使用动作指定的配置，否则使用当前智能体的配置）
        agent_config = self.agent_configs.get(action.agent, self.agent.config)
        # 确保父智能体与子智能体共享指标，以实现全局累积
        delegate_agent = agent_cls(
            config=agent_config, llm_registry=self.agent.llm_registry
        )

        # 在启动委托智能体前，对当前指标进行快照
        state = State(
            session_id=self.id.removesuffix('-delegate'),  # 会话ID（移除委托后缀）
            user_id=self.user_id,  # 关联的用户ID
            inputs=action.inputs or {},  # 子任务的输入参数（默认为空字典）
            iteration_flag=self.state.iteration_flag,  # 继承迭代控制标志
            budget_flag=self.state.budget_flag,  # 继承预算控制标志
            delegate_level=self.state.delegate_level + 1,  # 委托层级在父级基础上加1
            # 全局指标在父智能体与子智能体间共享
            metrics=self.state.metrics,
            # 从事件流的最新位置开始记录新事件
            start_id=self.event_stream.get_latest_event_id() + 1,
            # 记录委托前父智能体的指标快照
            parent_metrics_snapshot=self.state_tracker.get_metrics_snapshot(),
            # 记录父智能体当前的迭代次数
            parent_iteration=self.state.iteration_flag.current_value,
        )
```

<font style="color:rgb(0, 0, 0);">不同层级的控制标志不同，比如在上面代码中也有体现：</font>

```python
self.state.iteration_flag # 全局迭代控制

self.state.budget_flag # 全局预算控制
```

##### 持久化和恢复
<font style="color:rgb(0, 0, 0);">OpenHands 通过StateTracker管理状态的持久化，支持会话中断后的状态恢复，确保任务连续性。比如，save_state保存状态到存储。</font>

```python
class StateTracker:
    """管理并同步智能体在其生命周期内的状态。

    它负责：
    1. 维持智能体状态在多个会话间的持久性
    2. 通过过滤和跟踪相关事件来管理智能体历史（以前由智能体控制器执行）
    3. 在控制器和LLM组件之间同步指标
    4. 更新预算和迭代限制的控制标志
    """

    def __init__(
        self, sid: str | None, file_store: FileStore | None, user_id: str | None
    ):
        self.sid = sid  # 会话ID，用于标识当前会话
        self.file_store = file_store  # 文件存储对象，用于持久化状态
        self.user_id = user_id  # 用户ID，关联到特定用户

        # 过滤掉与智能体无关的事件
        # 这些事件将不被包含在智能体历史中
        self.agent_history_filter = EventFilter(
            exclude_types=(
                NullAction,  # 排除空动作事件
                NullObservation,  # 排除空观察事件
                ChangeAgentStateAction,  # 排除更改智能体状态的动作事件
                AgentStateChangedObservation,  # 排除智能体状态已更改的观察事件
            ),
            exclude_hidden=True,  # 排除隐藏事件
        )
```

##### 小结
<font style="color:black;">State 在 OpenHands 系统中起到以下关键作用：</font>

+ <font style="color:black;">信息中枢：聚合所有决策所需信息</font>
+ <font style="color:black;">控制中心：管理迭代、预算等控制流程</font>
+ <font style="color:black;">记忆载体：维护交互历史和上下文</font>
+ <font style="color:black;">协调机制：支持多 Agent 委托和状态共享</font>
+ <font style="color:black;">持久化基础：支持会话恢复和状态保存</font>
+ <font style="color:black;">接口桥梁：连接后端逻辑和前端展示</font>

<font style="color:black;">State 是 OpenHands 系统的 “大脑”，确保了整个智能体系统的连贯性和智能决策能力。</font>

#### LLM Adapter
<font style="color:black;">回归 AI Agent 的根本，其实就是 </font>**<font style="color:black;">Loop+Tokens</font>**<font style="color:black;">，我们拆解来看看：</font>

1. <font style="color:black;">Loop</font><font style="color:rgb(1, 1, 1);">：其实也就是循环，类比人类解决一个问题，就是不断去尝试，直到解决，这就是一个循环，只不过循环长短不同。</font>
2. <font style="color:black;">Tokens</font><font style="color:rgb(1, 1, 1);">：Loop 中不断的去让大模型思考决策，行动，和收集反馈信息继续下次的计划和执行。</font>

<font style="color:black;">因此，大语言模型是 OpenHands 的 "智能核心"，将 LLM 作为动态调度器的设计，是当前 AI Agent 领域的核心实现范式。即，将LLM做为一个主动的任务规划与函数调用引擎。这种模式带来了两大优势：</font>

+ <font style="color:black;">能力的涌现</font><font style="color:rgb(1, 1, 1);">：由于执行计划是LLM动态生成的，agent能够执行开发者从未明确编码过的行为，甚至自主决定编写并执行一个脚本来完成任务。</font>
+ <font style="color:rgb(1, 1, 1);">业务逻辑复杂度降低：开发者只需不断增加原子能力工具，复杂的业务编排逻辑交给 LLM 来决定，整体代码复杂度得以降低。</font>

<font style="color:rgb(0, 0, 0);">此架构范式让应用的能力上限不再受限于开发者预设的控制流，而是取决于 AI 在运行时对可用工具的动态组合与调用，为实现能处理复杂、多步任务，并具备一定自主性的通用 AI agent 提供了可参考的实现路径。</font>
<font style="color:black;">OpenHands 框架通过模块化的设计，实现了对主流 LLM 的无缝集成，既支持云端模型的便捷调用，也兼容本地部署的隐私化需求。</font>

<font style="color:black;">在云端集成方面，OpenHands 系统提供了统一的接口层，封装了 OpenAI、Azure、Mistral AI 等平台的 API 差异。开发者只需配置相应的 API 密钥和模型参数，框架就能自动适配不同模型的输入输出格式，实现 "一键切换"。这种设计的优势在于：当某一模型因负载过高响应缓慢时，系统可自动切换到备用模型，确保任务不中断；同时，也允许开发者根据任务特性选择最适合的模型（例如用代码生成能力突出的模型处理编程任务，用多模态模型处理包含图文的需求）。</font>

##### LLM
###### 作用
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">LLM</font>`<font style="color:black;"> 类是 OpenHands 框架中语言模型的核心封装类，继承自重试混入类（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RetryMixin</font>`<font style="color:black;">）和调试混入类（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">DebugMixin</font>`<font style="color:black;">），提供了统一的大语言模型调用接口。其核心职责是整合 LiteLLM 工具的多模型适配能力，处理模型配置解析、请求参数格式化、函数调用模拟、重试机制、日志记录、成本与延迟统计等全流程逻辑。</font>

<font style="color:black;">LLM 类为各类语言模型提供了统一接口，通过 LiteLLM 支持 100 余种模型提供商，并提供两大 API：一是保证广泛兼容性的标准对话补全 API（Chat Completions API），二是适配最新推理模型的 OpenAI 响应 API（Responses API）。</font>

+ <font style="color:black;">原生支持推理 / 扩展思考能力</font><font style="color:rgb(1, 1, 1);">：SDK 能够捕获并处理前沿模型的高级原生推理字段 —— 例如 Anthropic 模型的扩展思考字段 ThinkingBlock、OpenAI 模型的推理字段 ReasoningItemModel。SDK 为智能体透明化支持 OpenAI 响应 API，使客户端开发者可直接使用仅在该 API 开放的先进推理模型（如 GPT-5-Codex）。</font>
+ <font style="color:black;">内置非函数调用模型支持</font><font style="color:rgb(1, 1, 1);">：针对不原生支持函数调用的模型，SDK 实现了 NonNativeToolCallingMixin 混合类 —— 将工具 schema 转换为基于文本的提示指令，并通过结构化提示与正则提取技术，从模型输出中解析工具调用指令。这一设计使无函数调用能力的模型也能胜任智能体任务，大幅拓展了可用模型范围。</font>
+ <font style="color:black;">多 LLM 路由支持</font><font style="color:rgb(1, 1, 1);">：SDK 内置 RouterLLM（LLM 子类），允许智能体为不同的 LLM 请求匹配不同模型。开发者可通过自定义扩展 RouterLLM 并实现 select_llm () 方法，基于输入内容动态选择适配模型。</font>
+ <font style="color:black;">完善的工程化能力</font><font style="color:rgb(1, 1, 1);">：内置重试机制（支持失败重试、延迟策略）、请求 / 响应日志记录（可持久化到文件）、性能指标统计（延迟、成本），同时支持安全设置、缓存提示词等实用功能。</font>
+ <font style="color:black;">函数调用灵活支持</font><font style="color:rgb(1, 1, 1);">：对不原生支持函数调用的模型，提供基于提示词的模拟转换能力；对支持函数调用的模型，自动适配其参数格式，无需开发者关注底层差异。</font>
+ <font style="color:black;">配置化驱动</font><font style="color:rgb(1, 1, 1);">：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">LLMConfig</font>`<font style="color:rgb(1, 1, 1);"> 统一管理模型参数（温度系数、最大输出 token 数、API 密钥等），支持动态调整模型配置，适配不同场景需求。</font>

###### <font style="color:rgb(1, 1, 1);">LLM Class</font>
```python
class LLM(RetryMixin, DebugMixin):
    """语言模型（LLM）实例的封装类，提供统一的模型调用接口。

    属性:
        config: LLMConfig 对象，存储模型的配置参数（如模型名称、API密钥、温度系数等）。
    """

    def __init__(
        self,
        config: LLMConfig,
        service_id: str,
        metrics: Metrics | None = None,
        retry_listener: Callable[[int, int], None] | None = None,
    ) -> None:
        """初始化 LLM 实例。若传入 LLMConfig，其参数将作为默认值；
        直接传入的简单参数会覆盖 config 中的对应配置。

        参数:
            config: 模型配置对象，包含模型调用所需的所有参数。
            service_id: 服务标识，用于关联当前 LLM 实例所属的服务。
            metrics: 指标统计对象，用于记录模型调用的延迟、成本等信息（可选）。
            retry_listener: 重试回调函数，每次重试时触发，接收（当前重试次数，总重试次数）作为参数（可选）。
        """
        # 标记是否已尝试获取模型信息
        self._tried_model_info = False
        # 标记是否支持成本统计指标
        self.cost_metric_supported: bool = True
        # 深拷贝配置对象，避免外部修改影响内部状态
        self.config: LLMConfig = copy.deepcopy(config)
        # 服务标识赋值
        self.service_id = service_id
        # 初始化指标统计对象（若未传入则创建默认实例）
        self.metrics: Metrics = (
            metrics if metrics is not None else Metrics(model_name=config.model)
        )

        # 模型信息（如支持的功能、参数限制等，后续通过 init_model_info 初始化）
        self.model_info: ModelInfo | None = None
        # 标记是否启用函数调用功能
        self._function_calling_active: bool = False
        # 重试回调函数赋值
        self.retry_listener = retry_listener

        # 处理日志记录配置：若启用日志记录，需确保日志文件夹存在
        if self.config.log_completions:
            if self.config.log_completions_folder is None:
                raise RuntimeError(
                    'log_completions_folder is required when log_completions is enabled'
                )
            # 创建日志文件夹（若已存在则不报错）
            os.makedirs(self.config.log_completions_folder, exist_ok=True)

        # 调用 init_model_info 初始化模型信息，核心是获取 config.max_output_tokens（后续函数调用需用到）
        # 忽略初始化过程中的警告信息
        with warnings.catch_warnings():
            warnings.simplefilter('ignore')
            self.init_model_info()

        # 打印调试日志：模型是否支持视觉能力
        if self.vision_is_active():
            logger.debug('LLM: model has vision enabled')
        # 打印调试日志：是否启用提示词缓存
        if self.is_caching_prompt_active():
            logger.debug('LLM: caching prompt enabled')
        # 打印调试日志：模型是否支持函数调用
        if self.is_function_calling_active():
            logger.debug('LLM: model supports function calling')

        # 处理自定义分词器：若配置了自定义分词器，按指定路径加载
        if self.config.custom_tokenizer is not None:
            self.tokenizer = create_pretrained_tokenizer(self.config.custom_tokenizer)
        else:
            self.tokenizer = None

        # 初始化模型调用的基础参数
        kwargs: dict[str, Any] = {
            'temperature': self.config.temperature,  # 温度系数，控制输出随机性
            'max_completion_tokens': self.config.max_output_tokens,  # 最大输出token数
        }

        # 若配置了 top_k，添加到参数中（OpenAI 不支持该参数，LiteLLM 会特殊处理）
        if self.config.top_k is not None:
            kwargs['top_k'] = self.config.top_k
        # 若配置了 top_p，添加到参数中（OpenAI 不支持该参数，但 LiteLLM 支持）
        if self.config.top_p is not None:
            kwargs['top_p'] = self.config.top_p

        # 处理 OpenHands 专属模型：重写为 LiteLLM 代理格式
        if self.config.model.startswith('openhands/'):
            model_name = self.config.model.removeprefix('openhands/')
            self.config.model = f'litellm_proxy/{model_name}'
            self.config.base_url = 'https://llm-proxy.app.all-hands.dev/'
            logger.debug(
                f'Rewrote openhands/{model_name} to {self.config.model} with base URL {self.config.base_url}'
            )

        # 获取当前模型支持的功能特性
        features = get_features(self.config.model)
        # 处理支持推理努力度（reasoning_effort）的模型
        if features.supports_reasoning_effort:
            # Gemini 模型特殊处理：仅将 'low'/'none' 映射为优化的思考预算
            if 'gemini-2.5-pro' in self.config.model:
                logger.debug(
                    f'Gemini model {self.config.model} with reasoning_effort {self.config.reasoning_effort}'
                )
                if self.config.reasoning_effort in {None, 'low', 'none'}:
                    kwargs['thinking'] = {'budget_tokens': 128}  # 思考预算设为 128 token
                    kwargs['allowed_openai_params'] = ['thinking']  # 允许传递 thinking 参数
                    kwargs.pop('reasoning_effort', None)  # 移除原 reasoning_effort 参数
                else:
                    kwargs['reasoning_effort'] = self.config.reasoning_effort
                logger.debug(
                    f'Gemini model {self.config.model} with reasoning_effort {self.config.reasoning_effort} mapped to thinking {kwargs.get("thinking")}'
                )
            # Claude Sonnet 4.5 不支持 reasoning_effort，直接移除该参数
            elif 'claude-sonnet-4-5' in self.config.model:
                kwargs.pop('reasoning_effort', None)
            # 其他支持的模型，直接传递 reasoning_effort 参数
            else:
                kwargs['reasoning_effort'] = self.config.reasoning_effort
            # 推理类模型不支持 temperature 和 top_p，移除这两个参数
            kwargs.pop('temperature')
            kwargs.pop('top_p')

        # 处理 Azure 模型的参数兼容问题（参考：https://github.com/All-Hands-AI/OpenHands/issues/6777）
        if self.config.model.startswith('azure'):
            kwargs['max_tokens'] = self.config.max_output_tokens  # Azure 用 max_tokens 而非 max_completion_tokens
            kwargs.pop('max_completion_tokens')

        # 为支持安全设置的模型添加安全配置
        if 'mistral' in self.config.model.lower() and self.config.safety_settings:
            kwargs['safety_settings'] = self.config.safety_settings
        elif 'gemini' in self.config.model.lower() and self.config.safety_settings:
            kwargs['safety_settings'] = self.config.safety_settings

        # 支持 AWS Bedrock 模型：添加 AWS 相关配置参数
        kwargs['aws_region_name'] = self.config.aws_region_name
        if self.config.aws_access_key_id:
            # 从密钥管理中获取 AWS 访问密钥
            kwargs['aws_access_key_id'] = (
                self.config.aws_access_key_id.get_secret_value()
            )
        if self.config.aws_secret_access_key:
            # 从密钥管理中获取 AWS 密钥
            kwargs['aws_secret_access_key'] = (
                self.config.aws_secret_access_key.get_secret_value()
            )

        # 禁用 Claude Opus 4.1 的 Anthropic 扩展思考功能（避免需要 'thinking' 内容块，参考：#10510）
        if 'claude-opus-4-1' in self.config.model.lower():
            kwargs['thinking'] = {'type': 'disabled'}

        # Anthropic 约束：Opus 4.1 不能同时接受 temperature 和 top_p，若两者都存在则优先保留 temperature
        _model_lower = self.config.model.lower()
        if ('claude-opus-4-1' in _model_lower) and (
            'temperature' in kwargs and 'top_p' in kwargs
        ):
            kwargs.pop('top_p', None)

        # 绑定 LiteLLM 完成函数，预设固定参数（通过 partial 固化模型配置）
        self._completion = partial(
            litellm.completion,  # LiteLLM 的核心完成函数
            model=self.config.model,  # 模型名称
            # API 密钥（若配置则从密钥管理中获取）
            api_key=self.config.api_key.get_secret_value()
            if self.config.api_key
            else None,
            base_url=self.config.base_url,  # 模型服务基础 URL
            api_version=self.config.api_version,  # API 版本（如 Azure 需指定）
            custom_llm_provider=self.config.custom_llm_provider,  # 自定义 LLM 提供商
            timeout=self.config.timeout,  # 超时时间
            drop_params=self.config.drop_params,  # 是否允许 LiteLLM 丢弃不支持的参数
            seed=self.config.seed,  # 随机种子（保证输出可复现）
            **kwargs,  # 上述拼接的动态参数
        )

        # 保存未包装的原始 completion 函数（用于内部调用）
        self._completion_unwrapped = self._completion

        # 为 completion 函数添加重试装饰器（继承自 RetryMixin）
        @self.retry_decorator(
            num_retries=self.config.num_retries,  # 最大重试次数
            retry_exceptions=LLM_RETRY_EXCEPTIONS,  # 触发重试的异常类型
            retry_min_wait=self.config.retry_min_wait,  # 最小重试等待时间
            retry_max_wait=self.config.retry_max_wait,  # 最大重试等待时间
            retry_multiplier=self.config.retry_multiplier,  # 重试等待时间倍增系数
            retry_listener=self.retry_listener,  # 重试回调函数
        )
        def wrapper(*args: Any, **kwargs: Any) -> Any:
            """LiteLLM 完成函数的包装器，负责：
            1. 解析输入消息（处理 Message 对象与字典格式的转换）
            2. 模拟函数调用（对不支持函数调用的模型）
            3. 日志记录（输入提示词、输出响应）
            4. 性能指标统计（延迟、成本）
            5. 响应格式转换与异常处理
            """
            # 延迟导入以避免循环依赖
            from openhands.io import json

            # 初始化消息参数（存储用户传入的消息）
            messages_kwarg: (
                dict[str, Any] | Message | list[dict[str, Any]] | list[Message]
            ) = []
            # 标记是否需要模拟函数调用（模型不支持原生函数调用时为 True）
            mock_function_calling = not self.is_function_calling_active()

            # 处理位置参数：部分调用者可能直接传入 (model, messages, **kwargs)
            if len(args) > 1:
                # 忽略第一个参数（模型名称，已通过 partial 固化）
                # 设计原则：不允许覆盖已配置的模型参数
                messages_kwarg = args[1] if len(args) > 1 else args[0]
                kwargs['messages'] = messages_kwarg

                # 移除前两个位置参数（已转换为关键字参数）
                args = args[2:]
            # 处理关键字参数：若已传入 messages 则直接赋值
            elif 'messages' in kwargs:
                messages_kwarg = kwargs['messages']

            # 确保消息为列表格式（统一处理单条/多条消息）
            messages_list = (
                messages_kwarg if isinstance(messages_kwarg, list) else [messages_kwarg]
            )
            # 格式化消息：将 Message 对象转换为模型可识别的字典格式
            messages: list[dict] = []
            if messages_list and isinstance(messages_list[0], Message):
                messages = self.format_messages_for_llm(
                    cast(list[Message], messages_list)
                )
            else:
                messages = cast(list[dict[str, Any]], messages_list)

            # 更新 kwargs 中的 messages 为格式化后的结果
            kwargs['messages'] = messages

            # 保存原始函数调用相关消息（用于后续日志记录）
            original_fncall_messages = copy.deepcopy(messages)
            mock_fncall_tools = None
            # 若需要模拟函数调用且传入了工具配置，转换消息格式
            if mock_function_calling and 'tools' in kwargs:
                # 标记是否添加上下文学习示例（部分模型不需要）
                add_in_context_learning_example = True
                if (
                    'openhands-lm' in self.config.model
                    or 'devstral' in self.config.model
                ):
                    add_in_context_learning_example = False

                # 将函数调用格式的消息转换为普通文本提示（模拟函数调用）
                messages = convert_fncall_messages_to_non_fncall_messages(
                    messages,
                    kwargs['tools'],
                    add_in_context_learning_example=add_in_context_learning_example,
                )
                kwargs['messages'] = messages

                # 若模型支持停止词且未禁用，添加默认停止词
                if (
                    get_features(self.config.model).supports_stop_words
                    and not self.config.disable_stop_word
                ):
                    kwargs['stop'] = STOP_WORDS

                # 移除 tools 参数（模拟调用时不需要传递）
                mock_fncall_tools = kwargs.pop('tools')
                # OpenHands 自研模型特殊处理：禁用工具调用
                if 'openhands-lm' in self.config.model:
                    kwargs['tool_choice'] = 'none'
                else:
                    # 其他模型：移除 tool_choice 参数（模拟调用时不支持）
                    kwargs.pop('tool_choice', None)

            # 校验消息非空：无消息则抛出异常
            if not messages:
                raise ValueError(
                    'The messages list is empty. At least one message is required.'
                )

            # 记录 LLM 输入提示词日志
            self.log_prompt(messages)

            # 设置 LiteLLM 是否允许修改参数（默认允许，如为空消息添加默认内容）
            # 注意：该设置为全局，无法通过 partial 覆盖
            litellm.modify_params = self.config.modify_params

            # 非 LiteLLM 代理模型：移除 extra_body 参数（仅代理模型支持）
            if 'litellm_proxy' not in self.config.model:
                kwargs.pop('extra_body', None)

            # 记录调用开始时间（用于计算延迟）
            start_time = time.time()

            # 抑制 LiteLLM 调用过程中 httpx 库的弃用警告
            # 避免出现 "Use 'content=<...>' to upload raw bytes/text content" 警告
            with warnings.catch_warnings():
                warnings.filterwarnings(
                    'ignore', category=DeprecationWarning, module='httpx.*'
                )
                warnings.filterwarnings(
                    'ignore',
                    message=r'.*content=.*upload.*',
                    category=DeprecationWarning,
                )
                # 调用原始 completion 函数（非流式，返回 ModelResponse 对象）
                resp: ModelResponse = self._completion_unwrapped(*args, **kwargs)

            # 计算调用延迟并记录到指标中
            latency = time.time() - start_time
            response_id = resp.get('id', 'unknown')  # 获取响应 ID（无则设为 'unknown'）
            self.metrics.add_response_latency(latency, response_id)  # 记录延迟指标

            # 深拷贝原始响应（用于模拟函数调用场景的日志记录）
            non_fncall_response = copy.deepcopy(resp)

            # 若启用了函数调用模拟且存在工具配置，将响应转换回函数调用格式
            if mock_function_calling and mock_fncall_tools is not None:
                # 校验响应是否包含有效选项（Gemini 模型曾出现无选项的情况）
                if len(resp.choices) < 1:
                    raise LLMNoResponseError(
                        'Response choices is less than 1 - This is only seen in Gemini models so far. Response: '
                        + str(resp)
                    )

                # 获取非函数调用格式的响应消息
                non_fncall_response_message = resp.choices[0].message
                # 将 "原始消息 + 非函数调用响应" 转换为函数调用格式的响应
                fn_call_messages_with_response = (
                    convert_non_fncall_messages_to_fncall_messages(
                        messages + [non_fncall_response_message], mock_fncall_tools
                    )
                )
                # 提取转换后的函数调用响应消息
                fn_call_response_message = fn_call_messages_with_response[-1]
                # 确保响应消息为 LiteLLMMessage 类型（若为字典则转换）
                if not isinstance(fn_call_response_message, LiteLLMMessage):
                    fn_call_response_message = LiteLLMMessage(
                        **fn_call_response_message
                    )
                # 更新响应中的消息为函数调用格式
                resp.choices[0].message = fn_call_response_message

            # 二次校验响应有效性：确保 choices 非空且至少有一个选项
            if not resp.get('choices') or len(resp['choices']) < 1:
                raise LLMNoResponseError(
                    'Response choices is less than 1 - This is only seen in Gemini models so far. Response: '
                    + str(resp)
                )

            # 记录 LLM 响应日志
            self.log_response(resp)

            # 响应后处理：计算调用成本（如 token 消耗对应的费用）
            cost = self._post_completion(resp)

            # 若启用响应日志持久化，将请求/响应数据写入文件
            if self.config.log_completions:
                # 断言日志文件夹已配置（初始化时已校验，此处防止异常）
                assert self.config.log_completions_folder is not None
                # 构造日志文件名：模型名_时间戳.json（替换 '/' 为 '__' 避免路径错误）
                log_file = os.path.join(
                    self.config.log_completions_folder,
                    f'{self.config.model.replace("/", "__")}-{time.time()}.json',
                )

                # 构造日志数据字典
                _d = {
                    'messages': messages,  # 实际发送给模型的消息（可能是模拟函数调用格式）
                    'response': resp,      # 模型响应（可能是转换后的函数调用格式）
                    'args': args,          # 调用时的位置参数
                    'kwargs': {            # 调用时的关键字参数（过滤敏感/冗余字段）
                        k: v
                        for k, v in kwargs.items()
                        if k not in ('messages', 'client')
                    },
                    'timestamp': time.time(),  # 调用时间戳
                    'cost': cost,              # 调用成本（token 费用）
                }

                # 若启用了函数调用模拟，额外记录原始函数调用格式的消息和响应
                if mock_function_calling:
                    # 覆盖 response 为非函数调用格式（与 messages 保持一致）
                    _d['response'] = non_fncall_response
                    # 新增字段记录原始函数调用格式数据
                    _d['fncall_messages'] = original_fncall_messages
                    _d['fncall_response'] = resp

                # 将日志数据写入文件（JSON 格式）
                with open(log_file, 'w') as f:
                    f.write(json.dumps(_d))

            # 返回最终处理后的模型响应
            return resp

        # 将包装后的函数赋值给 _completion，后续通过该属性调用模型
        self._completion = wrapper
```

##### <font style="color:black;">LLMRegistry</font>
###### 作用
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">LLMRegistry</font>`<font style="color:black;"> 是 OpenHands 框架中管理 LLM 实例的核心组件，负责集中创建、复用和监控所有 LLM 资源。配合 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">create_registry_and_conversation_stats</font>`<font style="color:black;"> 函数，它构建了从配置解析到实例管理的完整链路，确保 LLM 资源高效利用且配置一致。LLMRegistry的功能如下。</font>

1. <font style="color:black;">集中化实例管理</font><font style="color:rgb(1, 1, 1);">：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">service_to_llm</font>`<font style="color:rgb(1, 1, 1);"> 映射表跟踪所有 LLM 实例，避免重复创建，降低资源消耗；严格检查同一服务 ID 的配置一致性，防止冲突。</font>
2. <font style="color:black;">灵活的实例获取机制</font><font style="color:rgb(1, 1, 1);">：</font>
    - <font style="color:rgb(1, 1, 1);">支持通过服务 ID 直接获取或创建 LLM（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">get_llm</font>`<font style="color:rgb(1, 1, 1);">）</font>
    - <font style="color:rgb(1, 1, 1);">支持从代理配置自动推导 LLM 配置（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">get_llm_from_agent_config</font>`<font style="color:rgb(1, 1, 1);">）</font>
    - <font style="color:rgb(1, 1, 1);">支持临时补充生成需求（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">request_extraneous_completion</font>`<font style="color:rgb(1, 1, 1);">）</font>
3. <font style="color:black;">多模型路由支持</font><font style="color:rgb(1, 1, 1);">：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">get_router</font>`<font style="color:rgb(1, 1, 1);"> 方法集成 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RouterLLM</font>`<font style="color:rgb(1, 1, 1);">，实现基于代理配置的动态模型选择，灵活应对复杂任务对不同模型的需求。</font>
4. <font style="color:black;">事件驱动的可扩展性</font><font style="color:rgb(1, 1, 1);">：提供 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">subscribe</font>`<font style="color:rgb(1, 1, 1);"> 和 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">notify</font>`<font style="color:rgb(1, 1, 1);"> 机制，允许外部组件（如 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ConversationStats</font>`<font style="color:rgb(1, 1, 1);">）订阅 LLM 注册事件，轻松扩展统计、监控等功能。</font>
5. <font style="color:black;">配置隔离与安全性</font><font style="color:rgb(1, 1, 1);">：通过深拷贝配置和严格的实例创建逻辑，确保不同服务的 LLM 配置相互隔离，避免外部修改干扰内部状态。</font>
6. <font style="color:black;">适配用户个性化设置</font><font style="color:rgb(1, 1, 1);">：结合 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">create_registry_and_conversation_stats</font>`<font style="color:rgb(1, 1, 1);"> 函数，支持通过用户设置覆盖默认配置，兼顾通用性与个性化需求。</font>

###### <font style="color:rgb(1, 1, 1);">工作流</font>
```python
┌───────────────────────────────────────────┐
│     create_registry_and_conversation_stats│
└───────────────────────────────────────────┘
                    │
                    ▼
┌─────────────────────────────────────────┐
│            解析配置                      │
└─────────────────────────────────────────┘
                    │
    ┌───────────────┴───────────────┐
    ▼                               ▼
┌───────────────────┐     ┌───────────────────┐
│ 初始化文件存储      │     │ 创建对话统计实例     │
│   (file_store)    │     │(conversationstats)│
│                   │     │ （用户设置优先）     │
└───────────────────┘     └───────────────────┘
    │                               │
    └───────────────┬───────────────┘
                    ▼
        ┌───────────────────────┐
        │   创建LLMRegistry      │
        │     （绑定配置）        │
        └───────────────────────┘
                    │
                    ▼
        ┌───────────────────────┐
        │   LLMRegistry核心流程  │
        └───────────────────────┘
                    │
                    ▼
        ┌───────────────────────┐
        │       初始化           │
        └───────────────────────┘
                    │
                    ▼
        ┌───────────────────────┐
        │    确定激活代理         │
        │   (agent_cls)         │
        └───────────────────────┘
                    │
                    ▼
        ┌───────────────────────┐
        │  创建主LLM实例          │
        │(active_agent_lm)      │
        └───────────────────────┘
                    │
                    ▼
┌─────────────────────────────────────────────────────┐
│         实例管理（get_llm/get_llm_from_agent_config) │
└─────────────────────────────────────────────────────┘
                    │
                    ▼
            ┌───────────────┐
            │    存在？      │
            └───────────────┘
                    │
        ┌───────────┴───────────┐
        ▼                       ▼
   ┌─────────┐            ┌─────────────┐
   │  是     │            │    否       │
   └─────────┘            └─────────────┘
        │                       │
        ▼                       ▼
┌─────────────────┐    ┌─────────────────┐
│ 检查服务ID       │    │  配置有效？       │
└─────────────────┘    └─────────────────┘
        │                       │
        ▼               ┌───────┴───────┐
┌─────────────────┐    ▼               ▼
│ 返回已有实例      │ ┌─────────┐   ┌─────────────┐
└─────────────────┘ │  是     │    │    否      │
                    └─────────┘   └─────────────┘
                         │               │
                         ▼               ▼
                  ┌─────────────┐  ┌─────────────┐
                  │创建新实例     │  │   处理异常  │
                  │并注册        │  │    或跳过   │
                  └─────────────┘  └─────────────┘
                         │
                         ▼
                  ┌─────────────────────┐
                  │ 通知订阅者            │
                  │（如对话统计）          │
                  └─────────────────────┘
                         │
         ┌───────────────┴───────────────┐
         ▼                               ▼
┌─────────────────────┐     ┌─────────────────────────┐
│     其他功能         │     │      多模型路由           │
│                     │     │    (get_router)         │
└─────────────────────┘     └─────────────────────────┘
                                       │
                                       ▼
                         ┌─────────────────────────────────┐
                         │      额外生成请求                 │
                         │ (request_extraneous_completion) │
                         └─────────────────────────────────┘
```

###### Codes
<font style="color:rgb(0, 0, 0);">LLMRegistry 的代码如下：</font>

```python
class LLMRegistry:
    """
    LLM注册表：管理所有LLM实例的生命周期、配置和事件通知的核心组件。

    作用：
    - 集中管理多个LLM实例，避免重复创建
    - 确保同一服务ID的LLM配置一致性
    - 支持事件订阅（如统计、监控）
    - 提供路由LLM（RouterLLM）的创建能力
    """
    def __init__(
        self,
        config: OpenHandsConfig,
        agent_cls: Optional[str] = None,
        retry_listener: Optional[Callable[[int, int], None]] = None,
    ):
        self.registry_id = str(uuid4())  # 注册表唯一标识
        self.config = copy.deepcopy(config)  # 深拷贝配置，避免外部修改影响
        self.retry_listener = retry_listener  # 重试事件监听器（可选）
        # 构建代理到LLM配置的映射（从全局配置中提取）
        self.agent_to_llm_config = self.config.get_agent_to_llm_config_map()
        self.service_to_llm: dict[str, LLM] = {}  # 服务ID到LLM实例的映射
        self.subscriber: Optional[Callable[[Any], None]] = None  # 事件订阅者（如统计器）

        # 确定当前激活的代理类型（用户指定优先，否则使用默认）
        selected_agent_cls = self.config.default_agent
        if agent_cls:
            selected_agent_cls = agent_cls

        # 基于代理类型获取对应的LLM配置
        agent_name = selected_agent_cls if selected_agent_cls is not None else 'agent'
        llm_config = self.config.get_llm_config_from_agent(agent_name)
        # 初始化并激活代理的主LLM实例
        self.active_agent_llm: LLM = self.get_llm('agent', llm_config)

    def _create_new_llm(
        self, service_id: str, config: LLMConfig, with_listener: bool = True
    ) -> LLM:
        """
        内部方法：创建新的LLM实例并注册到注册表中。

        参数：
            service_id: 服务唯一标识（用于区分不同LLM实例）
            config: LLM配置
            with_listener: 是否绑定重试监听器

        返回：
            新创建的LLM实例
        """
        # 根据是否需要监听器，初始化LLM
        if with_listener:
            llm = LLM(
                service_id=service_id, config=config, retry_listener=self.retry_listener
            )
        else:
            llm = LLM(service_id=service_id, config=config)

        # 记录到映射表中
        self.service_to_llm[service_id] = llm
        # 通知订阅者（如统计器）有新LLM注册
        self.notify(RegistryEvent(llm=llm, service_id=service_id))
        return llm

    def request_extraneous_completion(
        self, service_id: str, llm_config: LLMConfig, messages: list[dict[str, str]]
    ) -> str:
        """
        请求额外的LLM生成（用于非主流程的补充生成需求）。

        参数：
            service_id: 服务ID
            llm_config: 对应的LLM配置
            messages: 输入消息列表（格式：[{role: ..., content: ...}, ...]）

        返回：
            LLM生成的文本内容（去除首尾空白）
        """
        # 若服务ID未注册，则创建新LLM（不绑定监听器，适用于临时任务）
        if service_id not in self.service_to_llm:
            self._create_new_llm(
                config=llm_config, service_id=service_id, with_listener=False
            )

        # 获取LLM实例并执行生成
        llm = self.service_to_llm[service_id]
        response = llm.completion(messages=messages)
        return response.choices[0].message.content.strip()

    def get_llm_from_agent_config(self, service_id: str, agent_config: AgentConfig):
        """
        根据代理配置获取对应的LLM实例（支持复用已有实例）。

        参数：
            service_id: 服务ID
            agent_config: 代理配置对象

        返回：
            匹配的LLM实例
        """
        # 从代理配置中提取LLM配置
        llm_config = self.config.get_llm_config_from_agent_config(agent_config)
        # 若实例已存在，直接返回（配置不一致时暂不处理，预留更新逻辑）
        if service_id in self.service_to_llm:
            if self.service_to_llm[service_id].config != llm_config:
                # TODO: 未来支持动态更新LLM配置
                # 当代理委托的配置不同时，应复用现有LLM
                pass
            return self.service_to_llm[service_id]

        # 实例不存在则创建新的
        return self._create_new_llm(config=llm_config, service_id=service_id)

    def get_llm(
        self,
        service_id: str,
        config: Optional[LLMConfig] = None,
    ) -> LLM:
        """
        获取或创建指定服务ID的LLM实例（核心方法）。

        参数：
            service_id: 服务唯一标识
            config: LLM配置（新实例必需）

        返回：
            对应的LLM实例

        异常：
            ValueError: 同一服务ID配置不一致，或创建新实例时无配置
        """
        # 检查同一服务ID的配置是否一致（防止冲突）
        if (
            service_id in self.service_to_llm
            and self.service_to_llm[service_id].config != config
        ):
            raise ValueError(
                f"Service ID {service_id} requested with different config. Use a new service ID."
            )

        # 实例已存在则直接返回
        if service_id in self.service_to_llm:
            return self.service_to_llm[service_id]

        # 新实例必须提供配置
        if not config:
            raise ValueError("Cannot create new LLM without specifying config.")

        # 创建并返回新实例
        return self._create_new_llm(config=config, service_id=service_id)

    def get_active_llm(self) -> LLM:
        """返回当前激活的代理主LLM实例"""
        return self.active_agent_llm

    def get_router(self, agent_config: AgentConfig) -> LLM:
        """
        获取路由LLM实例（用于多模型路由选择）。

        参数：
            agent_config: 代理配置（包含路由规则）

        返回：
            路由LLM实例（RouterLLM）或主LLM（当路由为noop时）
        """
        # 从代理配置中获取路由名称
        router_name = agent_config.model_routing.router_name

        # 若为"noop_router"（无操作路由），直接返回主LLM
        if router_name == 'noop_router':
            return self.get_llm_from_agent_config('agent', agent_config)

        # 否则创建并返回路由LLM实例
        return RouterLLM.from_config(
            agent_config=agent_config,
            llm_registry=self,
            retry_listener=self.retry_listener,
        )

    def subscribe(self, callback: Callable[[RegistryEvent], None]) -> None:
        """
        订阅注册表事件（如新LLM创建）。

        参数：
            callback: 事件触发时的回调函数
        """
        self.subscriber = callback

        # 订阅后，立即通知已存在的主LLM实例（补报历史事件）
        self.notify(
            RegistryEvent(
                llm=self.active_agent_llm,
                service_id=self.active_agent_llm.service_id
            )
        )

    def notify(self, event: RegistryEvent) -> None:
        """
        通知订阅者事件发生（如LLM注册）。

        参数：
            event: 注册表事件对象
        """
        if self.subscriber:
            try:
                self.subscriber(event)
            except Exception as e:
                logger.warning(f"Failed to notify subscriber of event: {e}")

```











































### CodeActAgent
<font style="color:black;">大模型是不可控的。不是‘给LLM一堆工具让它自由发挥’，而是大部分由确定性代码构成，在关键决策点巧妙地融入LLM能力。好的 Agent 应用，是工程设计与 AI 能力的精妙结合，而不是对 AI 的盲目放权。</font>

<font style="color:black;">在 OpenHands 智能框架的生态中，CodeActAgent 占据着核心地位，它是基于 CodeAct 理念构建的核心代理模块。其设计初衷极具巧思：将各类复杂任务统一转化为 “代码执行” 的形式来完成，同时兼顾自然语言对话的交互特性。这一设计既保障了任务执行的精准性与高效性，又为人类与智能代理的协作提供了灵活空间，使其成为框架中处理自动化编程、数据处理等复杂场景的核心载体。</font>

#### <font style="color:black;">Baclground</font>
##### Agent的核心能力
<font style="color:rgb(0, 0, 0);">根据Google电子书的定义，一个真正的 AI 智能体拥有四项核心能力：</font>

1. **<font style="color:black;">做出动态决策 (Make dynamic decisions)</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">它们不是遵循预定的路径，而是根据所学到的东西决定下一步做什么。</font>
2. **<font style="color:black;">跨交互保持状态 (Maintain state across multiple interactions)</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">它们能记住自己做过什么，并利用这些历史来为未来的决策提供信息。</font>
3. **<font style="color:black;">自适应地使用工具 (Use tools adaptively)</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">它们可以从可用工具中进行选择，并以非预先编程的方式组合它们。</font>
4. **<font style="color:black;">根据结果修正方法 (Modify their approach based on results)</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">当一种策略不起作用时，它们可以尝试不同的方法。</font>

##### <font style="color:rgb(1, 1, 1);">Agent设计原则</font>
<font style="color:black;">使用 https://github.com/humanlayer/12-factor-agents 来切入，具体如下：</font>

+ **<font style="color:black;">原则一：</font>**<font style="color:black;">组织规划、工具调用，复杂Agent的工作范式</font>
+ **<font style="color:black;">原则二：</font>**<font style="color:black;">工具执行器，Agent“思考”和“行动”分离解耦、独立进化</font>
+ **<font style="color:black;">原则三：</font>**<font style="color:black;">通过工具调用来联系人类，Agent中的“人机协同”</font>
+ **<font style="color:black;">原则四：</font>**<font style="color:black;">提示词可调试、可迭代、可回滚、面向场景设计、A/B测试</font>
+ **<font style="color:black;">原则五：</font>**<font style="color:black;">建设上下文评估与仲裁，突破上下文有限束缚，提升“生成质量”</font>
+ **<font style="color:black;">原则六：</font>**<font style="color:black;">将错误压缩到上下文窗口，让Agent从错误中学习并尝试自我纠正</font>
+ **<font style="color:black;">原则七：</font>**<font style="color:black;">统一执行状态和业务状态，为Agent赋予了“自主恢复”的能力</font>
+ **<font style="color:black;">原则八：</font>**<font style="color:black;">使用简单的API来完成启动、暂停和恢复，实现“任务全生命周期”管理</font>
+ **<font style="color:black;">原则九：</font>**<font style="color:black;">有限状态机，拥有Agent的自主控制流</font>
+ **<font style="color:black;">原则十：</font>**<font style="color:black;">多个小而专注的Agent，共同组成“智能组织”</font>
+ **<font style="color:black;">原则十一：</font>**<font style="color:black;">从任何地方触发Agent，构建“无处不在的智能生产力”</font>
+ **<font style="color:black;">原则十二：</font>**<font style="color:black;">将Agent看做是一个“无状态的归约器”</font>

##### <font style="color:black;">Agent in OpenHands</font>
<font style="color:rgb(0, 0, 0);">智能体抽象将配置与执行状态分离，智能体被定义为无状态、不可变的规格对象，包含 LLM 设置、工具规格、安全策略与智能体核心逻辑，可序列化并跨进程传输。</font>

###### <font style="color:rgb(0, 0, 0);">事件驱动执行</font>
<font style="color:black;">智能体通过事件驱动循环逐步处理对话状态，不直接返回结果，而是通过回调函数 on_event (event: Event) -> None 输出结构化事件（如消息、动作、观察结果），实现事件生成与执行控制的分离。该设计支持：</font>

+ <font style="color:rgb(1, 1, 1);">安全介入 —— 基于风险分析在执行前审核或拦截动作；</font>
+ <font style="color:rgb(1, 1, 1);">增量执行 —— 智能体分步推进任务，支持暂停 / 恢复、上下文溢出恢复与长对话压缩；</font>
+ <font style="color:rgb(1, 1, 1);">事件流传输 —— 实时输出中间结果（如观察数据、推理轨迹），用于界面更新与监控。</font>

###### <font style="color:rgb(1, 1, 1);">基于技能与提示的智能体上下文定制</font>
<font style="color:black;">AgentContext 集中管理所有影响 LLM 行为的输入，包括系统 / 用户消息的前缀 / 后缀、用户定义的 Skill（技能）对象。技能可通过编程方式定义，或从 Markdown 文件（如 .openhands/skills/，及 .cursorrules、agents.md 等兼容格式）加载：</font>

+ <font style="color:black;">永久激活技能（trigger=None）：持续增强系统提示；</font>
+ <font style="color:black;">条件激活技能：基于用户输入的关键词匹配触发，可包含 MCP 工具。</font>

<font style="color:black;">该设计支持丰富的上下文与行为定制，无需修改智能体核心逻辑。</font>

###### <font style="color:black;">子智能体委托机制</font>
<font style="color:rgb(0, 0, 0);">SDK 通过委托工具实现分层智能体协作，充分体现了工具抽象的可扩展性。子智能体作为独立对话存在，继承父智能体的模型配置与工作空间上下文，无需修改核心 SDK 即可实现结构化并行处理与隔离。当前实现提供阻塞式并行执行能力，作为 openhands.tools 包中的标准工具 —— 父智能体创建并监控子智能体，直至所有任务完成。这一模式证明：异步委托、动态调度、容错恢复等复杂协作行为，均可通过用户自定义工具实现，无需修改核心框架，彰显了 SDK “高级智能体编排无需改动核心” 的可扩展设计原则。</font>

##### <font style="color:rgb(0, 0, 0);">CodeAct</font>
###### 理念
<font style="color:black;">CodeAct 理念的核心突破，在于将智能代理的动作空间提升至通用编程的高度 —— 通过让大语言模型（LLM）直接生成可执行代码，打破了传统工具调用的局限。以往的智能代理往往受困于固定的工具接口，只能机械地调用预设功能，而 CodeAct 赋予代理一个统一的 “可编程” 动作接口，就像为工匠配备了一套可灵活组合的精密工具，为解决复杂任务开辟了全新路径。</font>

<font style="color:black;">这一理念的本质，是深度挖掘 LLM 擅长编写代码的原生能力。它让代理的 “动作” 不再局限于单一的原子 API 调用，而是通过生成一段完整的 Python 代码，交由 Python 解释器执行来完成复杂任务。如此一来，代理能在单个动作中封装完整的逻辑流程：包括调用多个函数或工具、控制执行顺序、处理中间结果并存储，极大地提升了任务处理的连贯性与自主性。</font>

###### 模式
<font style="color:black;">CodeAct Agent 是一个极简主义的智能体，以 ReAct的模式，根据已有的若干 Action-Observation 对的轨迹决定下一步需要采取什么 Action。在每一轮的交互循环中，CodeActAgent 具备两种核心操作模式，二者相辅相成，共同支撑任务推进：</font>

1. <font style="color:black;">对话模式（Converse）：以自然语言为沟通桥梁，实现与人类的高效协作。例如当任务需求模糊时，代理会主动请求用户澄清细节；在执行关键操作前，也会向用户确认以规避风险，充分体现了人机协作的灵活性。</font>
2. <font style="color:black;">代码行动模式（CodeAct）：依托一组标准化工具展开具体操作，覆盖多类任务场景：</font>
    - <font style="color:black;">调用execute_bash函数执行 Linux 系统的 bash 命令，实现系统级操作；</font>
    - <font style="color:black;">通过execute_ipython_cell在 IPython 环境中运行 Python 代码，处理数据计算、逻辑执行等核心任务；</font>
    - <font style="color:black;">借助browser与fetch工具与网页浏览器交互，完成信息爬取、页面操作等需求；</font>
    - <font style="color:black;">利用str_replace_editor或edit_file工具编辑文件内容，实现文档修改、代码编写等功能。</font>

<font style="color:black;">这种 “对话 + 代码” 的双轨模式，不仅简化了智能代理的操作体系，更在实际应用中显著提升了任务处理性能。</font>

###### <font style="color:black;">特色</font>
<font style="color:black;">CodeActAgent 的特色如下：</font>

1. **<font style="color:rgb(1, 1, 1);">行动空间统一化：</font>**<font style="color:rgb(1, 1, 1);">打破传统代理多行动类型的碎片化设计，将所有任务（文件操作、数据处理、系统交互等）统一为 “代码执行” 行动，简化架构且提升执行效率。</font>
2. **<font style="color:rgb(1, 1, 1);">双模式交互能力：</font>**<font style="color:rgb(1, 1, 1);">支持 “自然语言对话” 与 “代码行动” 双模式，既可以通过自然语言与人类协作（如请求澄清），也能通过代码自主完成复杂任务，适配多样场景。</font>
3. **<font style="color:rgb(1, 1, 1);">插件化沙盒依赖：</font>**<font style="color:rgb(1, 1, 1);">通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">sandbox_plugins</font>`<font style="color:rgb(1, 1, 1);"> 定义沙盒环境所需插件，按顺序初始化确保依赖正确性，同时支持灵活扩展技能（如通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentSkillsRequirement</font>`<font style="color:rgb(1, 1, 1);"> 新增工具函数）</font>**<font style="color:rgb(1, 1, 1);">。</font>**
4. **<font style="color:rgb(1, 1, 1);">完善的记忆与上下文管理：</font>**<font style="color:rgb(1, 1, 1);">集成 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ConversationMemory</font>`<font style="color:rgb(1, 1, 1);"> 管理 “行动 - 观察” 历史，搭配 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Condenser</font>`<font style="color:rgb(1, 1, 1);"> 压缩长上下文，平衡上下文相关性与模型输入长度限制。</font>
5. **<font style="color:rgb(1, 1, 1);">灵活的模型路由支持：</font>**<font style="color:rgb(1, 1, 1);">通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">LLMRegistry.get_router</font>`<font style="color:rgb(1, 1, 1);"> 获取路由 LLM，可根据任务复杂度动态选择适配模型，兼顾性能与成本。</font>
6. **<font style="color:rgb(1, 1, 1);">极简主义设计：</font>**<font style="color:rgb(1, 1, 1);">核心逻辑聚焦 “代码执行” 单一行动空间，架构简洁易懂，同时保持高扩展性，便于后续功能迭代与定制化开发。</font>

#### 定义
<font style="color:rgb(0, 0, 0);">CodeActAgent的定义如下</font>

```python
class CodeActAgent(Agent):
    """
    CodeActAgent：极简主义的智能代理，基于 CodeAct 理念实现。
    核心逻辑：将模型的行动统一到“代码执行”这一单一行动空间，通过传递“行动-观察”对列表，
    引导模型决策下一步操作，兼顾简洁性与执行性能。

    核心理念（源自论文：https://arxiv.org/abs/2402.01030）：
    打破传统代理多行动类型的复杂设计，用代码执行统一所有行动，既简化架构又提升效率。
    """
    VERSION = '2.2'  # 代理版本号

    # 沙盒环境所需插件依赖（按初始化顺序排列）
    sandbox_plugins: list[PluginRequirement] = [
        # 注意：AgentSkillsRequirement 需在 JupyterRequirement 之前初始化
        # 原因：AgentSkillsRequirement 提供大量 Python 工具函数，
        # Jupyter 环境需要依赖这些函数才能正常工作
        AgentSkillsRequirement(),  # 提供代理核心技能函数的插件
        JupyterRequirement(),      # 提供交互式 Python 执行环境的插件
    ]

    def __init__(self, config: AgentConfig, llm_registry: LLMRegistry) -> None:
        """
        初始化 CodeActAgent 实例。

        参数：
            config (AgentConfig)：当前代理的配置对象（包含模型路由、记忆策略等）
            llm_registry (LLMRegistry)：LLM 注册表实例，用于获取所需 LLM 或路由 LLM
        """
        # 调用父类 Agent 的初始化方法，完成基础配置（如 LLM 注册、提示词管理器初始化）
        super().__init__(config, llm_registry)

        self.pending_actions: deque['Action'] = deque()  # 待执行的行动队列（双端队列，支持高效进出）
        self.reset()  # 重置代理状态（初始化行动历史、观察记录等）
        self.tools = self._get_tools()  # 获取代理可使用的工具集（从插件或配置中提取）

        # 初始化对话记忆实例：存储“行动-观察”对，支持记忆压缩、上下文管理
        self.conversation_memory = ConversationMemory(self.config, self.prompt_manager)

        # 初始化上下文压缩器：根据配置创建 Condenser 实例，用于压缩长对话历史
        self.condenser = Condenser.from_config(self.config.condenser, llm_registry)

        # 覆盖父类的 LLM 实例：如需模型路由，优先使用路由 LLM（根据代理配置动态选择模型）
        self.llm = self.llm_registry.get_router(self.config)
```

##### <font style="color:black;">可配置性</font>
<font style="color:rgb(0, 0, 0);">CodeActAgent 通过 AgentConfig，可以灵活启用 / 禁用各种功能，可配置的功能如下</font>

```python
config.enable_cmd # 启用命令执行
config.enable_think # 启用思考功能
config.enable_finish # 启用完成功能
config.enable_browsing # 启用浏览器功能
config.enable_jupyter # 启用 Jupyter
config.enable_editor # 启用文件编辑器
```

##### <font style="color:black;">Pugin System</font>
<font style="color:rgb(0, 0, 0);">CodeActAgent 通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">sandbox_plugins</font>`<font style="color:rgb(0, 0, 0);"> 定义沙盒环境所需插件，按顺序初始化确保依赖正确性，同时支持灵活扩展技能（如通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentSkillsRequirement</font>`<font style="color:rgb(0, 0, 0);"> 新增工具函数）。</font>

```python
   sandbox_plugins: list[PluginRequirement] = [
        # NOTE: AgentSkillsRequirement need to go before JupyterRequirement, since
        # AgentSkillsRequirement provides a lot of Python functions,
        # and it needs to be initialized before Jupyter for Jupyter to use those functions.
        AgentSkillsRequirement(), # 提供Python函数
        JupyterRequirement(), # 提供Jupyter支持
    ]
```

##### <font style="color:black;">工具系统Tools</font>
<font style="color:black;">工具是智能代理拓展能力边界的关键，正是工具的存在，让 LLM 从单纯的对话机器人（ChatBot）进化为具备实际执行能力的智能代理（Agent）。CodeAct 的方案却反其道而行之，以极致简洁的思路重构了工具调用逻辑 —— 它将 Python 作为唯一的工具，让 LLM 通过自主编写代码的方式实现各类功能调用，摒弃了传统多工具集成的复杂设计。</font>

<font style="color:black;">传统工具调用模式中，开发者需要在系统提示词（system prompt）中明确告知 LLM 可用的工具接口（Available APIs），LLM 再通过生成工具名和参数列表的方式调用工具，无论输出格式是文本还是 JSON，本质上都受限于预设范围。而 CodeAct 省去了这一繁琐的预定义步骤，将 Python 作为统一接口，LLM 在每一轮交互中直接生成代码并交由解释器执行。这种设计让动作空间更标准化，工具调用过程简洁优雅，充分释放了 LLM 的原生潜力。</font>

###### <font style="color:black;">工具集</font>
<font style="color:black;">CodeActAgent 则有所不同。CodeActAgent是一个混合型代理，它既允许模型执行任意代码，也提供了一些特定工具供模型使用。具体来说：</font>

+ <font style="color:black;">允许模型执行任意代码。CodeActAgent的核心理念是让模型能够执行任意代码：</font>
    - <font style="color:rgb(1, 1, 1);">通过create_cmd_run_tool工具，模型可以执行任何有效的Linux bash命令</font>
    - <font style="color:rgb(1, 1, 1);">通过IPythonTool工具，模型可以执行任何有效的Python代码</font>
    - <font style="color:rgb(1, 1, 1);">这符合CodeAct论文中提出的统一代码操作空间的概念，旨在简化和提高代理性能。</font>
+ <font style="color:black;">提供特定工具集。CodeActAgent 也提供了一些预定义的工具供模型使用：</font>
    - <font style="color:rgb(1, 1, 1);">ThinkTool：让模型记录其思考过程</font>
    - <font style="color:rgb(1, 1, 1);">FinishTool：结束交互</font>
    - <font style="color:rgb(1, 1, 1);">CondensationRequestTool：请求压缩对话历史</font>
    - <font style="color:rgb(1, 1, 1);">BrowserTool：与浏览器交互（非 Windows 平台）</font>
    - <font style="color:rgb(1, 1, 1);">LLMBasedFileEditTool 或 create_str_replace_editor_tool：编辑文件</font>
    - <font style="color:rgb(1, 1, 1);">create_task_tracker_tool：任务管理工具</font>
+ <font style="color:black;">工具启用的灵活性通过配置，可以控制哪些工具被启用</font>

<font style="color:rgb(0, 0, 0);">CodeActAgent支持丰富的工具集如下：</font>

```python
    def _get_tools(self) -> list['ChatCompletionToolParam']:
        # For these models, we use short tool descriptions ( < 1024 tokens)
        # to avoid hitting the OpenAI token limit for tool descriptions.
        SHORT_TOOL_DESCRIPTION_LLM_SUBSTRS = ['gpt-4', 'o3', 'o1', 'o4']

        use_short_tool_desc = False
        if self.llm is not None:
            # For historical reasons, previously OpenAI enforces max function description length of 1k characters
            # https://community.openai.com/t/function-call-description-max-length/529902
            # But it no longer seems to be an issue recently
            # https://community.openai.com/t/was-the-character-limit-for-schema-descriptions-upgraded/1225975
            # Tested on GPT-5 and longer description still works. But we still keep the logic to be safe for older models.
            use_short_tool_desc = any(
                model_substr in self.llm.config.model
                for model_substr in SHORT_TOOL_DESCRIPTION_LLM_SUBSTRS
            )

        tools = []
        if self.config.enable_cmd: # Bash命令执行工具
            tools.append(create_cmd_run_tool(use_short_description=use_short_tool_desc))
        if self.config.enable_think: # 思考工具，记录推理过程
            tools.append(ThinkTool)
        if self.config.enable_finish: # 完成工具，结束任务
            tools.append(FinishTool)
        if self.config.enable_condensation_request:
            tools.append(CondensationRequestTool)
        if self.config.enable_browsing: # 浏览器工具
            if sys.platform == 'win32':
                logger.warning('Windows runtime does not support browsing yet')
            else:
                tools.append(BrowserTool)
        if self.config.enable_jupyter: # IPython工具
            tools.append(IPythonTool)
        if self.config.enable_plan_mode:
            # In plan mode, we use the task_tracker tool for task management
            tools.append(create_task_tracker_tool(use_short_tool_desc))
        if self.config.enable_llm_editor: # 文件编辑工具
            tools.append(LLMBasedFileEditTool)
        elif self.config.enable_editor:
            tools.append(
                create_str_replace_editor_tool(
                    use_short_description=use_short_tool_desc,
                    runtime_type=self.config.runtime,
                )
            )
        return tools
```

###### <font style="color:black;">Browser Tool</font>
<font style="color:rgb(0, 0, 0);">BrowserTool 举例如下：</font>

```python
BrowserTool = ChatCompletionToolParam(
    type='function',
    function=ChatCompletionToolParamFunctionChunk(
        name=BROWSER_TOOL_NAME,
        description=_BROWSER_DESCRIPTION,
        parameters={
            'type': 'object',
            'properties': {
                'code': {
                    'type': 'string',
                    'description': (
                        'The Python code that interacts with the browser.\n'
                        + _BROWSER_TOOL_DESCRIPTION
                    ),
                },
                'security_risk': {
                    'type': 'string',
                    'description': SECURITY_RISK_DESC,
                    'enum': RISK_LEVELS,
                },
            },
            'required': ['code', 'security_risk'],
        },
    ),
)
```

<font style="color:rgb(0, 0, 0);">_BROWSER_TOOL_DESCRIPTION 如下。</font>

```python
_BROWSER_TOOL_DESCRIPTION = """
The following 15 functions are available. Nothing else is supported.

goto(url: str)
    Description: Navigate to a url.
    Examples:
        goto('http://www.example.com')

go_back()
    Description: Navigate to the previous page in history.
    Examples:
        go_back()

go_forward()
    Description: Navigate to the next page in history.
    Examples:
        go_forward()

noop(wait_ms: float = 1000)
    Description: Do nothing, and optionally wait for the given time (in milliseconds).
    You can use this to get the current page content and/or wait for the page to load.
    Examples:
        noop()

        noop(500)

scroll(delta_x: float, delta_y: float)
    Description: Scroll horizontally and vertically. Amounts in pixels, positive for right or down scrolling, negative for left or up scrolling. Dispatches a wheel event.
    Examples:
        scroll(0, 200)

        scroll(-50.2, -100.5)

fill(bid: str, value: str)
    Description: Fill out a form field. It focuses the element and triggers an input event with the entered text. It works for <input>, <textarea> and [contenteditable] elements.
    Examples:
        fill('237', 'example value')

        fill('45', 'multi-line\nexample')

        fill('a12', 'example with "quotes"')

select_option(bid: str, options: str | list[str])
    Description: Select one or multiple options in a <select> element. You can specify option value or label to select. Multiple options can be selected.
    Examples:
        select_option('a48', 'blue')

        select_option('c48', ['red', 'green', 'blue'])

click(bid: str, button: Literal['left', 'middle', 'right'] = 'left', modifiers: list[typing.Literal['Alt', 'Control', 'ControlOrMeta', 'Meta', 'Shift']] = [])
    Description: Click an element.
    Examples:
        click('a51')

        click('b22', button='right')

        click('48', button='middle', modifiers=['Shift'])

dblclick(bid: str, button: Literal['left', 'middle', 'right'] = 'left', modifiers: list[typing.Literal['Alt', 'Control', 'ControlOrMeta', 'Meta', 'Shift']] = [])
    Description: Double click an element.
    Examples:
        dblclick('12')

        dblclick('ca42', button='right')

        dblclick('178', button='middle', modifiers=['Shift'])

hover(bid: str)
    Description: Hover over an element.
    Examples:
        hover('b8')

press(bid: str, key_comb: str)
    Description: Focus the matching element and press a combination of keys. It accepts the logical key names that are emitted in the keyboardEvent.key property of the keyboard events: Backquote, Minus, Equal, Backslash, Backspace, Tab, Delete, Escape, ArrowDown, End, Enter, Home, Insert, PageDown, PageUp, ArrowRight, ArrowUp, F1 - F12, Digit0 - Digit9, KeyA - KeyZ, etc. You can alternatively specify a single character you'd like to produce such as "a" or "#". Following modification shortcuts are also supported: Shift, Control, Alt, Meta, ShiftLeft, ControlOrMeta. ControlOrMeta resolves to Control on Windows and Linux and to Meta on macOS.
    Examples:
        press('88', 'Backspace')

        press('a26', 'ControlOrMeta+a')

        press('a61', 'Meta+Shift+t')

focus(bid: str)
    Description: Focus the matching element.
    Examples:
        focus('b455')

clear(bid: str)
    Description: Clear the input field.
    Examples:
        clear('996')

drag_and_drop(from_bid: str, to_bid: str)
    Description: Perform a drag & drop. Hover the element that will be dragged. Press left mouse button. Move mouse to the element that will receive the drop. Release left mouse button.
    Examples:
        drag_and_drop('56', '498')

upload_file(bid: str, file: str | list[str])
    Description: Click an element and wait for a "filechooser" event, then select one or multiple input files for upload. Relative file paths are resolved relative to the current working directory. An empty list clears the selected files.
    Examples:
        upload_file('572', '/home/user/my_receipt.pdf')

        upload_file('63', ['/home/bob/Documents/image.jpg', '/home/bob/Documents/file.zip'])
"""
```

##### <font style="color:black;">Context</font>
<font style="color:rgb(0, 0, 0);">让 AI 做决策，意味着它需要对环境有深刻的理解，甚至具备一定程度的“常识”，在已知的模型能力下，往往和高质量的prompt和上下文强相关。要让 AI 胜任这个角色，必须给它提供一套明确的行动框架：清晰的工具集、详尽的工具使用场景、固定的工作流，甚至要细化到每个决策节点的触发时机。</font>

###### <font style="color:rgb(0, 0, 0);">需求</font>
<font style="color:black;">在以自然语言为接口、大模型为核心的 Software 3.0 时代，AI Agent 作为上下文驱动的生成式应用，需突破传统上下文窗口的固有局限。传统依赖上下文窗口维持对话状态与任务记忆的方式，存在长度受限、组织无序、知识静态、成本高昂四大痛点 —— 既无法承载超长历史信息，也难以高效检索与动态更新知识，更会因长文本处理消耗大量计算资源。</font>

<font style="color:black;">从本质上讲，上下文（Context）是提供给 LLM 的、用于完成下一步推理或生成任务的全部信息集合，从系统架构视角看，Agentic System 可类比为新型操作系统：LLM 扮演 CPU 角色，上下文窗口则如同容量有限的 RAM，而上下文工程就是核心的 “内存管理器”—— 其核心职责并非简单填充数据，而是通过智能调度算法，动态决定上下文数据的加载与换出，确保系统高效运行与结果精准性。</font>

<font style="color:rgb(0, 0, 0);">分为 </font>**<font style="color:black;">“上下文输入源” 和 “输出 / 工具支撑”</font>**<font style="color:rgb(0, 0, 0);"> 两类：</font>

| **<font style="color:rgb(0, 0, 0);">分类</font>** | **<font style="color:rgb(0, 0, 0);">模块</font>** | **<font style="color:rgb(0, 0, 0);">作用说明</font>** |
| :--- | :--- | :--- |
| **<font style="color:black;">上下文输入源</font>** | <font style="color:rgb(0, 0, 0);">Instructions / System Prompt</font> | <font style="color:rgb(0, 0, 0);">模型的 “规则 / 角色定义”，决定模型的行为模式（如 “你是一个严谨的助手”）</font> |
| <font style="color:rgb(0, 0, 0);">   </font> | <font style="color:rgb(0, 0, 0);">State / History（Short-term Memory）</font> | <font style="color:rgb(0, 0, 0);">短期记忆：当前会话的历史交互记录，保证对话连贯性</font> |
| <font style="color:rgb(0, 0, 0);">   </font> | <font style="color:rgb(0, 0, 0);">Long-term Memory</font> | <font style="color:rgb(0, 0, 0);">长期记忆：跨会话的用户 / 任务信息（如用户偏好、历史任务结果）</font> |
| <font style="color:rgb(0, 0, 0);">   </font> | <font style="color:rgb(0, 0, 0);">User Prompt</font> | <font style="color:rgb(0, 0, 0);">用户当前的查询指令，是上下文的核心触发点</font> |
| <font style="color:rgb(0, 0, 0);">   </font> | <font style="color:rgb(0, 0, 0);">Retrieved Information（RAG）</font> | <font style="color:rgb(0, 0, 0);">检索增强生成：从外部知识库（文档、数据库）中调取的相关信息</font> |
| **<font style="color:black;">输出 / 工具支撑</font>** | <font style="color:rgb(0, 0, 0);">Available Tools</font> | <font style="color:rgb(0, 0, 0);">模型可调用的外部工具（如计算器、搜索引擎），扩展模型能力</font> |
| <font style="color:rgb(0, 0, 0);">   </font> | <font style="color:rgb(0, 0, 0);">Structured Output</font> | <font style="color:rgb(0, 0, 0);">模型输出的结构化格式（如 JSON、表格），提升结果的可用性</font> |


###### <font style="color:black;">核心特色</font>
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentContext</font>`<font style="color:black;"> 是 OpenHands 框架中管理提示词扩展的核心结构，负责整合所有影响系统扩展和解释用户提示的上下文信息。它将静态环境细节（如代码库信息）和动态用户激活的扩展（如技能组件）结合，为大语言模型（LLM）交互提供完整的提示词上下文，是组装、格式化和注入所有与提示相关信息的主要容器。</font>

1. **<font style="color:black;">多维度上下文整合</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">统一管理代码库上下文、运行时环境、对话指令和知识技能等多类信息，避免上下文分散。</font>
2. **<font style="color:black;">技能扩展机制</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">支持通过技能（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Skill</font>`<font style="color:rgb(1, 1, 1);">）动态扩展提示词，技能可被用户输入触发，自动注入领域知识或指导信息。</font>
3. **<font style="color:black;">灵活的提示词后缀</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">提供系统消息后缀和用户消息后缀，可按需附加额外信息（如代码库详情、运行时参数）。</font>
4. **<font style="color:black;">用户技能自动加载</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">支持从本地目录自动加载用户自定义技能，且避免与显式技能重复。</font>

###### <font style="color:black;">Workflow</font>
```python
┌─────────────────────────────┐
│     AgentContext 初始化     │
└─────────────────────────────┘
              │
              ▼
┌─────────────────────────────┐
│        验证技能列表           │
│        （去重校验）           │
└─────────────────────────────┘
              │
              ▼
┌─────────────────────────────┐
│     检查是否加载用户技能       │
└─────────────────────────────┘
              │
              ▼
┌─────────────────────────────┐
│   从本地目录加载用户技能       │
│        （合并去重）          │
└─────────────────────────────┘
              │
      ┌───────┴───────┐
      ▼               ▼
┌─────────────────┐ ┌─────────────────┐
│生成系统消息后缀    │ │生成用户消息后缀   │
└─────────────────┘ └─────────────────┘
      │               │
      ▼               ▼
┌─────────────────┐ ┌─────────────────┐
│1.筛选无触发条件技能│ │1.提取用户消息文本  │
└─────────────────┘ └─────────────────┘
      │               │
      ▼               ▼
┌─────────────────┐ ┌─────────────────┐
│2.渲染模板生成后缀 │ │2.匹配技能触发关键词│
└─────────────────┘ └─────────────────┘
      │               │
      ▼               ▼
┌─────────────────┐ ┌─────────────────┐
│3.整合自定义系统后缀│ │3.渲染触发技能内容│
└─────────────────┘ └─────────────────┘
                          │
                          ▼
                 ┌─────────────────┐
                 │4.整合自定义用户后缀│
                 └─────────────────┘
```

###### <font style="color:black;">Codes</font>
```python
class AgentContext(BaseModel):
    """管理提示词扩展的核心结构。

    AgentContext 统一了所有影响系统扩展和解释用户提示的上下文输入，
    融合了静态环境细节和来自技能的动态用户激活扩展。

    具体包含：
    - **代码库上下文/代码库技能**：活跃代码库、分支信息及代码库技能提供的特定指令。
    - **运行时上下文**：当前执行环境（主机、工作目录、密钥、日期等）。
    - **对话指令**：约束或指导智能体在会话中行为的任务/渠道特定规则（可选）。
    - **知识技能**：可被用户输入触发的扩展组件，用于注入知识或领域特定指导。

    这些元素共同使 AgentContext 成为负责组装、格式化和注入所有提示相关上下文到
    LLM 交互中的主要容器。
    """  # noqa: E501

    skills: list[Skill] = Field(
        default_factory=list,
        description="List of available skills that can extend the user's input.",
    )
    system_message_suffix: str | None = Field(
        default=None, description="Optional suffix to append to the system prompt."
    )
    user_message_suffix: str | None = Field(
        default=None, description="Optional suffix to append to the user's message."
    )
    load_user_skills: bool = Field(
        default=False,
        description=(
            "Whether to automatically load user skills from ~/.openhands/skills/ "
            "and ~/.openhands/microagents/ (for backward compatibility). "
        ),
    )

    @field_validator("skills")
    @classmethod
    def _validate_skills(cls, v: list[Skill], _info):
        """验证技能列表，确保无重复名称。"""
        if not v:
            return v
        # 检查重复的技能名称
        seen_names = set()
        for skill in v:
            if skill.name in seen_names:
                raise ValueError(f"Duplicate skill name found: {skill.name}")
            seen_names.add(skill.name)
        return v

    @model_validator(mode="after")
    def _load_user_skills(self):
        """若启用，则从用户主目录加载自定义技能。"""
        if not self.load_user_skills:
            return self

        try:
            # 加载用户技能
            user_skills = load_user_skills()
            # 合并用户技能与显式技能，避免重复
            existing_names = {skill.name for skill in self.skills}
            for user_skill in user_skills:
                if user_skill.name not in existing_names:
                    self.skills.append(user_skill)
                else:
                    logger.warning(
                        f"Skipping user skill '{user_skill.name}' "
                        f"(already in explicit skills)"
                    )
        except Exception as e:
            logger.warning(f"Failed to load user skills: {str(e)}")

        return self

    def get_system_message_suffix(self) -> str | None:
        """获取包含代码库技能内容和自定义后缀的系统消息。

        自定义后缀通常包括：
        - 代码库信息（仓库名称、分支名称、PR编号等）
        - 运行时信息（如可用主机、当前日期）
        - 对话指令（如用户偏好、任务详情）
        - 代码库特定指令（从代码库技能收集）
        """
        # 筛选无触发条件的技能（始终激活的代码库技能）
        repo_skills = [s for s in self.skills if s.trigger is None]
        logger.debug(f"Triggered {len(repo_skills)} repository skills: {repo_skills}")
        # 构建工作区上下文信息
        if repo_skills:
            # TODO(test): 添加渲染测试确保功能正常
            formatted_text = render_template(
                prompt_dir=str(PROMPT_DIR),  # 模板目录
                template_name="system_message_suffix.j2",  # 系统消息后缀模板
                repo_skills=repo_skills,  # 代码库技能列表
                system_message_suffix=self.system_message_suffix or "",  # 自定义系统后缀
            ).strip()
            return formatted_text
        # 若无可激活的代码库技能，直接返回自定义系统后缀（非空时）
        elif self.system_message_suffix and self.system_message_suffix.strip():
            return self.system_message_suffix.strip()
        return None

    def get_user_message_suffix(
        self, user_message: Message, skip_skill_names: list[str]
    ) -> tuple[TextContent, list[str]] | None:
        """通过技能召回的知识增强用户消息。

        流程如下：
        - 提取用户消息的文本内容
        - 匹配查询中的技能触发词
        - 若有相关技能被触发，返回格式化的知识和触发的技能名称
        """  # noqa: E501

        user_message_suffix = None
        # 处理自定义用户消息后缀
        if self.user_message_suffix and self.user_message_suffix.strip():
            user_message_suffix = self.user_message_suffix.strip()

        # 提取用户消息中的纯文本内容
        query = "\n".join(
            c.text for c in user_message.content if isinstance(c, TextContent)
        ).strip()
        recalled_knowledge: list[SkillKnowledge] = []

        # 若查询为空，仅返回自定义用户后缀（如有）
        if not query:
            if user_message_suffix:
                return TextContent(text=user_message_suffix), []
            return None

        # 在查询中搜索技能触发词
        for skill in self.skills:
            if not isinstance(skill, Skill):
                continue
            # 匹配技能触发条件
            trigger = skill.match_trigger(query)
            if trigger and skill.name not in skip_skill_names:
                logger.info(
                    "Skill '%s' triggered by keyword '%s'",
                    skill.name,
                    trigger,
                )
                # 收集触发技能的知识
                recalled_knowledge.append(
                    SkillKnowledge(
                        name=skill.name,
                        trigger=trigger,
                        content=skill.content,
                    )
                )

        # 若有触发的技能，渲染知识内容
        if recalled_knowledge:
            formatted_skill_text = render_template(
                prompt_dir=str(PROMPT_DIR),
                template_name="skill_knowledge_info.j2",  # 技能知识模板
                triggered_agents=recalled_knowledge,  # 触发的技能知识列表
            )
            # 合并自定义用户后缀
            if user_message_suffix:
                formatted_skill_text += "\n" + user_message_suffix
            return TextContent(text=formatted_skill_text), [
                k.name for k in recalled_knowledge
            ]

        # 若无触发技能，仅返回自定义用户后缀（如有）
        if user_message_suffix:
            return TextContent(text=user_message_suffix), []
        return None
```

##### <font style="color:black;">Prompt</font>
<font style="color:black;">CodeActAgent的提示词（prompt）是通过PromptManager从文件中加载的。具体来说：</font>

+ **<font style="color:rgb(1, 1, 1);">提示词位置：</font>**<font style="color:rgb(1, 1, 1);">提示词文件位于openhands/agenthub/codeact_agent/prompts/目录下，主提示词文件名为codeact_agent_system_prompt.hbs。</font>
+ **<font style="color:rgb(1, 1, 1);">加载机制：</font>**<font style="color:rgb(1, 1, 1);">通过PromptManager类管理提示词，默认系统提示词文件名由AgentConfig的resolved_system_prompt_filename属性决定。</font>

##### <font style="color:black;">迭代</font>
<font style="color:black;">CodeActAgent 被设计为可以并且应该继续修改自己生成的代码。系统提供了多种工具和明确的指导原则来支持迭代开发过程。代理被鼓励通过多次迭代来完善其解决方案，包括修改、测试和重新修改代码，直到达到满意的结果。这种设计符合 CodeAct 论文的理念，即将所有操作统一到代码执行空间中，从而简化和提高代理性能。</font>

+ <font style="color:black;">系统设计系统设计明确鼓励 CodeActAgent 迭代修改代码：</font>
    - <font style="color:rgb(1, 1, 1);">在系统提示中，有明确的指导原则："当探索代码库时，使用高效的工具如 find、grep 和 git 命令，并在适当时候使用过滤器来最小化不必要的操作"</font>
    - <font style="color:rgb(1, 1, 1);">提示中还强调："在实现任何更改之前，首先通过探索彻底理解代码库"</font>
    - <font style="color:rgb(1, 1, 1);">"在 reproducing bugs 或 implementing fixes 时，使用单个文件而不是创建具有不同版本的多个文件"</font>
+ <font style="color:black;">系统提示中的文件系统指南明确支持修改现有代码：</font>
    - <font style="color:rgb(1, 1, 1);">"如果被要求编辑文件，直接编辑文件，而不是创建具有不同文件名的新文件"</font>
    - <font style="color:rgb(1, 1, 1);">"对于全局搜索和替换操作，考虑使用 sed 而不是多次打开文件编辑器"</font>
    - <font style="color:rgb(1, 1, 1);">"永远不要为同一文件创建多个版本"</font>
+ <font style="color:black;">系统提示中定义的问题解决工作流程明确支持迭代修改：</font>
    - <font style="color:rgb(1, 1, 1);">探索：彻底探索相关文件并理解上下文</font>
    - <font style="color:rgb(1, 1, 1);">分析：考虑多种方法并选择最有希望的一种</font>
    - <font style="color:rgb(1, 1, 1);">测试：为 bug 修复创建测试以在实施修复之前验证问题</font>
    - <font style="color:rgb(1, 1, 1);">实施：进行有针对性的、最小的更改以解决问题</font>
    - <font style="color:rgb(1, 1, 1);">验证：如果环境设置为运行测试，则彻底测试实现，包括边缘情况</font>
+ <font style="color:black;">CodeActAgent 拥有多种工具来支持迭代修改代码：</font>
    - <font style="color:rgb(1, 1, 1);">文件编辑工具（create_str_replace_editor_tool 和 LLMBasedFileEditTool）允许它修改现有文件</font>
    - <font style="color:rgb(1, 1, 1);">Bash 命令执行工具允许它运行测试、编译代码、安装依赖等</font>
    - <font style="color:rgb(1, 1, 1);">IPython 执行工具允许它测试代码片段</font>

#### <font style="color:rgb(1, 1, 1);">Workflow</font>
##### 决策流程
<font style="color:black;">step方法是决策过程，返回各种Action：</font>

+ <font style="color:rgb(1, 1, 1);">CmdRunAction(command) - 要运行的bash命令</font>
+ <font style="color:rgb(1, 1, 1);">IPythonRunCellAction(code) - 要运行的IPython代码</font>
+ <font style="color:rgb(1, 1, 1);">AgentDelegateAction(agent, inputs) - 用于（子）任务的委托操作</font>
+ <font style="color:rgb(1, 1, 1);">MessageAction(content) - 要运行的消息操作（例如，请求澄清）</font>
+ <font style="color:rgb(1, 1, 1);">AgentFinishAction() - 结束交互</font>
+ <font style="color:rgb(1, 1, 1);">CondensationAction(...) - 通过遗忘指定事件并可选地提供摘要来压缩对话历史</font>
+ <font style="color:rgb(1, 1, 1);">FileReadAction(path, ...) - 从指定路径读取文件内容</font>
+ <font style="color:rgb(1, 1, 1);">FileEditAction(path, ...) - 使用基于LLM（已弃用）或基于ACI的编辑方式编辑文件</font>
+ <font style="color:rgb(1, 1, 1);">AgentThinkAction(thought) - 记录代理的思考/推理过程</font>
+ <font style="color:rgb(1, 1, 1);">CondensationRequestAction() - 请求压缩对话历史</font>
+ <font style="color:rgb(1, 1, 1);">BrowseInteractiveAction(browser_actions) - 使用指定操作与浏览器交互</font>
+ <font style="color:rgb(1, 1, 1);">MCPAction(name, arguments) - 与MCP服务器工具交互</font>

```python
    def step(self, state: State) -> 'Action':
        """使用CodeAct Agent执行一步操作。

        包括收集先前步骤的信息，并提示模型生成要执行的命令。

        参数:
        - state (State): 用于获取更新的信息
        """
        # 处理待处理操作（如果有）
        if self.pending_actions:
            # 返回并移除队列中的第一个待处理操作
            return self.pending_actions.popleft()

        # 如果任务已完成，退出
        # 获取最新的用户消息
        latest_user_message = state.get_last_user_message()
        # 若用户输入"/exit"，则返回结束操作
        if latest_user_message and latest_user_message.content.strip() == '/exit':
            return AgentFinishAction()

        # 压缩状态中的事件。如果获得视图，将其传递给对话管理器处理；
        # 如果获得压缩事件，则返回该事件而非操作。控制器将立即要求代理使用新视图再次执行步骤
        condensed_history: list[Event] = []
        # 匹配压缩器返回的结果类型
        match self.condenser.condensed_history(state):
            # 若为View类型，提取事件列表作为压缩历史
            case View(events=events):
                condensed_history = events
            # 若为Condensation类型，返回其包含的压缩操作
            case Condensation(action=condensation_action):
                return condensation_action

        # 打印调试日志：显示处理的压缩事件数量和总事件数量
        logger.debug(
            f'从共{len(state.history)}个事件中处理{len(condensed_history)}个压缩事件'
        )

        # 获取初始用户消息（从状态历史中）
        initial_user_message = self._get_initial_user_message(state.history)
        # 构建用于LLM的消息列表（基于压缩历史和初始用户消息）
        messages = self._get_messages(condensed_history, initial_user_message)
        # 构建LLM调用参数
        params: dict = {
            'messages': messages,  # 消息列表
        }
        # 检查并添加可用工具（根据LLM配置过滤）
        params['tools'] = check_tools(self.tools, self.llm.config)
        # 添加额外元数据（从状态中提取，适配LLM格式）
        params['extra_body'] = {
            'metadata': state.to_llm_metadata(
                model_name=self.llm.config.model, agent_name=self.name
            )
        }
        # 调用LLM获取响应
        response = self.llm.completion(** params)
        # 打印调试日志：显示LLM返回的响应
        logger.debug(f'LLM返回的响应: {response}')
        # 将LLM响应转换为具体操作列表
        actions = self.response_to_actions(response)
        # 打印调试日志：显示转换后的操作
        logger.debug(f'response_to_actions转换后的操作: {actions}')
        # 将所有操作添加到待处理队列
        for action in actions:
            self.pending_actions.append(action)
        # 返回并移除队列中的第一个操作
        return self.pending_actions.popleft()


```

##### 消息处理
<font style="color:black;">_get_messages方法负责处理消息。该方法执行以下步骤：</font>

1. <font style="color:rgb(1, 1, 1);">检查事件中是否有SystemMessageAction，若缺失则添加（为了向后兼容）</font>
2. <font style="color:rgb(1, 1, 1);">将事件（操作和观察结果）处理为消息，包括SystemMessageAction</font>
3. <font style="color:rgb(1, 1, 1);">在函数调用模式下处理工具调用及其响应</font>
4. <font style="color:rgb(1, 1, 1);">管理消息角色交替（用户/助手/工具）</font>
5. <font style="color:rgb(1, 1, 1);">为特定LLM提供商（如Anthropic）应用缓存</font>
6. <font style="color:rgb(1, 1, 1);">在非函数调用模式下添加环境提醒</font>

```python
    def _get_messages(
        self, events: list[Event], initial_user_message: MessageAction
    ) -> list[Message]:
        """为LLM对话构建消息历史。

        该方法通过处理状态中的事件并将其格式化为LLM可理解的消息，构建结构化的对话历史。
        它处理常规消息流和函数调用场景。

        参数:
            events: 要转换为消息的事件列表

        返回:
            list[Message]: 格式化的消息列表，可直接供LLM使用，包括：
                - 带提示的系统消息（来自SystemMessageAction）
                - 操作消息（来自用户和助手）
                - 观察消息（包括工具响应）
                - 环境提醒（在非函数调用模式下）

        注意:
            - 在函数调用模式下，工具调用及其响应会被仔细跟踪以维持正确的对话流程
            - 同一角色的消息会被合并，以避免连续出现相同角色的消息
            - 对于Anthropic模型，会根据其文档对特定消息进行缓存
        """
        # 若未实例化提示管理器，抛出异常
        if not self.prompt_manager:
            raise Exception('提示管理器未实例化。')

        # 使用对话内存处理事件（包括SystemMessageAction）
        messages = self.conversation_memory.process_events(
            condensed_history=events,  # 压缩后的事件历史
            initial_user_action=initial_user_message,  # 初始用户消息
            max_message_chars=self.llm.config.max_message_chars,  # 消息最大字符数限制
            vision_is_active=self.llm.vision_is_active(),  # 是否启用视觉功能
        )

        # 若LLM启用了提示缓存，应用缓存机制
        if self.llm.is_caching_prompt_active():
            self.conversation_memory.apply_prompt_caching(messages)

        # 返回构建的消息列表
        return messages


```

##### 历史压缩
<font style="color:rgb(0, 0, 0);">在step函数中，会通过Condensor压缩对话历史，避免上下文过长。</font>

```python
        # Condense the events from the state. If we get a view we'll pass those
        # to the conversation manager for processing, but if we get a condensation
        # event we'll just return that instead of an action. The controller will
        # immediately ask the agent to step again with the new view.
        condensed_history: list[Event] = []
        match self.condenser.condensed_history(state):
            case View(events=events):
                condensed_history = events

            case Condensation(action=condensation_action):
                return condensation_action


```

##### 内存管理
<font style="color:black;">成员变量conversation_memory会进行会话内存管理。</font>

```python
self.conversation_memory = ConversationMemory(self.config, self.prompt_manager)
```

<font style="color:black;">具体代码参见：</font>

```python
def _get_messages(
    self, events: list[Event], initial_user_message: MessageAction
) -> list[Message]:
    # Use ConversationMemory to process events (including SystemMessageAction)
    messages = self.conversation_memory.process_events(
        condensed_history=events,
        initial_user_action=initial_user_message,
        max_message_chars=self.llm.config.max_message_chars,
        vision_is_active=self.llm.vision_is_active(),
    )

    if self.llm.is_caching_prompt_active():
        self.conversation_memory.apply_prompt_caching(messages)

        return messages
```




### AgentController
<font style="color:black;">现在的 AI Agent 系统基本都遵循一个通用架构，主要包含三大件：</font>

+ <font style="color:rgb(1, 1, 1);">负责"思考"的 LLM 后端</font>
+ <font style="color:rgb(1, 1, 1);">负责"执行"的工具框架</font>
+ <font style="color:rgb(1, 1, 1);">负责协调的控制循环</font>

<font style="color:black;">AgentController 类就对应第三部分，这是用户查询的主入口和协调者。负责管理整个事件循环，接收执行逻辑产出的事件，与其他组件协作处理并提交事件操作，并将处理后的事件转发到上游（如 UI）。它本质上根据产出的事件逐轮驱动对话。</font>

#### <font style="color:black;">分析 AgentController</font>
##### 1.1 定义
<font style="color:rgb(0, 0, 0);">AgentController的主要代码如下：</font>

```python
class AgentController:
    # 控制器唯一标识ID
    id: str
    # 被控制的Agent实例（核心决策组件）
    agent: Agent
    # Agent执行的最大迭代次数（防止无限循环）
    max_iterations: int
    # 事件流实例（组件间通信的核心枢纽）
    event_stream: EventStream
    # 当前系统状态（包含完整上下文信息）
    state: State
    # 动作确认模式开关（开启时需确认后才执行Agent动作）
    confirmation_mode: bool
    # Agent名称到LLM配置的映射（用于委托代理场景）
    agent_to_llm_config: dict[str, LLMConfig]
    # Agent名称到Agent配置的映射（用于委托代理场景）
    agent_configs: dict[str, AgentConfig]
    # 父控制器实例（存在层级委托时非空）
    parent: 'AgentController | None' = None
    # 委托的子控制器实例（当前控制器委托任务时非空）
    delegate: 'AgentController | None' = None
    # 待处理的动作信息：元组包含动作对象和时间戳（记录动作创建时间）
    _pending_action_info: tuple[Action, float] | None = None
    # 控制器关闭状态标记（True表示已关闭，不再处理任务）
    _closed: bool = False
    # 缓存的第一条用户消息（用于初始化上下文等场景）
    _cached_first_user_message: MessageAction | None = None

    def __init__(
        self,
        agent: Agent,
        event_stream: EventStream,
        conversation_stats: ConversationStats,
        iteration_delta: int,
        budget_per_task_delta: float | None = None,
        agent_to_llm_config: dict[str, LLMConfig] | None = None,
        agent_configs: dict[str, AgentConfig] | None = None,
        sid: str | None = None,
        file_store: FileStore | None = None,
        user_id: str | None = None,
        confirmation_mode: bool = False,
        initial_state: State | None = None,
        is_delegate: bool = False,
        headless_mode: bool = True,
        status_callback: Callable | None = None,
        replay_events: list[Event] | None = None,
        security_analyzer: 'SecurityAnalyzer | None' = None,
    ):
        """初始化AgentController类的新实例。

        参数:
            agent: 被控制的Agent实例。
            event_stream: 用于发布事件的事件流实例。
            conversation_stats: 对话统计信息实例（记录交互指标等）。
            iteration_delta: Agent可执行的最大迭代次数。
            budget_per_task_delta: 每个任务允许的最大预算（单位：美元），超出则停止Agent。
            agent_to_llm_config: Agent名称到LLM配置的映射字典（用于委托给其他Agent时）。
            agent_configs: Agent名称到Agent配置的映射字典（用于委托给其他Agent时）。
            sid: Agent的会话ID。
            file_store: 文件存储实例（用于状态持久化等）。
            user_id: 用户唯一标识。
            confirmation_mode: 是否启用Agent动作的确认模式。
            initial_state: 控制器的初始状态。
            is_delegate: 该控制器是否为委托控制器（子控制器）。
            headless_mode: Agent是否以无头模式运行（无GUI交互）。
            status_callback: 处理状态更新的可选回调函数。
            replay_events: 用于回放的事件日志列表。
            security_analyzer: 安全分析器实例（用于动作安全校验）。
        """
        # 初始化控制器ID：优先使用传入的sid，否则使用事件流的sid
        self.id = sid or event_stream.sid
        # 记录用户ID
        self.user_id = user_id
        # 记录文件存储实例
        self.file_store = file_store
        # 绑定被控制的Agent
        self.agent = agent
        # 记录无头模式状态
        self.headless_mode = headless_mode
        # 标记当前控制器是否为委托控制器
        self.is_delegate = is_delegate
        # 绑定对话统计实例
        self.conversation_stats = conversation_stats

        # 先设置事件流，后续可能需要订阅事件
        self.event_stream = event_stream

        # 非委托控制器需要订阅事件流，以接收并处理系统事件
        if not self.is_delegate:
            self.event_stream.subscribe(
                EventStreamSubscriber.AGENT_CONTROLLER,  # 订阅者类型（标识为Agent控制器）
                self.on_event,  # 事件回调处理函数
                self.id  # 订阅者ID（当前控制器ID）
            )

        # 初始化状态跟踪器：负责状态的管理、持久化与恢复
        self.state_tracker = StateTracker(sid, file_store, user_id)

        # 设置初始状态：支持从历史会话状态、父Agent状态或全新状态初始化
        self.set_initial_state(
            state=initial_state,  # 传入的初始状态（可能为None）
            conversation_stats=conversation_stats,  # 对话统计信息
            max_iterations=iteration_delta,  # 最大迭代次数
            max_budget_per_task=budget_per_task_delta,  # 任务最大预算
            confirmation_mode=confirmation_mode,  # 动作确认模式
        )

        # 将状态跟踪器中的状态赋值给控制器的state属性
        # 注意：此处为了向后兼容暂时共享状态，后续应将状态逻辑统一迁移到状态管理器
        self.state = self.state_tracker.state

        # 初始化Agent到LLM配置的映射：无传入配置则设为空字典
        self.agent_to_llm_config = agent_to_llm_config if agent_to_llm_config else {}
        # 初始化Agent配置映射：无传入配置则设为空字典
        self.agent_configs = agent_configs if agent_configs else {}
        # 记录初始的最大迭代次数（用于后续重置等场景）
        self._initial_max_iterations = iteration_delta
        # 记录初始的任务最大预算（用于后续重置等场景）
        self._initial_max_budget_per_task = budget_per_task_delta

        # 初始化卡顿检测器：用于识别Agent是否陷入执行卡顿
        self._stuck_detector = StuckDetector(self.state)
        # 绑定状态回调函数（用于对外通知状态更新）
        self.status_callback = status_callback

        # 初始化回放管理器：用于处理事件回放场景
        self._replay_manager = ReplayManager(replay_events)

        # 记录动作确认模式状态
        self.confirmation_mode = confirmation_mode

        # 绑定安全分析器实例（用于动作的安全校验）
        self.security_analyzer = security_analyzer

        # 向事件流中添加系统消息（初始化Agent的系统上下文等）
        self._add_system_message()
```

##### 1.2 核心职责
<font style="color:black;">AgentController 的核心职责可归结为三大支柱：</font>

+ **<font style="color:black;">监听事件流</font>****<font style="color:rgb(1, 1, 1);">。</font>**<font style="color:rgb(1, 1, 1);">它是系统事件流的核心订阅者，能够捕捉所有关键变化 —— 无论是用户指令、Agent 的决策输出，还是环境的反馈结果。这一能力使其成为系统的 “感知中枢”，确保对全局动态的全面掌控。</font>
+ **<font style="color:black;">管理状态机</font>****<font style="color:rgb(1, 1, 1);">。</font>**<font style="color:rgb(1, 1, 1);">它负责维护任务的当前状态，并根据接收到的事件触发精准的状态转换。例如，当 Agent 执行过程中需要用户确认时，AgentController 会主动暂停系统运行，等待用户输入后再恢复流程，保障任务执行的连贯性，比如：</font>
    - **<font style="color:rgb(1, 1, 1);">状态管理：</font>**<font style="color:rgb(1, 1, 1);">维护代理的运行状态（RUNNING, STOPPED, ERROR, FINISHED等）</font>
    - **<font style="color:rgb(1, 1, 1);">初始化控制：</font>**<font style="color:rgb(1, 1, 1);">创建和配置代理实例</font>
    - **<font style="color:rgb(1, 1, 1);">运行控制：</font>**<font style="color:rgb(1, 1, 1);">控制代理的执行步骤和迭代</font>
    - **<font style="color:rgb(1, 1, 1);">关闭处理：</font>**<font style="color:rgb(1, 1, 1);">优雅地关闭代理并清理资源</font>
+ **<font style="color:black;">驱动 Agent 运行</font>****<font style="color:rgb(1, 1, 1);">。</font>**<font style="color:rgb(1, 1, 1);">它通过 step() 方法推动系统迭代前进，这一方法并非无限循环，而是采用 “事件触发” 机制 —— 仅在接收到特定观察结果后才被激活，促使 Agent 针对新情况思考下一步行动，既保证了任务推进的效率，又避免了无效消耗。</font>

<font style="color:rgb(0, 0, 0);">AgentController 带来的架构化、确定性方法，并非要限制大语言模型的潜力。恰恰相反，这套方法是为这些潜力搭建一个“容器”，让其能安全地在生产环境中释放价值。它的核心作用，是把行为不确定的概率模型，封装成行为相对可控、风险可预判的软件组件。对于那些希望将AI技术真正落地到关键业务中的开发者和决策者来说，未来的核心竞争力，不仅在于能否用上最先进的模型，更在于是否掌握了驾驭这些模型的成熟方法论与稳健框架。给AI Agent套上“确定性”的缰绳，让其行为可控、风险可防，是它从“技术炫技”走向“实际创造价值”的必经之路。</font>

##### 1.3 具体功能
<font style="color:black;">AgentController的具体功能如下：</font>

1. **<font style="color:black;">代理生命周期管理</font>**

<font style="color:black;">状态管理：维护代理的运行状态（RUNNING, STOPPED, ERROR, FINISHED等） </font>

<font style="color:black;">初始化控制：创建和配置代理实例 </font>

<font style="color:black;">运行控制：控制代理的执行步骤和迭代 </font>

<font style="color:black;">关闭处理：优雅地关闭代理并清理资源</font>

2. **<font style="color:black;">事件处理与分发 </font>**

<font style="color:black;">事件订阅：订阅 EventStream 中的事件 </font>

<font style="color:black;">事件路由：将事件分发给相应的处理逻辑 </font>

<font style="color:black;">动作处理：处理代理产生的各种动作（Action） </font>

<font style="color:black;">观察处理：处理环境返回的观察结果（Observation）</font>

3. **<font style="color:black;">代理执行控制 </font>**

<font style="color:black;">步进执行：通过_step() 方法控制代理逐步执行 </font>

<font style="color:black;">迭代限制：控制代理的最大执行步数 </font>

<font style="color:black;">预算管理：管理任务的预算限制（基于成本） </font>

<font style="color:black;">卡死检测：检测并处理代理陷入循环的情况</font>

4. **<font style="color:black;">委托机制管理 </font>**

<font style="color:black;">子代理创建：支持创建委托代理处理子任务</font>

<font style="color:black;">层级管理：管理代理间的层级关系 </font>

<font style="color:black;">结果聚合：收集和处理委托代理的执行结果</font>

5. **<font style="color:black;">安全与确认机制 </font>**

<font style="color:black;">安全分析：集成安全分析器评估动作风险 </font>

<font style="color:black;">确认模式：在高风险操作前请求用户确认 </font>

<font style="color:black;">权限控制：控制代理可执行的操作类型</font>

6. **<font style="color:black;">状态跟踪与持久化 </font>**

<font style="color:black;">状态追踪：通过 StateTracker 跟踪代理状态 </font>

<font style="color:black;">历史记录：维护代理执行历史 </font>

<font style="color:black;">状态保存：持久化代理状态以便恢复</font>

7. **<font style="color:black;">错误处理与恢复 </font>**

<font style="color:black;">异常处理：捕获并处理各种运行时异常 </font>

<font style="color:black;">错误状态：将代理置于适当的错误状态 </font>

<font style="color:black;">恢复机制：提供从错误状态恢复的能力</font>

8. **<font style="color:black;">指标监控 </font>**

<font style="color:black;">成本跟踪：跟踪API调用成本 </font>

<font style="color:black;">令牌使用：监控提示和完成令牌的使用情况 </font>

<font style="color:black;">性能指标：收集执行性能数据</font>

9. **<font style="color:black;">重放与调试 </font>**

<font style="color:black;">事件重放：支持重放历史事件用于调试 </font>

<font style="color:black;">轨迹记录：记录代理执行轨迹</font>

10. **<font style="color:black;">多代理协调 </font>**

<font style="color:black;">父子代理协调：管理父子代理间的消息传递 </font>

<font style="color:black;">资源共享：在代理间共享资源和状态</font>

##### 1.4 多个实例
<font style="color:black;">从代码中可以看出：AgentController 不是单例模式。可以创建多个实例。</font>

<font style="color:black;">AgentController 类有一个标准的 init 方法，允许创建多个实例每个实例都有唯一的 id 属性（通常是 session ID）：</font>

+ <font style="color:black;">委托模式：代码中明确支持 parent-delegate 关系，其中一个 AgentController 可以创建另一个 AgentController作为委托</font>
+ <font style="color:black;">每个会话一个实例：每个用户会话或任务通常会创建一个独立的 AgentController 实例，通过 sid（session ID）参数区分不同的控制器实例</font>
+ <font style="color:black;">实例属性：每个实例都有自己的状态（state）、事件流（event_stream）、代理（agent）等独立的属性</font>

<font style="color:black;">因此，AgentController 是一个普通的类，不是单例，可以创建多个实例来管理不同的代理会话。项目中 AgentController 的数量是动态的，取决于：</font>

+ <font style="color:rgb(1, 1, 1);">同时进行的会话数量（每个会话一个主控制器）</font>
+ <font style="color:rgb(1, 1, 1);">每个会话中代理委托任务的数量（每个委托任务一个委托控制器）</font>

<font style="color:black;">系统会根据实际使用情况动态创建和销毁AgentController 。每个会话一个主控制器：</font>

+ <font style="color:rgb(1, 1, 1);">每当用户开始一个新的会话或任务时，会创建一个主 AgentController 实例委托代理控制器。</font>
+ <font style="color:rgb(1, 1, 1);">当主代理需要委托子任务给其他代理时，会为每个委托任务创建一个新的 AgentController 实例在 start_delegate 方法中创建委托控制器实例创建方式。</font>

##### <font style="color:rgb(1, 1, 1);">1.5 工作流程</font>
<font style="color:black;">AgentController 主要工作流程是初始化代理，管理状态，并驱动主循环，逐步推动代理前进。具体如下：</font>

+ <font style="color:rgb(1, 1, 1);">初始化：创建代理实例并设置初始状态</font>
+ <font style="color:rgb(1, 1, 1);">事件监听：订阅事件流并处理传入事件</font>
+ <font style="color:rgb(1, 1, 1);">决策执行：根据事件决定是否执行代理步骤</font>
+ <font style="color:rgb(1, 1, 1);">动作生成：让代理生成下一步动作</font>
+ <font style="color:rgb(1, 1, 1);">结果处理：处理动作执行后的观察结果</font>
+ <font style="color:rgb(1, 1, 1);">状态更新：更新代理状态并决定下一步行动</font>

```python
       +-----------------------+
       |  AgentController Init |
       +-----------+-----------+
                   |
       +-----------v-----------+
       |  Subscribe to Events  |
       +-----------+-----------+
                   |
       +-----------v-----------+
       |    Initialize State   |
       +-----------+-----------+
                   |
       +-----------v-----------+
       |  Add System Message   |
       +-----------+-----------+
                   |
       +-----------v-----------+ <----------+
       |    Wait for Events    |            |
       +-----------+-----------+            |
                   |                        |
       +-----------v-----------+            |
       | Handle Incoming Event |            |
       +-----------+-----------+            |
                   |                        |
         __________|__________              |
        |                     |             |
+-------v-------+     +-------v-------+     |
|  Has Active   |     | Process Event |     |
|   Delegate?   |     +-------+-------+     |
+-------+-------+             |             |
        |             ________v________     |
   +----+----+       |   Is Action or  |    |
   |   Yes   |       |   Observation?  |    |
   +----+----+       +--------+--------+    |
        |                     |             |
+-------v-------+      +------v------+      |
| Forward Event |      |    Action   |      |
|  to Delegate  |      +------+------+      |
+-------+-------+             |             |
        |             +-------v-------+     |
+-------v-------+     | Handle Action |     |
|  Is Delegate  |     |     Type      |     |
|   Finished?   |     +-------+-------+     |
+---+-------+---+             |             |
    |       |         +-------v-------+     |
 +--v--+ +--v--+      | Msg, Delegate,|     |
 | No  | | Yes |      | Finish, State |     |
 +--+--+ +--+--+      +-------+-------+     |
    |       |                 |             |
    |   +---v---+     +-------v-------+     |
    |   |  End  |     |  Update Agent |     |
    |   |Delegate|    |     State     |     |
    |   +---+---+     +-------+-------+     |
    |       |                 |             |
    |   +---v---+     ________v________     |
    |   | Resume|    |  Should Agent   |    |
    |   | Parent|    |      Step?      |----+
    |   +-------+    +--------+--------+
    |                         |
+---v-----------+     +-------v-------+
|     Add to    |     | Execute Agent |
|  EventStream  |     |     Step      |
+---------------+     +-------+-------+
                              |
                      +-------v-------+
                      | Check Limits  |
                      | & Stuck Detect|
                      +-------+-------+
                              |
                      +-------v-------+
                      |Generate Action|
                      +-------+-------+
                              |
                      ________v________
                     | Runnable Action?|
                     +---+---------+---+
                         |         |
                  +------+--+   +--v---+
                  |   Yes   |   |  No  |
                  +------+--+   +--+---+
                         |         |
                  +------v------+  |
                  |  Security   |  |
                  |  Analysis   |  |
                  +------+------+  |
                         |         |
                  +------v------+  |
                  | Set Pending |  |
                  |   Action    |  |
                  +------+------+  |
                         |         |
                  +------v---------v---+
                  | Add to EventStream |
                  +--------------------+
```

#### 重点功能
##### Agent路由
<font style="color:black;">在多智能体系统里，“路由” 本质是让任务精准流转到合适的处理单元，工程上这一步通常靠工具调用机制落地。具体来说，当系统触发某个工具调用时，会先解析其中的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateAction</font>`<font style="color:black;">指令 —— 这个指令在</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentController</font>`<font style="color:black;">里有专门的处理逻辑，一旦匹配成功，就会自动启动一个全新的委托智能体（Delegate Agent），之后所有相关的事件流都会定向转发给这个委托智能体，由它完成后续处理。</font>

<font style="color:black;">OpenHands 这套路由方案，更适合简单的单向任务流转场景，要是需要多级路由，就得靠嵌套</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentController</font>`<font style="color:black;">来实现。但从实际工程实践来看，不太建议用多智能体路由的思路解决问题。核心原因是这种方式会让系统架构变得臃肿，不仅增加开发、调试的复杂度，还会引入很多不可控因素 —— 比如智能体间的通信延迟、状态同步误差等。</font>

<font style="color:black;">其实很多时候，单智能体搭配多个工具的方案就足够应对需求，完全没必要非得用多智能体。如果遇到单智能体处理起来吃力的场景，也可以先试试</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">MicroAgent</font>`<font style="color:black;">这类提示词增强方案，通过优化指令逻辑提升单智能体的处理能力，从而避开多智能体带来的复杂设计。</font>

###### <font style="color:black;">流程</font>
<font style="color:black;">OpenHands 多智能体系统的</font>**<font style="color:black;">动作分发与委托智能体管理</font>**<font style="color:black;">是系统任务流转和多智能体协同的核心逻辑。主要功能包括：</font>

1. <font style="color:rgb(1, 1, 1);">动作类型路由：根据输入动作的类型（状态变更、消息、委托启动、任务完成 / 拒绝），分发到对应的处理方法，实现逻辑解耦。</font>
2. <font style="color:rgb(1, 1, 1);">消息处理：区分用户 / 智能体来源的消息，执行日志记录、动态召回策略（首次消息召回上下文，非首次召回知识库）、智能体状态切换。</font>
3. <font style="color:rgb(1, 1, 1);">委托智能体启动：支持子任务拆分，通过创建委托智能体处理细分任务，继承父智能体配置（迭代限制、预算、指标），同时维护独立会话标识和事件记录范围。</font>
4. <font style="color:rgb(1, 1, 1);">状态与指标管理：确保父子智能体状态同步、全局指标累积，支持任务完成 / 拒绝后的状态标记和结果保存。</font>

```python
+-----------------------------------------------------------+
|                      启动动作处理流程                     |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------+-----------------------------+
|                     接收动作（Action）                    |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                        判断动作类型                       |
+--------+-----------+------------+------------+------------+
         |           |            |            |            |
         v           v            v            v            v
+----------+ +-----------+ +------------+ +------------+ +------------+
|  Change  | |  Message  | |AgentDelegate| | AgentFinish| | AgentReject|
|  Agent   | |           | |            | |            | |            |
|  State   | |           | |            | |            | |            |
| Action处理| | Action处理| |  Action处理 | |  Action处理 | |  Action处理 |
+----+-----+ +-----+-----+ +------+-----+ +------+-----+ +------+-----+
     |             |              |              |              |
     v             v              v              v              v
+----------+ +-----------+ +------------+ +------------+ +------------+
|设置智能体| | 分发到    | |1. 创建委托 | | 保存输出   | | 保存输出   |
|状态      | |_handle_ | |   智能体   | | 标记完成   | | 标记拒绝   |
|          | | message_| |2. 初始化状态| |            | |            |
|          | | action  | |3. 启动并关联| |            | |            |
+----------+ +-----------+ +------+-----+ +------------+ +------------+
                                  |
                                  v
+---------------------------------+-------------------------+
|                      委托智能体处理子任务                 |
+---------------------------------+-------------------------+
                                  |
                                  v
+-----------------------------------------------------------+
|                     事件流定向到委托智能体                |
+-----------------------------------------------------------+
```

##### 代理生命周期管理
<font style="color:rgb(0, 0, 0);">对于Agent Controller来说，Agent 的状态管理是个很重要的工作，比如维护代理的运行状态，这就是 set_agent_state_to完成的工作。在各种函数中都有调用调用 set_agent_state_to。比如：</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_react_to_exception</font>`<font style="color:rgb(0, 0, 0);">，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_handle_action</font>`<font style="color:rgb(0, 0, 0);">，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_handle_observation</font>`<font style="color:rgb(0, 0, 0);">，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_handle_message_action</font>`<font style="color:rgb(0, 0, 0);"> 这些函数。</font>

###### 流程
<font style="color:black;">该方法是 OpenHands 智能体的</font>**<font style="color:black;">状态管理核心接口</font>**<font style="color:black;">，负责统一处理智能体状态变更的全流程，维护代理的运行状态（RUNNING, STOPPED, ERROR, FINISHED等）确保状态一致性、可追溯性和系统稳定性。主要功能包括：</font>

1. <font style="color:rgb(1, 1, 1);">状态变更校验：避免重复设置相同状态，减少无效操作。</font>
2. <font style="color:rgb(1, 1, 1);">关联逻辑触发：状态切换为停止 / 错误时执行重置（释放资源），错误恢复为运行时调整控制限制（如迭代次数上限）。</font>
3. <font style="color:rgb(1, 1, 1);">动作确认处理：用户确认 / 拒绝后，更新待处理动作的确认状态并分发到事件流，完成动作闭环。</font>
4. <font style="color:rgb(1, 1, 1);">事件分发：状态变更后生成 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentStateChangedObservation</font>`<font style="color:rgb(1, 1, 1);"> 事件，携带错误原因（错误状态时），供其他模块订阅响应。</font>
5. <font style="color:rgb(1, 1, 1);">状态持久化：任何状态变更都强制保存，防止崩溃或意外导致状态丢失。</font>

<font style="color:black;">主要特色</font>

1. <font style="color:rgb(1, 1, 1);">原子性设计：状态更新流程一气呵成，先更新状态再处理副作用，确保后续逻辑基于最新状态。</font>
2. <font style="color:rgb(1, 1, 1);">副作用闭环：状态变更关联的重置、限制调整、动作处理、事件分发等逻辑统一封装，避免分散冗余。</font>
3. <font style="color:rgb(1, 1, 1);">可追溯性：状态变更日志、事件携带的错误原因、持久化存储，形成完整的状态追溯链路。</font>
4. <font style="color:rgb(1, 1, 1);">鲁棒性保障：重复状态拦截、崩溃防护（强制保存）、属性安全访问（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">hasattr</font>`<font style="color:rgb(1, 1, 1);"> 校验），提升系统稳定性。</font>
5. <font style="color:rgb(1, 1, 1);">扩展性强：新增状态时只需在枚举中添加，核心流程无需大幅修改，适配不同业务场景。</font>

```python
+-----------------------------------------------------------+
|             调用 set_agent_state_to(new_state)            |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------+-----------------------------+
|                      输出状态变更日志                     |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                    新状态 == 当前状态？                   |
+--------------+-----------------------------+--------------+
               |                             |
               v                             v
        +------+------+               +------+------+
        |      是     |               |      否     |
        |     返回    |               |   保存旧状态 |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|        更新 self.state.agent_state 为新状态               |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                  新状态是 STOPPED / ERROR？               |
+--------------+-----------------------------+--------------+
               |                             |
               v                             v
        +------+------+               +------+------+
        |      是     |               |      否     |
        | 执行 _reset()|               |     跳过    |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|             旧状态是 ERROR 且 新状态是 RUNNING？          |
+--------------+-----------------------------+--------------+
               |                             |
               v                             v
        +------+------+               +------+------+
        |      是     |               |      否     |
        | 调整控制标志 |                |     跳过    |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|          存在待处理动作且新状态是 确认/拒绝？             |
+--------------+-----------------------------+--------------+
               |                             |
               v                             v
        +------+------+               +------+------+
        |      是     |               |      否     |
        | 更新确认状态 |                |     跳过    |
        | 并加入事件流 |                |            |
        +------+------+               +------+------+
               |                             |
               +------------+----------------+
                            |
                            v
+---------------------------+-------------------------------+
|                添加状态变更观察事件到事件流                   |
+---------------------------+-------------------------------+
                            |
                            v
+---------------------------+-------------------------------+
|                 保存智能体状态到持久化存储                    |
+---------------------------+-------------------------------+
                            |
                            v
+---------------------------+-------------------------------+
|                       状态更新流程结束                       |
+-----------------------------------------------------------+
```

##### 代理执行控制
<font style="color:rgb(0, 0, 0);">OpenHands 通过_step() 方法控制代理逐步执行，代理的最大执行步数，管理任务的预算限制（基于成本），检测并处理代理陷入循环的情况等。</font>

###### <font style="color:rgb(0, 0, 0);">Workflow</font>
<font style="color:black;">该代码是 OpenHands 智能体的核心单步执行逻辑，封装了智能体单步生命周期的完整流程，是系统任务执行的核心入口。主要功能包括：</font>

1. <font style="color:rgb(1, 1, 1);">前置条件拦截：校验智能体状态（仅 RUNNING 状态可执行）和待处理动作（无 Pending 动作时才继续），避免并行执行冲突。</font>
2. <font style="color:rgb(1, 1, 1);">核心可控性校验：同步预算与全局指标确保资源不超支，检测智能体是否陷入循环，校验迭代次数 / 预算等控制标志，防止系统失控。</font>
3. <font style="color:rgb(1, 1, 1);">动作生成与回放适配：支持回放模式（直接从回放轨迹获取动作）和正常模式（调用智能体生成动作），适配不同使用场景。</font>
4. <font style="color:rgb(1, 1, 1);">异常精细化处理：针对动作格式错误、LLM 响应异常、函数调用异常等，添加错误事件到事件流；针对上下文窗口溢出，支持历史截断或抛出统一异常，兼容不同 LLM 的错误提示格式。</font>
5. <font style="color:rgb(1, 1, 1);">高危动作安全校验：对命令执行、文件操作、交互式浏览等风险动作，通过安全分析器标记风险等级，在确认模式下触发用户确认，保障执行安全。</font>
6. <font style="color:rgb(1, 1, 1);">状态与事件管理：待确认动作自动切换智能体状态为 “等待用户确认”，非空动作同步到事件流供其他模块订阅，同时准备前端展示指标，兼顾系统协同与可视化需求。</font>

```python
+-----------------------------------------------------------+
|                  启动 _step() 单步执行流程                |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                       检查前置条件                        |
| 1. 智能体状态是否为 RUNNING?                              |
| 2. 是否存在待处理动作?                                    |
+--------------+--------------+--------------+--------------+
               |              |              |
               v              v              v
        +------+------+ +------+------+ +------+------+
        |    不满足   | |    不满足   | |   满足条件   |
        |     返回    | |     返回    | |     继续     |
        +-------------+ +--------------+ +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|            输出步骤日志（层级/本地步骤/全局迭代）         |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                        核心校验流程                       |
| 1. 同步预算与指标                                         |
| 2. 检查是否陷入循环 -> 是则抛异常                         |
| 3. 执行控制标志校验 -> 超限则抛异常                       |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                     判断是否为回放模式?                   |
+--------------+-----------------------------+--------------+
               |                             |
               v                             v
        +------+------+               +------+------+
        |      是     |               |      否     |
        |    从回放   |               | 调用智能体生成 |
        |   获取动作  |               |     动作     |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|                        动作异常处理                       |
| 1. 动作生成异常 -> 添加错误事件                           |
| 2. 上下文溢出 -> 截断/抛异常                              |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                     可执行动作安全校验                    |
| 1. 是否为高危动作类型?                                    |
| 2. 安全分析器标记风险等级                                 |
| 3. 需确认则标记待确认状态                                 |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                      非空动作后续处理                     |
| 1. 待确认 -> 切换状态为等待用户确认                       |
| 2. 准备前端指标数据                                       |
| 3. 添加动作到事件流                                       |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------+-----------------------------+
|                        输出动作日志                       |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------+-----------------------------+
|                       单步执行流程结束                    |
+-----------------------------------------------------------+
```

##### 回调
<font style="color:rgb(0, 0, 0);">AgentController注册了事件回调函数</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">on_event</font>`<font style="color:rgb(0, 0, 0);">，回调函数里设置标识符</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_pending_action</font>`<font style="color:rgb(0, 0, 0);">，同时轮询任务</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_start_step_loop</font>`<font style="color:rgb(0, 0, 0);">调用Agent的step方法，该方法用于预测下一个action。</font>

###### 核心功能
1. <font style="color:black;">事件转发机制</font><font style="color:rgb(1, 1, 1);">：当存在活跃子智能体时，自动将事件转发给子智能体处理，确保层级化智能体协作的连贯性。</font>
2. <font style="color:black;">状态判断逻辑</font><font style="color:rgb(1, 1, 1);">：通过检查子智能体状态（完成、错误、拒绝等），决定是否终止子智能体并恢复父智能体处理流程。</font>
3. <font style="color:black;">事件分类处理</font><font style="color:rgb(1, 1, 1);">：区分动作（Action）和观察结果（Observation）事件，分别调用对应处理方法，保证事件处理的针对性。</font>
4. <font style="color:black;">步骤触发控制</font><font style="color:rgb(1, 1, 1);">：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">should_step</font>`<font style="color:rgb(1, 1, 1);"> 方法判断是否触发智能体下一步操作，结合用户消息等场景做特殊日志记录，增强流程可观测性。</font>

###### <font style="color:rgb(1, 1, 1);">Workflow</font>
```python
+-----------------------------------------------------------+
|                 AgentController.on_event                  |
+-----------------------------+-----------------------------+
                              |
              ________________v________________
             /                                 \
    +-------v-------+                  +--------v-------+
    | 存在活跃子智能体? |        否        | 继续父智能体处理 |
    +-------+-------+                  +--------+-------+
            | 是                                |
            v                                   v
    +-------+-------+                  +--------+-------+
    | 子智能体未完成/ |                  |   __on_event() |
    |     未出错?    |                  +--------+-------+
    +-------+-------+                           |
            |                                   v
            v                          +--------+-------+
    +-------+-------+                  | 事件是否为隐藏 |
    | 转发事件给子  |                  |      类型?     |
    | 智能体处理    |                  +---+--------+---+
    +-------+-------+                      |        |
            |                              | 是     | 否
            v                              v        v
    +-------+-------+              +-------+---+ +--+---+
    | 子智能体已完成/ |              |  忽略事件 | | 继续 |
    |     已出错     |              +-----------+ +--+---+
    +-------+-------+                                |
            |                                        v
            v                          +-------------+-------+
    +-------+-------+                  |  添加事件到历史记录 |
    | 终止子智能体  |                  +-------------+-------+
    |     流程      |                                |
    +---------------+                                v
                                       +-------------+-------+
                                       | 事件类型是 Action/  |
                                       |    Observation?     |
                                       +---+-------------+---+
                                           |             |
                                   +-------v-------+ +---v-----------+
                                   |   处理Action  | |处理Observation|
                                   +-------+-------+ +---+-----------+
                                           |             |
                                           +------+------+
                                                  |
                                                  v
                                       +----------+----------+
                                       | 是否需要触发下一步? |
                                       +---+-------------+---+
                                           |             |
                                         是|           否|
                                   +-------v-------+ +---v-----------+
                                   |   执行下一步  | |  检查用户消息 |
                                   +---------------+ |  记录警告日志 |
                                                     +---------------+
```

##### 全链路可观测
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:black;">作用 是存储整个agent工作过程的产生的所有事件、执行状态、任务plan等信息</font>

<font style="color:black;">在任务执行的任意时刻，用户或开发者都需要清晰掌握 Agent 的运行状态：是处于思考决策阶段，还是正在执行具体命令？是等待外部资源响应，还是因参数错误陷入停滞？这种可观测性需要工作流架构对每一个环节进行日志记录、状态标记和实时反馈，构建起透明的监控体系，为问题排查和性能优化提供支撑。</font>

<font style="color:rgb(0, 0, 0);">OpenHands 在 start_delegate，_step 和 end_delegate 都会对监控做出处理。</font>

##### <font style="color:rgb(0, 0, 0);">驯服决策的“不确定性”</font>
<font style="color:rgb(0, 0, 0);">LLM 的生成特性决定了其输出天然带有随机性。Agent 在执行任务时，可能突然产生无效操作 —— 比如调用不存在的工具，或是在循环中重复相同步骤。这种非确定性如果缺乏有效管控，会直接导致任务失败。因此，系统必须构建一套智能纠错机制，能够实时检测异常行为，并通过重试、回滚或重新规划等方式修正路径，这需要对任务逻辑和模型行为有深刻的理解。</font>

###### <font style="color:rgb(0, 0, 0);">Workflow</font>
<font style="color:black;">OpenHands 智能体的</font>**<font style="color:black;">异常捕获与统一处理机制</font>**<font style="color:black;">是保障系统稳定性和容错能力的关键模块。主要功能包括：</font>

1. <font style="color:rgb(1, 1, 1);">异常包裹：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_step_with_exception_handling</font>`<font style="color:rgb(1, 1, 1);"> 方法包裹核心业务逻辑（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_step</font>`<font style="color:rgb(1, 1, 1);">），捕获所有执行过程中的异常，避免系统崩溃。</font>
2. <font style="color:rgb(1, 1, 1);">异常分类处理：在 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_react_to_exception</font>`<font style="color:rgb(1, 1, 1);"> 中，根据异常类型细分错误状态（如 LLM 认证失败、服务不可用、预算耗尽等），提供精准的错误定位依据。</font>
3. <font style="color:rgb(1, 1, 1);">状态与错误存储：捕获异常后，更新智能体状态（如 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ERROR</font>`<font style="color:rgb(1, 1, 1);">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RATE_LIMITED</font>`<font style="color:rgb(1, 1, 1);">），并存储错误详情，便于后续排查。</font>
4. <font style="color:rgb(1, 1, 1);">外部通知：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">status_callback</font>`<font style="color:rgb(1, 1, 1);"> 回调函数，将错误状态同步给外部系统，支持监控和告警。</font>
5. <font style="color:rgb(1, 1, 1);">容错优化：对未知异常进行包装，返回用户友好提示；对速率限制异常区分 “重试耗尽” 和 “可重试” 场景，提升系统灵活性。</font>

```python
+-----------------------------------------------------------+
|          启动 _step_with_exception_handling()             |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|             执行核心业务逻辑 await self._step()            |
+--------------+-----------------------------+--------------+
               |                             |
               v                             v
        +------+------+               +------+------+
        |   无异常发生 |               |  捕获到异常  |
        |   流程结束   |               |             |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|             输出错误日志（含会话ID、异常堆栈）            |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                 判断异常类型是否为已知类型?               |
+--------------+-----------------------------+--------------+
               |                             |
               v                             v
        +------+------+               +------+------+
        | 已知异常类型 |               | 未知异常类型 |
        |直接上报原异常|               |包装为RuntimeError|
        +------+------+               +------+------+
               |                             |
               +------------+----------------+
                            |
                            v
+---------------------------+-------------------------------+
|             调用 _react_to_exception(reported)            |
+---------------------------+-------------------------------+
                            |
                            v
+---------------------------+-------------------------------+
|           存储错误信息到 self.state.last_error            |
+---------------------------+-------------------------------+
                            |
                            v
+-----------------------------------------------------------+
|                     存在 status_callback?                 |
+--------------+-----------------------------+--------------+
               |                             |
               v                             v
        +------+------+               +------+------+
        | 是：细分错误 |               |  否：跳过回调 |
        | 触发回调通知 |               |             |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|            特殊处理速率限制异常（判断重试次数）           |
+--------------+-----------------------------+--------------+
               |                             |
               v                             v
        +------+------+               +------+------+
        | 重试耗尽:    |               | 仍有重试:    |
        | 设为 ERROR   |               | 设为 RATE_LIMITED|
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|              其他异常：设置智能体状态为 ERROR             |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------+-----------------------------+
|                       异常处理流程结束                    |
+-----------------------------------------------------------+
```

### Runtime
#### 工作机制
##### Environment和Sandbox
<font style="color:black;">Environment 指的是 Agent 可操作的容器，相当于给了 Agent 一台可自行操作的计算机，Agent 可以在其中端到端地完成任务，这个赛道包括 Sandbox、Browser Infra、Agent 操作系统等不同的细分领域。</font>

<font style="color:black;">其中，Sandbox 是一种安全机制，为执行中的程序提供隔离环境，即为 Agent 提供了一个可以隔离运行的虚拟机环境，开发者可以在这个环境中实现 Agent 的开发、部署、运行。</font>

##### <font style="color:black;">安全执行</font>
<font style="color:black;">代码安全执行的五大理由</font>

1. <font style="color:black;">安全性</font><font style="color:rgb(1, 1, 1);">：在执行不受信任的代码时，必须确保这些代码不会对主机系统造成损害。沙盒环境通过严格的访问控制，防止恶意代码访问或修改主机系统的资源，从而保护主机免受潜在威胁。</font>
2. <font style="color:black;">一致性</font><font style="color:rgb(1, 1, 1);">：沙盒环境确保代码在不同机器和配置下的执行结果具有一致性。这种一致性消除了“在我的机器上可以运行”的常见问题，使得代码在任何环境下都能稳定运行。</font>
3. <font style="color:black;">资源控制</font><font style="color:rgb(1, 1, 1);">：通过沙盒化，可以精确控制资源的分配和使用。这不仅防止了失控的进程对主机系统造成影响，还确保了资源的合理分配，提升了系统的整体性能。</font>
4. <font style="color:black;">隔离性</font><font style="color:rgb(1, 1, 1);">：不同的项目或用户可以在各自的隔离环境中工作，互不干扰。这种隔离性不仅保护了主机系统，还确保了不同项目之间的独立性，避免了资源竞争和潜在的冲突。</font>
5. <font style="color:black;">可复现性</font><font style="color:rgb(1, 1, 1);">：沙盒环境的一致性和可控性使得复现错误和问题变得更为容易。这在调试和问题解决过程中尤为重要，因为一致的环境可以确保问题的重现和解决。</font>

##### <font style="color:rgb(1, 1, 1);">解决方案</font>
<font style="color:black;">OpenHands 通过基于 Docker 容器的沙盒环境，为代码执行构建了一道坚固的“安全防线”。每个项目在启动时，系统会自动创建一个独立的 Docker 容器作为其专属沙盒。这个沙盒拥有隔离的文件系统、网络环境和资源配额，确保代码只能访问容器内部的文件，网络请求被限制在预设的安全域内，CPU 和内存的使用也受到严格管控。</font>

<font style="color:black;">这种隔离性带来了三重保障：</font>

+ <font style="color:black;">避免项目间干扰</font><font style="color:rgb(1, 1, 1);">：某一项目的代码错误（如无限循环导致的内存溢出）只会影响其所在的沙盒，不会波及其他项目或主机系统。</font>
+ <font style="color:black;">防范恶意代码风险</font><font style="color:rgb(1, 1, 1);">：即使 AI 生成的代码中包含潜在的危险操作（如删除系统文件），也会被沙盒环境拦截，无法对主机造成实质损害。</font>
+ <font style="color:black;">简化环境一致性管理</font><font style="color:rgb(1, 1, 1);">：沙盒的基础镜像可以预先配置好特定版本的编程语言、依赖库和工具链，确保代码在开发、测试、生产环境中的执行结果一致，避免了“在我电脑上能运行”的问题。</font>

##### <font style="color:rgb(1, 1, 1);">核心功能</font>
<font style="color:black;">Runtime的核心功能可以概括为四个主要方面：</font>

1. <font style="color:rgb(1, 1, 1);">工作环境的构建与管理：Runtime负责创建和管理代理的工作区域，无论是隔离性更强的容器环境还是便捷的本地环境，都能根据需求提供定制化的工作空间，确保代理在执行任务时不会受到外部因素的干扰。</font>
2. <font style="color:rgb(1, 1, 1);">动作的执行：代理发出的指令，如文件编辑、命令执行等，都由Runtime解析并精确执行，它充当了决策与实践之间的桥梁。</font>
3. <font style="color:rgb(1, 1, 1);">环境变量的维护：Runtime负责维护任务执行所需的环境变量，为任务执行提供必要的配置支持。</font>
4. <font style="color:rgb(1, 1, 1);">环境的生命周期管理：Runtime全程管理环境的生命周期，从初始化到断开连接，形成完整的闭环。同时，通过EventStream实时输出执行日志和观察结果，为控制器、记忆系统、MCP等组件提供关键的状态反馈，确保整个系统的协同运作。</font>

##### <font style="color:rgb(1, 1, 1);">工作机制</font>
<font style="color:black;">OpenHands 运行时系统采用基于 Docker 容器实现的客户端 - 服务器架构，其工作机制概述如下：</font>

1. <font style="color:black;">用户输入</font><font style="color:rgb(1, 1, 1);">：用户提供一个自定义的基础 Docker 镜像。</font>
2. <font style="color:black;">镜像构建</font><font style="color:rgb(1, 1, 1);">：OpenHands 以用户提供的镜像为基础，构建一个新的 Docker 镜像（即 “OH 运行时镜像”）。该新镜像包含 OpenHands 专属代码，核心为 “运行时客户端”。</font>
3. <font style="color:black;">容器启动</font><font style="color:rgb(1, 1, 1);">：当 OpenHands 启动时，会使用 OH 运行时镜像启动一个 Docker 容器。</font>
4. <font style="color:black;">动作执行服务器初始化</font><font style="color:rgb(1, 1, 1);">：动作执行服务器在容器内部初始化一个 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ActionExecutor</font>`<font style="color:rgb(1, 1, 1);">（动作执行器），配置必要组件（如 Bash Shell）并加载指定的插件。</font>
5. <font style="color:black;">通信过程</font><font style="color:rgb(1, 1, 1);">：OpenHands 后端通过 RESTful API 与动作执行服务器通信，发送动作指令并接收执行反馈数据。</font>
6. <font style="color:black;">动作执行</font><font style="color:rgb(1, 1, 1);">：运行时客户端接收来自后端的动作指令，在沙箱环境中执行这些指令，并将执行反馈数据回传。</font>
7. <font style="color:black;">反馈数据返回</font><font style="color:rgb(1, 1, 1);">：动作执行服务器将执行结果以反馈数据（Observation）的形式发送回 OpenHands 后端。</font>

```python
+-----------------------------------------------------------+
|                    用户自定义 Docker 镜像                 |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------+-----------------------------+
|                       OpenHands 后端                      |
+-------+---------------------+---------------------+-------+
        |                     |                     |
      构建                   生成                  生成
        |                     |                     |
        v                     v                     v
+-------+-------+     +-------+-------+     +-------+-------+
|  OH 运行时镜像 |     |    事件流       | <--->+      代理     |
+-------+-------+     +-------+-------+     +-------+-------+
        |                     ^
      启动                    |
        |             执行动作以获取观察结果;
        |             通过 REST API;
        v                     |
+-------+---------------------+---------------------+-------+
|                        Docker 容器                        |
|  +-----------------------------------------------------+  |
|  |                     动作执行器                      |  |
|  +-------+------------------+------------------+------+  |
|          |                  |                  |          |
|        初始化             初始化             初始化       |
|          |                  |                  |          |
|  +-------v-------+  +-------v-------+  +-------v-------+  |
|  |     浏览器    |  |   Bash Shell  |  |      插件     |  |
|  +---------------+  +---------------+  +-------+-------+  |
|                                               |          |
|                                             初始化       |
|                                               |          |
|                                        +------v-------+  |
|                                        | Jupyter服务器 |  |
|                                        +--------------+  |
+-----------------------------------------------------------+
```

#### 核心逻辑
<font style="color:black;">Runtime是在用户交互期间为用户的智能体应用程序提供动力的底层引擎。它是一个系统，接收用户定义的智能体、工具和回调，并协调它们对用户输入的执行，管理信息流、状态变化以及与外部服务（如 LLM 或存储）的交互。可以将运行时视为你的智能体应用程序的"引擎"。用户定义部件（智能体、工具），而运行时处理它们如何连接并一起运行以满足用户请求。</font>

<font style="color:black;">Runtime支持多种执行环境，包括Docker容器、本地环境等，使Agent能够安全地执行代码和命令。其派生类有：DockerRuntime、RemoteRuntime、LocalRuntime、KubernetesRuntime、CLIRuntime。</font>

<font style="color:black;">核心功能</font>

+ <font style="color:rgb(1, 1, 1);">命令执行：提供Bash shell访问能力。</font>
+ <font style="color:rgb(1, 1, 1);">浏览器交互：支持网页浏览和交互操作。</font>
+ <font style="color:rgb(1, 1, 1);">文件系统操作：文件读写，编辑等操作。</font>
+ <font style="color:rgb(1, 1, 1);">git 操作管理：仓库克隆、分支管理、变更跟踪。</font>
+ <font style="color:rgb(1, 1, 1);">环境变量管理：运行时环境变量配置。</font>
+ <font style="color:rgb(1, 1, 1);">插件系统管理：支持VSCode、Jupyter等插件集成。</font>

##### 工作流程
<font style="color:black;">Runtime作为EventStreamSubscriber.RUNTIME订阅者，处理来自事件流的Action并生成Observation。Runtime的工作流程如下：</font>

1. <font style="color:black;">初始化</font><font style="color:rgb(1, 1, 1);">：</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Runtime</font>`<font style="color:rgb(1, 1, 1);">使用配置和事件流进行初始化。</font>
    - <font style="color:rgb(1, 1, 1);">设置环境变量。</font>
    - <font style="color:rgb(1, 1, 1);">加载并初始化插件。</font>
2. <font style="color:black;">动作处理</font><font style="color:rgb(1, 1, 1);">：</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Runtime</font>`<font style="color:rgb(1, 1, 1);">通过事件流接收动作。</font>
    - <font style="color:rgb(1, 1, 1);">验证并路由到适当的执行方法。</font>
3. <font style="color:black;">动作执行</font><font style="color:rgb(1, 1, 1);">：</font>
    - <font style="color:rgb(1, 1, 1);">使用</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">run</font>`<font style="color:rgb(1, 1, 1);">方法执行bash命令</font>
    - <font style="color:rgb(1, 1, 1);">使用</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">run_ipython</font>`<font style="color:rgb(1, 1, 1);">方法执行IPython单元</font>
    - <font style="color:rgb(1, 1, 1);">使用</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">read</font>`<font style="color:rgb(1, 1, 1);">和</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">write</font>`<font style="color:rgb(1, 1, 1);">方法执行文件操作</font>
    - <font style="color:rgb(1, 1, 1);">使用</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">browse</font>`<font style="color:rgb(1, 1, 1);">和</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">browse_interactive</font>`<font style="color:rgb(1, 1, 1);">方法浏览网页</font>
    - <font style="color:rgb(1, 1, 1);">执行不同类型的动作：</font>
4. <font style="color:black;">观察生成</font><font style="color:rgb(1, 1, 1);">：</font>
    - <font style="color:rgb(1, 1, 1);">动作执行后，生成相应的观察结果。</font>
    - <font style="color:rgb(1, 1, 1);">观察结果被添加到事件流中。</font>
5. <font style="color:black;">插件集成</font><font style="color:rgb(1, 1, 1);">：</font>
    - <font style="color:rgb(1, 1, 1);">插件如Jupyter和AgentSkills被初始化并集成到运行时。</font>
6. <font style="color:black;">沙盒环境</font><font style="color:rgb(1, 1, 1);">：</font>
    - `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ActionExecutor</font>`<font style="color:rgb(1, 1, 1);">在Docker容器内设置沙盒环境。</font>
    - <font style="color:rgb(1, 1, 1);">初始化用户环境和bash shell。</font>
    - <font style="color:rgb(1, 1, 1);">从OpenHands后端接收的动作在此沙盒环境中执行。</font>
7. <font style="color:black;">浏览器交互</font><font style="color:rgb(1, 1, 1);">：</font>
    - <font style="color:rgb(1, 1, 1);">使用</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">BrowserEnv</font>`<font style="color:rgb(1, 1, 1);">类处理网络浏览动作。</font>

##### Runtime与其他组件关系
<font style="color:black;">Runtime与其他组件的主要关系如下：</font>

+ <font style="color:rgb(1, 1, 1);">运行时与</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">openhands.events</font>`<font style="color:rgb(1, 1, 1);">模块中定义的事件系统紧密交互。</font>
+ <font style="color:rgb(1, 1, 1);">依赖于</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">openhands.core.config</font>`<font style="color:rgb(1, 1, 1);">中的配置类。</font>
+ <font style="color:rgb(1, 1, 1);">日志通过</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">openhands.core.logger</font>`<font style="color:rgb(1, 1, 1);">处理。</font>

###### <font style="color:black;">EventStream</font>
<font style="color:rgb(0, 0, 0);">Runtime通过与EventStream与其他模块进行事件驱动的交互。</font>

```python

class Runtime(FileEditRuntimeMixin):
     # Runtime订阅事件流
     event_stream.subscribe(
                        EventStreamSubscriber.RUNTIME, self.on_event, self.sid
            )
     # Runtime处理传入的事件
     def on_event(self, event: Event) -> None:
        if isinstance(event, Action):
            asyncio.get_event_loop().run_until_complete(self._handle_action(event))           # Runtime返回观察结果给事件流
    self.event_stream.add_event(observation, source)
```

###### AgentController
<font style="color:black;">AgentController通过EventStream向Runtime发送操作命令，Runtime执行后将结果返回。</font>

+ <font style="color:rgb(1, 1, 1);">AgentController 发送Action  → EventStream</font>
+ <font style="color:rgb(1, 1, 1);">Runtime 接到 Action 后执行</font>
+ <font style="color:rgb(1, 1, 1);">Rutime 发送 Observation  → EventStream</font>
+ <font style="color:rgb(1, 1, 1);">AgentController  接收到 Observation  并继续执行决策流程</font>

###### Session
<font style="color:rgb(0, 0, 0);">WebSession 和 AgentSession 负责管理 Runtime 的生命周期</font>

```python
# AgentSession
runtime_cls = get_runtime_cls(runtime_name)
# 创建Runtime实例
self.runtime = runtime_cls(
                config=config,
                event_stream=self.event_stream,
                llm_registry=self.llm_registry,
                sid=self.sid,
                plugins=agent.sandbox_plugins,
                status_callback=self._status_callback,
                headless_mode=False,
                attach_to_existing=False,
                git_provider_tokens=overrided_tokens,
                env_vars=env_vars,
                user_id=self.user_id,
            )
# 连接到Runtime
await self.runtime.connect()

# 关闭Runtime
EXECUTOR.submit(self.runtime.close)
```

###### Plugin系统
<font style="color:rgb(0, 0, 0);">Runtime管理和执行各种插件功能。</font>

```python
# 初始化加载插件
        self.plugins = (
            copy.deepcopy(plugins) if plugins is not None and len(plugins) > 0 else []
        )
        # add VSCode plugin if not in headless mode
        if not headless_mode:
            self.plugins.append(VSCodeRequirement())

# 执行插件相关操作
        if any(isinstance(plugin, JupyterRequirement) for plugin in self.plugins):
            code = 'import os\n'
            for key, value in env_vars.items():
                # Note: json.dumps gives us nice escaping for free
                code += f'os.environ["{key}"] = {json.dumps(value)}\n'
            code += '\n'
            self.run_ipython(IPythonRunCellAction(code))
            ......
```

###### 文件系统和存储
<font style="color:rgb(0, 0, 0);">Runtime 提供文件操作能力。</font>

```python
    def read(self, action: FileReadAction) -> Observation:
    def write(self, action: FileWriteAction) -> Observation:
```

###### git仓库
<font style="color:rgb(0, 0, 0);">Runtime 提供git仓库操作能力。</font>

```python
    async def clone_or_init_repo(
        self,
        git_provider_tokens: PROVIDER_TOKEN_TYPE | None,
        selected_repository: str | None,
        selected_branch: str | None,
    ) -> str:
```

###### Python&MCP
<font style="color:rgb(0, 0, 0);">Runtime 提供运行python代码和call_tool_mcp操作能力。</font>

```python

def run_ipython(self, action: IPythonRunCellAction) -> Observation:

async def call_tool_mcp(self, action: MCPAction) -> Observation:
```

#####





































### FunctionCall
<font style="color:rgb(0, 0, 0);">大模型本质上是一个文本生成器，它不能直接操作系统、调用 API、访问数据库。所有这些能力都需要额外的工程实现。Agent 工具使用模式是突破大语言模型（LLM）固有局限、实现 Agent 与现实世界交互的核心架构范式，其本质是让 LLM 从单纯的文本生成器转变为具备感知、推理和行动能力的智能体，核心依托 ReAct 循环中模型对工具调用时机的自主决策能力。</font>

<font style="color:rgb(0, 0, 0);">function_calling.py 文件是 OpenHands 中 CodeActAgent 的核心组件，负责将 LLM 的函数调用响应转换为具体的 Agent Action，填补意图与执行的 “翻译鸿沟”。</font>

#### <font style="color:rgb(0, 0, 0);">工具系统设计</font>
##### 需求
<font style="color:rgb(0, 0, 0);">LLM 本身受限于静态训练数据，无法获取实时信息、执行外部操作或访问专有数据，而工具使用模式通过搭建 LLM 与外部系统的桥梁，解决了这一关键问题。该模式的核心逻辑是将外部能力封装为 “工具”，让 LLM 基于用户需求自主决策工具的调用策略，再通过框架层完成工具执行与结果反馈，最终由 LLM 整合结果形成响应或推进下一步流程。</font>

##### <font style="color:rgb(0, 0, 0);">工具调用的本质</font>
<font style="color:rgb(0, 0, 0);">工具调用的核心在于：LLM需要把用户的非结构化需求（一段自然语言文本）转换为结构化的函数调用（函数名和参数），然后与其他应用程序交互，再将结构化结果返回给模型，让模型能够基于这些结果进行下一步决策。</font>

<font style="color:rgb(0, 0, 0);">问题的本质在于，历史上其他系统（数据库、API、文件系统等）只能处理结构化信息，而LLM擅长处理非结构化信息（文本）。因此，LLM必须想办法在两种信息形式之间架起桥梁：将非结构化的用户需求转换为结构化的函数调用，这样才能与外部系统交互。</font>

<font style="color:rgb(0, 0, 0);">工具调用解决了核心问题：让LLM能够稳定地输出结构化的工具调用请求，实现了"非结构化→结构化"的转换。</font>

##### <font style="color:rgb(0, 0, 0);">设计原则</font>
<font style="color:black;">Function Call 的目标不是让模型“会调用工具”，而是让它“根据业务逻辑正确调用工具”。难点不在工具本身，而在“决策”，模型到底什么时候调用、调用哪个、调用顺序是什么、缺信息时要不要追问、多轮对话怎么推进。 这需要进行针对性训练，也需要在实际使用中做针对性调整。</font>

<font style="color:black;">因此，Agent 工具使用模式的核心设计原则围绕 </font>**<font style="color:black;">“解耦、智能决策、扩展性、实用性”</font>**<font style="color:black;"> 四大核心展开，是保障该模式能高效落地、适配复杂场景的关键准则，具体可梳理为以下几大原则：</font>

<font style="color:black;">合格的Agent Tool 应该是一个“可理解、安全且具备容错能力”的交互接口。</font>

###### 工具抽象与标准化原则
<font style="color:rgb(0, 0, 0);">工具需被抽象为</font>**<font style="color:black;">统一的接口范式</font>**<font style="color:rgb(0, 0, 0);">，无论其底层是函数、API、数据库查询还是其他 Agent，都需定义标准化的描述维度（如名称、用途、参数类型与约束、返回值格式）。这种标准化让 LLM 能以一致的逻辑理解和调用不同类型的工具，也让框架的编排层能统一处理工具的执行请求，避免因工具类型差异导致的调用逻辑混乱。</font>

<font style="color:rgb(0, 0, 0);">例如，将 “天气查询 API” 和 “数据分析 Agent” 都封装为包含 “入参 - 出参 - 功能描述” 的工具对象，让 LLM 无需区分其底层实现即可决策调用。</font>

###### <font style="color:rgb(0, 0, 0);">工具与LLM解耦原则</font>
<font style="color:rgb(0, 0, 0);">通过 工具注册表（ToolRegistry） 实现工具与 LLM 的解耦，工具的注册、更新、移除独立于 LLM 的推理逻辑。框架在启动时完成工具的实例化与注册，LLM 仅通过注册表获取工具的 “声明信息”，调用时也由调度层通过注册表查找并执行工具。这种设计让工具的迭代无需修改 LLM 的推理逻辑，同时支持动态扩展工具集，例如新增 “邮件发送工具” 时，仅需在注册表中完成注册，LLM 即可感知并使用该工具。</font>

###### <font style="color:rgb(0, 0, 0);">LLM自主决策核心原则</font>
<font style="color:rgb(0, 0, 0);">将工具组合与调用的决策权完全交予 LLM，开发者仅负责提供原子化工具，不编写固定的业务流程代码。LLM 基于用户请求的复杂程度、工具的能力边界，在运行时动态生成工具调用的顺序、参数与次数，实现 “按需组合工具”。这一原则充分发挥了 LLM 的推理能力，让 Agent 能适配未预设的复杂任务场景。</font>

<font style="color:rgb(0, 0, 0);">例如用户要求 “分析近一周的股票数据并生成可视化报告”，LLM 可自主决策先调用 “股票数据查询工具”，再调用 “数据分析工具”，最后调用 “可视化生成工具”。</font>

###### <font style="color:rgb(0, 0, 0);">结构化交互原则</font>
<font style="color:rgb(0, 0, 0);">LLM 与框架之间的工具调用交互需遵循</font>**<font style="color:black;">结构化数据格式（如 JSON）</font>**<font style="color:rgb(0, 0, 0);">，而非自然语言。LLM 生成的工具调用请求需明确包含 “工具名称、参数键值对、调用优先级” 等结构化信息，框架的编排层通过解析该结构化数据执行工具，避免因自然语言歧义导致的调用错误。这一原则是保障工具调用准确性的基础，例如 LLM 生成</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">{"tool_name": "weather_query", "params": {"city": "北京", "date": "2025-12-01"}}</font>`<font style="color:rgb(0, 0, 0);">的结构化请求，框架可直接解析并执行对应的天气查询逻辑。</font>

###### <font style="color:rgb(0, 0, 0);">结果闭环与迭代推理原则</font>
<font style="color:rgb(0, 0, 0);">工具执行的结果需完整回传给 LLM，形成 “请求 - 决策 - 调用 - 反馈 - 再决策” 的</font>**<font style="color:black;">闭环推理流程</font>**<font style="color:rgb(0, 0, 0);">。LLM 结合工具反馈的结果，可进一步判断是否需要继续调用其他工具、调整参数重新调用同一工具，或整合结果生成最终响应。这一原则让 Agent 具备 “反思式” 的推理能力。</font>

<font style="color:rgb(0, 0, 0);">例如调用 “翻译工具” 得到的结果不符合需求时，LLM 可自主决策调整翻译的目标语言参数，重新调用工具获取更准确的结果。</font>

###### <font style="color:rgb(0, 0, 0);">广义工具拓展原则</font>
<font style="color:rgb(0, 0, 0);">突破 “工具 = 函数” 的狭义认知，将工具的范畴拓展至</font>**<font style="color:black;">API、数据库、其他专业 Agent、物理设备接口</font>**<font style="color:rgb(0, 0, 0);">等所有外部能力载体。这一原则让 Agent 能作为 “智能编排者”，整合跨领域、跨类型的外部资源，构建更复杂的多 Agent 协作或跨系统交互场景。例如，主 Agent 可将 “图像识别任务” 委托给专用的 “视觉 Agent”（将其视为工具），或通过 API 工具控制智能硬件完成物理世界的操作。</font>

###### <font style="color:rgb(0, 0, 0);">分层调用或者渐进式原则</font>
<font style="color:black;">向 LLM 一次性灌输超过 100 个工具会导致 </font>**<font style="color:black;">上下文混淆 (Context Confusion)</font>**<font style="color:black;">，极易引发幻觉或参数错误。Manus 等先进架构通过</font>**<font style="color:black;">三层分层设计</font>**<font style="color:black;">缓解了这一问题。</font>

<font style="color:black;">其实，Skills 也是这一原则的体现。</font>

##### <font style="color:black;">Anthropic设计高效工具的最佳实践</font>
<font style="color:black;">Anthropic 在其博客中给出了设计高效工具的最佳实践。</font>

+ <font style="color:rgb(1, 1, 1);">选择合适的工具进行实现 (以及不实现哪些工具)</font>
+ <font style="color:rgb(1, 1, 1);">为工具划分命名空间以明确功能边界</font>
+ <font style="color:rgb(1, 1, 1);">从工具向 AI 智能体返回有意义的上下文</font>
+ <font style="color:rgb(1, 1, 1);">优化工具响应的 Token 效率</font>
+ <font style="color:rgb(1, 1, 1);">对工具描述和规格进行提示词 (prompt) 工程</font>

##### <font style="color:rgb(0, 0, 0);">Agent工具调用的生命周期</font>
<font style="color:black;">具体落地时，工具使用模式遵循标准化的实现流程：</font>

+ <font style="color:rgb(1, 1, 1);">首先需完成工具定义与注册，将外部函数、API、数据库查询甚至其他 Agent 能力等封装为工具，并把工具的用途、参数等信息注册到工具注册表，供 LLM 感知可用能力；</font>
+ <font style="color:rgb(1, 1, 1);">接着 LLM 接收用户请求后，结合工具信息判断是否需要调用工具及调用何种工具；若决定调用，LLM 生成包含工具名称与参数的结构化请求；</font>
+ <font style="color:rgb(1, 1, 1);">随后框架的编排层依据该请求执行对应工具，获取执行结果并回传给 LLM；</font>
+ <font style="color:rgb(1, 1, 1);">最后 LLM 结合工具结果，要么生成最终响应，要么进一步决策是否继续调用其他工具。</font>

<font style="color:black;">字节跳动技术团队也给出了Agent 工具调用的生命周期的几个阶段，以及设计 Tools 应该考虑的关键要素及方法：</font>

1. <font style="color:black;">类型安全与自动化：充分利用 Python 类型系统和 Pydantic，自动处理 schema 生成和数据验证，防止模型“瞎猜”。</font>
    1. <font style="color:rgb(1, 1, 1);">使用 Pydantic BaseModel：利用 Pydantic 进行复杂参数验证，自动处理 Schema 生成和数据验证。</font>
    2. <font style="color:rgb(1, 1, 1);">限制枚举值：通过 </font>_<font style="color:black;">Literal</font>_<font style="color:rgb(1, 1, 1);"> 等方式限制可选参数，减少模型出错概率。</font>
    3. <font style="color:rgb(1, 1, 1);">设置默认值：清晰的默认值非常关键，能减轻模型负担并防止响应过大。</font>
2. <font style="color:black;">LLM 友好的接口设计：LLM 无法像传统程序那样通过技术文档理解接口，它依赖于自然语言描述来决定如何使用工具。</font>
    1. <font style="color:rgb(1, 1, 1);">自然语言优先：使用自然语言描述签名、参数和错误信息，避免使用晦涩的技术术语。</font>
    2. <font style="color:rgb(1, 1, 1);">花费 50% 的时间去打磨 </font>_<font style="color:black;">Docstring</font>_<font style="color:rgb(1, 1, 1);">，善于用***Examples*** 和 </font>_<font style="color:black;">Sample Case</font>_<font style="color:rgb(1, 1, 1);"> 引导模型准确传参。</font>
    3. <font style="color:rgb(1, 1, 1);">遵守实现“单一责任”原则，不要给模型一个过于复杂的组合接口，而是拆解成参数清晰、职责明确的小型工具，让 Agent 的决策链路更加稳定</font>
3. <font style="color:black;">使用 OpenAPI 规范集成外部 API 转化为 Tools：推荐使用OpenAPIToolset 工具集，它可以利用 </font>_<font style="color:black;">OperationParser</font>_<font style="color:black;"> 自动从 OpenAPI spec 生成 function declaration、参数 schema 和请求构建逻辑，实现标准化的快速创建。</font>
4. <font style="color:black;">构建自我修复能力，而不是直接终止：工具不应在遇到错误时直接抛出异常导致流程终止，而应引导 Agent 调整策略。</font>
    1. <font style="color:rgb(1, 1, 1);">结构化错误返回包含 </font>_<font style="color:black;">error</font>_<font style="color:rgb(1, 1, 1);"> 信息和 </font>_<font style="color:black;">recovery_suggestion</font>_<font style="color:rgb(1, 1, 1);">（修复建议）。</font>
    2. <font style="color:rgb(1, 1, 1);">配合 </font>_<font style="color:black;">ReflectAndRetryToolPlugin</font>_<font style="color:rgb(1, 1, 1);"> 等插件拦截错误，提供结构化反思指导，让 Agent 从失败中学习并自动重试。</font>
5. <font style="color:black;">加入 Human - in - the - loop（安全防护机制）和关键行为确认。</font>
    1. <font style="color:rgb(1, 1, 1);">通过人工确认，将关键行为的决策权和责任交还给用户。</font>
    2. <font style="color:rgb(1, 1, 1);">通过 </font>_<font style="color:black;">require_confirmation</font>_<font style="color:rgb(1, 1, 1);"> 定义工具是否需要开启确认模式。</font>_<font style="color:black;">tool_context.tool_confirmation</font>_<font style="color:rgb(1, 1, 1);"> 在敏感操作执行前，验证用户是否已经授权了本次行为。</font>
    3. <font style="color:rgb(1, 1, 1);">当无法决策或缺少关键信息时，</font>_<font style="color:black;">ask_human</font>_<font style="color:rgb(1, 1, 1);"> 主动请求用户帮助。</font>
6. <font style="color:black;">性能优化与上下文管理：为了保证 Agent 的响应速度并防止上下文溢出，需要对结果进行精细控制。提供多个Tools 给模型调用的时候，可以通过实现异步的方案调用，将串行调用转为并行以加速执行。通过 </font>_<font style="color:black;">max_query_result_rows</font>_<font style="color:black;"> 限制返回数量，或仅返回摘要而非全文，避免 LLM Context 溢出</font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

<font style="color:rgb(0, 0, 0);"></font>

#### OpenHands 的工具设计
##### 工具调用引擎
<font style="color:black;">给予智能体一个工具很简单，但让它可靠、安全、有效地使用这个工具，才是真正的难题。工具调用引擎作为智能体连接现实世界的 “手脚”，承担着工具管理、交互执行与流程管控的核心职责，其核心功能与实现要点如下：</font>

1. <font style="color:rgb(1, 1, 1);">交互能力扩展：打通外部工具与资源（API、本地工具、第三方服务等），突破智能体纯文本输出的局限，使其具备操作实体、获取实时数据的能力；</font>
2. <font style="color:rgb(1, 1, 1);">全生命周期管理：支持工具的注册、查询、更新与卸载，允许动态扩展工具库，适配多样化任务需求；</font>
3. <font style="color:rgb(1, 1, 1);">全流程自动化：覆盖工具调用的参数校验、格式转换、结果解析与错误处理，无需人工干预即可完成端到端执行。</font>

##### 核心设计模式
<font style="color:black;">OpenHands V1 工具系统以 “动作 → 执行 → 观察” 三层抽象为核心，构建了类型安全且可扩展的基础框架。其核心逻辑为：</font>

+ **<font style="color:rgb(1, 1, 1);">动作：</font>**<font style="color:rgb(1, 1, 1);">大语言模型生成的 JSON 格式工具调用指令，经 Pydantic 模型校验后转化为标准化 Action 对象；</font>
+ **<font style="color:rgb(1, 1, 1);">执行：</font>**<font style="color:rgb(1, 1, 1);">ToolExecutor 组件接收校验后的 Action 并执行底层操作；</font>
+ **<font style="color:rgb(1, 1, 1);">观察：</font>**<font style="color:rgb(1, 1, 1);">最终执行结果（含正常输出与错误信息）通过 Observation 组件以结构化格式返回，且自动适配大语言模型的理解范式。</font>

<font style="color:black;">这一设计统一了自定义工具与 MCP（模型通信协议）工具的接入标准，为工具的定义、调用与管理提供了单一接口，大幅降低了多类型工具的整合成本。</font>

##### <font style="color:black;">鲁棒性与兼容性解决方案</font>
<font style="color:black;">针对工具接口异构、外部环境不稳定、接口变更易引发链路崩溃等核心痛点，OpenHands 设计了三层攻坚方案：</font>

1. **<font style="color:rgb(1, 1, 1);">适配层隔离：</font>**<font style="color:rgb(1, 1, 1);">通过 Tool Wrapper 工具封装层统一各类工具的输入输出格式，屏蔽原生接口的参数结构、响应方式差异，使上层系统无需关注工具底层实现；</font>
2. **<font style="color:rgb(1, 1, 1);">智能容错机制：</font>**<font style="color:rgb(1, 1, 1);">基于错误类型分类（网络超时、权限不足、参数非法等），预设重试、降级、回滚等策略，例如网络波动时自动重试，核心工具不可用时切换备用工具；</font>
3. **<font style="color:rgb(1, 1, 1);">版本化管理：</font>**<font style="color:rgb(1, 1, 1);">支持工具版本标注与适配层动态调整，当工具接口变更时，仅需修改对应 Wrapper 逻辑，无需改动核心执行流程，保障任务链路稳定性。</font>

#### 功能解析
<font style="color:rgb(0, 0, 0);">ReAct框架是一个将思考与行动（调用工具）深度绑定的框架。在这个框架的驱动下，AI在思考过程中如果意识到「我的内部知识不足以支撑下一步决策」，就会主动伸出「search_api」去链接互联网，把动态的客观事实传回大脑，再继续思考。因此Agent Framework的首要职责是设计模型的思考结构、记忆机制和与世界交互的范式。</font>

##### <font style="color:rgb(0, 0, 0);">流程</font>
<font style="color:black;">function_calling 在总体流程中如下：</font>

+ <font style="color:rgb(1, 1, 1);">工具使用（函数调用）允许 Agent 与外部系统交互并访问动态信息。</font>
+ <font style="color:rgb(1, 1, 1);">它涉及定义具有 LLM 可以理解的清晰描述和参数的工具。</font>
+ <font style="color:rgb(1, 1, 1);">LLM 决定何时使用工具并生成结构化函数调用。</font>
+ <font style="color:rgb(1, 1, 1);">Agent 框架执行实际的工具调用并将结果返回给 LLM。</font>

```python
LLM Response
    ↓
function_calling.response_to_action() （从tool生成Action）
    ↓
具体的Action对象（CmdRunAction，IPythonRunCellAction等）
    ↓
AgentController（调度Action）
    ↓
Runtime（执行Action）
    ↓
Observation （执行结果）
    ↓
Agent（依据结果做下一步决策）
```

##### 工具注册与管理
###### 如何与LLM确定tool_calls
**Prompt**

<font style="color:black;">工具不是“给模型一个黑盒 API”，而是</font>**<font style="color:black;">带有严格契约的能力组件</font>**<font style="color:black;">：</font>

+ <font style="color:rgb(1, 1, 1);">明确输入输出结构</font>
+ <font style="color:rgb(1, 1, 1);">对参数范围、权限、错误做硬约束</font>

<font style="color:black;">对于与外部世界交互的智能体而言，最重要的是</font>**<font style="color:black;">“为工具使用编写提示词”</font>**<font style="color:black;">。LLM 能否正确使用你提供的工具，几乎完全取决于你如何</font>_<font style="color:black;">描述</font>_<font style="color:black;">这个工具。一个有效的工具描述必须：</font>

1. **<font style="color:black;">使用主动动词</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">以清晰的动作开始（例如，用 get_current_weather 而不是 weather_data）。</font>
2. **<font style="color:black;">明确输入</font>**<font style="color:rgb(1, 1, 1);">：清楚地说明需要的参数及其格式（例如：city (string), date (string, YYYY-MM-DD)）。</font>
3. **<font style="color:black;">描述输出</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">告诉模型会返回什么（例如：“返回一个包含‘high’, ‘low’和‘conditions’的 JSON 对象”）。</font>
4. **<font style="color:black;">提及限制</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">如果工具只在特定区域有效，一定要说明（例如：“注意：仅适用于美国城市。”）。</font>

**<font style="color:rgb(1, 1, 1);">哪些工具</font>**

<font style="color:black;">具体到 OpenHands，首先需要明确哪些外部功能或服务可以被调用。这些工具可以是一个原生函数或方法（比如litellm.ChatCompletionToolParam参数形式），也可以是工具类的实例，或者一个智能体的实例。</font>

<font style="color:black;">工具首先需要向大模型进行自我介绍。这是通过一个符合 JSON Schema 规范的配置对象完成的。它详细定义了工具的名称（如read_file）、功能描述（用于读取文件内容），以及最重要的——参数（如 absolute_path、offset等）。这份介绍是模型理解并决定如何使用该工具的依据。</font>

<font style="color:black;">工具使用模式通常通过函数调用机制实现，使 Agent 能连接外部 API、数据库、服务，甚至执行代码。该机制让位于 Agent 核心的大语言模型（LLM）能基于用户请求或任务状态，决策何时以及如何调用特定外部函数。</font>

<font style="color:black;">如果以函数的形式存在，例如查询数据库、调用天气 API 或执行数学计算等。每个工具应包含以下信息：</font>

+ <font style="color:rgb(1, 1, 1);">工具名称（name）</font>
+ <font style="color:rgb(1, 1, 1);">描述（description）</font>
+ <font style="color:rgb(1, 1, 1);">参数定义（parameters），包括参数类型、是否必填等</font>

<font style="color:black;">LLM 会根据函数/工具名称、描述（来自文档字符串或 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">description</font>`<font style="color:black;"> 字段）和参数模式，结合对话和指令，决定调用哪个工具。</font>

###### <font style="color:black;">配置工具列表</font>
<font style="color:rgb(0, 0, 0);">其次要将定义好的工具整理成一个列表，并通过 LLM 的接口传入。LLM 会基于这些工具的信息决定在生成响应时是否调用它们。</font>

<font style="color:rgb(0, 0, 0);">CodeActAgent 的tools属性会维持工具。</font>

```python
class CodeActAgent(Agent):
    def __init__(self, config: AgentConfig, llm_registry: LLMRegistry) -> None:
        self.tools = self._get_tools()
```

<font style="color:rgb(0, 0, 0);">_get_tools 具体如下。</font>

```python
    def _get_tools(self) -> list['ChatCompletionToolParam']:
        # For these models, we use short tool descriptions ( < 1024 tokens)
        # to avoid hitting the OpenAI token limit for tool descriptions.
        SHORT_TOOL_DESCRIPTION_LLM_SUBSTRS = ['gpt-4', 'o3', 'o1', 'o4']

        use_short_tool_desc = False
        if self.llm is not None:
            use_short_tool_desc = any(
                model_substr in self.llm.config.model
                for model_substr in SHORT_TOOL_DESCRIPTION_LLM_SUBSTRS
            )

        tools = []
        if self.config.enable_cmd:
            tools.append(create_cmd_run_tool(use_short_description=use_short_tool_desc))
        if self.config.enable_think:
            tools.append(ThinkTool)
        if self.config.enable_finish:
            tools.append(FinishTool)
        if self.config.enable_condensation_request:
            tools.append(CondensationRequestTool)
        if self.config.enable_browsing:
            tools.append(BrowserTool)
        if self.config.enable_jupyter:
            tools.append(IPythonTool)
        if self.config.enable_plan_mode:
            # In plan mode, we use the task_tracker tool for task management
            tools.append(create_task_tracker_tool(use_short_tool_desc))
        if self.config.enable_llm_editor:
            tools.append(LLMBasedFileEditTool)
        elif self.config.enable_editor:
            tools.append(
                create_str_replace_editor_tool(
                    use_short_description=use_short_tool_desc,
                    runtime_type=self.config.runtime,
                )
            )
        return tools
```

<font style="color:rgb(0, 0, 0);">以 IPythonTool 为例，我们看看如何定义这些工具。</font>

```python
_IPYTHON_DESCRIPTION = """Run a cell of Python code in an IPython environment.
* The assistant should define variables and import packages before using them.
* The variable defined in the IPython environment will not be available outside the IPython environment (e.g., in terminal).
"""

IPythonTool = ChatCompletionToolParam(
    type='function',
    function=ChatCompletionToolParamFunctionChunk(
        name='execute_ipython_cell',
        description=_IPYTHON_DESCRIPTION,
        parameters={
            'type': 'object',
            'properties': {
                'code': {
                    'type': 'string',
                    'description': 'The Python code to execute. Supports magic commands like %pip.',
                },
                'security_risk': {
                    'type': 'string',
                    'description': SECURITY_RISK_DESC,
                    'enum': RISK_LEVELS,
                },
            },
            'required': ['code', 'security_risk'],
        },
    ),
)
```

###### 支持的工具类型
<font style="color:black;">在工具规划时，需要控制“颗粒度”和“数量”，具体如下：</font>

+ <font style="color:rgb(1, 1, 1);">遵循“最小必要接口”：只暴露完成任务必须的参数和功能，去掉无意义或永远是固定值的参数。</font>
+ <font style="color:rgb(1, 1, 1);">避免拆得过碎：从“用户要完成的任务”出发，把强相关步骤打包成一个任务型工具，而不是几十个原子接口。</font>
+ <font style="color:rgb(1, 1, 1);">以“任务导向”而不是“接口罗列”为中心设计工具集，让模型理解“现在要完成什么事”。</font>

<font style="color:black;">OpenHands支持的工具类型如下：</font>

+ <font style="color:rgb(1, 1, 1);">命令行工具（CmdRunTool）：执行 Bash 命令</font>
+ <font style="color:rgb(1, 1, 1);">IPython 工具（IPythonTool）：要运行的IPython代码</font>
+ <font style="color:rgb(1, 1, 1);">AgentDelegateAction：将任务委托给浏览智能体（BrowsingAgent）</font>
+ <font style="color:rgb(1, 1, 1);">AgentFinishAction：标记任务结束并返回最终思考</font>
+ <font style="color:rgb(1, 1, 1);">LLMBasedFileEditTool: LLM 基于文件编辑工具（已废弃）</font>
+ <font style="color:rgb(1, 1, 1);">字符串替换编辑工具：支持文件读取和替换操作</font>
+ <font style="color:rgb(1, 1, 1);">AgentThinkAction：记录智能体的思考过程</font>
+ <font style="color:rgb(1, 1, 1);">CondensationRequestAction：触发历史上下文精简</font>
+ <font style="color:rgb(1, 1, 1);">BrowserTool：执行交互式浏览操作</font>
+ <font style="color:rgb(1, 1, 1);">TaskTrackingAction：管理任务列表（计划、更新等）</font>
+ <font style="color:rgb(1, 1, 1);">MCPAction：调用 MCP 注册的工具</font>

<font style="color:black;">其中，几个工具的特点如下：</font>

1. `**<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">execute_bash</font>**`
+ <font style="color:rgb(1, 1, 1);">执行任何有效的Linux bash命令</font>
+ <font style="color:rgb(1, 1, 1);">通过将长时间运行的命令在后台运行并重定向输出来处理</font>
+ <font style="color:rgb(1, 1, 1);">支持通过STDIN输入和进程中断的交互式进程</font>
+ <font style="color:rgb(1, 1, 1);">处理命令超时并在后台模式下自动重试</font>
2. `**<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">execute_ipython_cell</font>**`
+ <font style="color:rgb(1, 1, 1);">在IPython环境中运行Python代码</font>
+ <font style="color:rgb(1, 1, 1);">支持如</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">%pip</font>`<font style="color:rgb(1, 1, 1);">的魔法命令</font>
+ <font style="color:rgb(1, 1, 1);">变量限定在IPython环境中</font>
+ <font style="color:rgb(1, 1, 1);">使用前需要定义变量和导入包</font>
3. `**<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">web_read</font>**`**<font style="color:rgb(1, 1, 1);"> 和 </font>**`**<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">browser</font>**`
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">web_read</font>`<font style="color:rgb(1, 1, 1);">：读取并转换网页内容为Markdown</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">browser</font>`<font style="color:rgb(1, 1, 1);">：通过Python代码与网页交互</font>
+ <font style="color:rgb(1, 1, 1);">支持常见的浏览器操作，如导航、点击、填写表单、滚动</font>
+ <font style="color:rgb(1, 1, 1);">处理文件上传和拖放操作</font>
4. `**<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">str_replace_editor</font>**`
+ <font style="color:rgb(1, 1, 1);">通过字符串替换查看、创建和编辑文件</font>
+ <font style="color:rgb(1, 1, 1);">跨命令调用的持久状态</font>
+ <font style="color:rgb(1, 1, 1);">带行号的文件查看</font>
+ <font style="color:rgb(1, 1, 1);">精确匹配的字符串替换</font>
+ <font style="color:rgb(1, 1, 1);">编辑的撤销功能</font>
5. `**<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">edit_file</font>**`**<font style="color:rgb(1, 1, 1);">（基于LLM）</font>**
+ <font style="color:rgb(1, 1, 1);">使用基于LLM的内容生成编辑文件</font>
+ <font style="color:rgb(1, 1, 1);">支持部分文件编辑，具有行范围</font>
+ <font style="color:rgb(1, 1, 1);">通过编辑特定部分处理大文件</font>
+ <font style="color:rgb(1, 1, 1);">向文件添加内容的追加模式</font>

<font style="color:rgb(0, 0, 0);">具体代码如下</font>

```python
from openhands.events.action import (
    Action,
    ActionSecurityRisk,
    AgentDelegateAction,
    AgentFinishAction,
    AgentThinkAction,
    BrowseInteractiveAction,
    CmdRunAction,
    FileEditAction,
    FileReadAction,
    IPythonRunCellAction,
    MessageAction,
    TaskTrackingAction,
)
```

<font style="color:black;">可以通过配置参数启用/禁用工具：</font>

+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">enable_browsing</font>`<font style="color:rgb(1, 1, 1);">：启用浏览器交互工具</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">enable_jupyter</font>`<font style="color:rgb(1, 1, 1);">：启用IPython代码执行</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">enable_llm_editor</font>`<font style="color:rgb(1, 1, 1);">：启用基于LLM的文件编辑（如果禁用，则回退到字符串替换编辑器）</font>

##### BrowserTool
<font style="color:rgb(0, 0, 0);">BrowserTool 的定义如下：</font>

```python
for _, action in _browser_action_space.action_set.items():
    assert action.signature in _BROWSER_TOOL_DESCRIPTION, (
        f'Browser description mismatch. Please double check if the BrowserGym updated their action space.\n\nAction: {action.signature}'
    )
    assert action.description in _BROWSER_TOOL_DESCRIPTION, (
        f'Browser description mismatch. Please double check if the BrowserGym updated their action space.\n\nAction: {action.description}'
    )

BrowserTool = ChatCompletionToolParam(
    type='function',
    function=ChatCompletionToolParamFunctionChunk(
        name=BROWSER_TOOL_NAME,
        description=_BROWSER_DESCRIPTION,
        parameters={
            'type': 'object',
            'properties': {
                'code': {
                    'type': 'string',
                    'description': (
                        'The Python code that interacts with the browser.\n'
                        + _BROWSER_TOOL_DESCRIPTION
                    ),
                },
                'security_risk': {
                    'type': 'string',
                    'description': SECURITY_RISK_DESC,
                    'enum': RISK_LEVELS,
                },
            },
            'required': ['code', 'security_risk'],
        },
    ),
)
```

##### Python解释器集成
<font style="color:black;">CodeAct 集成了 Python 解释器，使其能够：</font>

+ <font style="color:rgb(1, 1, 1);">动态运行脚本并根据执行结果进行调整。这就像是智能体有了“大脑”，可以根据实际情况灵活应变。</font>
+ <font style="color:rgb(1, 1, 1);">利用现有的 Python 库，而不是重新发明特定任务的工具。Python 社区已经积累了大量的工具库，CodeAct 可以直接使用这些“现成的零件”，大大提高了效率。</font>
+ <font style="color:rgb(1, 1, 1);">在单个执行周期内处理使用控制流结构（循环、条件语句）的复杂逻辑。这意味着智能体可以处理更复杂的任务，就像我们写程序一样，可以使用循环和判断语句来控制程序的流程。</font>

<font style="color:black;">例如，如果给 LLM 的任务是分析数据集，CodeAct 允许它生成和执行 Python 代码来进行数据清洗、可视化和统计分析 —— 所有这些都在一个无缝的工作流程中完成。</font>

##### 解析工具调用
<font style="color:rgb(0, 0, 0);">CodeActAgent.step() 中会调用response_to_actions将LLM响应（tool）转换为具体操作列表。</font>

###### <font style="color:rgb(0, 0, 0);">在CodeActAgent的使用</font>
<font style="color:black;">step() 作为 CodeAct 智能体的核心执行入口，负责单步动作生成，主要功能包括：</font>

+ <font style="color:rgb(1, 1, 1);">待办动作优先执行：维护动作队列，确保动作顺序执行；</font>
+ <font style="color:rgb(1, 1, 1);">退出条件检测：响应用户 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">/exit</font>`<font style="color:rgb(1, 1, 1);"> 指令，终止任务；</font>
+ <font style="color:rgb(1, 1, 1);">上下文压缩：通过压缩器筛选冗余历史，优化 LLM 输入效率；</font>
+ <font style="color:rgb(1, 1, 1);">LLM 调用适配：组装对话消息、工具配置、元数据，生成合规的 LLM 请求；</font>
+ <font style="color:rgb(1, 1, 1);">响应转动作：将 LLM 输出转换为系统可执行动作，存入队列并返回队首动作。</font>

<font style="color:black;">在 CodeActAgent.step() 方法中，self.llm.completion() 方法会调用底层的 LLM API（如 OpenAI、Anthropic 等）。</font>

```python
response = self.llm.completion(**params)
```

<font style="color:black;">这些 API 的响应会被 LiteLLM 库封装成 ModelResponse 对象，其中包含 choices 属性。choices 属性是一个列表，包含了模型生成的所有候选响应（通常只有一个）。choices 是在 LLM 生成响应的过程中由 LiteLLM 库自动设置的，而不是在 OpenHands 代码中手动设置的。</font>

<font style="color:black;">当 LLM 被触发时，如果启用了工具调用，它会在输出中包含 tool_calls 字段。该字段是一个列表，每个元素描述了一个具体的工具调用请求，包括：</font>

+ <font style="color:rgb(1, 1, 1);">调用的工具名称</font>
+ <font style="color:rgb(1, 1, 1);">传递给工具的参数</font>
+ <font style="color:rgb(1, 1, 1);">其他元数据</font>

<font style="color:black;">OpenHands 会根据 tool_calls 中的信息，实际执行对应的工具函数，并将执行结果返回给 LLM。LLM 可以利用这些结果继续生成更准确的回复。</font>

<font style="color:rgb(0, 0, 0);">流程图如下：</font>

```python
+-----------------------------------------------------------+
|                调用 CodeActAgent.step(state)               |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                   待执行动作队列是否非空？                  |
+--------------+-----------------------------+--------------+
               |                             |
        +------+------+               +------+------+
        |      是     |               |      否     |
        | 返回队首动作 |               |     继续    |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|                最新用户消息是否为 "/exit"？                 |
+--------------+-----------------------------+--------------+
               |                             |
        +------+------+               +------+------+
        |      是     |               |      否     |
        | 返回 Finish  |               |     继续    |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|                  调用压缩器处理上下文历史                  |
+--------------+-----------------------------+--------------+
               |                             |
      +--------v--------+           +--------v--------+
      | 为Condensation型|           |   若为View型    |
      |   返回压缩动作  |           |   返回压缩视图  |
      |   直接返回动作  |           |   提取压缩后事件|
      +-----------------+           +--------+--------+
                                             |
                                             v
+--------------------------------------------+--------------+
|           构建 LLM 输入消息 (初始消息 + 压缩历史)          |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|              调用 check_tools 适配 LLM 工具配置            |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                      调用 LLM 生成响应                    |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|            响应转动作列表 (response_to_actions)           |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                  动作列表添加到待执行队列                  |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                        返回队首动作                       |
+-----------------------------------------------------------+
```

```python
    def step(self, state: State) -> 'Action':
        """使用CodeAct Agent执行一步操作。

        包括收集先前步骤的信息，并提示模型生成要执行的命令。

        参数:
        - state (State): 用于获取更新的信息

        返回:
        - CmdRunAction(command) - 要运行的bash命令
        - IPythonRunCellAction(code) - 要运行的IPython代码
        - AgentDelegateAction(agent, inputs) - 用于（子）任务的委托操作
        - MessageAction(content) - 要运行的消息操作（例如，请求澄清）
        - AgentFinishAction() - 结束交互
        - CondensationAction(...) - 通过遗忘指定事件并可选地提供摘要来压缩对话历史
        - FileReadAction(path, ...) - 从指定路径读取文件内容
        - FileEditAction(path, ...) - 使用基于LLM（已弃用）或基于ACI的编辑方式编辑文件
        - AgentThinkAction(thought) - 记录代理的思考/推理过程
        - CondensationRequestAction() - 请求压缩对话历史
        - BrowseInteractiveAction(browser_actions) - 使用指定操作与浏览器交互
        - MCPAction(name, arguments) - 与MCP服务器工具交互
        """
        # 处理待处理操作（如果有）
        if self.pending_actions:
            # 返回并移除队列中的第一个待处理操作
            return self.pending_actions.popleft()

        # 如果任务已完成，退出
        # 获取最新的用户消息
        latest_user_message = state.get_last_user_message()
        # 若用户输入"/exit"，则返回结束操作
        if latest_user_message and latest_user_message.content.strip() == '/exit':
            return AgentFinishAction()

        # 压缩状态中的事件。如果获得视图，将其传递给对话管理器处理；
        # 如果获得压缩事件，则返回该事件而非操作。控制器将立即要求代理使用新视图再次执行步骤
        condensed_history: list[Event] = []
        # 匹配压缩器返回的结果类型
        match self.condenser.condensed_history(state):
            # 若为View类型，提取事件列表作为压缩历史
            case View(events=events):
                condensed_history = events
            # 若为Condensation类型，返回其包含的压缩操作
            case Condensation(action=condensation_action):
                return condensation_action

        # 获取初始用户消息（从状态历史中）
        initial_user_message = self._get_initial_user_message(state.history)
        # 构建用于LLM的消息列表（基于压缩历史和初始用户消息）
        messages = self._get_messages(condensed_history, initial_user_message)
        # 构建LLM调用参数
        params: dict = {
            'messages': messages,  # 消息列表
        }
        # 检查并添加可用工具（根据LLM配置过滤）
        params['tools'] = check_tools(self.tools, self.llm.config)
        # 添加额外元数据（从状态中提取，适配LLM格式）
        params['extra_body'] = {
            'metadata': state.to_llm_metadata(
                model_name=self.llm.config.model, agent_name=self.name
            )
        }
        # 调用LLM获取响应
        response = self.llm.completion(** params)
        # 将LLM响应转换为具体操作列表
        actions = self.response_to_actions(response)
        # 将所有操作添加到待处理队列
        for action in actions:
            self.pending_actions.append(action)
        # 返回并移除队列中的第一个操作
        return self.pending_actions.popleft()

```

###### 构造tools相关信息
<font style="color:black;">check_tools 作为工具配置的兼容性适配层，主要功能包括：</font>

+ <font style="color:rgb(1, 1, 1);">模型识别：检测 LLM 是否为 Gemini 系列；</font>
+ <font style="color:rgb(1, 1, 1);">字段清理：移除 Gemini 不支持的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">default</font>`<font style="color:rgb(1, 1, 1);"> 字段和非兼容格式（仅保留 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">enum</font>`<font style="color:rgb(1, 1, 1);"> 和 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">date-time</font>`<font style="color:rgb(1, 1, 1);">）；</font>
+ <font style="color:rgb(1, 1, 1);">配置保护：深拷贝原始工具列表，避免修改原始配置，保障复用性。</font>

###### <font style="color:rgb(1, 1, 1);">解析工具调用LLM相应解析与转换</font>
<font style="color:black;">在 response_to_actions 函数中会解析工具调用。</font>

`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">response_to_actions</font>`<font style="color:black;"> 是 OpenHands 系统中</font>**<font style="color:black;">LLM 响应与系统动作的核心转换桥梁</font>**<font style="color:black;">，负责将 LLM 输出的自然语言响应（含工具调用指令）转换为系统可直接执行的标准化动作列表。主要功能包括：</font>

1. **<font style="color:rgb(1, 1, 1);">响应解析：</font>**<font style="color:rgb(1, 1, 1);">提取 LLM 响应中的文本思考内容和工具调用信息，兼容字符串、文本片段列表等多种内容格式。</font>
2. **<font style="color:rgb(1, 1, 1);">工具映射：</font>**<font style="color:rgb(1, 1, 1);">根据工具名称，将 LLM 调用的工具映射为对应系统动作（如命令行执行、文件操作、智能体委托等 11 类动作）。</font>
3. **<font style="color:rgb(1, 1, 1);">参数校验与标准化：</font>**<font style="color:rgb(1, 1, 1);">严格校验每个动作的必填参数，处理可选参数格式转换（如布尔值、超时时间），过滤无效参数，确保动作合法性。</font>
4. **<font style="color:rgb(1, 1, 1);">元数据补充：</font>**<font style="color:rgb(1, 1, 1);">为动作添加工具调用元数据（调用 ID、函数名等）和响应 ID，便于追踪和关联令牌使用数据。</font>
5. **<font style="color:rgb(1, 1, 1);">异常处理：</font>**<font style="color:rgb(1, 1, 1);">针对参数解析失败、必填参数缺失、工具未注册等场景，抛出明确的校验异常，保障流程稳健性。</font>
6. **<font style="color:rgb(1, 1, 1);">无工具调用适配：</font>**<font style="color:rgb(1, 1, 1);">当响应仅含文本内容时，自动创建消息动作，支持用户交互响应。</font>

<font style="color:black;">这里的 response.choices 是从 ModelResponse 对象中获取的，而 ModelResponse 是 LiteLLM 库中的一个类。</font>

```python
+-----------------------------------------------------------+
|            调用 response_to_actions(response)             |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|          初始化空动作列表，提取响应中的助手消息           |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                   消息是否包含工具调用？                  |
+--------------+-----------------------------+--------------+
               |                             |
        +------+------+               +------+------+
        |      否     |               |      是     |
        | 创建消息动作 |               | 提取思考内容 |
        | (文本+等待响应)|               |             |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|                      遍历每个工具调用                     |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|            解析工具调用参数（JSON 字符串转字典）          |
+--------------+-----------------------------+--------------+
               |                             |
        +------+------+               +------+------+
        |   解析失败   |               |   解析成功   |
        |   抛校验异常 |               |     继续     |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|                 根据工具名称匹配对应动作类型              |
|   /||||||||||||||||||||| \                                |
|  命令行工具 | IPython工具 | 委托动作 | 完成动作 | ... (其他) |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|               校验动作必须参数，处理可选参数              |
+--------------+-----------------------------+--------------+
               |                             |
        +------+------+               +------+------+
        |   参数无效   |               |   参数有效   |
        |   抛校验异常 |               |     继续     |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|                为第一个动作添加思考内容                   |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|            添加工具调用元数据（ID、函数名等）             |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                   将动作添加到结果列表                    |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                   所有工具调用处理完毕？                  |
+--------------+-----------------------------+--------------+
               |                             |
        +------+------+               +------+------+
        |      否     |               |      是     |
        |   继续遍历  |               | 为所有动作   |
        |             |               | 添加响应 ID  |
        +-------------+               +------+------+
                                             |
                                             v
+--------------------------------------------+--------------+
|                   返回标准动作列表                        |
+-----------------------------------------------------------+
```

<font style="color:rgb(0, 0, 0);">response_to_actions 全部代码如下：</font>

```python
def response_to_actions(
    response: ModelResponse, mcp_tool_names: Optional[List[str]] = None
) -> List[Action]:
    """将 LLM 模型响应转换为 OpenHands 系统可执行的动作列表。

    核心逻辑：解析模型响应中的工具调用或文本消息，根据工具名称映射为对应的系统动作，
    校验参数合法性，补充元数据，最终返回标准化的动作列表。

    参数：
        response: LLM 输出的原始响应对象（包含工具调用或文本内容）
        mcp_tool_names: MCP 注册的工具名称列表（可选），用于识别 MCP 工具调用

    返回：
        标准化的系统动作列表，可直接被智能体控制器执行
    """
    actions: List[Action] = []
    # 断言响应仅包含一个选项（当前系统仅支持单选项响应）
    assert len(response.choices) == 1, 'Only one choice is supported for now'
    choice = response.choices[0]
    assistant_msg = choice.message

    # 处理包含工具调用的响应
    if hasattr(assistant_msg, 'tool_calls') and assistant_msg.tool_calls:
        # 提取思考内容：支持字符串或文本片段列表两种格式
        thought = ''
        if isinstance(assistant_msg.content, str):
            thought = assistant_msg.content
        elif isinstance(assistant_msg.content, list):
            for msg in assistant_msg.content:
                if msg['type'] == 'text':
                    thought += msg['text']

        # 遍历每个工具调用，转换为对应系统动作
        for i, tool_call in enumerate(assistant_msg.tool_calls):
            action: Action
            logger.debug(f'Tool call in function_calling.py: {tool_call}')

            # 解析工具调用参数（JSON 字符串转字典）
            try:
                arguments = json.loads(tool_call.function.arguments)
            except json.decoder.JSONDecodeError as e:
                # 参数解析失败，抛出校验异常
                raise FunctionCallValidationError(
                    f'Failed to parse tool call arguments: {tool_call.function.arguments}'
                ) from e

            # ================================================
            # 1. 命令行工具（CmdRunTool）：执行 Bash 命令
            # ================================================
            if tool_call.function.name == create_cmd_run_tool()['function']['name']:
                # 校验必填参数 "command"
                if 'command' not in arguments:
                    raise FunctionCallValidationError(
                        f'Missing required argument "command" in tool call {tool_call.function.name}'
                    )
                # 转换 "is_input" 参数为布尔值（默认 false）
                is_input = arguments.get('is_input', 'false') == 'true'
                # 创建命令行执行动作
                action = CmdRunAction(command=arguments['command'], is_input=is_input)

                # 处理可选参数 "timeout"（设置硬超时时间）
                if 'timeout' in arguments:
                    try:
                        action.set_hard_timeout(float(arguments['timeout']))
                    except ValueError as e:
                        raise FunctionCallValidationError(
                            f"Invalid float passed to 'timeout' argument: {arguments['timeout']}"
                        ) from e
                # 为动作设置安全风险等级
                set_security_risk(action, arguments)

            # ================================================
            # 2. IPython 工具：执行 Jupyter 代码
            # ================================================
            elif tool_call.function.name == IPythonTool['function']['name']:
                # 校验必填参数 "code"
                if 'code' not in arguments:
                    raise FunctionCallValidationError(
                        f'Missing required argument "code" in tool call {tool_call.function.name}'
                    )
                # 创建 IPython 代码执行动作
                action = IPythonRunCellAction(code=arguments['code'])
                # 设置安全风险等级
                set_security_risk(action, arguments)

            # ================================================
            # 3. AgentDelegateAction：将任务委托给浏览智能体（BrowsingAgent）
            # ================================================
            elif tool_call.function.name == 'delegate_to_browsing_agent':
                action = AgentDelegateAction(
                    agent='BrowsingAgent',
                    inputs=arguments,
                )

            # ================================================
            # 4. AgentFinishAction：标记任务结束并返回最终思考
            # ================================================
            elif tool_call.function.name == FinishTool['function']['name']:
                action = AgentFinishAction(
                    final_thought=arguments.get('message', ''),
                )

            # ==================================================
            # 5. LLMBasedFileEditTool: LLM 基于文件编辑工具（已废弃）
            # ================================================
            elif tool_call.function.name == LLMBasedFileEditTool['function']['name']:
                # 校验必填参数 "path" 和 "content"
                if 'path' not in arguments:
                    raise FunctionCallValidationError(
                        f'Missing required argument "path" in tool call {tool_call.function.name}'
                    )
                if 'content' not in arguments:
                    raise FunctionCallValidationError(
                        f'Missing required argument "content" in tool call {tool_call.function.name}'
                    )
                # 创建文件编辑动作（直接写入内容模式）
                action = FileEditAction(
                    path=arguments['path'],
                    content=arguments['content'],
                    start=arguments.get('start', 1),  # 默认起始行 1
                    end=arguments.get('end', -1),    # 默认结束行 -1（全文）
                    impl_source=arguments.get(
                        'impl_source', FileEditSource.LLM_BASED_EDIT
                    ),
                )

            # ================================================
            # 6. 字符串替换编辑工具：支持文件读取和替换操作
            # ================================================
            elif (
                tool_call.function.name
                == create_str_replace_editor_tool()['function']['name']
            ):
                # 校验必填参数 "command" 和 "path"
                if 'command' not in arguments:
                    raise FunctionCallValidationError(
                        f'Missing required argument "command" in tool call {tool_call.function.name}'
                    )
                if 'path' not in arguments:
                    raise FunctionCallValidationError(
                        f'Missing required argument "path" in tool call {tool_call.function.name}'
                    )
                path = arguments['path']
                command = arguments['command']
                # 提取除 "command" 和 "path" 外的其他参数
                other_kwargs = {
                    k: v for k, v in arguments.items() if k not in ['command', 'path']
                }

                # 命令为 "view"：创建文件读取动作
                if command == 'view':
                    action = FileReadAction(
                        path=path,
                        impl_source=FileReadSource.OH_ACI,
                        view_range=other_kwargs.get('view_range', None),  # 可选读取范围
                    )
                # 其他命令：创建文件编辑动作（替换模式）
                else:
                    # 移除不需要的 "view_range" 参数
                    if 'view_range' in other_kwargs:
                        other_kwargs.pop('view_range')

                    # 过滤无效参数（仅保留工具定义中允许的参数）
                    valid_kwargs_for_editor = {}
                    str_replace_editor_tool = create_str_replace_editor_tool()
                    valid_params = set(
                        str_replace_editor_tool['function']['parameters']['properties'].keys()
                    )

                    for key, value in other_kwargs.items():
                        if key in valid_params:
                            # "security_risk" 是合法参数，但不传入编辑动作
                            if key != 'security_risk':
                                valid_kwargs_for_editor[key] = value
                        else:
                            raise FunctionCallValidationError(
                                f'Unexpected argument {key} in tool call {tool_call.function.name}. Allowed arguments are: {valid_params}'
                            )

                    # 创建文件编辑动作（替换模式）
                    action = FileEditAction(
                        path=path,
                        command=command,
                        impl_source=FileEditSource.OH_ACI,
                        **valid_kwargs_for_editor,
                    )

                # 为动作设置安全风险等级
                set_security_risk(action, arguments)

            # ================================================
            # 7. AgentThinkAction：记录智能体的思考过程
            # ================================================
            elif tool_call.function.name == ThinkTool['function']['name']:
                action = AgentThinkAction(thought=arguments.get('thought', ''))

            # ================================================
            # 8. CondensationRequestAction：触发历史上下文精简
            # ================================================
            elif tool_call.function.name == CondensationRequestTool['function']['name']:
                action = CondensationRequestAction()

            # ================================================
            # 9. BrowserTool：执行交互式浏览操作
            # ================================================
            elif tool_call.function.name == BrowserTool['function']['name']:
                # 校验必填参数 "code"
                if 'code' not in arguments:
                    raise FunctionCallValidationError(
                        f'Missing required argument "code" in tool call {tool_call.function.name}'
                    )
                action = BrowseInteractiveAction(browser_actions=arguments['code'])
                set_security_risk(action, arguments)

            # ================================================
            # 10. TaskTrackingAction：管理任务列表（计划、更新等）
            # ================================================
            elif tool_call.function.name == TASK_TRACKER_TOOL_NAME:
                # 校验必填参数 "command"
                if 'command' not in arguments:
                    raise FunctionCallValidationError(
                        f'Missing required argument "command" in tool call {tool_call.function.name}'
                    )
                # "plan" 命令需额外校验 "task_list"
                if arguments['command'] == 'plan' and 'task_list' not in arguments:
                    raise FunctionCallValidationError(
                        f'Missing required argument "task_list" for "plan" command in tool call {tool_call.function.name}'
                    )

                raw_task_list = arguments.get('task_list', [])
                # 校验 "task_list" 格式为列表
                if not isinstance(raw_task_list, list):
                    raise FunctionCallValidationError(
                        f'Invalid format for "task_list". Expected a list but got {type(raw_task_list)}.'
                    )

                # 标准化任务列表：确保每个任务为字典且包含必要字段
                normalized_task_list = []
                for i, task in enumerate(raw_task_list):
                    if isinstance(task, dict):
                        normalized_task = {
                            'id': task.get('id', f'task-{i + 1}'),  # 自动生成ID（无则补全）
                            'title': task.get('title', 'Untitled task'),  # 默认标题
                            'status': task.get('status', 'todo'),  # 默认状态为待办
                            'notes': task.get('notes', ''),  # 默认备注为空
                        }
                    else:
                        # 格式非法，抛出异常
                        logger.warning(
                            f'Unexpected task format in task_list: {type(task)} - {task}'
                        )
                        raise FunctionCallValidationError(
                            f'Unexpected task format in task_list: {type(task)}. Each task shoud be a dictionary.'
                        )
                    normalized_task_list.append(normalized_task)

                # 创建任务跟踪动作
                action = TaskTrackingAction(
                    command=arguments['command'],
                    task_list=normalized_task_list,
                )

            # ================================================
            # 11. MCPAction：调用 MCP 注册的工具
            # ================================================
            elif mcp_tool_names and tool_call.function.name in mcp_tool_names:
                action = MCPAction(
                    name=tool_call.function.name,
                    arguments=arguments,
                )

            # ================================================
            # 未知工具：抛出未注册异常
            # ================================================
            else:
                raise FunctionCallNotExistsError(
                    f'Tool {tool_call.function.name} is not registered. (arguments: {arguments}). Please check the tool name and retry with an existing tool.'
                )

            # 仅为第一个动作添加思考内容（避免重复）
            if i == 0:
                action = combine_thought(action, thought)
            # 为动作添加工具调用元数据（用于追踪和日志）
            action.tool_call_metadata = ToolCallMetadata(
                tool_call_id=tool_call.id,
                function_name=tool_call.function.name,
                model_response=response,
                total_calls_in_response=len(assistant_msg.tool_calls),
            )
            # 将动作添加到结果列表
            actions.append(action)

    # 无工具调用：创建消息动作（传递文本内容，等待用户响应）
    else:
        actions.append(
            MessageAction(
                content=str(assistant_msg.content) if assistant_msg.content else '',
                wait_for_response=True,
            )
        )

    # 为所有动作添加响应 ID（用于关联令牌使用数据）
    for action in actions:
        action.response_id = response.id

    # 断言至少返回一个动作（确保流程有效性）
    assert len(actions) >= 1
    return actions
```

[https://www.zhihu.com/question/1959742114519844109/answer/1983526566437880277](https://www.zhihu.com/question/1959742114519844109/answer/1983526566437880277)

### Memory
<font style="color:black;">大模型正在从生成工具演化为具有长期交互能力的智能体，这对“记忆能力”提出了更高的要求，因为大模型的 “记忆能力”，决定了它能走多远，从单轮问答到多轮协作，从通用助手到垂直 Agent，核心都是 “能否记住关键信息、锚定核心目标”——只有记忆突破，AI才能“持续陪伴”，这是增加用户黏性的必然。</font>

<font style="color:black;">而LLM有限的上下文窗口决定了我们不可能将所有历史信息塞入提示。因此，设计一个高效的 「记忆检索」机制至关重要。这不仅仅是技术选型（如使用向量数据库），更是策略设计。如何将对话历史、过往的行动轨迹、成功的经验与失败的教训进行压缩、提炼并结构化存储。</font>

#### 大模型Agent记忆系统
##### 核心定位与需求背景
<font style="color:black;">在以自然语言为接口、大模型为核心的 Software 3.0 时代，AI Agent 作为上下文驱动的生成式应用，需突破传统上下文窗口的固有局限。传统依赖上下文窗口维持对话状态与任务记忆的方式，存在长度受限、组织无序、知识静态、成本高昂四大痛点 —— 既无法承载超长历史信息，也难以高效检索与动态更新知识，更会因长文本处理消耗大量计算资源。</font>

<font style="color:black;">从系统架构视角看，Agentic System 可类比为新型操作系统：LLM 扮演 CPU 角色，上下文窗口则如同容量有限的 RAM，而上下文工程就是核心的 “内存管理器”—— 其核心职责并非简单填充数据，而是通过智能调度算法，动态决定上下文数据的加载与换出，确保系统高效运行与结果精准性。</font>

<font style="color:black;">构建持久化、结构化、可检索的 Agent 记忆系统，成为解决上述问题、支撑复杂任务执行的关键，它记录 Agent 的交互历程与知识积累，是连接短期交互与长期智能的核心纽带。</font>

##### <font style="color:black;">主要功能</font>
<font style="color:black;">记忆系统作为 Agent 的 “数据飞轮”，是实现真正智能的关键，其核心功能可类比人类认知机制，涵盖多维度能力：</font>

1. **<font style="color:rgb(1, 1, 1);">全类型数据存储与管理：</font>**<font style="color:rgb(1, 1, 1);">记录 Agent 运行过程中的交互信息、任务数据、工具结果等，为决策提供全面支撑，保障任务执行的连贯性；</font>
2. **<font style="color:rgb(1, 1, 1);">分层记忆架构：</font>**<font style="color:rgb(1, 1, 1);">构建短期记忆（当前任务即时上下文，如用户最新指令、工具返回结果）、工作记忆（当前任务执行步骤、待处理子任务）、长期记忆（历史经验、用户偏好、领域知识库）的三级架构，适配不同场景需求；</font>
3. **<font style="color:rgb(1, 1, 1);">高效检索与更新：</font>**<font style="color:rgb(1, 1, 1);">支持按语义相似度、时间戳、任务相关性等多维度快速召回信息，结合增量更新机制动态优化记忆内容；</font>
4. **<font style="color:rgb(1, 1, 1);">核心能力支撑：</font>**<font style="color:rgb(1, 1, 1);">实现多轮对话状态维持、历史经验积累与复用、复杂推理链路延续，以及基于用户偏好的个性化服务。</font>

##### 核心挑战
<font style="color:black;">Agent 系统输出不及预期的根源，在基础模型能力达标的前提下，多归因于上下文机制失效 —— 要么缺失关键信息，要么因数据过量导致退化，进而引发幻觉。而记忆系统的构建面临三大核心难点：</font>

1. **<font style="color:rgb(1, 1, 1);">记忆膨胀与冗余：</font>**<font style="color:rgb(1, 1, 1);">长期积累的记忆数据易出现冗余、冲突内容，直接降低检索效率与决策准确性；</font>
2. **<font style="color:rgb(1, 1, 1);">检索与召回偏差：</font>**<font style="color:rgb(1, 1, 1);">语义匹配不精准或任务相关性判断失误，可能导致关键信息遗漏，引发任务理解断层；</font>
3. **<font style="color:rgb(1, 1, 1);">记忆更新与丢失：</font>**<font style="color:rgb(1, 1, 1);">更新策略不合理会导致过期数据占据资源，或关键信息因优先级设置不当被误删，影响任务连贯性。</font>

#####
<font style="color:black;">记忆不是静态的数据库，它是一个活的系统。研究者将其生命周期拆解为三个核心过程：</font>**<font style="color:black;">形成、演化、检索</font>**<font style="color:black;">。</font>

+ **<font style="color:rgb(1, 1, 1);">记忆形成（Formation）：</font>**
    - **<font style="color:rgb(1, 1, 1);">混合存储架构：</font>**<font style="color:rgb(1, 1, 1);">短期记忆基于 Redis 等内存缓存实现低延迟访问；长期记忆结合 Milvus、Chroma 等向量数据库（支持语义检索）与关系型数据库（存储结构化数据），兼顾检索效率与数据规范性；</font>
    - **<font style="color:rgb(1, 1, 1);">记忆筛选：</font>**<font style="color:rgb(1, 1, 1);">通过语义摘要、知识蒸馏等方法来从大量记忆中筛选出最重要的片段，通过记忆巩固（Consolidation）存入长期记忆。</font>
    - **<font style="color:rgb(1, 1, 1);">记忆增强机制：</font>**<font style="color:rgb(1, 1, 1);">集成 RAG 技术，将内部记忆与外部知识库结合，弥补记忆局限，提升决策准确性与知识覆盖面。</font>
+ **<font style="color:rgb(1, 1, 1);">记忆演化（Evolution）：</font>**<font style="color:rgb(1, 1, 1);">记忆库如果不维护，就会变得混乱、冲突、过时。</font>
    - **<font style="color:rgb(1, 1, 1);">智能记忆治理：</font>**<font style="color:rgb(1, 1, 1);">引入记忆演化算法，自动整合、集成、剔除冗余、过期、冲突数据，通过数据压缩降低存储压力；支持记忆优先级设置，确保关键信息不丢失；</font>
+ **<font style="color:rgb(1, 1, 1);">记忆检索（Retrieval）</font>**
    - **<font style="color:rgb(1, 1, 1);">检索与更新优化：</font>**<font style="color:rgb(1, 1, 1);">优化记忆检索机制，结合语义相似度、语法检索、图检索等与任务相关性排序提升召回准确性；设计增量更新策略，基于任务重要性与数据时效性动态调整存储优先级；</font>
    - **<font style="color:rgb(1, 1, 1);">前后处理：</font>**<font style="color:rgb(1, 1, 1);">可以主动发起记忆检索的动作，而不是等待指令；也可以Agent需要对检索结果进行重排序（Re-ranking）和过滤，确保喂给大模型的上下文是纯净的。</font>

#### <font style="color:black;">大模型Agent记忆系统分类体系</font>
##### 经典分层框架：基于存储时效的核心分类
<font style="color:black;">Agent 记忆系统的分层设计根植于 1968 年 Atkinson-Shiffrin 记忆模型的核心逻辑，结合 AI 应用场景优化后，形成 “感知 - 短期 - 长期” 三级时效分层体系，各层级功能与特性明确区分：</font>

+ **<font style="color:black;">感知记忆（环境感知记忆）</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">最瞬时的记忆形态，仅存储当下环境中的即时数据（如视觉、声音信息），无长期复用价值，仅在当前瞬间有效，需通过转化机制进入更高层级记忆才能长期保留。</font>
+ **<font style="color:black;">短期记忆（工作记忆）</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">聚焦当前任务与会话的即时信息存储，对应 Agent 的 Session 级别数据管理，通常基于 ES 等技术实现，将会话内容、实体信息、任务执行中间状态统一为标准化 Segment 格式，核心作用是保障上下文连续性与即时响应能力。其概念与 1974 年 Baddeley & Hitch 模型中的 “工作记忆” 高度契合，仅保留任务处理所需的短期有效信息。</font>
+ **<font style="color:black;">长期记忆</font>**<font style="color:rgb(1, 1, 1);">：Agent 实现 “持续进化” 的核心支撑，可长期甚至永久存储海量数据与经验，与短期记忆形成功能互补 —— 短期记忆保障即时处理效率，长期记忆提供背景知识与历史经验沉淀，二者协同实现智能决策。</font>

##### <font style="color:black;">功能导向分类：长期记忆的细分纬度</font>
<font style="color:black;">从实际应用功能出发，长期记忆可进一步划分为四大核心类型，覆盖不同场景的记忆需求：</font>

+ **<font style="color:black;">检索记忆</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">通过 RAG 技术对接外部知识库，核心价值是补充模型原生知识，同时减少内部知识冲突，提升信息获取的精准性与时效性。</font>
+ **<font style="color:black;">通用记忆</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">通过预训练或后续微调沉淀的基础通用知识，构成 Agent 的核心认知底座，支撑各类基础任务的理解与执行。</font>
+ **<font style="color:black;">规则记忆</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">以强化学习（RL）、提示词（Prompt）等方式固化的行为规范，用于约束 Agent 输出格式（如 JSON、CoT 链式推理）与行为边界，确保响应的一致性与合规性。</font>
+ **<font style="color:black;">个性化记忆</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">通过会话内容摘要等方式提取的用户画像信息，包括用户偏好、行为习惯、身份特征等，支撑长期交互中的个性化服务。</font>

#### <font style="color:black;">比对差异</font>
<font style="color:rgb(0, 0, 0);">上下文、知识库、记忆，它们在系统里的角色完全不同。先简略看看几个常见概念的区别。</font>

**<font style="color:black;">上下文解决的是「这一次」</font>**

<font style="color:black;">上下文窗口是把最近的对话和信息塞给模型，让它在当前任务里保持连贯。窗口再大也有边界，而且天然是会话级的。它适合一次性写方案、短期问答、单次任务冲刺。</font>

**<font style="color:black;">知识库解决的是它「不知道」你们公司</font>**

<font style="color:black;">RAG 的核心价值是补齐模型权重之外的企业知识、业务数据、文档。它更偏静态知识和结构化事实。它适合企业客服知识问答、产品文档检索、合规和规则解释。</font>

**<font style="color:black;">AI 记忆解决的是它「不懂你」</font>**

<font style="color:black;">AI 记忆系统要保存并调用用户过去与模型的交互历史，为新会话设置上下文，并持续改进用户画像，让 Agent 能稳定输出个性化结果。</font>

##### <font style="color:black;">Agent记忆与LLM记忆</font>
+ **<font style="color:black;">LLM记忆</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">通常指模型内部的技术优化，例如如何优化 Transformer的 </font><font style="color:black;">KV Cache（键值缓存）</font><font style="color:rgb(1, 1, 1);"> 以减少重复计算，或者通过架构调整（如 Mamba、RWKV）让模型能处理更长的上下文窗口。这更像是计算机的“显存优化”，关注的是单次推理的效率和容量。</font>
+ **<font style="color:black;">Agent记忆</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">这是指一个智能体为了在环境中长期存在，维护的一个</font><font style="color:black;">持久的、动态演化的认知状态</font><font style="color:rgb(1, 1, 1);">。它不仅是存储数据，更包含了“我是谁”、“我经历过什么”、“用户的偏好是什么”这些核心认知，是跨越多次交互周期的。</font>

##### <font style="color:black;">Agent记忆与RAG</font>
<font style="color:black;">总体上，RAG有助于Agent更准确的回答问题；而Memory则有助于Agent表现的更加智能。</font>**<font style="color:black;">Memory 更像一本随时可写、可删、可更新的“笔记本”或“硬盘”；而 RAG 更像一套结构稳定、更新不那么频繁的“参考书体系”。</font>**

<font style="color:black;">具体来看。</font>

+ **<font style="color:black;">RAG</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">通常是静态的知识外挂，有Modular RAG、Graph RA、Agentic RAG三类。比如您有一个巨大的文档库（比如公司手册），模型去里面搜索答案。它解决的是“知识库”的问题，通常用于单次任务，知识库本身很少随交互而改变。RAG像是代理的研究图书管理员，从静态、共享的知识库中检索事实信息。</font>
+ **<font style="color:black;">Agent记忆</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">是</font><font style="color:black;">动态生长</font><font style="color:rgb(1, 1, 1);">的。随着 Agent与您的每一次交互，它的记忆库都在发生变化——它会记下新的经验，修正错误的认知，甚至遗忘不再重要的信息。它强调的是</font><font style="color:black;">交互历史</font><font style="color:rgb(1, 1, 1);">和</font><font style="color:black;">经验积累</font><font style="color:rgb(1, 1, 1);">。内存管理像是私人助理，携带记录每个用户交互细节的私人笔记本。</font>

##### <font style="color:black;">Agent记忆与上下文工程</font>
+ **<font style="color:black;">上下文工程</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">是一种资源管理手段。因为模型的窗口有限，我们通过各种技巧（如Prompt压缩、重要性筛选）把最重要的信息塞进去。</font>
    - <font style="color:rgb(1, 1, 1);">在未来，一个人的本质，就是其所有上下文的总和。</font>
    - <font style="color:black;">提示词工程</font><font style="color:rgb(1, 1, 1);">是为了获得最佳推理结果而编写和组织 LLM 指令的方法，</font><font style="color:black;">上下文工程</font><font style="color:rgb(1, 1, 1);">则是指在 LLM 推理过程中，动态规划和维护最优的输入 token 集合（集合包括任何可能进入上下文的信息）。</font>
+ **<font style="color:black;">Agent记忆</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">是</font><font style="color:black;">认知建模</font><font style="color:rgb(1, 1, 1);">。它决定了哪些信息值得被保留下来成为长期记忆，并在未来几天、几个月甚至几年后被调用。上下文工程是“怎么塞进去”，而 Agent记忆是“该塞什么”（的一部分）。</font>

#### <font style="color:black;">OpenHands Memory功能解析</font>
##### 三层结构
<font style="color:black;">在智能代理的运行机制中，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Memory</font>`<font style="color:black;">模块扮演着 “记忆中心” 的角色，专门负责处理和管理代理所需的上下文信息。上下文管理的挑战在于如何在有限的上下文窗口内提供最相关的信息。由于大语言模型的上下文窗口存在容量限制，单纯把所有历史信息堆砌进去显然不现实。为此，OpenHands 设计了一套三层记忆模型：</font>

+ **<font style="color:rgb(1, 1, 1);">Condenser 专注于历史压缩</font>**
+ **<font style="color:rgb(1, 1, 1);">ConversationMemory 专注于消息格式化</font>**
+ **<font style="color:rgb(1, 1, 1);">而 View 作为中间数据结构连接两者</font>**

<font style="color:black;">这三个层共同构成了 OpenHands 中对话历史管理和消息处理的核心机制，分别负责压缩、表示和转换三个关键环节。既让代理能够获取到决策所需的完整上下文，又通过</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Condenser</font>`<font style="color:black;">的机制有效避免了上下文窗口溢出，保障了代理在长时间任务中逻辑的连贯性。巧妙应对 “上下文有限” 这一难题。</font>

```python
memory/
│
│──── condenser/ # 历史压缩器
│         │
│         │──── condenser.py # 压缩器基类
│         │──── ... # 各种压缩策略
│
│──── conversation_memory.py # 对话内存管理
│──── view.py # 事件视图
```

###### <font style="color:black;">View</font>
<font style="color:black;">View  作为中间数据结构，连接压缩和转换两个阶段。View  的主要工作是对原始的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Event Stream</font>`<font style="color:black;">进行首次过滤和整理。在众多事件中，有些对语言模型的决策没有直接帮助，比如</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">NullAction</font>`<font style="color:black;">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentStateChangedObservation</font>`<font style="color:black;">这类 “噪声” 事件，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">View</font>`<font style="color:black;">会将它们排除在外。同时，它还会处理 “记忆压缩” 相关事件，最终形成一个相对简洁的事件序列。作为内存管理系统里处理事件历史的关键部分，view.py 能确保代理在处理长对话历史时，不会超出上下文的限制。</font>

+ <font style="color:rgb(1, 1, 1);">Condenser.condensed_history () 方法返回压缩后的历史记录，可能包含：</font>
    - <font style="color:rgb(1, 1, 1);">View对象：View 包含筛选后、处理后的事件列表（经过压缩或过滤后的一组事件，供后续处理使用）</font>
    - <font style="color:rgb(1, 1, 1);">Condensation对象：表示需要执行的压缩操作（如请求摘要）</font>

###### <font style="color:black;">ConversationMemory</font>
<font style="color:black;">ConversationMemory 的核心任务是将</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">View</font>`<font style="color:black;">提供的事件列表 —— 这些列表更贴合机器的处理方式 —— 转换成语言模型更容易理解的对话格式，也就是</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">List[Message]</font>`<font style="color:black;">。每个</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Message</font>`<font style="color:black;">对象都包含 “角色”（比如 “用户”“助手”“工具”）和 “内容” 两部分，这正好符合大多数语言模型 API 对输入格式的要求。</font>

<font style="color:black;">ConversationMemory 专注于消息格式转换，确保消息格式正确，提高 LLM 理解效率：</font>

+ <font style="color:rgb(1, 1, 1);">接收来自 View 的事件列表</font>
+ <font style="color:rgb(1, 1, 1);">使用 process_events () 方法将事件转换为适合 LLM 的消息格式，处理包括系统消息、用户消息、工具调用和观察结果等在内的完整对话流程</font>
+ <font style="color:rgb(1, 1, 1);">输出可以直接传递给 LLM 的消息列表</font>

<font style="color:black;">相关配置：</font>

+ <font style="color:rgb(1, 1, 1);">CondenserPipelineConfig：定义压缩器管道配置</font>
+ <font style="color:rgb(1, 1, 1);">各种具体的压缩器配置如ConversationWindowCondenserConfig、BrowserOutputCondenserConfig、LLMSummarizingCondenserConfig 等</font>

<font style="color:black;">这种设计实现了关注点分离：Condenser 专注于历史压缩，ConversationMemory 专注于消息格式化，而 View 作为中间数据结构连接两者。</font>

###### <font style="color:black;">Condenser</font>
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Condenser</font>`<font style="color:black;">是解决长上下文问题的关键环节。当</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">View</font>`<font style="color:black;">中的事件数量超出预设的阈值时，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Condenser</font>`<font style="color:black;">就会启动工作。它会借助语言模型对一部分较早的历史事件进行总结，生成一个简短的</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">CondensationObservation</font>`<font style="color:black;">事件。之后，用这个总结来替代那些被移除的大量原始事件，从而实现对上下文的 “有损压缩”。</font>

<font style="color:black;">Condenser 专注于历史压缩算法实现，可以通过 Condenser 减少传递给 LLM 的上下文大小，降低计算成本，也防止超出 LLM 的上下文窗口限制</font>

+ <font style="color:rgb(1, 1, 1);">负责压缩对话历史，控制传递给 LLM 的事件数量</font>
+ <font style="color:rgb(1, 1, 1);">内部使用 CondenserPipeline 来应用多种压缩策略（如窗口限制、浏览器输出压缩、LLM 摘要等）</font>

##### <font style="color:black;">工作流程</font>
```python
Agent.step()（决策层）
  ↓
Condenser.condensed_history()（历史压缩器）
  ↓
View.from_events() （事件视图）
  ↓
返回View(events=[...])
  ↓
Agent处理View.events
  ↓
ConversationMemory.process_events()（对话内存）
  ↓
LLM处理压缩后的事件历史
```

#### Ref
[https://mp.weixin.qq.com/s?__biz=Mzk1NzQ1ODk5NQ==&mid=2247523993&idx=1&sn=af3cb2b1d7d0154690d91ae92cd1e438&chksm=c299943166d4ae09321d628140bdbee8ea1878d15eb4e6cb23b4200d044219b533b185e9aad4&mpshare=1&srcid=1208mey7lR0lI66BBwF79D5U&sharer_shareinfo=0f43207268e5ba03d31cbb62389e7faa&sharer_shareinfo_first=0f43207268e5ba03d31cbb62389e7faa&scene=21#wechat_redirect](https://mp.weixin.qq.com/s?__biz=Mzk1NzQ1ODk5NQ==&mid=2247523993&idx=1&sn=af3cb2b1d7d0154690d91ae92cd1e438&chksm=c299943166d4ae09321d628140bdbee8ea1878d15eb4e6cb23b4200d044219b533b185e9aad4&mpshare=1&srcid=1208mey7lR0lI66BBwF79D5U&sharer_shareinfo=0f43207268e5ba03d31cbb62389e7faa&sharer_shareinfo_first=0f43207268e5ba03d31cbb62389e7faa&scene=21#wechat_redirect)

### MicroAgents
<font style="color:black;">很多Agent系统会采用多智能体（multi-agent）架构，划分不同子模块/子Agent各司其职，由中央调度Agent统筹管理整个生命周期。这种模块化架构能将复杂任务拆解给最擅长该子任务的模块，发挥各模型所长，避免单一模型在某些任务上的弱点。</font>

<font style="color:black;">在OpenHands 中，</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Microagents</font>`<font style="color:black;"> 本质上是一组量身定制的指令模块，核心作用是给 OpenHands 工具注入更聚焦的能力 —— 不管是某个细分领域的专业知识，还是特定任务的标准化流程，都能通过它们来落地。对开发者来说，这些小模块就像身边的专项助手：遇到 Git 操作、代码审查这类具体场景时，不用再手动梳理步骤，微型代理会提供现成的专业指引；重复任务能直接交给它们自动化处理，还能保证不同项目里的操作逻辑保持一致，省不少事。</font>

`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Microagents</font>`<font style="color:black;"> 允许我们为 Agent “外挂”领域知识，而无需修改 Agent 的核心代码或 Prompt。</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Memory</font>`<font style="color:black;"> 组件会在任务开始时或在对话中检测到特定关键词时，自动加载相应的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Microagent</font>`<font style="color:black;"> 文件内容，并将其作为上下文信息提供给 LLM。这使得 Agent 能够：</font>

+ <font style="color:black;">快速适应特定项目：</font><font style="color:rgb(1, 1, 1);"> 通过加载项目专属的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">repo.md</font>`<font style="color:rgb(1, 1, 1);">，Agent 可以了解项目的架构、编码规范和测试方法。</font>
+ <font style="color:black;">利用领域知识：</font><font style="color:rgb(1, 1, 1);"> 比如，当用户提到 “Python” 时，可以自动注入一份关于 Python 最佳实践的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">knowledge.md</font>`<font style="color:rgb(1, 1, 1);">。</font>

#### Requirement
##### Multi-Agent System
<font style="color:rgb(0, 0, 0);">多智能体系统</font><font style="color:black;">的核心逻辑是 “分工协作”：遇到复杂任务时，先把大任务拆成一个个小模块，比如把 “完成一份市场分析报告” 拆成 “数据收集”“统计计算”“报告撰写”“合规审核” 几个子任务，再给每个子任务分配专门的 “专家” 智能体 —— 有的专攻数据爬取，有的擅长数学建模，有的精通文案润色。</font>

<font style="color:black;">这些智能体不用包揽所有事，只需要把自己领域的工作做精。它们之间还能随时沟通：数据爬取的智能体拿到素材后，会同步给统计计算的智能体；计算结果出来后，再传给文案智能体，过程中如果遇到问题，还能互相协调调整。这种模式不仅让每个智能体都能发挥专长，还可能产生意外的 “协作红利”—— 就像一个高效的团队，整体能完成的事，远超出单个成员的能力总和。</font>

<font style="color:black;">从实际开发来看，多智能体也更实用：每个智能体都是独立模块，开发时不用考虑全盘，测试和维护起来更简单；如果某个领域需要升级，直接替换对应的智能体就行，不用动整个系统；而且智能体之间怎么沟通、传递信息，都能提前设定好规则，比单个智能体混乱调用工具要可控得多。</font>

##### <font style="color:rgb(0, 0, 0);">Multi-Agent</font>
<font style="color:rgb(0, 0, 0);">多智能体（Multi-Agent）系统与单一智能体工作流的核心区别，在于突破了 “顺序接力” 的任务执行模式，实现了智能体间的高效并行协作。也有研究人员认为，Sub-Agents 是 Multi-Agent 体系下的一种架构模式，而不是一个与 Multi-Agent 对立的总体范式。</font>

```python
Multi-Agent（多智能体系统） ，本质上是一群相对独立的智能体在协作。它们可能有各自的目标、各自的状态、各自的上下文，通过通信协议来协调。

而Sub-Agent（子代理） ，本质上是集中式架构下的分工。一个主智能体掌控全局，把任务委派给几个专用的子代理。这些子代理更像工具，无状态，只处理被分配的子任务。就像一个项目经理手下有几个专精的执行者。项目经理知道全局目标和上下文，根据需要把任务分发给不同的人，拿到结果后再整合。

关键区别在于：控制权和上下文。

Multi-Agent模式下，控制权是分布式的，每个Agent都有一定的自主权，上下文是隔离的。而Sub-Agent模式下，控制权是集中式的，主智能体说了算，上下文是共享的。
```

##### <font style="color:rgb(0, 0, 0);">连接机制</font>
**<font style="color:black;">多智能体（Multi-Agent）</font>**<font style="color:black;">的核心思想是：</font>**<font style="color:black;">让专业的人干专业的事</font>**<font style="color:black;">。我们创建多个拥有独立 Prompt 和独立工具的 Agent，然后通过某种机制把它们连起来。最基础的连接机制有两种：</font>**<font style="color:black;">Handoffs（交接/路由）</font>**<font style="color:black;"> 和 </font>**<font style="color:black;">Orchestrator-Workers（指挥/分发）</font>**<font style="color:black;">。</font>

<font style="color:black;">handoffs 指的是一个智能体将其执行上下文和执行权交接给另一个智能体。handoffs需要包含两个最基本的要素：</font>

+ **<font style="color:rgb(1, 1, 1);">目的地：下一个智能体</font>**
+ **<font style="color:rgb(1, 1, 1);">State：传递给下一个智能体的信息</font>**

<font style="color:black;">其实，工具调用也是一种连接机制，比如一个智能体（如主管）将另一个智能体作为工具进行调用。移交更适用于自主协作的场景，而工具调用则提供了更明确的层级控制和接口约束。</font>

##### <font style="color:rgb(0, 0, 0);">Sub-Agent</font>
<font style="color:black;">Sub-agent 这一架构的核心设计是引入 “协调者智能体（Orchestrator Agent）” 作为全局管控核心，其核心职责是先深度理解整体任务目标，再通过合理的任务拆解策略，将复杂任务分解为多个可独立执行的子任务，进而委派给多个并行工作的 “子智能体（Sub-agent）”。</font>

<font style="color:black;">该系统的实现逻辑为：</font>

+ <font style="color:rgb(1, 1, 1);">在协调者智能体的视角中，调用子智能体与调用普通工具（Tool）的交互模式完全一致。协调者通过工具调用（tool calling）机制，以提示词（prompt）形式向子智能体下达明确指令；</font>
+ <font style="color:rgb(1, 1, 1);">子智能体接收指令后，在独立的执行环境中自主完成分配的任务，无需与其他子智能体交互，最终仅将完成结果反馈给协调者。</font>

<font style="color:black;">子智能体架构能够高效落地的本质，是上下文工程（Context Engineering）的成功实践。其核心思想在于精准把控 “信息供给的时机与内容”—— 为每个子智能体创建专注且隔离的执行环境，确保其在处理对应子任务时，能获得最匹配的信息与工具支持。这种设计不仅能大幅提升整个系统的任务处理性能，还能通过职责拆分与环境隔离，降低复杂目标的实现成本，成为应对大规模、多维度复杂任务的高效架构方案。</font>

##### <font style="color:black;">microagents</font>
**<font style="color:black;">Agent as Tool就像一个专家顾问，主智能体调用它时，给出明确的输入，拿到明确的输出，就像调用一个API。这个专家顾问有自己的逻辑，但主智能体不需要知道细节。</font>**

<font style="color:black;">而Sub-Agent（委派式子代理）更像一个项目经理的分身，它在主智能体的全局上下文中工作，处理复杂的多步骤流程，可以访问主智能体的对话历史和状态。</font>

<font style="color:black;">结合 Google Cloud 对两种代理模式的核心界定，以及 OpenHands 的 microagents（微代理）的功能特性来看，</font>**<font style="color:black;">microagents 本质上属于 Agent as Tool（工具式子代理）</font>**<font style="color:black;"> 。下面结合两者的核心差异与 microagents 的具体表现展开分析：</font>

1. <font style="color:black;">从核心定义与控制逻辑来看</font>
    - <font style="color:rgb(1, 1, 1);">Google Cloud 明确，Agent as Tool 是封装好的特定任务专家，主代理调用它时只需传递清晰输入并获取直接输出，类似事务性 API，无需关注其内部逻辑；而 Sub - Agent 是接受委派的角色，需自主处理复杂多步骤流程，和主代理是层级协作关系，拥有一定自主决策与流程管理权。</font>
    - <font style="color:rgb(1, 1, 1);">OpenHands 的 microagents 不管是知识代理、任务代理还是仓库代理，均是响应特定触发条件来执行固定功能。比如知识代理靠 “docker”“container” 等关键词触发，提供对应领域的标准化支持；任务代理按预设交互式模板，接收参数后完成 PR 描述生成等操作。它们不会自主规划复杂任务流程，完全由系统或主流程触发调用，契合 Agent as Tool 的 “被动响应、执行特定功能” 的控制逻辑。</font>
2. <font style="color:black;">从上下文与状态特性来看</font>
    - <font style="color:rgb(1, 1, 1);">Agent as Tool 具有上下文隔离、无状态的特点，运行在自身独立会话中，无法获取调用方的对话历史和状态，且每次交互的信息都靠单次请求传递。而 Sub - Agent 能共享主代理的上下文，处于同一会话，适合需要多步骤推进的有状态流程。</font>
    - <font style="color:rgb(1, 1, 1);">microagents 是独立封装的模块，不同代理间相互隔离。例如仓库代理仅加载所在项目的专属规范，知识代理只聚焦单一领域的知识输出。它们的运行不依赖其他代理的历史状态，每次触发都是基于当前的输入信息执行任务并返回结果，不存在与主流程或其他代理共享上下文来推进多步骤任务的情况，符合 Agent as Tool 的无状态、上下文隔离特征。</font>
3. <font style="color:black;">从复用性与耦合度来看</font>
    - <font style="color:rgb(1, 1, 1);">Agent as Tool 的一大优势是复用性强，可在不同代理或系统中被重复调用，与调用方的耦合度低；而 Sub - Agent 和主代理耦合紧密，是特定流程的一部分，复用性较弱，多适配所属的层级协作体系。</font>
    - <font style="color:rgb(1, 1, 1);">microagents 的设计着重于高复用性。公共微代理库中的代理可跨不同项目使用，私有仓库代理虽为团队专属，但也是在项目内部的固定场景中重复发挥作用。并且它们可通过简单配置接入系统，无需和主流程进行深度的层级绑定开发，这种高复用、低耦合的特性，和 Sub - Agent 的强耦合特征不符，反而匹配 Agent as Tool 的核心特点。</font>

##### 原理
###### 协作
<font style="color:black;">多智能体不仅仅是把任务拆分，它引入了一个全新的优化维度，</font>**<font style="color:black;">协作（Collaboration）</font>**<font style="color:black;">。</font>

<font style="color:black;">有研究者问了一个深刻的问题：</font>**<font style="color:black;">为什么两个Agent配合往往比一个超级Agent更好？</font>**<font style="color:black;">答案在于一个新的概率项--- 协作概率。</font>

<font style="color:black;">在多智能体系统中，Agent A（比如产品经理）执行动作后，不仅仅是产生一个结果，它通过动作产生了一个</font>**<font style="color:black;">上下文（Context），并把这个上下文传递给Agent B（比如程序员）。</font>**

<font style="color:black;">这听起来很抽象，但请这样理解： 协作和协商（Negotiation），本质上是在</font>**<font style="color:black;">搜索最优的通信上下文</font>**<font style="color:black;">。</font>

+ **<font style="color:black;">单体Agent</font>****<font style="color:rgb(1, 1, 1);">：只能自己闷头干，必须在给定的S下硬解a。</font>**
+ **<font style="color:black;">多智能体</font>****<font style="color:rgb(1, 1, 1);">：Agent A的任务变成了“寻找一种最好的说法”，使得Agent B成功的概率最大化。</font>**

<font style="color:black;">研究者指出，这种“通过对话来动态调整上下文”的能力，实际上是在</font>**<font style="color:black;">运行时（Runtime）动态微调系统的参数</font>**<font style="color:black;">，而不需要重新训练模型。这就是多智能体系统强大的数学根源，它增加了一个巨大的、可优化的参数空间。</font>

###### <font style="color:black;">token</font>
<font style="color:rgb(0, 0, 0);">Anthropic 在其博客中指出，多智能体系统之所以有效，主要是因为它们</font>**<font style="color:black;">投入足够的token来解决问题</font>**<font style="color:rgb(0, 0, 0);">。在分析中，三个因素解释了BrowseComp评估中95%的性能差异（该评估测试浏览智能体定位难以找到信息的能力）。研究发现，仅</font>**<font style="color:black;">token使用量</font>**<font style="color:rgb(0, 0, 0);">就解释了80%的差异，</font>**<font style="color:black;">工具调用次数</font>**<font style="color:rgb(0, 0, 0);">和</font>**<font style="color:black;">模型选择</font>**<font style="color:rgb(0, 0, 0);">是另外两个解释因素。</font>

###### <font style="color:rgb(0, 0, 0);">成本</font>
<font style="color:black;">虽然多智能体协作听起来很美，但研究者非常冷静地泼了一盆冷水：</font>**<font style="color:black;">协作是有成本的（Collaboration Costs）。</font>**

<font style="color:black;">用户增加的每一个Agent，每一次交互，都会带来：</font>

1. <font style="color:black;">延迟（Latency）</font><font style="color:rgb(1, 1, 1);">：网络请求和生成的耗时。</font>
2. <font style="color:black;">算力消耗（Tokens）</font><font style="color:rgb(1, 1, 1);">：真金白银的成本。</font>
3. <font style="color:black;">复杂性（Complexity）</font><font style="color:rgb(1, 1, 1);">：系统越复杂，越容易出错。</font>

#### 基本梳理
##### 基类定义
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Microagents</font>`<font style="color:rgb(0, 0, 0);"> 是 Openhands 中一种</font>**<font style="color:black;">模块化的知识注入机制</font>**<font style="color:rgb(0, 0, 0);">。它们通常是一些 Markdown 文件，包含了针对特定领域、特定仓库或特定任务的知识、指南或代码片段。</font>

<font style="color:rgb(0, 0, 0);">从系统架构的角度看，微型代理（Microagents）本质是轻量化的 “专项执行者”—— 它们不负责整体任务的统筹规划，只聚焦某一类特定工作，比如专门处理代码格式化、数据校验这类单一职责。和主智能体（主 Agent）的 “总指挥” 角色不同，它们更像随时待命的 “专业小分队”，平时不占用过多系统资源，一旦主智能体需要，要么被直接召唤上场，要么接手主智能体拆分出来的细分任务，灵活又高效。</font>

<font style="color:rgb(0, 0, 0);">这些专项执行者并不是孤立的 “散兵”，系统早就设计好了一套统一的集成逻辑，核心就是</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">get_microagents_from_selected_repo</font>`<font style="color:rgb(0, 0, 0);">这个核心方法。具体用起来很简单：用户或者团队可以在自己的代码仓库里，单独建一个文件夹专门存放微型代理，不管是自己开发的，还是适配好的专项工具，都可以放在这里统一管理。等系统将这个仓库设为当前的工作仓库时，会自动扫描这个专属文件夹，把里面所有的微型代理一次性加载进来，相当于为系统搭建了一个 “专项工具储备库”。之后主智能体在处理复杂任务时，比如遇到需要专门做日志分析或者接口调试的环节，就能直接从这个储备库里调取对应的微型代理，一起协同完成工作。</font>

```python
class BaseMicroagent(BaseModel):
    """Base class for all microagents."""

    name: str
    content: str
    metadata: MicroagentMetadata
    source: str  # path to the file
    type: MicroagentType

    PATH_TO_THIRD_PARTY_MICROAGENT_NAME: ClassVar[dict[str, str]] = {
        '.cursorrules': 'cursorrules',
        'agents.md': 'agents',
        'agent.md': 'agents',
    }
```

##### 微型代理的类型
<font style="color:black;">大多数微型代理使用带有YAML前导的Markdown文件。对于仓库代理（repo.md），前导是可选的 - 如果未提供，文件将使用默认设置作为仓库代理加载。</font>

<font style="color:black;">KnowledgeMicroagent 和 RepoMicroagent 都是 BaseMicroagent 的子类，但它们有不同的用途和激活机制。这两种微代理类型共同构成了 OpenHands 系统中灵活而强大的知识管理机制，允许同时拥有按需访问的专业知识和持续可用的仓库特定知识。</font>

###### <font style="color:black;">KnowledgeMicroagent</font>
<font style="color:black;">知识代理提供由对话中的关键词触发的专业技能。它们帮助：</font>

+ <font style="color:rgb(1, 1, 1);">语言最佳实践</font>
+ <font style="color:rgb(1, 1, 1);">框架指南</font>
+ <font style="color:rgb(1, 1, 1);">常见模式</font>
+ <font style="color:rgb(1, 1, 1);">工具使用</font>

<font style="color:black;">基本特征</font>

+ <font style="color:rgb(1, 1, 1);">类型：MicroagentType.KNOWLEDGE 或 MicroagentType.TASK</font>
+ <font style="color:rgb(1, 1, 1);">激活方式：关键词触发，当消息中包含特定触发词时激活</font>

<font style="color:black;">主要功能</font>

+ <font style="color:rgb(1, 1, 1);">提供专业领域知识和特定技能指导</font>
+ <font style="color:rgb(1, 1, 1);">用于语言最佳实践、框架指南、常见模式和工具使用</font>
+ <font style="color:rgb(1, 1, 1);">通过 match_trigger 方法匹配消息中的触发词</font>

<font style="color:black;">激活机制</font>

+ <font style="color:rgb(1, 1, 1);">需要在 frontmatter 中定义 triggers 数组</font>
+ <font style="color:rgb(1, 1, 1);">仅在用户输入包含触发词时才会被激活</font>

<font style="color:black;">适用场景</font>

+ <font style="color:rgb(1, 1, 1);">特定技术栈的使用指南</font>
+ <font style="color:rgb(1, 1, 1);">框架或工具的最佳实践</font>
+ <font style="color:rgb(1, 1, 1);">特定领域的专业知识</font>
+ <font style="color:rgb(1, 1, 1);">需要用户输入的任务型微代理（TaskMicroagent）</font>

```python
class KnowledgeMicroagent(BaseMicroagent):
    """Knowledge micro-agents provide specialized expertise that's triggered by keywords in conversations.

    They help with:
    - Language best practices
    - Framework guidelines
    - Common patterns
    - Tool usage
    """

    def __init__(self, **data):
        super().__init__(**data)
        if self.type not in [MicroagentType.KNOWLEDGE, MicroagentType.TASK]:
            raise ValueError('KnowledgeMicroagent must have type KNOWLEDGE or TASK')

    def match_trigger(self, message: str) -> str | None:
        """Match a trigger in the message.

        It returns the first trigger that matches the message.
        """
        message = message.lower()
        for trigger in self.triggers:
            if trigger.lower() in message:
                return trigger

        return None

    @property
    def triggers(self) -> list[str]:
        return self.metadata.triggers
```

###### RepoMicroagent
<font style="color:black;">仓库代理提供仓库特定的知识和指导方针。它们是：</font>

+ <font style="color:rgb(1, 1, 1);">从</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">.openhands/microagents/repo.md</font>`<font style="color:rgb(1, 1, 1);">加载</font>
+ <font style="color:rgb(1, 1, 1);">特定于个别仓库</font>
+ <font style="color:rgb(1, 1, 1);">为其仓库自动激活</font>
+ <font style="color:rgb(1, 1, 1);">非常适合团队实践和项目惯例</font>

<font style="color:black;">基本特征</font>

+ <font style="color:rgb(1, 1, 1);">类型为 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">MicroagentType.REPO_KNOWLEDGE</font>`
+ <font style="color:rgb(1, 1, 1);">激活方式：始终激活，与特定仓库关联</font>

<font style="color:black;">主要功能</font>

+ <font style="color:rgb(1, 1, 1);">提供仓库特定的知识和指南</font>
+ <font style="color:rgb(1, 1, 1);">包含私有的、仓库特定的指令</font>
+ <font style="color:rgb(1, 1, 1);">自动加载并与当前仓库关联</font>

<font style="color:black;">激活机制</font>

+ <font style="color:rgb(1, 1, 1);">自动激活，不需要触发词</font>
+ <font style="color:rgb(1, 1, 1);">在处理相关仓库时始终可用</font>
+ <font style="color:rgb(1, 1, 1);">通常来自 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">.openhands/microagents/repo.md</font>`<font style="color:rgb(1, 1, 1);"> 文件</font>

<font style="color:black;">适用场景</font>

+ <font style="color:rgb(1, 1, 1);">仓库特定的开发规范</font>
+ <font style="color:rgb(1, 1, 1);">团队实践和约定</font>
+ <font style="color:rgb(1, 1, 1);">项目特定的工作流程</font>
+ <font style="color:rgb(1, 1, 1);">自定义文档引流</font>
+ <font style="color:rgb(1, 1, 1);">通用仓库指南</font>

```python
class RepoMicroagent(BaseMicroagent):
    """Microagent specialized for repository-specific knowledge and guidelines.

    RepoMicroagents are loaded from `.openhands/microagents/repo.md` files within repositories
    and contain private, repository-specific instructions that are automatically loaded when
    working with that repository. They are ideal for:
        - Repository-specific guidelines
        - Team practices and conventions
        - Project-specific workflows
        - Custom documentation references
    """

    def __init__(self, **data):
        super().__init__(**data)
        if self.type != MicroagentType.REPO_KNOWLEDGE:
            raise ValueError(
                f'RepoMicroagent initialized with incorrect type: {self.type}'
            )
```

###### TaskMicroagent
<font style="color:rgb(0, 0, 0);">TaskMicroagent 是 KnowledgeMicroagent 的子类，具有特殊的任务导向特性，需要用户输入才能执行。</font>

<font style="color:black;">核心特点</font>

<font style="color:black;">需要用户输入</font>

+ <font style="color:rgb(1, 1, 1);">变量提取：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">extract_variables</font>`<font style="color:rgb(1, 1, 1);"> 方法从内容中提取变量（格式为 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">${variable_name}</font>`<font style="color:rgb(1, 1, 1);">）</font>
+ <font style="color:rgb(1, 1, 1);">输入检测：</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">requires_user_input</font>`<font style="color:rgb(1, 1, 1);"> 方法检查内容中是否包含变量</font>
+ <font style="color:rgb(1, 1, 1);">输入定义：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">inputs</font>`<font style="color:rgb(1, 1, 1);"> 属性获取预定义的输入元数据</font>

<font style="color:black;">特殊触发方式</font>

+ <font style="color:rgb(1, 1, 1);">命令式触发：通过格式 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">/agent_name</font>`<font style="color:rgb(1, 1, 1);"> 触发，例如 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">/test_task</font>`
+ <font style="color:rgb(1, 1, 1);">自动触发词添加：如果 frontmatter 中没有定义触发词，系统会自动添加 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">/</font>`<font style="color:rgb(1, 1, 1);"> 前缀的触发词</font>

<font style="color:black;">适用场景</font>

<font style="color:black;">TaskMicroagent 适用于以下场景：</font>

+ <font style="color:rgb(1, 1, 1);">需要参数的任务：需要用户提供特定参数才能执行的任务</font>
+ <font style="color:rgb(1, 1, 1);">交互式操作：需要与用户进行交互以获取必要信息的操作</font>
+ <font style="color:rgb(1, 1, 1);">模板化任务：可以通过填充变量来执行的标准化任务</font>

##### 微型代理的来源
<font style="color:rgb(0, 0, 0);">OpenHands从两个来源加载微型代理：</font>

###### <font style="color:rgb(0, 0, 0);">可共享微型代理(公共)</font>
<font style="color:black;">此目录（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">OpenHands/microagents</font>`<font style="color:black;">）包含所有OpenHands用户都可以使用的可共享微型代理：</font>

+ <font style="color:rgb(1, 1, 1);">由OpenHands仓库维护</font>
+ <font style="color:rgb(1, 1, 1);">非常适合重用知识和常见工作流程</font>

```python
OpenHands/microagents/
├── # 关键词触发的专业技能
│   ├── git.md         # Git 操作
│   ├── testing.md     # 测试实践
│   └── docker.md      # Docker 指南
├── # 这些微型代理总是加载
    ├── pr_review.md   # PR 审查流程
    ├── bug_fix.md     # Bug 修复工作流程
    └── feature.md     # 功能实现
```

###### 仓库指令(私有)
<font style="color:black;">每个仓库可以在</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">.openhands/microagents/repo.md</font>`<font style="color:black;">中拥有自己的指令。这些指令是：</font>

+ <font style="color:rgb(1, 1, 1);">私有于该仓库</font>
+ <font style="color:rgb(1, 1, 1);">在使用该仓库时自动加载</font>
+ <font style="color:rgb(1, 1, 1);">非常适合仓库特定的指导方针和团队实践</font>

```python
your-repository/
├── .openhands/
    ├── microagents/
        ├── repo.md    # 仓库特定的指令
        ├── ...        # 仅在此仓库内可用的私有微型代理
```

<font style="color:black;">当OpenHands与仓库协作时，它将：</font>

1. <font style="color:rgb(1, 1, 1);">如果存在，从</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">.openhands/microagents/repo.md</font>`<font style="color:rgb(1, 1, 1);">加载仓库特定的指令</font>
2. <font style="color:rgb(1, 1, 1);">根据对话中的关键词加载相关的知识代理</font>

##### 升级为SKILL
<font style="color:black;">注意：在OpenHands最新代码中，对MicroAgent升级为Skills，我们会在其他系列中进行Skill的相关学习和分析。</font>

<font style="color:black;">https://github.com/OpenHands/extensions</font>

<font style="color:black;">https://docs.openhands.dev/overview/skills</font>

<font style="color:black;">https://docs.openhands.dev/sdk/arch/skill</font>

**<font style="color:black;">KnowledgeMicroagent</font>**<font style="color:black;"></font>

```python
ounter(lineounter(lineounter(line
KnowledgeMicroagent is the legacy name for what is now called a Knowledge Skill (keyword-triggered skill).

Knowledge Skills are keyword-triggered skills that activate when specific keywords are detected in user messages. They use a KeywordTrigger with regex patterns to match against user input, and when matched, inject domain-specific knowledge into the agent's context.
```

**RepoMicroagent**

```python
ounter(lineounter(lineounter(lineounter(lineounter(line
RepoMicroagent is the legacy term for what is now called a Repository Skill (or "General Skill" / "Permanent Context"). These are always-active, repository-specific guidelines that are automatically loaded into the agent's context at conversation start.

The recommended approach is to create an AGENTS.md file at your repository root. This file contains project purpose, setup instructions, repo structure, and development guidelines. It has no trigger — it's always injected into the system prompt.

You can also use model-specific variants like GEMINI.md or CLAUDE.md. Legacy paths (.openhands/microagents/) are still supported but deprecated in favor of .agents/skills/
```

#### 实现
##### 处理流程
+ <font style="color:rgb(1, 1, 1);">CodeActAgent 通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">response_to_actions</font>`<font style="color:rgb(1, 1, 1);"> 将工具调用转换为 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateAction</font>`<font style="color:rgb(1, 1, 1);">。</font>
+ <font style="color:rgb(1, 1, 1);">AgentController 接收到 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateAction</font>`<font style="color:rgb(1, 1, 1);"> 并调用 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">start_delegate</font>`<font style="color:rgb(1, 1, 1);"> 方法创建新的代理控制器处理委托任务。</font>

##### 触发条件
<font style="color:black;">AgentDelegateAction 会在以下条件下生成：</font>

+ <font style="color:rgb(1, 1, 1);">LLM 决定将任务委托给另一个专门的代理，比如LLM 调用名为 delegate_to_browsing_agent 的工具函数</font>

<font style="color:black;">该工具函数需要以下参数：</font>

+ <font style="color:rgb(1, 1, 1);">agent：要委托给的代理名称</font>
+ <font style="color:rgb(1, 1, 1);">task：委托的具体任务描述</font>
+ <font style="color:rgb(1, 1, 1);">可选的 inputs：传递给委托代理的额外输入参数</font>

```python
            # ================================================
            # AgentDelegateAction (Delegation to another agent)
            # ================================================
            elif tool_call.function.name == 'delegate_to_browsing_agent':
                action = AgentDelegateAction(
                    agent='BrowsingAgent',
                    inputs=arguments,
                )
```

##### AgentDelegateAction
<font style="color:rgb(0, 0, 0);">AgentDelegateAction 是由 LLM 决定委托任务时通过调用相应工具函数生成的，然后通过 response_to_actions 方法处理并添加到待处理动作队列中，最终在 step 方法中返回执行。</font>

```python
@dataclass
class AgentDelegateAction(Action):
    agent: str
    inputs: dict
    thought: str = ''
    action: str = ActionType.DELEGATE

    @property
    def message(self) -> str:
        return f"I'm asking {self.agent} for help with this task."
```

##### AgentController
###### 委托代理机制
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentController</font>`<font style="color:black;"> 通过 </font>**<font style="color:black;">“委托代理（Delegate）机制”</font>**<font style="color:black;"> 实现对 microAgent（子智能体）的全生命周期控制，核心流程如下：</font>

1. **<font style="color:black;">触发启动</font>**<font style="color:rgb(1, 1, 1);">：主 Agent 生成 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateAction</font>`<font style="color:rgb(1, 1, 1);"> 动作（含子智能体名称、任务参数），主控制器通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">start_delegate()</font>`<font style="color:rgb(1, 1, 1);"> 方法初始化子智能体控制器（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentController</font>`<font style="color:rgb(1, 1, 1);"> 实例，标记 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">is_delegate=True</font>`<font style="color:rgb(1, 1, 1);">）。</font>
2. **<font style="color:black;">资源与状态隔离</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">子智能体控制器继承主控制器的事件流、文件存储等资源，但拥有独立的状态（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:rgb(1, 1, 1);">），包括独立的迭代次数、预算限制、任务上下文，避免与主 Agent 相互干扰。</font>
3. **<font style="color:black;">事件转发与独立执行</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">子智能体运行期间，主控制器将所有事件（如用户消息、工具反馈）转发给子控制器处理，子智能体独立执行任务（无需主 Agent 干预）。</font>
4. **<font style="color:black;">状态监控与终止</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">主控制器实时检查子智能体状态，当子智能体完成（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">FINISHED</font>`<font style="color:rgb(1, 1, 1);">）、拒绝（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">REJECTED</font>`<font style="color:rgb(1, 1, 1);">）或出错（</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">ERROR</font>`<font style="color:rgb(1, 1, 1);">）时，通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">end_delegate()</font>`<font style="color:rgb(1, 1, 1);"> 方法终止子智能体，回收资源并接收其执行结果。</font>
5. **<font style="color:black;">结果整合</font>****<font style="color:rgb(1, 1, 1);">：</font>**<font style="color:rgb(1, 1, 1);">子智能体终止后，主控制器将其输出结果封装为 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateObservation</font>`<font style="color:rgb(1, 1, 1);"> 事件，回传给主 Agent，主 Agent 基于该结果继续执行后续任务。</font>

###### 功能概述
`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentController</font>`<font style="color:black;"> 是 OpenHands 框架中智能体（Agent）的核心控制组件，负责管理 Agent 的生命周期（启动、运行、终止）、事件处理（动作 / 观察结果）、状态维护、资源调度，以及子智能体（microAgent）的委托与协同，是多智能体系统中实现 “主 - 子 Agent 协作” 与 “任务拆分执行” 的核心枢纽。</font>

1. **<font style="color:black;">主 - 子 Agent 交互机制</font>****<font style="color:rgb(1, 1, 1);">：</font>**
    - <font style="color:rgb(1, 1, 1);">主 Agent 以 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateAction</font>`<font style="color:rgb(1, 1, 1);"> 为 “调用接口”，将子任务委托给 microAgent，类比工具调用（Tool Calling）的简洁模式。</font>
    - <font style="color:rgb(1, 1, 1);">子智能体拥有独立的控制器实例，运行期间事件全转发、状态全隔离，执行完成后通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateObservation</font>`<font style="color:rgb(1, 1, 1);"> 回传结果，实现 “委托 - 执行 - 回调” 的闭环。</font>
2. **<font style="color:black;">事件处理机制</font>****<font style="color:rgb(1, 1, 1);">：</font>**
    - <font style="color:rgb(1, 1, 1);">事件分流：根据是否存在活跃子智能体，决定事件是转发给子控制器还是主控制器自行处理。</font>
    - <font style="color:rgb(1, 1, 1);">类型适配：区分 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Action</font>`<font style="color:rgb(1, 1, 1);">（动作）和 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">Observation</font>`<font style="color:rgb(1, 1, 1);">（观察结果）事件，分别调用对应处理方法，支持 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AgentDelegateAction</font>`<font style="color:rgb(1, 1, 1);">、用户消息、工具反馈等多类事件。</font>
    - <font style="color:rgb(1, 1, 1);">步骤触发：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">should_step()</font>`<font style="color:rgb(1, 1, 1);"> 方法判断是否触发 Agent 下一步执行（如用户消息、子智能体结果回调时自动触发）。</font>
3. **<font style="color:black;">全生命周期状态管理</font>****<font style="color:rgb(1, 1, 1);">：</font>**
    - <font style="color:rgb(1, 1, 1);">支持 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">RUNNING</font>`<font style="color:rgb(1, 1, 1);">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AWAITING_USER_INPUT</font>`<font style="color:rgb(1, 1, 1);">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">AWAITING_USER_CONFIRMATION</font>`<font style="color:rgb(1, 1, 1);">、</font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">FINISHED</font>`<font style="color:rgb(1, 1, 1);"> 等多状态切换，状态变更时自动同步到事件流并持久化。</font>
    - <font style="color:rgb(1, 1, 1);">子智能体状态实时监控，异常时自动终止并回收资源，确保系统稳定性。</font>
4. **<font style="color:black;">鲁棒性设计</font>****<font style="color:rgb(1, 1, 1);">：</font>**
    - <font style="color:rgb(1, 1, 1);">防卡死机制：内置 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">StuckDetector</font>`<font style="color:rgb(1, 1, 1);"> 检测 Agent 循环卡死，触发异常处理。</font>
    - <font style="color:rgb(1, 1, 1);">预算与迭代限制：通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">State</font>`<font style="color:rgb(1, 1, 1);"> 中的 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">iteration_flag</font>`<font style="color:rgb(1, 1, 1);"> 和 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">budget_flag</font>`<font style="color:rgb(1, 1, 1);"> 控制最大迭代次数与任务预算，避免资源耗尽。</font>
    - <font style="color:rgb(1, 1, 1);">异常容错：对 LLM 错误（如上下文窗口溢出、API 超时）、子智能体执行错误等场景，提供降级策略（如历史截断、重试）。</font>
5. **<font style="color:black;">多智能体协同支持</font>****<font style="color:rgb(1, 1, 1);">：</font>**
    - <font style="color:rgb(1, 1, 1);">子智能体继承主 Agent 的资源（事件流、文件存储、安全分析器），但状态独立，支持多层级委托（子智能体可再委托其他 microAgent）。</font>
    - <font style="color:rgb(1, 1, 1);">主控制器统一汇总所有智能体的执行 metrics（成本、Token 消耗），便于全局监控。</font>

###### 层级型的合作模式
<font style="color:black;">Agent和Microagent之间是层级型的合作模式。：</font>

<font style="color:black;">层级结构：</font>

+ <font style="color:rgb(1, 1, 1);">Agent是主要的决策者，负责整体任务的执行</font>
+ <font style="color:rgb(1, 1, 1);">Microagent是小型的、专门化的代理，用于处理特定子任务或提供特定功能</font>
+ <font style="color:rgb(1, 1, 1);">Agent可以调用Microagent，但Microagent不能直接调用Agent</font>

<font style="color:black;">具体实现方式：</font>

+ <font style="color:rgb(1, 1, 1);">Microagent被加载到Memory中，作为工具提供给Agent使用</font>
+ <font style="color:rgb(1, 1, 1);">在openhands/server/session/agent_session.py中，可以看到microagents通过get_microagents_from_selected_repo方法加载，并通过memory.load_user_workspace_microagents添加到内存中</font>
+ <font style="color:rgb(1, 1, 1);">Agent可以在需要时调用这些microagents来执行特定任务</font>

<font style="color:black;">两种类型的Microagents：</font>

+ <font style="color:rgb(1, 1, 1);">Repo Agents：针对特定仓库的代理，处理与该仓库相关的任务</font>
+ <font style="color:rgb(1, 1, 1);">KnowledgeAgents：提供特定领域知识的代理</font>

<font style="color:black;">工作流程：</font>

+ <font style="color:rgb(1, 1, 1);">Agent在执行任务时，可以决定是否需要调用某个Microagent</font>
+ <font style="color:rgb(1, 1, 1);">Microagent执行完任务后，将结果返回给Agent</font>
+ <font style="color:rgb(1, 1, 1);">Agent根据Microagent的输出继续执行后续操作</font>

<font style="color:black;">加载机制：</font>

+ <font style="color:rgb(1, 1, 1);">Microagents可以从多个位置加载： 从选定的仓库中的.openhands/microagents目录</font>
+ <font style="color:rgb(1, 1, 1);">从组织/用户级别的仓库（例如github.com/acme-co/.openhands/microagents）</font>

<font style="color:black;">因此，这是一种层级型的合作模式，其中Agent作为主控制器，Microagent作为专门的助手提供特定功能，两者之间不是对等的网络型关系，也不是监督者与被监督者的关系。</font>

###### Workflow
<font style="color:black;">主 - 子 Agent 交互与控制流程图</font>

```python
+-----------------------------------------------------------+
|                    主 AgentController                     |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|            主 Agent 生成 AgentDelegateAction              |
|          （含子智能体名称、任务参数、上下文）             |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                 调用 start_delegate() 方法                |
|  - 初始化子控制器（is_delegate=True）                     |
|  - 分配独立状态（迭代次数、预算、上下文）                 |
|  - 继承主控制器资源（事件流、文件存储）                   |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------------------------------------+
|                      子智能体独立运行                     |
|  - 主控制器转发所有事件给子控制器                         |
|  - 子智能体执行任务，无需主 Agent 干预                    |
+--------------+--------------+--------------+--------------+
               |              |              |
               v              v              v
        +------+------+ +------+------+ +------+------+
        | 子智能体完成 | | 子智能体拒绝 | | 子智能体出错 |
        | (FINISHED)   | | (REJECTED)   | | (ERROR)      |
        +------+------+ +------+------+ +------+------+
               |              |              |
               +--------------+--------------+
                              |
                              v
+-----------------------------+-----------------------------+
|                  调用 end_delegate() 方法                 |
|  - 终止子智能体，回收资源                                 |
|  - 接收子智能体输出结果                                   |
|  - 封装为 AgentDelegateObservation 事件                   |
+-----------------------------+-----------------------------+
                              |
                              v
+-----------------------------+-----------------------------+
|               主 Agent 处理子智能体结果                   |
|  - 基于结果继续执行主任务                                 |
+-----------------------------------------------------------+
```

<font style="color:black;">AgentController 核心事件处理流程图</font>

```python

```

##### Codes
###### 调用大模型
```python
class CodeActAgent(Agent):
    def step(self, state: State) -> 'Action':
        """Performs one step using the CodeAct Agent."""
        initial_user_message = self._get_initial_user_message(state.history)
        messages = self._get_messages(condensed_history, initial_user_message)
        params: dict = {
            'messages': messages,
        }
        params['tools'] = check_tools(self.tools, self.llm.config)
        params['extra_body'] = {
            'metadata': state.to_llm_metadata(
                model_name=self.llm.config.model, agent_name=self.name
            )
        }
        response = self.llm.completion(**params)
        actions = self.response_to_actions(response) # 在这里处理返回值
        for action in actions:
            self.pending_actions.append(action)
        return self.pending_actions.popleft()
```

###### 解析
<font style="color:rgb(0, 0, 0);">如果发现需要调用 delegate_to_browsing_agent，则生成一个 AgentDelegateAction。</font>

```python
def response_to_actions(
    response: ModelResponse, mcp_tool_names: list[str] | None = None
) -> list[Action]:
            # ================================================
            # AgentDelegateAction (Delegation to another agent)
            # ================================================
            elif tool_call.function.name == 'delegate_to_browsing_agent':
                action = AgentDelegateAction(
                    agent='BrowsingAgent',
                    inputs=arguments,
                )
```

###### 执行
<font style="color:rgb(0, 0, 0);">AgentController 中会处理AgentDelegateAction，执行microAgent。</font>

```python
    async def start_delegate(self, action: AgentDelegateAction) -> None:
        """启动委托智能体以处理子任务。

        OpenHands 是多智能体系统：
        - 「任务（task）」：系统与用户之间的完整对话，始于用户初始输入（通常是任务描述），
          终于智能体发起的完成动作、用户停止操作或错误触发。
        - 「子任务（subtask）」：智能体与用户或其他智能体之间的对话。
          若单个智能体即可完成任务，则任务与子任务合一；否则任务由多个子任务组成，每个子任务由独立智能体处理。

        参数：
            action (AgentDelegateAction)：包含待启动委托智能体信息的动作对象
        """
        # 根据动作中指定的智能体名称，获取对应的智能体类
        agent_cls: Type[Agent] = Agent.get_cls(action.agent)
        # 获取智能体配置：优先使用动作指定的配置，未指定则复用当前智能体的配置
        agent_config = self.agent_configs.get(action.agent, self.agent.config)
        # 创建委托智能体实例（确保父子智能体共享LLM注册信息）
        # 注：父子智能体共享指标，实现全局指标累积
        delegate_agent = agent_cls(
            config=agent_config, llm_registry=self.agent.llm_registry
        )

        # 启动委托智能体前，创建初始状态（继承父智能体关键配置）
        state = State(
            session_id=self.id.removesuffix('-delegate'),  # 会话ID：移除父智能体的委托后缀
            user_id=self.user_id,  # 继承用户ID，保持用户关联
            inputs=action.inputs or {},  # 子任务输入参数（默认为空字典）
            iteration_flag=self.state.iteration_flag,  # 继承迭代控制标志（限制迭代次数）
            budget_flag=self.state.budget_flag,  # 继承预算控制标志（限制资源使用）
            delegate_level=self.state.delegate_level + 1,  # 委托层级+1（标识子智能体层级）
            metrics=self.state.metrics,  # 共享全局指标（父子智能体指标统一累积）
            start_id=self.event_stream.get_latest_event_id() + 1,  # 事件起始ID：从最新事件后开始记录
            parent_metrics_snapshot=self.state_tracker.get_metrics_snapshot(),  # 父智能体指标快照（用于后续对比）
            parent_iteration=self.state.iteration_flag.current_value,  # 父智能体当前迭代次数
        )
        # 输出调试日志：记录委托智能体启动信息
        self.log(
            'debug',
            f'start delegate, creating agent {delegate_agent.name}',
        )

        # 创建委托智能体的控制器（核心：标记is_delegate=True，避免直接订阅事件流）
        self.delegate = AgentController(
            sid=self.id + '-delegate',  # 会话ID：在父ID后添加委托后缀，唯一标识
            file_store=self.file_store,  # 继承文件存储对象（用于状态持久化）
            user_id=self.user_id,  # 继承用户ID
            agent=delegate_agent,  # 待管理的委托智能体实例
            event_stream=self.event_stream,  # 共享事件流（父子智能体事件互通）
            conversation_stats=self.conversation_stats,  # 继承对话统计信息
            iteration_delta=self._initial_max_iterations,  # 迭代次数增量（子任务的最大迭代限制）
            budget_per_task_delta=self._initial_max_budget_per_task,  # 单任务预算增量（子任务的资源限制）
            agent_to_llm_config=self.agent_to_llm_config,  # 继承LLM配置映射
            agent_configs=self.agent_configs,  # 继承智能体配置字典
            initial_state=state,  # 初始状态（继承父智能体配置后的状态）
            is_delegate=True,  # 标记为委托智能体（关键：避免重复订阅事件流）
            headless_mode=self.headless_mode,  # 继承无头模式（无交互界面）配置
            security_analyzer=self.security_analyzer,  # 继承安全分析器（用于安全校验）
        )

```

###### Microagents记忆提示模版
<font style="color:rgb(0, 0, 0);">openhands/microagent/prompts/generate_remember_prompt.j2 是一个 Jinja2 模板文件，其主要作用是生成用于更新特殊参考文件的提示语。这个特殊文件存储着重要的信息和学习成果，用于执行特定任务，并且可以在时间推移过程中扩展以纳入新知识和经验。</font>

<font style="color:black;">核心功能</font>

+ **<font style="color:rgb(1, 1, 1);">事件分析：分析提供给它的新事件子集</font>**
+ **<font style="color:rgb(1, 1, 1);">更新决策：确定是否需要对特殊参考文件进行更新</font>**
+ **<font style="color:rgb(1, 1, 1);">提示生成：生成指导另一个 AI 正确高效地进行这些更新的提示语</font>**

<font style="color:black;">处理流程</font>

+ <font style="color:rgb(1, 1, 1);">接收事件数据：通过 {{ events }} 变量接收待分析的事件</font>
+ <font style="color:rgb(1, 1, 1);">内容分析：分析这些事件以确定需要更新文件的哪些部分</font>
+ <font style="color:rgb(1, 1, 1);">生成更新指令：创建一个结构化的提示，包含具体的更新说明</font>

<font style="color:black;">指导原则</font>

<font style="color:black;">根据模板内容，生成的提示必须遵循以下准则：</font>

<font style="color:black;">内容要求</font>

+ <font style="color:rgb(1, 1, 1);">清晰指定：明确指出文件的哪些部分需要更新或添加新章节</font>
+ <font style="color:rgb(1, 1, 1);">提供上下文：解释基于新事件为什么需要这些更新</font>
+ <font style="color:rgb(1, 1, 1);">具体信息：精确说明应添加或修改的信息内容</font>

<font style="color:black;">格式要求</font>

+ <font style="color:rgb(1, 1, 1);">保持结构：维持文件现有的结构和格式</font>
+ <font style="color:rgb(1, 1, 1);">保持一致性：确保更新与现有内容一致，不产生矛盾</font>

<font style="color:black;">技术实现</font>

<font style="color:black;">模板结构</font>

<font style="color:black;">jinja2</font><font style="color:black;"><update_prompt></update_prompt></font>

<font style="color:black;">数据流</font>

+ <font style="color:rgb(1, 1, 1);">输入：通过 events 变量传入的新事件数据</font>
+ <font style="color:rgb(1, 1, 1);">处理：模板逻辑分析事件并生成更新提示</font>
+ <font style="color:rgb(1, 1, 1);">输出：包含在 <update_prompt> 标签内的生成提示</font>

<font style="color:black;">应用场景</font>

<font style="color:black;">这个模板主要用于：</font>

<font style="color:black;">记忆维护</font>

+ <font style="color:rgb(1, 1, 1);">在 AI 执行任务过程中，持续更新重要知识库</font>
+ <font style="color:rgb(1, 1, 1);">确保系统能从新经验中学习并改进</font>

<font style="color:black;">自动化更新</font>

+ <font style="color:rgb(1, 1, 1);">使 AI 能够自动维护自己的知识基础</font>
+ <font style="color:rgb(1, 1, 1);">减少手动更新参考文件的需求</font>

<font style="color:black;">与其他组件的关系</font>

<font style="color:black;">与微代理系统集成</font>

+ <font style="color:rgb(1, 1, 1);">作为 Microagent 系统的一部分，支持知识的动态更新</font>
+ <font style="color:rgb(1, 1, 1);">与 KnowledgeMicroagent 和 RepoMicroagent 配合工作</font>

<font style="color:black;">与事件系统连接</font>

+ <font style="color:rgb(1, 1, 1);">利用事件系统（EventStream）收集需要学习的事件</font>
+ <font style="color:rgb(1, 1, 1);">与 AgentController 协同工作以维护状态和历史记录</font>

<font style="color:black;">这个模板是 OpenHands 系统中实现持续学习和知识管理的关键组件，允许 AI 系统从交互中学习并将这些知识持久化到参考文件中。</font>

###### <font style="color:black;">get_prompt函数</font>
<font style="color:rgb(0, 0, 0);">get_prompt 函数是一个 FastAPI 路由处理器，位于 /openhands/server/routes/manage_conversations.py 文件中，路径为 /conversations/{conversation_id}/remember-prompt。其主要作用是基于特定事件生成一个提示模板，用于更新特殊参考文件。这个函数是 OpenHands 系统中实现持续学习和知识管理的关键组件之一，它使得 AI 系统能够从对话历史中的特定事件生成更新提示，从而维护和扩展其知识库。</font>

<font style="color:black;">参数处理</font>

+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">conversation_id</font>`<font style="color:rgb(1, 1, 1);">：通过依赖注入验证的对话 ID</font>
+ `<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">event_id</font>`<font style="color:rgb(1, 1, 1);">：查询参数，指定要从中获取上下文文件的事件 ID</font>
+ <font style="color:rgb(1, 1, 1);">其他依赖：用户设置存储、对话元数据等</font>

<font style="color:black;">核心处理步骤</font>

<font style="color:black;">获取事件存储</font>

```plain
event_store = EventStore(
    sid=conversation_id, file_store=file_store, user_id=metadata.user_id
)
```

<font style="color:rgb(0, 0, 0);">创建一个事件存储实例来访问特定对话的事件历史。</font>

<font style="color:black;">提取上下文事件</font>

<font style="color:black;">调用 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">_get_contextual_events(event_store, event_id)</font>`<font style="color:black;"> 方法：</font>

+ <font style="color:rgb(1, 1, 1);">获取目标事件前后各 4 个事件（总共约 9 个事件）</font>
+ <font style="color:rgb(1, 1, 1);">过滤掉无意义的事件类型（如 NullAction、NullObservation 等）</font>
+ <font style="color:rgb(1, 1, 1);">返回格式化的事件字符串</font>

**<font style="color:black;">生成提示模板</font>**

+ <font style="color:rgb(1, 1, 1);">从用户设置中加载 LLM 配置</font>
+ <font style="color:rgb(1, 1, 1);">使用 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">generate_prompt_template</font>`<font style="color:rgb(1, 1, 1);"> 函数基于事件内容生成提示模板</font>
+ <font style="color:rgb(1, 1, 1);">模板使用 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">generate_remember_prompt.j2</font>`<font style="color:rgb(1, 1, 1);"> Jinja2 模板</font>

**<font style="color:black;">生成最终提示</font>**

+ <font style="color:rgb(1, 1, 1);">通过 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">generate_prompt</font>`<font style="color:rgb(1, 1, 1);"> 函数调用 LLM 生成最终提示</font>
+ <font style="color:rgb(1, 1, 1);">从 LLM 响应中提取 `` 标签之间的内容</font>

<font style="color:black;">与系统其他组件的关系</font>

<font style="color:black;">模板系统</font>

+ <font style="color:rgb(1, 1, 1);">使用 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">generate_remember_prompt.j2</font>`<font style="color:rgb(1, 1, 1);"> 模板（位于 </font>`<font style="color:rgb(30, 107, 184);background-color:rgba(27, 31, 35, 0.05);">/openhands/microagent/prompts/</font>`<font style="color:rgb(1, 1, 1);"> 目录）</font>
+ <font style="color:rgb(1, 1, 1);">该模板专门用于生成更新特殊参考文件的提示</font>

<font style="color:black;">事件系统</font>

+ <font style="color:black;">与 EventStore 和事件过滤系统集成 利用 EventFilter 来筛选相关事件</font>
+ <font style="color:black;">与 conversation_manager 集成以请求 LLM 完成</font>

<font style="color:black;">应用场景</font>

<font style="color:black;">这个函数主要用于：</font>

+ <font style="color:rgb(1, 1, 1);">记忆维护：生成用于更新 AI 记忆文件的提示</font>
+ <font style="color:rgb(1, 1, 1);">知识积累：基于特定事件序列构建知识更新</font>
+ <font style="color:rgb(1, 1, 1);">自动化学习：允许 AI 从交互中学习并更新其参考知识</font>

<font style="color:black;">返回值</font>

<font style="color:black;">返回一个 JSON 响应，包含：</font>

+ <font style="color:rgb(1, 1, 1);">status：请求状态（成功/失败）</font>
+ <font style="color:rgb(1, 1, 1);">prompt：生成的提示内容，可用于更新特殊参考文件</font>

<font style="color:rgb(0, 0, 0);">

</font>
