set(LIBS)

set(SRCS
    src/mandelbrot.cpp
    src/utils.cpp)

include_directories("includes")

add_library(Fractals ${SRCS})