cmake_minimum_required(VERSION 3.7)
project(oap)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(oap ${SOURCE_FILES})


include_directories(libs)
set(LIBS_FILES
        libs/console_io_lib/console_io_lib.h
        libs/console_io_lib/console_io_lib.cpp
        libs/git_rep/date/date.h
        libs/git_rep/date/date.cpp
        libs/git_rep/git_rep_io.h
        libs/git_rep/git_rep_io.cpp
        libs/database/database.cpp
        libs/database/database.h
        libs/list/GitRepStackList.h
        libs/list/GitRepStackList.cpp
        libs/menu/menu.cpp
        libs/menu/menu.h)
add_executable(libs ${LIBS_FILES})


set(CMAKE_EXE_LINKER_FLAGS "-static")