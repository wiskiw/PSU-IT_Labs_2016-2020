cmake_minimum_required(VERSION 3.7)
project(c8_1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(c8_1 ${SOURCE_FILES})


set(CMAKE_EXE_LINKER_FLAGS "-static")