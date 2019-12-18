cmake_minimum_required(VERSION 3.7)
project(pl2_8)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(pl2_8 ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "-static")