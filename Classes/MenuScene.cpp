#include "MenuScene.h"
#include <array>
#include <tuple>
#include "helpers.h"
#include "FractalScene.h"
#include "MandelbrotFractalScene.h"
#include "VisibleRect.h"

USING_NS_CC;

struct {
    const char * fractal_name;
    std::function<Scene * ()> callback;
} const g_fractals[] = {    
    { "Mandelbrot", []() { return MandelbrotFractalScene::createScene(); }},   
};
const size_t g_fractals_size = ARRAY_SIZE(g_fractals);
#define LINE_SPACE 40

Scene * MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_menu = Menu::create();
    m_menu->setPosition(Point::ZERO);
    this->addChild(m_menu);
    
    for (size_t i = 0; i < g_fractals_size; ++i)
    {
        LabelTTF * label = LabelTTF::create(g_fractals[i].fractal_name, "Arial", 24);
                
        MenuItemLabel * menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(MenuScene::menuCallback, this));
        menuItem->setPosition(Point(VisibleRect::center().x, (VisibleRect::top().y - (i + 1) * LINE_SPACE)));
        
        m_menu->addChild(menuItem, i);
    }
    
   
    EventListenerTouchOneByOne * touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(MenuScene::onTouchMoved, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    EventListenerMouse * mouseListener = EventListenerMouse::create();
    mouseListener->onMouseScroll = CC_CALLBACK_1(MenuScene::onMouseScroll, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
    
    return true;
}


bool MenuScene::onTouchBegan(Touch * touch, Event * event)
{
    m_beginTouchPoint = touch->getLocation();
    
    return true;
}


void MenuScene::onTouchMoved(Touch * touch, Event * event)
{
    Point currentTouchPoint = touch->getLocation();
    float deltaY = currentTouchPoint.y - m_beginTouchPoint.y;
    this->moveMenuBy(deltaY);  
    m_beginTouchPoint = currentTouchPoint;
}


void MenuScene::onMouseScroll(Event * event)
{
    EventMouse * mouseEvent = static_cast<EventMouse *>(event);
    float deltaY = mouseEvent->getScrollY() * 6;
    this->moveMenuBy(deltaY);
}


void MenuScene::menuCallback(Object * sender)
{
    MenuItem * menuItem = static_cast<MenuItem *>(sender);
    int index = menuItem->getLocalZOrder();
    
    Scene * scene = g_fractals[index].callback();
    Director::getInstance()->pushScene(scene);
}

void MenuScene::moveMenuBy(float y)
{
    Point menuPosition = m_menu->getPosition();
    menuPosition.y += y;
    
    if (menuPosition.y < 0.0f)
    {
        menuPosition.y = 0;
    } else if (menuPosition.y > ((g_fractals_size + 1) * LINE_SPACE - VisibleRect::getVisibleRect().size.height)) {
        menuPosition.y = (g_fractals_size + 1) * LINE_SPACE - VisibleRect::getVisibleRect().size.height;
    }    
    m_menu->setPosition(menuPosition);
}
