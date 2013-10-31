#ifndef FRACTALS_MANDELBROT_H
#define FRACTALS_MANDELBROT_H

#include <SFML/Graphics.hpp>

class Mandelbrot
{
private:
    float m_scaleFactor;
    sf::Vector2f m_center;
    unsigned int m_maxIters;
    sf::Shader m_shader;
    
public:
    Mandelbrot();
    ~Mandelbrot();
    
    float getScaleFactor() const;
    void setScaleFactor(float scaleFactor);
    void scale(float scaleFactor);
    
    const sf::Vector2f & getCenter() const;
    void setCenter(const sf::Vector2f & center);
    
    unsigned int getMaxIters() const;
    void setMaxIters(unsigned int maxIters);
    
    const sf::Shader & getShader() const;
};

#endif // FRACTALS_MANDELBROT_H