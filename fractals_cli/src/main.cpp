#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include <fractals/mandelbrot.h>

static int size = 512;

int main(int argc, char const * argv[])
{
    char nameBuffer[256];
    
    sf::Image image;
    image.create(size, size);
    
    Mandelbrot mandelbrot = Mandelbrot();
    mandelbrot.setCenter(sf::Vector2f(-0.1f, 0.0f));
    mandelbrot.setScaleFactor(0.4f);
    for (unsigned int i = 0; i < 10; ++i) {        
        snprintf(nameBuffer, sizeof(nameBuffer), "mandelbrot_%03u.png", i);
        
        mandelbrot.drawToImage(image);
        image.saveToFile(nameBuffer);
        
        float scaleFactor = mandelbrot.getScaleFactor();
        scaleFactor *= 1.1f;
        mandelbrot.setScaleFactor(scaleFactor);
    }

    return EXIT_SUCCESS;
}