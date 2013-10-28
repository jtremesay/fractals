#include <stdio.h>
#include <stdlib.h>

#include <Imlib2.h>
#include <fractals/mandelbrot.h>

static int size = 2048;

int main(int argc, char const * argv[])
{
    Imlib_Image image = imlib_create_image(size, size);
    imlib_context_set_image(image);
    imlib_image_set_format("png");

    float zoomScale = 0.001f;
    for (unsigned int i = 0; i < 10; ++i) {
        DATA32 * buffer = imlib_image_get_data();
        mandelbrot(buffer, size, size, 0.0f, 0.0f, zoomScale);
        imlib_image_put_back_data(buffer);

        char nameBuffer[256];
        snprintf(nameBuffer, sizeof(nameBuffer), "mandelbrot_%03u.png", i);
        imlib_save_image(nameBuffer);

        zoomScale *= 0.9f;
    }

    imlib_free_image();

    return EXIT_SUCCESS;
}