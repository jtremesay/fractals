set(LIBS
    ${SFML_LIBRARIES}
    Fractals)

include_directories("../libfractals/includes/")

set(SRCS
    src/main.cpp)

add_executable(fractals_gui ${SRCS})
target_link_libraries(fractals_gui ${LIBS})