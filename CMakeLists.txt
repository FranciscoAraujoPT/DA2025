cmake_minimum_required(VERSION 3.30)
project(DA)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES
        src/*.cpp
)

add_executable(DA ${SRC_FILES})

install(DIRECTORY data DESTINATION ${CMAKE_BINARY_DIR})
