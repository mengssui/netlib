# 设置头文件路径
include_directories(../include)

# 设置链接库,生成库的时候如果需要链接别的库也要加上
add_library(threadpool_static threadpool.cc) # 默认静态STATIC，否则第二个参数指明SHARED
target_link_libraries(threadpool_static pthread)

# 设置链接库的输出位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)