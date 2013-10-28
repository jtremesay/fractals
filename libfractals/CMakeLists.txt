set(LIBS
    ${SFML_LIBRARIES})

set(SRCS
    src/mandelbrot.cpp)

include_directories("includes")

add_library(Fractals ${SRCS})
target_link_libraries(Fractals ${LIBS})