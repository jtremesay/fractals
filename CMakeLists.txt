cmake_minimum_required(VERSION 2.8)

project(fractals)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeTests)

find_package(Imlib2 REQUIRED)
find_package(SFML 2 REQUIRED system window graphics network audio)

include(FindOpenMP OPTIONAL)
if(OPENMP_FOUND)
    message("OpenMP parallelization enabled")
    add_definitions("${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_subdirectory(libfractals)
add_subdirectory(fractals_cli)