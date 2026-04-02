"""
这是huggingface上下载的shailja/fine-tuned-codegen-2B-Verilog模型，使用时需要先到huggingface官网上将这个模型下载到你的计算机上才能使用
"""

import os

import tensorflow as tf
import torch
from transformers import AutoModelForCausalLM, AutoTokenizer

os.environ['HF_HUB_DISABLE_SYMLINKS_WARNING'] = '1'  # 禁用 symlink 警告

tf.compat.v1.logging.set_verbosity(tf.compat.v1.logging.ERROR)  # 屏蔽 TensorFlow 日志

# 配置 Prompt 和设备
prompt = """
在这里输入设计需求（需要格式化的设计需求，因为这个模型不具备完整的自然语言理解能力），格式化见scheme_to_input.py
"""
device = 'cuda' if torch.cuda.is_available() else 'cpu'

# 加载模型（补充 try-catch 异常处理）
try:
    tokenizer = AutoTokenizer.from_pretrained('shailja/fine-tuned-codegen-2B-Verilog')
    model = AutoModelForCausalLM.from_pretrained(
        'shailja/fine-tuned-codegen-2B-Verilog'
    ).to(device)
except Exception as e:
    print(f'模型加载失败: {e}')
    exit()

# 执行生成
input_ids = tokenizer(prompt, return_tensors='pt').input_ids.to(device)
try:
    sample = model.generate(
        input_ids,
        max_length=128,
        temperature=0.5,
        top_p=0.9,
        pad_token_id=tokenizer.eos_token_id,  # 添加结束符避免截断
    )
    decoded = (
        tokenizer.decode(sample[0], truncate_before_pattern=[r'endmodule'])
        + 'endmodule'
    )
    print('\n 生成的 Verilog 代码:\n' + decoded)
except RuntimeError as e:
    print(f'生成失败（显存不足？）: {e}')
