def change_pattern(scheme):
    import os

    from dotenv import load_dotenv
    from openai import OpenAI

    load_dotenv()
    API_KEY = os.getenv('MY_API_KEY')
    BASE_URL = os.getenv('MY_BASE_URL')
    load_dotenv()

    client = OpenAI(api_key=API_KEY, base_url=BASE_URL)

    prompt = """
    你是一个 Verilog 专家助理，负责将用户的设计需求转换为适合代码生成模型的结构化输入，你的输出需要让shailja/fine-tuned-codegen-2B-Verilog模型理解。请严格遵循以下规则：

    需求分解
    1. 提取所有功能需求
    2. 提取物理接口："输入" "输出" "信号"等
    3. 标注约束条件：

    输出必须严格遵守，且输出必须为英文,你的工作只是转换设计需求的格式，不需要给出具体代码：
    //module <模块名称>
    module module_name #(
      // input:  <用户描述的输入特征>
      input 类型 [位宽] 信号名,
      // output:  <用户描述的输出特征>
      output 类型 [位宽] 信号名
    );
    // functions: <自然语言描述其实现的功能>
    // constraints： <关键约束>
    """

    input = scheme
    response = client.chat.completions.create(
        model='deepseek-reasoner',
        messages=[
            {'role': 'system', 'content': prompt},
            {'role': 'user', 'content': input},
        ],
        stream=False,
    )
    print(response.choices[0].message.content)

    file_path = 'E:/pycharm/autogen/src/scheme.txt'
    open(file_path, 'w', encoding='utf-8-sig').write(
        response.choices[0].message.content
    )
