cmake_minimum_required(VERSION 3.30)
project(DA)

set(CMAKE_CXX_STANDARD 20)

# Find all source files recursively
file(GLOB_RECURSE SRC_FILES
        src/main.cpp
        src/data_structures/*.cpp
        src/data_handling/*.cpp
        src/route_planning/*.cpp
        src/env_friendly_routes/*.cpp
        src/utils/*.cpp
)

# Add the executable
add_executable(DA ${SRC_FILES}
        src/env_friendly_routes/HybridRoutes.h)

# Include directories
target_include_directories(DA PRIVATE src)

# Copy data files (if needed for execution)
file(GLOB_RECURSE DATA_FILES ./data/*)
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_BINARY_DIR}/data)
