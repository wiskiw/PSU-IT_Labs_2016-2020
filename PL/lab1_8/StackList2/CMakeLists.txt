cmake_minimum_required(VERSION 3.7)
project(StackList)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp StackList.cpp StackList.h)
add_executable(StackList ${SOURCE_FILES})
