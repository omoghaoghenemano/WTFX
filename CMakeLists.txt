# filepath: /Users/oghenemano/WaveletRepresentation/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(WaveletRepresentation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)
add_library(Generator STATIC
    src/generator/phatomwavelet.cpp
)

# Add the executable
add_executable(WaveletRepresentation
    src/main.cpp
)


target_link_libraries(WaveletRepresentation PRIVATE Generator)

target_include_directories(WaveletRepresentation PRIVATE 
    ${PROJECT_SOURCE_DIR}/src/include
)