cmake_minimum_required(VERSION 3.8)
project(OpenGL_Test)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(OpenGL_Test ${SOURCE_FILES})

# target_link_libraries(OpenGL_Test ${OPENGL_LIBRARIES} libopengl32.a libglu32.a libfreeglut.a)

add_executable(texture_mapping ${SOURCE_FILES})
link_directories(${OPENGL_gl_LIBRARY})
target_link_libraries(OpenGL_Test libfreeglut.a libfreeglut_static.a ${OPENGL_gl_LIBRARY})
