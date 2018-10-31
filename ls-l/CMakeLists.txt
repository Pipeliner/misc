cmake_minimum_required(VERSION 3.6)
project(ls_l)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ls.c)

add_executable(ls ${SOURCE_FILES})