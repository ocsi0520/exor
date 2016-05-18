project(exor)

cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${OpenMP_CXX_FLAGS}")

set( srcfile gondolkodos.cpp)

add_executable(gondolkodos ${srcfile})
