cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-Wall -fexceptions -std=c++11")

set(filesys_SRCS
    filesys.cpp
)

add_executable(filesys
    ${filesys_SRCS}
)
