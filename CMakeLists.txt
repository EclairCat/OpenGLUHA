cmake_minimum_required(VERSION 3.20)

project(opengl_rabie)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(GLFW-CMake-starter)

include_directories(include GLFW)

add_executable(opengl_rabie glad.c training.cpp)
target_link_libraries(opengl_rabie glfw m)
find_package(OpenGL REQUIRED)