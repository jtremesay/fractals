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
    mandelbrot.setRatio(static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y));
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                mandelbrot.setRatio(static_cast<float>(event.size.width) / static_cast<float>(event.size.height));
            } else if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta > 0) {
                    mandelbrot.scale(0.9f);
                } else {
                    mandelbrot.scale(1.1f);
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    sf::Vector2f center = mandelbrot.getCenter();
                    float scale = mandelbrot.getScaleFactor();
                    center.x += 0.05f * scale;
                    mandelbrot.setCenter(center);
                } else if (event.key.code == sf::Keyboard::Right) {
                    sf::Vector2f center = mandelbrot.getCenter();
                    float scale = mandelbrot.getScaleFactor();
                    center.x -= 0.05f * scale;
                    mandelbrot.setCenter(center);
                } else if (event.key.code == sf::Keyboard::Up) {
                    sf::Vector2f center = mandelbrot.getCenter();
                    float scale = mandelbrot.getScaleFactor();
                    center.y += 0.05f * scale;
                    mandelbrot.setCenter(center);
                } else if (event.key.code == sf::Keyboard::Down) {
                    sf::Vector2f center = mandelbrot.getCenter();
                    float scale = mandelbrot.getScaleFactor();
                    center.y -= 0.05f * scale;
                    mandelbrot.setCenter(center);
                } else if (event.key.code == sf::Keyboard::A) {
                    unsigned int iter = mandelbrot.getMaxIters();
                    if (iter < 1024) {
                        ++iter;
                        mandelbrot.setMaxIters(iter);
                    }
                } else if (event.key.code == sf::Keyboard::Z) {
                    unsigned int iter = mandelbrot.getMaxIters();
                    if (iter > 0) {                        
                        --iter;
                        mandelbrot.setMaxIters(iter);
                    }
                }
            }
        }
        
        window.clear();
        window.draw(blankSprite, &mandelbrot.getShader());
        window.display();
    }
    
    return EXIT_SUCCESS;
}