#ifndef __MANDELBROT_FRACTAL_SCENE_H__
#define __MANDELBROT_FRACTAL_SCENE_H__

#include "FractalScene.h"

class FractalSprite;

class MandelbrotFractalScene : public FractalScene
{
public:
    static cocos2d::Scene * createScene();
    
    CREATE_FUNC(MandelbrotFractalScene); 
    
protected:
    FractalSprite * createFractalSprite() override;
};

#endif // __MANDELBROT_FRACTAL_SCENE_H__
