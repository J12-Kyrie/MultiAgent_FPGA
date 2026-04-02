import os

from autogen import ConversableAgent
from dotenv import load_dotenv

from MultiAgent_FPGA.old_code_autogen.running_vivado import run_vivado
from MultiAgent_FPGA.old_code_autogen.scheme_to_input import change_pattern
from MultiAgent_FPGA.old_code_autogen.verilog_code_writer import (
    testbench_writer,
    writer,
)

load_dotenv()  # 自动加载项目根目录的 .env 文件

API_KEY = os.getenv('MY_API_KEY')
BASE_URL = os.getenv('MY_BASE_URL')

designer_system_message1 = """
你是一个FPGA领域verilog代码设计需求分析的专家。
你的工作是分析用户的设计需求，给出其中需要用verilog来实现的设计方案（基于Vivado）。
你要给出具体的verilog代码，这不是你的工作，你只需要给出方案。
在分析完用户需求之后，若用户的需求不明确，你应该继续向用户询问。
在分析完用户需求之后，若还有需要用户确定的具体的参数，你应该继续向用户询问。
verilog的输入，输出，函数的功能，关键约束是很重要的，你需要确认这些参数。
在你的回答之后，若有需要用户补充内容，如确切的设计需求，参数等，用户会把你的上一个回复的内容和针对你的回复添加的内容输入给你，你需要基于你的上一个回复和用户的添加的内容来生成你的回答
在所有需求和参数确定完成之后，你的回答需要严格遵守格式：‘design scheme：{你的方案}’，除了‘final scheme：{你的方案}’，不要再包含其他文本。在{你的方案}中，只因该包含与设计有关的要素，参数等，需要以设计电路名字为开头，不要给出别的东西（如改进建议，总结，设计过程等），在所有需求确定之前不要输出design scheme，否则程序就结束了。
在你的最终方案中，只需要包含可以用verilog代码完成的部分，不需要包含硬件资源信息、接口数据、所使用的编程工具信息等其他的信息，你的方案不是代码，只是确定完用户需求后的总结。
"""

designer_system_message = """
1.You are an expert in analyzing Verilog code design requirements in the field of FPGA.
2.Your job is to analyze users' design requirements and propose a design scheme that needs to be implemented using Verilog (based on Vivado).
3.Providing the actual Verilog code is not part of your job; you only need to deliver the design scheme.
4.After analyzing the user's requirements, if the requirements are unclear, you should continue asking the user for clarification.
5.If there are specific parameters that still need to be confirmed by the user after your analysis, you should continue to inquire.
6.The inputs, outputs, function descriptions, and key constraints of the Verilog design are very important — you need to confirm these parameters.
7.After your response, if there is any need for user-provided details — such as exact design requirements or parameters — the user will input your previous reply together with the additional information. You should generate your next response based on both your previous reply and the user's additions.
8.Once all requirements and parameters are confirmed, your response must strictly follow the format: ‘design scheme: {your scheme}’.
9.Except for ‘design scheme: {your scheme}’, do not include any other text.
10.Within {your scheme}, include only design-related elements and parameters. The scheme should start with the name of the circuit being designed. Do not provide anything else (e.g., improvement suggestions, summary, or design process).
Do not output the design scheme until all requirements are confirmed — otherwise, the process ends prematurely.
In your final scheme, only include parts that can be implemented using Verilog. Do not include information about hardware resources, interface data, programming tools, or any other unrelated content.
Your scheme is not code, but a finalized summary of the design based on user requirements.
"""

designer = ConversableAgent(
    'designer',
    system_message=designer_system_message1,
    llm_config={
        'config_list': [
            {'model': 'deepseek-reasoner', 'api_key': API_KEY, 'base_url': BASE_URL}
        ]
    },
    code_execution_config=False,  # Turn off code execution, by default it is off.
    function_map=None,  # No registered functions, by default it is None.
    human_input_mode='NEVER',  # Never ask for human input.
)

user_input = input('你想设计什么?')
input_message = user_input
condition = True
while condition:
    scheme = designer.generate_reply(
        messages=[{'role': 'user', 'content': input_message}]
    )
    print(scheme)
    if 'design scheme' in scheme:
        condition = False
    else:
        user_input = input('你想添加什么内容?')
        input_message = (
            '你的上一个回答是：\n'
            + scheme
            + '\n对此，用户的添加内容为：\n'
            + user_input
        )

change_pattern(scheme)

file_path = 'E:/pycharm/autogen/src/scheme.txt'
with open(file_path, 'r', encoding='utf-8-sig') as f:
    modeled_scheme = f.read()
code = writer(modeled_scheme)
testbench = testbench_writer(modeled_scheme, code)

ask = input('是否启动仿真？(y/n)')
if ask == 'y':
    result = run_vivado()

"""while result:
    code=debug(modeled_scheme,code,testbench)
    testbench=testbench_writer(modeled_scheme,code)
"""
