import os

from autogen import ConversableAgent
from dotenv import load_dotenv

load_dotenv()  # 自动加载项目根目录的 .env 文件

API_KEY = os.getenv('MY_API_KEY')
BASE_URL = os.getenv('MY_BASE_URL')


def debug(scheme, verilog_code, testbench):
    file_path = 'E:/pycharm/autogen/vivado.log'
    with open(file_path, 'a') as f:
        vivado_log = f.read()
    os.remove(file_path)
    input = (
        '设计方案为：\n'
        + scheme
        + 'verilog的代码为：\n'
        + verilog_code
        + '\n'
        + 'testbench的代码为\n'
        + testbench
        + '\n'
        + 'vivado的日志：\n'
        + vivado_log
    )

    debug_agent_system_message = """
    1、你是一个给verilog代码debug的代理。
    2、用户会将他的设计方案、verilog的.v文件的代码、testbench的代码、以及Vivado软件的日志提供给你，你需要根据这些信息对verilog的.v文件的代码进行修正。
    3、重要提示：Vivado软件所支持的verilog版本为Verilog-2005版本，所提供给你的verilog的.v文件的代码的错误很有可能是因为其语法规则不符合Verilog-2005版本的语法规则。且你修正后的代码也必须符合Verilog-2005版本的语法规则。
    4、修正.v文件的verilog代码就好，不要修改testbench，修改testbench是别的代理的工作。
    5、你的最终回答要严格遵守以'module'开始，以'endmodule'结束的格式，不要回答除了代码之外的其他单词或句子，也不要以'```verilog'开始，不要以'```'结束。
    """

    debug_agent = ConversableAgent(
        'designer',
        system_message=debug_agent_system_message,
        llm_config={
            'config_list': [
                {'model': 'deepseek-reasoner', 'api_key': API_KEY, 'base_url': BASE_URL}
            ]
        },
        code_execution_config=False,  # Turn off code execution, by default it is off.
        function_map=None,  # No registered functions, by default it is None.
        human_input_mode='NEVER',  # Never ask for human input.
    )

    debug_code = debug_agent.generate_reply(
        messages=[{'role': 'user', 'content': input}]
    )
    print(debug_code)

    filepath = 'E:/pycharm/autogen/src/programming.v'
    with open(filepath, 'w', encoding='utf-8-sig') as file_object:
        file_object.write(debug_code)

    return debug_code
