cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeTests)

find_package(Imlib2 REQUIRED)
include(FindOpenMP OPTIONAL)
if(OPENMP_FOUND)
    message("OpenMP parallelization enabled")
    add_definitions("${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SRCS
    main.c
    mandelbrot.c
    utils.c)

set(LIBS
    ${IMLIB2_LIBRARIES})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

add_executable(fractals ${SRCS})
target_link_libraries(fractals ${LIBS})