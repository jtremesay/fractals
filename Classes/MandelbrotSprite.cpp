#include "MandelbrotSprite.h"


MandelbrotSprite::MandelbrotSprite() :
    m_maxIters(64)
{
    _fragSourceFile = "shaders/mandelbrot.fsh";
    m_scaleFactor = 2.f;
}

int MandelbrotSprite::getMaxIters() const
{
    return m_maxIters;
}

void MandelbrotSprite::setMaxIters(int maxIters)
{
    m_maxIters = maxIters;
}

void MandelbrotSprite::buildCustomUniforms()
{
    this->FractalSprite::buildCustomUniforms();
    
    m_uniformMaxIters = glGetUniformLocation(this->getShaderProgram()->getProgram(), "u_maxIters");
}


void MandelbrotSprite::setCustomUniforms()
{
    this->FractalSprite::setCustomUniforms();
    
    this->getShaderProgram()->setUniformLocationWith1f(m_uniformMaxIters, m_maxIters);
}