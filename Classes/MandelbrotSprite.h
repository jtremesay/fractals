#ifndef __MANDELBROT_SPRITE_H__
#define __MANDELBROT_SPRITE_H__

#include "FractalSprite.h"

class MandelbrotSprite : public FractalSprite
{
public:  
    MandelbrotSprite();
    
    virtual int getMaxIters() const;
    virtual void setMaxIters(int maxIters);
    
    CREATE_FUNC(MandelbrotSprite);
    
protected:
    void buildCustomUniforms() override;
    void setCustomUniforms() override;
    
    
protected:
    int m_maxIters;
    
    GLuint m_uniformMaxIters;
};

#endif // __MANDELBROT_SPRITE_H__