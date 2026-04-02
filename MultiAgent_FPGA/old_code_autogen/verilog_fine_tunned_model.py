import os

os.environ['HF_HOME'] = 'E:/huggingface'
os.environ['HF_HUB_DISABLE_SYMLINKS_WARNING'] = '1'
os.environ['PYTORCH_CUDA_ALLOC_CONF'] = (
    'expandable_segments:True,garbage_collection_threshold:0.6'  # 新增
)

import torch
from transformers import AutoModelForCausalLM, AutoTokenizer

filepath = 'E:/pycharm/autogen/src/scheme.txt'
with open(filepath, 'r', encoding='utf-8-sig') as file_object:
    prompt = file_object.read()


device = 'cuda' if torch.cuda.is_available() else 'cpu'

# 关键优化后的模型加载
try:
    tokenizer = AutoTokenizer.from_pretrained('shailja/fine-tuned-codegen-2B-Verilog')
    model = AutoModelForCausalLM.from_pretrained(
        'shailja/fine-tuned-codegen-2B-Verilog',
        device_map='auto',
        load_in_8bit=True,  # 8 位量化
        torch_dtype=torch.float16,  # 半精度
        low_cpu_mem_usage=True,  # 低内存模式
    )
except Exception as e:
    print(f'模型加载失败: {e}')
    exit()

input_ids = tokenizer(prompt, return_tensors='pt').input_ids.to(device)
try:
    sample = model.generate(
        input_ids,
        max_length=3000,
        temperature=0.8,
        do_sample=True,
        top_p=0.9,
        pad_token_id=tokenizer.eos_token_id,
    )
    decoded = (
        tokenizer.decode(sample[0], truncate_before_pattern=[r'endmodule'])
        + 'endmodule'
    )
    print('\n 生成的 Verilog 代码:\n' + decoded)
    file_path = 'E:/pycharm/autogen/src/programming.v'
    with open(file_path, 'w', encoding='utf-8-sig') as file_object:
        file_object.write(decoded)
except RuntimeError as e:
    print(f'生成失败（显存不足）: {e}')
finally:
    torch.cuda.empty_cache()
