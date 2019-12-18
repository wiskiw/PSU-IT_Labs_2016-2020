cmake_minimum_required(VERSION 3.7)
project(pl2_9)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(pl2_9 ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "-static")