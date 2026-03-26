import os
from openai import file_from_path

from dotenv import load_dotenv

load_dotenv()  # 自动加载项目根目录的 .env 文件

API_KEY = os.getenv('MY_API_KEY')
BASE_URL = os.getenv('MY_BASE_URL')
load_dotenv()
from autogen import ConversableAgent


def writer(reply):
    #verilog代码编写agent
    verilog_writer_system_message = """You are a verilog expert.
    Your code will run in Vivado. Please ensure that your Verilog code complies with the specifications in Vivado.
    Your task is to analyse the user's requests of IC design, and realise the function using verilog language.
    Write the verilog codes of .v file is ok, test-bench code is not your work.
    Your reply begin with 'module' and end with 'endmodule', don't reply other contents and words, don't begin with '```verilog' and don't end with '```'.
    """

    verilog_writer_system_message1="""
    1、你是一个Verilog—2005代码编写的专家。
    2、你的任务是分析用户的设计需求，然后使用Verilog-2005版本的Verilog语言来实现，并且给出完整的、可执行的代码。
    3、编写.v文件的代码就可以，不要编写testbench的代码，那不是你的任务。
    4、你必须严格遵守Verilog—2005版本verilog代码所有的语法规范，这是非常重要的，不要使用Verilog-2005版本不能使用的语法规则。
    5、在你的代码中，注意Verilog-2005参数的声明规范，确保你声明的参数可以使用。
    6、你的回答要严格遵守格式：以'module'开始，以'endmodule'结束。不要回答除了代码之外的单词或句子，也不要以'```verilog'开始，不要以'```'结束。
    """
    verilog_writer = ConversableAgent(
        "verilog writer",
        system_message=verilog_writer_system_message1,
        llm_config={"config_list": [{"model": "deepseek-reasoner", "api_key": API_KEY,"base_url":BASE_URL}]},
        code_execution_config=False,  # Turn off code execution, by default it is off.
        function_map=None,  # No registered functions, by default it is None.
        human_input_mode="NEVER",  # Never ask for human input.
    )
    #用户输入agent
    #need=input("what do you need?\n")
    need=reply
    reply1 = verilog_writer.generate_reply(messages=[{"content": need, "role": "user"}])
    print(reply1)
    filepath='E:/pycharm/autogen/src/programming.v'
    filename = 'programming.v'
    with open(filepath, 'w') as file_object:
        file_object.write(reply1)

    return reply1

#取得.v文件
def testbench_writer(need,code):
    verilog_test_writer_system_message = """
    1、你是一个Verilog-2005语言的testbench代买编写专家。
    2、我会把用户的设计需求和.v文件中的代码给你，你需要以此来编写你的testbench的代码。
    3、你必须严格遵守Verilog-2005版本Verilog的语法规范，这是非常重要的，不要使用Verilog-2005版本Verilog不能使用的语法。
    4、你的testbench的代码需要能够在波形中展现出模块的功能，在模块能产生不同输出时要能看到输出端口波形的变化
    5、你的回答需要严格遵守格式：以
    ”
    `timescale 1ns / 1ps 
    module programming_testbench;
    “开始，以 ”endmodule “结束。不要回答除了代码以外的其它单词、句子和符号等。不要以”```verilog"开始，不要以“```”结束。
    """
    verilog_test_writer_system_message1 = """
        You are an expert in writing testbenches using the Verilog-2005 language.

        I will provide you with the user's design requirements and the .v file containing the Verilog code. You are to write the testbench code based on that.

        You must strictly follow the Verilog-2005 syntax specification. This is very important. Do not use any syntax that is not supported in Verilog-2005.

        Your testbench must demonstrate all functionalities of the Verilog code in the .v file, such as how different inputs produce different outputs and how different input scenarios trigger various behaviors.

        Your response must strictly follow this format:
        It must start with "`timescale 1ns / 1ps" followed by "module programming_testbench;"
        It must end with "endmodule"
        Do not include any words, sentences, or symbols outside of the code.
        Do not begin the code with "```verilog" and do not end it with "```".
        """

    verilog_test_writer=ConversableAgent(
        "verilog test writer",
        system_message=verilog_test_writer_system_message,
        llm_config={"config_list": [{"model": "deepseek-reasoner", "api_key": API_KEY,"base_url":BASE_URL}]},
        code_execution_config=False,  # Turn off code execution, by default it is off.
        function_map=None,  # No registered functions, by default it is None.
        human_input_mode="NEVER",  # Never ask for human input.
    )
    prompt="设计方案为：\n"+need+"\n.v文件的代码为：\n"+code

    testbenchcode=verilog_test_writer.generate_reply(messages=[{"content": prompt, "role": "user"}])
    print(testbenchcode)

    filepath='E:/pycharm/autogen/src/programming_testbench.v'
    filename = 'programming_testbench.v'
    with open(filepath, 'w') as file_object:
        file_object.write(testbenchcode)

    return testbenchcode





