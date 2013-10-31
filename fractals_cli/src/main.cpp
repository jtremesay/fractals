#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include <fractals/mandelbrot.h>

static int size = 512;

int main(int argc, char const * argv[])
{
    char nameBuffer[256];
    
    sf::RenderTexture renderTexture;
    renderTexture.create(size, size);
    
    sf::Image blankImage;
    blankImage.create(1, 1, sf::Color::White);
    
    sf::Texture blankTexture;
    blankTexture.loadFromImage(blankImage);
    
    sf::Sprite blankSprite;
    blankSprite.setTexture(blankTexture);
    blankSprite.setPosition(0, 0);
    blankSprite.setScale(size, size);
    
    Mandelbrot mandelbrot;
    mandelbrot.setCenter(sf::Vector2f(0.0f, 0.0f));
    mandelbrot.setScaleFactor(2.0f);
    for (unsigned int i = 0; i < 1; ++i) {
        renderTexture.clear();
        renderTexture.draw(blankSprite, &mandelbrot.getShader());
        renderTexture.display();
        
        snprintf(nameBuffer, sizeof(nameBuffer), "mandelbrot_gpu_%03u.png", i);
        renderTexture.getTexture().copyToImage().saveToFile(nameBuffer);
        
        mandelbrot.scale(0.9);
    }

    return EXIT_SUCCESS;
}