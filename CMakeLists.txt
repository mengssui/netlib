# 版本要求
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

# 项目名称
PROJECT(myNetwrokLib)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 增加子目录，子目录中会有对应的CMakeLists.txt 
add_subdirectory(test)
add_subdirectory(src)
