def run_vivado():
    import subprocess

    # Vivado 路径和 Tcl 脚本路径
    vivado_path = r"E:/vivado/Vivado/2023.1/bin/vivado.bat"
    tcl_script = r"E:/pycharm/autogen/tcl_script1.tcl"

    try:
        # 运行 Vivado 并加载 Tcl 脚本
        subprocess.run([vivado_path, "-mode", "batch", "-source", tcl_script], shell=True, check=True)
        print("Vivado 仿真、综合和波形显示已完成！")
        return False
    except subprocess.CalledProcessError as e:
        print(f"运行 Vivado 时发生错误：{e}")
        return True
    except FileNotFoundError:
        print("未找到 Vivado 或 Tcl 脚本，请检查路径！")
        return "未找到 Vivado 或 Tcl 脚本，请检查路径！"

run_vivado()
