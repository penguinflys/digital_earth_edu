cmake_minimum_required(VERSION 3.10)

project(Digital_Earth)
# CPP standard 11
set(CMAKE_CXX_FLAGS "-std=c++14")
# debug with gdb (on vscode)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")
add_subdirectory(src)
add_subdirectory(utils)

# Find Pangolin (https://github.com/stevenlovegrove/Pangolin)
find_package(Pangolin 0.4 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

# find system installed GDAL package with predefined CMake variable for finding GDAL
find_package(GDAL REQUIRED)
# Specify location of GDAL header files
include_directories(include ${GDAL_INCLUDE_DIRS})
# opencv
find_package(OpenCV REQUIRED)
# eigen3
# find_package (Eigen3 3.3 REQUIRED NO_MODULE)


set(HEADER_FILES src/includes/Triface.h src/includes/DataIO.h src/includes/ElevationAndTexture.h src/includes/gdal2cv.h src/includes/utils.h)
set(SOURCES_FILES 
    src/main.cpp src/Triface.cpp src/DataIO.cpp src/ElevationAndTexture.cpp
    utils/utils.cpp src/gdal2cv.cpp
    src/includes/Triface.h src/includes/DataIO.h src/includes/ElevationAndTexture.h
    src/includes/gdal2cv.h src/includes/utils.h
    )

add_executable(MainFunc ${SOURCES_FILES})

target_include_directories(MainFunc PUBLIC utils)
target_include_directories(MainFunc PUBLIC src)
target_include_directories(MainFunc PUBLIC src/includes)

target_link_libraries(MainFunc ${Pangolin_LIBRARIES} )
# Specify GDAL libraries to link your cpp executable target against
target_link_libraries(MainFunc ${GDAL_LIBRARIES})
# link OpenCV lib
target_link_libraries(MainFunc ${OpenCV_LIBS})

# link Eigen3
# target_link_libraries(MainFunc Eigen3::Eigen)
# target_link_libraries(MainFunc src)
# target_link_libraries(MainFunc utils)