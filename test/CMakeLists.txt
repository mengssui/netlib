# 所有源文件并起名
aux_source_directory(. SRC_LIST)

# 头文件路径
include_directories(../include)

# 增加源文件路径


# 设置执行文件位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 执行程序
add_executable(timestamp_test timestamp_test.cc)
add_executable(atomic_test atomic_test.cc)
