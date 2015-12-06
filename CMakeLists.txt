cmake_minimum_required(VERSION 3.3)
project(wacc_10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cc)
add_executable(wacc_10 ${SOURCE_FILES})