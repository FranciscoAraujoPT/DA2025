cmake_minimum_required(VERSION 3.30)
project(DA)

set(CMAKE_CXX_STANDARD 20)

add_executable(DA main.cpp
        data_structures/Location.cpp
        data_structures/Location.h
        data_structures/Street.cpp
        data_structures/Street.h
        file_handling/CSVReader.cpp
        file_handling/CSVReader.h
        data_structures/Graph.h
        data_structures/MutablePriorityQueue.h
)

file(GLOB_RECURSE data ./data/*)

file(COPY ${data} DESTINATION data)

