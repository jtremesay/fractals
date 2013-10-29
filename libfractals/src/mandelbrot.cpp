#include "fractals/mandelbrot.h"
#include <cmath>

#ifdef _OPENMP
#   include <omp.h>
#endif // _OPENMP

Mandelbrot::Mandelbrot() :
    m_scaleFactor(0.0f),
    m_center(sf::Vector2f(0.0f, 0.0f)),
    m_maxIters(64)
{
}

Mandelbrot::~Mandelbrot()
{
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

unsigned int Mandelbrot::getMaxIters() const
{
    return m_maxIters;
}

void Mandelbrot::setMaxIters(unsigned int maxIters)
{
    m_maxIters = maxIters;
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
            
            unsigned int iter = 0;
            do {
                ++iter;
                sf::Vector2f n = sf::Vector2f(z.x * z.x - z.y * z.y + c.x,
                                              2 * z.x * z.y + c.y);
                z = n;
                const float d = n.x * n.x + n.y * n.y;
                if (d > escapeValue || iter > m_maxIters) {
                    break;
                }
                
            } while (true);
            
            if (iter <= m_maxIters) {
                const float nic = (float(iter) - (logf(logf(sqrt((z.x * z.x) + (z.y * z.y)))) / logf(2.0))) / float(m_maxIters);
                const float sin_nic = sinf(nic);                
                image.setPixel(x, y, sf::Color((0.3f * sin_nic) * 255, 
                                               (1.0f * sin_nic) * 255,
                                               (4.0f * sin_nic) * 255));
            } else {
                image.setPixel(x, y, sf::Color::Black);
            }
        }        
    }
}
