cmake_minimum_required(VERSION 3.7)
project(ts1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp StackList.cpp StackList.h)
add_executable(ts1 ${SOURCE_FILES})

include_directories(libs)
set(LIBS_FILES
        console_io_lib/console_io_lib.h
        console_io_lib/console_io_lib.cpp)
add_executable(libs ${LIBS_FILES})