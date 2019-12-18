cmake_minimum_required(VERSION 3.7)
project(pl2_10)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c menu/Menu.c menu/Menu.h tasks/task1/task1.c tasks/task1/task1.h tasks/task2/task2.c tasks/task2/task2.h tasks/task3/task3.c tasks/task3/task3.h tasks/task4/task4.c tasks/task4/task4.h)
add_executable(pl2_10 ${SOURCE_FILES})