cmake_minimum_required(VERSION 3.7)
project(D_List)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(D_List ${SOURCE_FILES})

set(LIBS_FILES
        console_io_lib/console_io_lib.h
        console_io_lib/console_io_lib.cpp)
add_executable(libs ${LIBS_FILES})