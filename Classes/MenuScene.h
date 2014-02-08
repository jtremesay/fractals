#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public  cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    bool init() override;    
    
    bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event  * event) override;
    void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event  * event) override;
    virtual void onMouseScroll(cocos2d::Event * event);
    
    CREATE_FUNC(MenuScene);
    
protected:
    void menuCallback(Object * sender);
    void moveMenuBy(float y);
    
    
protected:
    cocos2d::Menu * m_menu;
    cocos2d::Point m_beginTouchPoint;
};

#endif // __MENU_SCENE_H__
