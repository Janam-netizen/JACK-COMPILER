cmake_minimum_required(VERSION 3.19)
project(reg_alloc_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(reg_alloc_cpp
        basic_block.h
        color.h
        color.cpp
        flowgraph.cpp
        flowgraph.h
        code_gen.cpp
        code_gen.h
        liveness.cpp)
