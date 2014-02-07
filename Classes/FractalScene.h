#ifndef __FRACTAL_SCENE_H__
#define __FRACTAL_SCENE_H__

#include <thread>
#include "cocos2d.h"

class FractalSprite;

class FractalScene : public  cocos2d::Layer
{
public:
    bool init() override;    
    
protected:
    virtual void moveLeftCallback(Object * sender);
    virtual void moveRightCallback(Object * sender);
    virtual void moveUpCallback(Object * sender);
    virtual void moveDownCallback(Object * sender);
    virtual void zoomInCallback(Object * sender);
    virtual void zoomOutCallback(Object * sender);
    virtual void backCallback(Object * sender);
    
    virtual void updateOSD();
    
    virtual FractalSprite * createFractalSprite() = 0;
    
protected:    
    FractalSprite * m_fractal;
    
    cocos2d::LabelTTF * m_osdLabel;
};

#endif // __FRACTAL_SCENE_H__
