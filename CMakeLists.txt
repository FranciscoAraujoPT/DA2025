cmake_minimum_required(VERSION 3.30)
project(DA)

set(CMAKE_CXX_STANDARD 20)

add_executable(DA main.cpp
        Location.cpp
        Location.h
        Street.cpp
        Street.h
        CSVReader.cpp
        CSVReader.h
        Graph.h
        MutablePriorityQueue.h
)

file(GLOB_RECURSE data ./data/*)

file(COPY ${data} DESTINATION data)

