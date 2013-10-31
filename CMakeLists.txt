cmake_minimum_required(VERSION 2.8)

project(fractals)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeTests)

find_package(SFML 2 REQUIRED graphics system window)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(libfractals)
add_subdirectory(fractals_cli)
add_subdirectory(fractals_gui)