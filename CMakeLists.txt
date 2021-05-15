# 版本要求
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

# 项目名称
PROJECT(myNetwrokLib)
set(CXX_FLAGS
 -g
 -O0
 -D_FILE_OFFSET_BITS=64
 -Wall
# -Wextra
# -Werror
 -Wconversion
# -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 -std=c++11
 -rdynamic
 )

set(CMAKE_CXX_COMPILE_FEATURES "g++")


# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 增加子目录，子目录中会有对应的CMakeLists.txt 
add_subdirectory(src)
add_subdirectory(test)
