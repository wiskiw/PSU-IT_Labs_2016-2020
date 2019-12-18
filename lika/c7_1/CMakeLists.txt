cmake_minimum_required(VERSION 3.7)
project(c7_1)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(c7_1 ${SOURCE_FILES})


set(CMAKE_EXE_LINKER_FLAGS "-static")
