cmake_minimum_required(VERSION 3.9)
project(pl_l8_27)

set(CMAKE_CXX_STANDARD 11)

add_executable(pl_l8_27 main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})