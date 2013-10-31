#include <cstdlib>

#include <SFML/Window.hpp>

#include <fractals/mandelbrot.h>

int main(int argc, char const * argv[])
{    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fractals GUI");
    
    sf::Image blankImage;
    blankImage.create(1, 1, sf::Color::White);
    
    sf::Texture blankTexture;
    blankTexture.loadFromImage(blankImage);
    
    sf::Sprite blankSprite;
    blankSprite.setTexture(blankTexture);
    blankSprite.setPosition(0, 0);
    blankSprite.setScale(window.getSize().x, window.getSize().y);
    
    Mandelbrot mandelbrot;
    mandelbrot.setCenter(sf::Vector2f(0.0f, 0.0f));
    mandelbrot.setScaleFactor(2.0f);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear();
        window.draw(blankSprite, &mandelbrot.getShader());
        window.display();
    }
    
    return EXIT_SUCCESS;
}