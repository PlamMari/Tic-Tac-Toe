cmake_minimum_required(VERSION 3.0.0)
project(chess VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file (GLOB SRC_FILES 
    ./*.cpp
    ./pieces/*.cpp
)

add_executable(chess ${SRC_FILES})