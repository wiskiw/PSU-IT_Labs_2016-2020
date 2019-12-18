cmake_minimum_required(VERSION 3.8)
project(lab6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
set(SOURCE_FILES main1.cpp)
add_executable(lab6 ${SOURCE_FILES})