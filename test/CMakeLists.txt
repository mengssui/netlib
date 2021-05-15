# 所有源文件并起名
aux_source_directory(. SRC_LIST)

# 头文件路径
include_directories(../include)

# 设置执行文件位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 寻找库文件
find_library(THREADPOOL threadpool_static HINTS ${PROJECT_SOURCE_DIR}/lib)

# 执行程序
add_executable(timestamp_test timestamp_test.cc)
add_executable(atomic_test atomic_test.cc)
add_executable(thread_test thread_test.cc)
target_link_libraries(thread_test pthread)

add_executable(threadpool_test threadpool_test.cc)
target_link_libraries(threadpool_test mynetlib)

add_executable(logger_test logger_test.cc)
target_link_libraries(logger_test mynetlib)

