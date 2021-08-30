cmake_minimum_required(VERSION 3.1)
project(SampleApp)

find_library(LIBPTHREAD pthread REQUIRED)

file(GLOB Sample_Gif_Src "sample-gif/*.cc")
add_executable(sample-gif ${Sample_Gif_Src})
target_link_libraries(sample-gif ${LIBPTHREAD})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

file(GLOB Sample_OpenGL_Window "sample-opengl/*.cc")
add_executable(sample-opengl sample-gif/decoder.cc ${Sample_OpenGL_Window})
target_link_libraries(sample-opengl ${OPENGL_LIBRARIES} glfw)