#include "fractals/mandelbrot.h"
#include <cmath>

#ifdef _OPENMP
#   include <omp.h>
#endif // _OPENMP

Mandelbrot::Mandelbrot() :
    m_scaleFactor(0.0f),
    m_center(sf::Vector2f(0.0f, 0.0f)),
    m_colors(new sf::Color[256])
{        
    for (unsigned int n = 0; n < 42; ++n) {
        m_colors[n] = sf::Color(255, n * 6, 0);
        m_colors[n + 42] = sf::Color((255 - n * 6), 255, 0);
        m_colors[n + 84] = sf::Color(0, 255, n * 6);        
        m_colors[n + 126] = sf::Color(0, (255 - n * 6), 255);
        m_colors[n + 168] = sf::Color(n * 6, 0, 255);       
        m_colors[n + 210] = sf::Color(255, 0, (255 - n * 6));
    }   
}

Mandelbrot::~Mandelbrot()
{
    delete[] m_colors;
}

float Mandelbrot::getScaleFactor() const
{
    return m_scaleFactor;
}

void Mandelbrot::setScaleFactor(float scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

const sf::Vector2f & Mandelbrot::getCenter() const
{
    return m_center;
}

void Mandelbrot::setCenter(const sf::Vector2f & center)
{
    m_center = center;
}

void Mandelbrot::drawToImage(sf::Image & image) const
{
    const sf::Vector2u & targetSize = image.getSize();
    const sf::Vector2f size = sf::Vector2f(targetSize.x, targetSize.y);
    const sf::Vector2f halfSize = sf::Vector2f(size.x / 2.0f, size.y / 2.0f);
    
    const float escapeValue = 4.0f;
    
    #pragma omp parallel for
    for (unsigned int y = 0; y < targetSize.y; ++y) {
        for (unsigned x = 0; x < targetSize.x; ++x) {
            sf::Vector2f c = sf::Vector2f((x - halfSize.x) / halfSize.x / m_scaleFactor,
                                          (y - halfSize.y) / halfSize.y / m_scaleFactor);
            sf::Vector2f z = sf::Vector2f(0.0f, 0.0f);
            
            unsigned int color = 0;
            do {
                ++color;
                sf::Vector2f n = sf::Vector2f(z.x * z.x - z.y * z.y + c.x,
                                              2 * z.x * z.y + c.y);
                z = n;
                const float d = n.x * n.x + n.y * n.y;
                if (d > escapeValue || color > 256) {
                    break;
                }
                
            } while (true);
            
            if (color <= 256) {
                image.setPixel(x, y, m_colors[color]);
            } else {
                image.setPixel(x, y, sf::Color::Black);
            }
        }        
    }
}
