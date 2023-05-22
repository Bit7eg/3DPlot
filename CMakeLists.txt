cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

set(OpenGLLibs glfw3 glew32s opengl32)

set(ExtFiles Shader Camera Config)

project(3DPlot)

link_directories(lib)
include_directories(include)

add_subdirectory(src_libs/Shader)
add_subdirectory(src_libs/Camera)
add_subdirectory(src_libs/Config)

add_executable(${PROJECT_NAME} main.cpp src_libs/libs.h)

target_link_libraries(${PROJECT_NAME} ${ExtFiles} ${OpenGLLibs})

file(COPY shaders DESTINATION ./)
file(COPY figures DESTINATION ./)
file(COPY config.txt DESTINATION ./)
