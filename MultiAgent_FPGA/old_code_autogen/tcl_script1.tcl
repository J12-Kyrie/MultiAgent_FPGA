# 定义项目路径
set project_dir "E:/pycharm/autogen/"
set src_dir "${project_dir}/src"

# 创建新项目
create_project vivado_project ${project_dir}/vivado_project -force

# 添加源文件和测试文件
add_files "${src_dir}/programming.v"
add_files "${src_dir}/programming_testbench.v" -fileset sim_1

# 设置顶层模块
set_property top programming_testbench [get_filesets sim_1]

# 仿真设置
set_property sim_mode behavioral [get_filesets sim_1]
set_property target_simulator xsim [get_filesets sim_1]

# 运行仿真
launch_simulation

# 打开波形窗口（仿真 GUI 环境会自动加载）
start_gui
