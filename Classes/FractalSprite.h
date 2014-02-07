#ifndef __FRACTAL_SPRITE_H__
#define __FRACTAL_SPRITE_H__

#include "ShaderSprite.h"

class FractalSprite : public ShaderSprite
{
public:
    FractalSprite();
    
    virtual const cocos2d::Point & getRatio() const;
    virtual void setRatio(const cocos2d::Point & ratio);
    
    virtual const cocos2d::Point & getCenter() const;
    virtual void setCenter(const cocos2d::Point & center);
    
    virtual float getScaleFactor() const;
    virtual void setScaleFactor(float scaleFactor);
    
    
protected:
    void buildCustomUniforms() override;
    void setCustomUniforms() override;
    
    
protected:
    GLuint m_uniformRatio;
    GLuint m_uniformCenter;
    GLuint m_uniformScaleFactor;
    
    
protected:
    cocos2d::Point m_ratio;
    cocos2d::Point m_center;
    float m_scaleFactor;
};

#endif // __FRACTAL_SPRITE_H__