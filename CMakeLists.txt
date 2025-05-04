# filepath: /Users/oghenemano/WaveletRepresentation/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(WaveletRepresentation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set policy to suppress warnings about FindBoost
cmake_policy(SET CMP0167 NEW)

find_package(ITK REQUIRED)
find_package(VTK
  COMPONENTS
  CommonColor
  FiltersSources
  CommonDataModel
  RenderingCore
  RenderingVolume
  RenderingVolumeOpenGL2

)

# Include directories
include_directories(include)

add_library(Generator STATIC
    src/generator/phatomwavelet.cpp
)

add_library(Extraction STATIC
 src/extraction/data_extraction.cc
)

add_library(Transformation STATIC
 src/transformation/wavelet_transform.cc
)

add_library(ImagePreprocessing STATIC 
 src/image_processing/image_prepocessing.cpp
)


# Add the executable
add_executable(WaveletRepresentation
    src/main.cc
)


target_link_libraries(WaveletRepresentation
  PRIVATE
   ${VTK_LIBRARIES}
)


target_link_libraries(WaveletRepresentation PRIVATE ${ITK_LIBRARIES})
target_link_libraries(WaveletRepresentation PRIVATE ${VTK_LIBRARIES})

target_link_libraries(ImagePreprocessing PRIVATE ${ITK_LIBRARIES})

target_link_libraries(Extraction PRIVATE ${ITK_LIBRARIES})

target_link_libraries(ImagePreprocessing PRIVATE Generator)



target_include_directories(WaveletRepresentation PRIVATE 
    ${PROJECT_SOURCE_DIR}/src/include
)
target_include_directories(ImagePreprocessing PRIVATE 
    ${PROJECT_SOURCE_DIR}/src/include
)
# Link libraries
target_link_libraries(WaveletRepresentation PRIVATE Generator ImagePreprocessing Extraction Transformation ${VTK_LIBRARIES} ${ITK_LIBRARIES})


vtk_module_autoinit(
  TARGETS WaveletRepresentation
  MODULES ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS ImagePreprocessing
  MODULES ${VTK_LIBRARIES}
)