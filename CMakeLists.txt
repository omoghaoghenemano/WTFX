cmake_minimum_required(VERSION 3.14)
project(WaveletRepresentation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory for public headers
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Add the executable
add_executable(WaveletRepresentation
    src/main.cpp
)

