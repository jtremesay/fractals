set(LIBS
    ${IMLIB2_LIBRARIES}
    Fractals)

include_directories("../libfractals/includes/")

set(SRCS
    src/main.cpp)


add_executable(fractals_cli ${SRCS})
target_link_libraries(fractals_cli ${LIBS})