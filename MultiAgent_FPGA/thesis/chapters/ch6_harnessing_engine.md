# 第六章 Harnessing Engine：LLM约束引擎设计

## 6.1 Harnessing Engine概念与架构

### 6.1.1 问题定义：LLM在硬件设计中的失败模式

大语言模型在硬件设计任务中展现出令人期待的代码生成能力，但同时暴露出若干系统性失败模式，这些失败模式在FPGA RTL生成场景中尤为突出：

**失败模式一：幻觉端口/信号**。LLM在生成Verilog代码时，可能凭借训练数据中的统计模式"自行发明"实际不存在的端口（如将`key_in`改写为`key_data`），或在例化子模块时连接错误的端口名称。由于Verilog对未声明信号有时会静默警告而非报错，这类错误可能通过编译但在仿真阶段才暴露。

**失败模式二：语法错误**。LLM生成的Verilog代码有时包含非法语法结构，如在`always`块中混用阻塞/非阻塞赋值、在组合逻辑中使用时序敏感列表错误、参数化语法不兼容等。这类错误通常在L0编译门控阶段即可捕获，但若Agent仅修改部分代码而引入新的语法问题，则可能形成"修复一处、引入两处"的循环。

**失败模式三：Scope drift（范围漂移）**。Agent在修复单个模块问题时，可能"顺手"修改了其他模块的接口定义或共享头文件，破坏模块间的已冻结接口契约。这类问题在单模块测试中不可见，只有在集成阶段才会暴露。

**失败模式四：过度修改**。修复Agent面对一个编译错误时，可能大幅重写整个模块而非进行最小化修复，将原本正确的逻辑也一并破坏。这种"推倒重来"模式缺乏收敛保证，可能导致验证状态在REPAIRING和L0_FAIL之间无限循环。

**失败模式五：格式错误**。LLM可能输出Markdown代码块包裹的Verilog代码、在RTL文件中夹杂自然语言解释、或将完整JSON文件内容逐字输出到对话中，破坏文件格式和上下文效率。

### 6.1.2 Harnessing Engine设计理念

针对上述失败模式，本文提出"Harnessing Engine"（驾驭引擎）概念。其核心设计理念是：**不依赖LLM自律，通过结构化的外部约束从六个层面系统性地驾驭LLM行为**。

"Harnessing"（驾驭）一词的选择具有深刻的工程意涵：驾驭不是压制，而是通过设计良好的约束结构，引导LLM的能力在期望的范围内发挥作用。如同马具（harness）不限制马的力量，而是引导其方向，Harnessing Engine不试图消除LLM的创造性，而是通过六层约束确保这种创造性不会越出工程规约的边界。

Harnessing Engine的六层约束从架构上形成了一个完整的防御体系：

[图6-1: Harnessing Engine六层架构图（从Skill领域知识注入到SlashCommand用户接口）]

六层约束的分工如下表所示：

[表6-1: LLM失败模式-约束层级防御矩阵（详见6.8节）]

---

## 6.2 Skill层：领域知识注入

### 6.2.1 三级Skill注册体系

本系统构建了由16个Skill文件组成的三级注册体系，通过`skill_refs.py`统一管理。三级注册体系的分工严格区分了运行时注入与离线参考的职责：

**运行时Skill（Runtime Skills，5个）**：通过`get_runtime_skill_refs()`（`aes_mvp/skill_refs.py:22-51`）获取，直接注入到Agent的系统提示词中，在运行时作为硬约束约束Agent行为：

| Skill键 | 名称 | 用途 |
|---------|------|------|
| `aes_verilator_profile` | aes-verilator-profile | AES节点分类、向量、Checkpoint、L2约定 |
| `aes_module_patterns` | aes-module-patterns | S-box、密钥扩展、轮变换、顶层集成的参考模式 |
| `aes_tb_contracts` | aes-tb-contracts | 自检C++ Testbench契约、向量和Checkpoint语义 |
| `aes_repair_heuristics` | aes-repair-heuristics | 编译/Checkpoint/延迟/握手失败的修复启发式规则 |
| `openhands_sdk_subagent_delegation` | openhands-sdk-subagent-delegation | 子Agent注册、spawn、委派和任务边界规则 |

**内存Skill（Memory Skills，5个）**：通过`get_memory_skill_refs()`（`aes_mvp/skill_refs.py:54-83`）获取，由`MemoryStore`管理，包含验证通过的AES参考RTL代码，用于工作区预填充：

| Skill键 | 对应模块 | 内容 |
|---------|---------|------|
| `aes_memory_sbox` | aes_sbox | 验证通过的S-box RTL+TB参考实现 |
| `aes_memory_key_schedule` | aes_key_schedule_128 | 验证通过的密钥扩展RTL+TB参考实现 |
| `aes_memory_round_transform` | aes_round_transform | 验证通过的轮变换RTL+TB参考实现 |
| `aes_memory_encrypt_core` | aes128_encrypt_core | 验证通过的顶层加密核RTL+TB参考实现 |
| `aes_memory_shared` | 公共 | aes_sbox_lut.vh + aes_tb_common.hpp上下文 |

**文档Skill（Documentation Skills，6个）**：通过`get_documentation_skill_refs()`（`aes_mvp/skill_refs.py:86-120`）获取，供`synthesis.py`中的`ModuleDesignBrief`生成使用，不注入Agent运行时提示词。

[表6-2: 16个Skill文件分类表（名称、类型、用途）]

### 6.2.2 Skill分组与按角色注入

Skill按Agent角色分组，实现精准注入。`WORKER_FPGA_CORE_SKILL_KEYS`（`aes_mvp/skill_refs.py:158-163`）包含3个核心Worker技能；`REPAIR_CORE_SKILL_KEYS`仅包含`aes_repair_heuristics`；`ORCHESTRATOR_CORE_SKILL_KEYS`仅包含`aes_verilator_profile`。

`select_worker_skill_keys(active_mode)`函数根据当前工作模式动态选择技能子集：generate模式使用`WORKER_FPGA_CORE_SKILL_KEYS`，repair模式使用`REPAIR_CORE_SKILL_KEYS`，l2_execute模式使用`L2_WORKER_SKILL_KEYS`（仅`aes_verilator_profile`）。这一按模式精准注入的设计减少了提示词的冗余信息，降低了LLM"混淆技能"的可能性。

### 6.2.3 SKILLS_AS_AUTHORITY_CONTRACT

`SKILLS_AS_AUTHORITY_CONTRACT`（`aes_mvp/prompt_contracts.py:72-77`）是Skill层的元约束：

```
Repository skills are the authority for FPGA, Verilator, and SDK policy;
do not paraphrase or restate them.
```

这一约束明确告知Agent：Skill文件是工程策略的权威来源，Agent不得根据自身训练数据"推断"或"改写"技能内容。与胡昆越AutoGen方案的对比：该方案仅有`system_message`中的纯文本指令，无结构化技能体系，Agent可能基于通用训练数据"自行推断"HDL设计规则，而这些推断与项目规约可能存在偏差。

---

## 6.3 Prompt层：行为约束合成

### 6.3.1 可组合Prompt架构

本系统的提示词不是单一的静态字符串，而是通过`compose_prompt()`函数（`aes_mvp/prompt_contracts.py:32-49`）将四层组件动态组合而成：

```python
def compose_prompt(
    role_intro: str,
    *,
    base_contracts: Iterable[BaseContract],
    phase_mixins: Iterable[PhaseMixin] = (),
    instance_payload: InstancePayload | None = None,
    skill_block: str | None = None,
) -> str:
```

四层组件的职责划分如下：

[图6-2: Prompt合成流程图（角色引言 → BaseContract硬约束 → PhaseMixin阶段约束 → InstancePayload实例负载 → SkillBlock技能块）]

**第一层：角色引言（role_intro）**：声明Agent的身份和职责范围，如`You are the Module Worker SubAgent for aes_sbox.`，确立了任务局部性。

**第二层：基础合约（BaseContract）**：硬约束集合，在所有工作模式下均有效，不可覆盖。5个核心BaseContract的约束维度各异：

| BaseContract | 约束维度 | 核心条款 |
|------------|---------|---------|
| AES_SCOPE_CONTRACT | 范围锁定 | AES-128加密专用，encrypt-only，block-handshake |
| STRUCTURED_IO_CONTRACT | IO规范 | 以契约JSON为信息源，禁止cat完整大型JSON文件 |
| NO_RAW_VERILATOR_CONTRACT | 工具隔离 | 禁止直接调用verilator_compile或verilator_simulate |
| FRAMEWORK_OWNS_PROGRESS_CONTRACT | 控制权归属 | 框架而非Agent拥有批次推进和工作流完成权 |
| SKILLS_AS_AUTHORITY_CONTRACT | 权威源 | Skill文件是FPGA/Verilator/SDK策略的权威 |

**第三层：阶段混入（PhaseMixin）**：针对当前执行阶段的补充约束，随工作模式动态切换。例如，`REPAIR_PHASE_ROUND_1`要求"第一个工具调用必须是对primary_target_file的file_editor edit"，强制Agent先编辑后验证，防止无效的信息收集操作浪费修复轮次预算。

**第四层：实例负载（InstancePayload）**：当前任务的具体参数，如可写文件列表、Campaign参数、特殊行为注记等。

### 6.3.2 PhaseMixin的阶段适配机制

`_select_phase_mixins(active_mode)`函数（`aes_mvp/prompts.py:89-108`）根据当前工作模式选择阶段混入组合：

- `generate`模式：加入`GENERATE_PHASE`和`MEMORY_CONSULTATION_DIRECTIVE`
- `repair_round_1`：加入`REPAIR_PHASE_ROUND_1`（编辑优先协议）
- `repair_round_2+`：加入`REPAIR_PHASE_ROUND_2_PLUS`（允许先查看文件当前状态）
- `validate`模式：加入`VALIDATE_PHASE`（读多写少）
- `l2_execute`模式：加入`L2_PHASE`（禁止RTL/TB编辑）

`REPAIR_PHASE_ROUND_1`与`REPAIR_PHASE_ROUND_2_PLUS`的区别体现了对修复过程的精细控制：第一轮修复时，Agent应直接基于`repair_request.json`中的`primary_file_excerpt`和`first_edit_steps`进行编辑，不需要重新阅读文件（内容已在修复请求中提供）；第二轮及后续轮次，先前的编辑可能改变了文件状态，Agent需要先查看当前文件状态再进行针对性修复。

### 6.3.3 典型反幻觉指令

Prompt层包含若干针对特定幻觉模式的反幻觉指令：

- `"Never cat whole large JSON files; use bounded reads only"` — 防止Agent将整个工作区JSON文件内容输出到对话，导致上下文溢出
- `"first tool call MUST be a file_editor edit on primary_target_file"` — 防止修复Agent在预算有限的情况下浪费调用次数在信息收集上
- `"Do not change cross-module architecture, frozen interfaces, or integration policy"` — 防止Scope drift
- `"Do not broadly scan unrelated paths before consulting the task contract"` — 防止Agent在任务开始时进行无边界的文件系统探索

---

## 6.4 Memory层：验证代码预填充

### 6.4.1 MemoryStore核心机制

`MemoryStore`（`aes_mvp/memory.py:57-174`）是AES参考内存检索的单一信息源，封装了从Skill文件中提取验证通过代码的完整逻辑。其核心注册表为`_MEMORY_REGISTRY`（`aes_mvp/memory.py:18-23`）：

```python
_MEMORY_REGISTRY: dict[str, str] = {
    'aes_sbox': 'aes_memory_sbox',
    'aes_key_schedule_128': 'aes_memory_key_schedule',
    'aes_round_transform': 'aes_memory_round_transform',
    'aes128_encrypt_core': 'aes_memory_encrypt_core',
}
```

每个`module_id`映射到对应的内存Skill键，Skill文件中包含经过Verilator验证的RTL Verilog和C++ Testbench代码，通过Markdown代码块（````verilog`和````cpp`）标记。`_extract_code_block()`函数（`aes_mvp/memory.py:39-44`）使用正则表达式提取特定语言的代码块内容。

### 6.4.2 两种使用模式

Memory层提供两种互补的使用模式：

**`populate_workspace()`**（`aes_mvp/memory.py:114-159`）：生成模式。将参考代码写入工作区`draft/rtl/<module_id>.v`和`draft/tb/<module_id>_tb.cpp`文件。写入采用"仅在不存在时写入"的策略（`if not rtl_path.exists(): rtl_path.write_text(...)`），防止覆盖Agent已进行的修改。若内存提取失败（RTL或TB为None），则抛出`RuntimeError`，这是一个硬错误——框架不允许在无参考实现的情况下进入生成阶段。

**`build_prompt_block()`**（`aes_mvp/memory.py:97-112`）：提示词注入模式。将参考代码以`=== MEMORY: <name> ===`块的形式直接注入Agent系统提示词，使Agent在生成模式下能够"看到"参考实现：

```
=== MEMORY: aes-memory-sbox ===
[skill文件内容，含验证通过的Verilog和C++代码]
=== END MEMORY ===
```

这一设计的核心洞察是：**将Agent的任务从"从零生成正确代码"降级为"基于参考实现解决集成问题"**。从零生成正确的AES RTL代码需要LLM同时掌握AES算法、Verilog语法、Verilator兼容性规约和Checkpoint协议，任何一项理解偏差都会导致失败。而基于参考实现进行适应性修改，Agent只需关注当前任务的具体差异，显著降低了出错概率。

### 6.4.3 MEMORY_CONSULTATION_DIRECTIVE与REPAIR_MEMORY_DIRECTIVE的区分

两个Memory相关的PhaseMixin体现了不同阶段的内存使用策略：

`MEMORY_CONSULTATION_DIRECTIVE`（`aes_mvp/prompt_contracts.py:185-194`）用于generate/validate模式：

```
Your workspace draft files are pre-populated from verified AES reference memory.
The === MEMORY === blocks in your system prompt contain the same code that was
written to your draft files. The reference code passes all Verilator checkpoints.
You may reproduce it verbatim or adapt it.
```

`REPAIR_MEMORY_DIRECTIVE`（`aes_mvp/prompt_contracts.py:196-204`）用于repair模式：

```
Your workspace draft files were originally pre-populated from verified AES reference
memory. The on-disk draft files are the current truth — they may have been modified
by prior repair rounds. Do not assume the original reference memory matches the
current file state. Always read the actual file before editing.
```

这一区分防止了修复Agent基于"记忆中的参考实现"而非"磁盘上的当前状态"进行修复，避免了修复轮次之间状态不一致的问题。

---

## 6.5 Hooks层：执行回调与门控

### 6.5.1 run_executor自定义工具

`run_executor`（`aes_mvp/runtime/execution_tools.py:30-147`）是本系统最重要的约束机制之一，也是Agent触发框架执行动作的唯一合法入口。其设计核心是：**通过单一受控工具替代多个原始工具，在Agent和底层EDA工具之间建立强制性的代理层**。

`run_executor`的执行流程：

1. Agent调用`run_executor(request_path=<task_contract.json>)`
2. `_load_task_contract()`从路径读取并验证任务合约JSON（`DelegateBatchTask` Pydantic模型）
3. `_infer_executor_kind()`根据任务模式推断执行器类型（GENERATE_NODE、RUN_NODE、RECORD_REPAIR_EDIT）
4. 调度对应的执行器（`L0Executor`、`L1Executor`、`L2CampaignExecutor`、`IntegrationRegressionExecutor`）
5. 返回`RunExecutorObservation`，包含执行状态、结果路径和下一步读取提示

### 6.5.2 RunExecutorObservation的引导性设计

`RunExecutorObservation`（`aes_mvp/runtime/execution_tools.py:39-116`）不仅是执行结果的载体，还是Agent下一步行为的引导者。`next_read_paths`字段明确告知Agent执行结束后应读取哪些文件；`next_read_hints`中的`NextReadHints`包含`action`（READ_ARTIFACTS、EDIT_PRIMARY_TARGET、WAIT_FOR_NEXT_BATCH、ESCALATE_TO_ORCHESTRATOR）和`reason`字段，将框架的判断意图以结构化方式传达给Agent。

这一设计的意义在于：Agent接收到`run_executor`的返回值后，不需要根据自身判断决定下一步查看什么文件或采取什么行动，而是遵循框架通过`next_read_hints`提供的明确指示，大幅减少了Agent决策的不确定性。

### 6.5.3 verify_repair_edit哈希验证

`verify_repair_edit()`（`aes_mvp/generation.py:680-735`）是Hooks层的另一核心机制，用于机器化验证修复编辑的真实性。其验证逻辑包含两个独立条件：

**条件一：文件哈希变化验证**。框架在写入修复请求前记录`primary_target_file`的SHA256哈希值（存入`repair_contract.edit_verification['baseline_hashes']`），修复后对比当前哈希。若哈希未变化，说明Agent声称已修复但实际未修改文件，验证失败并拒绝推进至重新验证阶段。

**条件二：必要Token存在验证**。`repair_contract.must_add_tokens`列出修复后文件必须包含的token（如`CHECKPOINT|CHK_XXX|PASS|`），框架验证这些token确实出现在修改后的文件中。验证器还接受等价形式：若token以`CHECKPOINT|`开头，则`emit_checkpoint("CHK_XXX", ...)`调用也被视为满足要求。

这一双重验证机制彻底消除了Agent"虚假声称修复成功"的可能性——没有真实的文件修改和必要代码的添加，框架不会进入重新验证阶段。

### 6.5.4 Batch Gate回调机制

框架通过文件系统轮询实现Batch Gate，将文件系统作为Agent和框架之间的通信通道：Agent将执行结果写入工作区文件（如`validation_summary.json`、`module_run_result.json`），框架的`run_current_batch_until_gate()`定期轮询这些文件，判断批次完成条件。当所有节点均有结果文件产生且状态满足门控条件时，框架结束当前批次，推进到下一状态。

---

## 6.6 MCP层：工具能力供给

### 6.6.1 Model Context Protocol的角色

Model Context Protocol（MCP）是AI Agent与外部工具之间的标准化通信协议。在本系统中，MCP承担着连接LLM Agent与Verilator EDA工具链的桥梁角色，将复杂的Verilator命令行接口封装为Agent可调用的结构化工具接口。

[图6-3: MCP通信架构图（Agent → run_executor → VerilatorMCPAdapter → MCP stdio协议 → verilator-mcp Node.js进程 → Verilator可执行文件）]

### 6.6.2 VerilatorMCPAdapter封装细节

`VerilatorMCPAdapter`（`aes_mvp/adapters/verilator.py:122-216`）封装了所有与Verilator MCP服务器的通信细节，对上层执行器（L0/L1/L2/Integration Executor）提供简洁的`compile()`和`simulate()`异步接口。其关键封装逻辑包括：

**输入文件过滤**：`_filter_verilator_input_files()`（`aes_mvp/adapters/verilator.py:81-91`）过滤掉目录路径和非标准扩展名文件，只保留`.v`/`.sv`（Verilog源文件）和`.cpp`/`.cc`/`.cxx`（C++ Testbench）。这防止了Agent传入不合法文件路径导致Verilator报错。

**include标志自动生成**：`_verilog_include_directories()`自动提取Verilog源文件的父目录，生成`-I/path/to/rtl`格式的include标志，确保`` `include "aes_sbox_lut.vh" ``等头文件引用能够正确解析。

**C++17标准自动添加**：当编译文件列表中包含C++源文件时，自动在`verilatorFlags`中添加`-CFLAGS -std=c++17`，无需Agent手动指定编译选项。

**plusargs传递**：`aes_mvp_package_root`等运行时参数通过Verilator plusargs机制传递给Testbench，Testbench通过`resolve_path(argc, argv, requested, fallback)`函数读取，实现了向量文件的路径无关解析。

### 6.6.3 MCP工具过滤：防止Agent绕过框架

`build_verilator_stdio_server()`（`aes_mvp/adapters/verilator.py:43-74`）配置MCP服务器时，框架在更高层（`SdkAgentFactory`）过滤掉两个MCP工具：`verilator_testbenchgenerator`和`verilator_naturallanguage`。这一过滤的设计意图是：

- **禁用testbenchgenerator**：防止Agent绕过框架的C++自检Testbench体系，使用自动生成的Testbench（自动Testbench无法实现Checkpoint协议）
- **禁用naturallanguage**：防止Agent以自然语言描述方式调用Verilator，绕过框架的结构化执行路径

这两个工具的禁用体现了MCP层的核心约束原则：Agent只能使用框架明确授权的工具子集，任何可能绕过约束体系的工具入口均被封闭。

---

## 6.7 SlashCommand层：用户交互接口

### 6.7.1 CLI命令体系

`__main__.py`（`aes_mvp/__main__.py`）实现了完整的CLI命令体系，每个命令对应一套完整的验证/执行语义：

```bash
python -m MultiAgent_FPGA.aes_mvp validate           # 契约验证（无需API密钥）
python -m MultiAgent_FPGA.aes_mvp smoke-sdk           # SDK烟测
python -m MultiAgent_FPGA.aes_mvp smoke-provider      # DeepSeek API预检
python -m MultiAgent_FPGA.aes_mvp run-node <module>   # 单节点L0+L1验证
python -m MultiAgent_FPGA.aes_mvp generate-node <module>  # 工作区初始化+验证
python -m MultiAgent_FPGA.aes_mvp record-repair-edit <module>  # 记录修复编辑
python -m MultiAgent_FPGA.aes_mvp run-integration     # 集成回归测试
python -m MultiAgent_FPGA.aes_mvp run-aes-mvp         # 全流程自主执行
python -m MultiAgent_FPGA.aes_mvp run-aes-mvp --dry-run  # 干运行（仅规划，不执行）
```

### 6.7.2 命令即合约的设计原则

每个CLI命令背后是完整的语义定义：`run-node`命令不仅调用执行器，还管理工作区状态（初始化、验证、修复预算检查）、生成报告文件、更新工作区记录；`record-repair-edit`命令先运行`verify_repair_edit()`验证修复真实性，再调用`write_edit_receipt()`写入编辑收据，为后续重新验证提供可追溯的审计链。

`--dry-run`选项实现了规划与执行的分离：框架完成全部初始化（bootstrap、SpecIR/PlanDAG/Manifest合成、Policy验证），但仅输出将要执行的批次计划而不实际调用LLM API，供用户在正式运行前检查执行策略。

---

## 6.8 六层协同：约束覆盖矩阵

### 6.8.1 LLM失败模式-约束层级防御矩阵

六层约束并非相互独立，而是形成了对LLM失败模式的多层防御体系。下表展示了每种失败模式由哪些约束层级防御：

[表6-3: LLM失败模式-约束层级防御矩阵]

| 失败模式 | Skill层 | Prompt层 | Memory层 | Hooks层 | MCP层 | SlashCommand层 |
|---------|--------|---------|---------|--------|------|--------------|
| **幻觉端口/信号** | `aes_module_patterns`提供正确端口规范；`aes_verilator_profile`明确模块接口 | `AES_SCOPE_CONTRACT`范围锁定；`WORKER_REQUEST_AUTHORITY`以合约为信息源 | `populate_workspace()`写入正确端口的参考RTL；`build_prompt_block()`内联参考实现 | L0编译门控捕获端口连接错误 | Verilator编译器严格验证端口声明 | `validate`命令预检契约完整性 |
| **语法错误** | `verilog_verilator`提供Verilator合规Verilog规则；`aes_tb_contracts`提供合规TB模式 | `STRUCTURED_IO_CONTRACT`约束输出格式 | 参考实现本身是语法正确的Verilog代码 | L0编译门控精确定位语法错误行；`RunExecutorObservation.next_read_hints`引导读取编译日志 | Verilator编译器是语法权威；自动添加`-CFLAGS -std=c++17` | `run-node`命令明确L0失败含义 |
| **Scope drift** | `openhands_sdk_subagent_delegation`明确任务边界规则 | `WORKER_LOCAL_SCOPE`限制可写范围；`ORCHESTRATOR_ONLY_CURRENT_BATCH`限制批次范围 | `populate_workspace()`只写入当前模块的draft目录 | `run_executor`只接受当前任务合约路径；`verify_repair_edit()`只验证primary_target_file | 工具过滤禁用可能越界的工具 | 每个命令的workspace_root参数限制操作范围 |
| **过度修改** | `aes_repair_heuristics`提供最小化修复启发式规则 | `REPAIR_PHASE_ROUND_1`要求首次编辑仅针对primary_target_file；禁止secondary_target_files的预读 | `REPAIR_MEMORY_DIRECTIVE`要求以磁盘状态为准，不基于记忆重写 | `verify_repair_edit()`双重验证（哈希+token）；修复预算限制（默认2次） | — | `record-repair-edit`命令强制显式编辑记录 |
| **格式错误** | — | `STRUCTURED_IO_CONTRACT`："Never cat whole large JSON files"；以合约JSON为信息源 | 内存注入使用`=== MEMORY ===`块而非原始文件内容 | `RunExecutorObservation.to_llm_content`将执行结果序列化为结构化文本行 | MCP结果通过`_extract_text_from_result()`提取纯文本 | CLI命令输出格式化JSON报告 |

### 6.8.2 一个Module Worker的完整约束链路

以`aes_sbox`模块的generate阶段为例，展示六层约束的协同工作：

1. **Skill层**：Agent系统提示词注入`aes_verilator_profile`、`aes_module_patterns`、`aes_tb_contracts`三个技能文件，Agent获取S-box模块的端口规范、Checkpoint协议规则和Testbench写法规范
2. **Prompt层**：`compose_prompt()`组合`AES_SCOPE_CONTRACT`（范围锁定）、`NO_RAW_VERILATOR_CONTRACT`（工具隔离）、`WORKER_LOCAL_SCOPE`（写作范围限于draft/）、`GENERATE_PHASE`（工作区内生成）、`MEMORY_CONSULTATION_DIRECTIVE`（参考内存为权威）
3. **Memory层**：`MemoryStore.populate_workspace('aes_sbox', workspace_root)`将验证通过的S-box Verilog代码写入`draft/rtl/aes_sbox.v`；`build_prompt_block('aes_sbox')`将参考代码内联到提示词中
4. **Hooks层**：Agent调用`run_executor(request_path=task_contract.json)` → 框架执行L0+L1 → 若L1通过，`RunExecutorObservation`返回`status: passed`；若L0失败，返回`next_read_hints: [action: EDIT_PRIMARY_TARGET, reason: "compile error"]`
5. **MCP层**：`VerilatorMCPAdapter`过滤输入文件，自动生成include标志，调用verilator-mcp的`verilator_compile`和`verilator_simulate`工具
6. **SlashCommand层**：整个过程通过`python -m MultiAgent_FPGA.aes_mvp run-node aes_sbox`触发，命令封装了完整的工作区初始化、执行、报告生成语义

### 6.8.3 与胡昆越方案的约束密度对比

本系统采用六层约束驾驭LLM，而胡昆越AutoGen方案的约束主要集中于单一层（system_message中的自然语言指令）。两种方案的约束密度对比：

| 约束维度 | 本文方案 | 胡昆越方案 |
|---------|--------|---------|
| 领域知识注入 | 16个结构化Skill文件，按角色按阶段精准注入 | system_message中的纯文本描述 |
| 提示词约束 | 5个BaseContract × N个PhaseMixin的可组合结构 | 单一system_message |
| 代码参考 | MemoryStore提供验证通过的参考RTL+TB | 无结构化代码参考 |
| 执行验证 | `verify_repair_edit()`哈希验证；Batch Gate轮询 | 依赖Agent自报告 |
| 工具隔离 | `run_executor`单一入口；MCP工具白名单过滤 | 直接调用Vivado xsim |
| 操作接口 | 9个语义明确的CLI命令 | `human_input_mode="NEVER"`自运行 |

这一对比表明，本系统的约束密度显著高于单层方案，在多个维度形成了对LLM失败模式的冗余防御。Harnessing Engine的价值在于：即使某一层约束被LLM"绕过"（如Agent忽略了某个Prompt约束），其他层的约束仍能将行为控制在可接受范围内，形成了系统级的鲁棒性。

这种多层约束的设计哲学与系统工程中的"深度防御"原则一脉相承：单点约束在面对LLM的随机性和不可预测性时是脆弱的，而多层冗余约束则能在统计意义上保证系统行为的可靠性。
