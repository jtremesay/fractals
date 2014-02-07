#include "FractalSprite.h"

USING_NS_CC;

FractalSprite::FractalSprite() :
    m_ratio(Point(1.f, 1.f)),
    m_center(Point::ZERO),
    m_scaleFactor(1.f)
{
    
}

const cocos2d::Point & FractalSprite::getRatio() const
{
    return m_ratio;
}

void FractalSprite::setRatio(const Point& ratio)
{
    m_ratio = ratio;
}

const Point& FractalSprite::getCenter() const
{
    return m_center;
}

void FractalSprite::setCenter(const Point& center)
{
    m_center = center;
}

float FractalSprite::getScaleFactor() const
{
    return m_scaleFactor;
}

void FractalSprite::setScaleFactor(float scaleFactor)
{
    m_scaleFactor = scaleFactor;
}


void FractalSprite::buildCustomUniforms()
{
    m_uniformRatio = glGetUniformLocation(this->getShaderProgram()->getProgram(), "u_ratio");
    m_uniformCenter = glGetUniformLocation(this->getShaderProgram()->getProgram(), "u_center");
    m_uniformScaleFactor = glGetUniformLocation(this->getShaderProgram()->getProgram(), "u_scaleFactor");
}


void FractalSprite::setCustomUniforms()
{
    this->getShaderProgram()->setUniformLocationWith2f(m_uniformRatio, m_ratio.x, m_ratio.y);
    this->getShaderProgram()->setUniformLocationWith2f(m_uniformCenter, m_center.x, m_center.y);
    this->getShaderProgram()->setUniformLocationWith1f(m_uniformScaleFactor, m_scaleFactor);
}
