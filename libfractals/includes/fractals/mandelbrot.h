#ifndef FRACTALS_MANDELBROT_H
#define FRACTALS_MANDELBROT_H

#include <SFML/Graphics.hpp>

class Mandelbrot
{
private:
    float m_scaleFactor;
    sf::Vector2f m_center;
    sf::Color * m_colors;
    
public:
    Mandelbrot();
    ~Mandelbrot();
    
    float getScaleFactor() const;
    void setScaleFactor(float scaleFactor);
    
    const sf::Vector2f & getCenter() const;
    void setCenter(const sf::Vector2f & center);
    
    void drawToImage(sf::Image & image) const;
};

#endif // FRACTALS_MANDELBROT_H