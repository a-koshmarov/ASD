cmake_minimum_required(VERSION 3.9)
project(Smallsort)

set(CMAKE_STATIC "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_STANDARD 11)

add_executable(Smallsort main.cpp)