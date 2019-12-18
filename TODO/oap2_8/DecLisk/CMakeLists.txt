cmake_minimum_required(VERSION 3.7)
project(DecLisk)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DecList.cpp DecList.h)
add_executable(DecLisk ${SOURCE_FILES})


include_directories(libs)
set(LIBS_FILES
        console_io_lib/console_io_lib.h
        console_io_lib/console_io_lib.cpp)
add_executable(libs ${LIBS_FILES})