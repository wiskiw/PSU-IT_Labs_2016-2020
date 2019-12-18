cmake_minimum_required(VERSION 3.7)
project(pl2_5)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(pl2_5 ${SOURCE_FILES})

set(LIBS_FILES
        console_io_lib/console_io_lib.h
        console_io_lib/console_io_lib.cpp)
add_executable(libs ${LIBS_FILES})