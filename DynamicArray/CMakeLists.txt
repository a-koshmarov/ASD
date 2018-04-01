cmake_minimum_required(VERSION 3.8)
project(DynamicArray)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Matrix.h MatrixTemplate.h)
add_executable(DynamicArray ${SOURCE_FILES})