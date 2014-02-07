#include "MandelbrotFractalScene.h"
#include "MandelbrotSprite.h"

USING_NS_CC;

Scene * MandelbrotFractalScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MandelbrotFractalScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

FractalSprite * MandelbrotFractalScene::createFractalSprite()
{
    MandelbrotSprite * fractal = MandelbrotSprite::create();
    
    return fractal;
}