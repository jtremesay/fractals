#include "fractals/mandelbrot.h"
#include <cmath>

#ifdef _OPENMP
#   include <omp.h>
#endif // _OPENMP

static const char vertex_shader[] = R"SHADER(
void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}
)SHADER";

static const char fragment_shader[] = R"SHADER(
uniform sampler2D texture;
uniform float m_scaleFactor;
uniform float m_maxIters;
uniform vec2 m_center;

void main()
{
    vec2 c = (gl_TexCoord[0].xy - 0.5) / 1.0 * m_scaleFactor - m_center;
    vec2 z = c;
    
    float iter = 0.0;
    vec4 output_color;
    do {
        iter += 1.0;
        z = vec2((z.x * z.x - z.y * z.y) + c.x,
                 (z.y * z.x + z.x * z.y) + c.y);
        if ((dot(z, z) > 4.0) || iter > m_maxIters) {
            break;
        }  
    } while (true);
    
    if (iter <= m_maxIters) {
        float nic = (iter - (log(log(length(z))) / log(2.0))) / m_maxIters;
        float sin_nic = sin(nic);                
        output_color = vec4((0.3 * sin_nic), 
                            (1.0 * sin_nic),
                            (4.0 * sin_nic),
                            1.0);
    } else {
        output_color = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = gl_Color * pixel * output_color;
}    
)SHADER";

Mandelbrot::Mandelbrot()
{
    m_shader.loadFromMemory(vertex_shader, fragment_shader);
    
    this->setScaleFactor(1.0f);
    this->setCenter(sf::Vector2f(0.0f, 0.0f));
    this->setMaxIters(64);
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
    
    m_shader.setParameter("m_scaleFactor", m_scaleFactor);
}

void Mandelbrot::scale(float scaleFactor) {
    this->setScaleFactor(m_scaleFactor * scaleFactor);
}

const sf::Vector2f & Mandelbrot::getCenter() const
{
    return m_center;
}

void Mandelbrot::setCenter(const sf::Vector2f & center)
{
    m_center = center;
    
    m_shader.setParameter("m_center", m_center);
}

unsigned int Mandelbrot::getMaxIters() const
{
    return m_maxIters;
}

void Mandelbrot::setMaxIters(unsigned int maxIters)
{
    m_maxIters = maxIters;
    
    m_shader.setParameter("m_maxIters", static_cast<float>(m_maxIters));
}

const sf::Shader & Mandelbrot::getShader() const
{    
    return m_shader;
}