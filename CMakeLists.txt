cmake_minimum_required(VERSION 3.10)
project(Perception)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子目录
add_subdirectory(strategy)
add_subdirectory(pybind)
