cmake_minimum_required(VERSION 3.9)
project(osisp_l2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(osisp_l2 main.cpp)