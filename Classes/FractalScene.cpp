#include "FractalScene.h"
#include "FractalSprite.h"
#include "VisibleRect.h"

USING_NS_CC;

bool FractalScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    const Rect visibleRect = VisibleRect::getVisibleRect();
    
    
    m_fractal = this->createFractalSprite();
    if (m_fractal)
    {
        m_fractal->setTexture("white.png");
        m_fractal->initShader();
        m_fractal->setBackgroundNotification();
        m_fractal->setPosition(VisibleRect::center());
        m_fractal->setScaleX(visibleRect.size.width);
        m_fractal->setScaleY(visibleRect.size.height);
        m_fractal->setRatio(Point(visibleRect.size.width / visibleRect.size.height, 1.f));
        this->addChild(m_fractal);       
    }
    
    Menu * menu = Menu::create();
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    
    const float buttonSize = 64.f;    
    // Keyboard
    const Point keyboardCenterPoint = Point(32.f + buttonSize * 1.5f, visibleRect.size.height / 2.f);
    MenuItem * leftButton = MenuItemImage::create("ArrowNormal.png", "ArrowSelected.png", CC_CALLBACK_1(FractalScene::moveLeftCallback, this));
    leftButton->setPosition(Point(keyboardCenterPoint.x - buttonSize, keyboardCenterPoint.y));
    leftButton->setRotation(180.f);
    menu->addChild(leftButton);
    
    MenuItem * rightButton = MenuItemImage::create("ArrowNormal.png", "ArrowSelected.png", CC_CALLBACK_1(FractalScene::moveRightCallback, this));
    rightButton->setPosition(Point(keyboardCenterPoint.x + buttonSize, keyboardCenterPoint.y));
    menu->addChild(rightButton);
    
    MenuItem * upButton = MenuItemImage::create("ArrowNormal.png", "ArrowSelected.png", CC_CALLBACK_1(FractalScene::moveUpCallback, this));
    upButton->setPosition(Point(keyboardCenterPoint.x, keyboardCenterPoint.y + buttonSize));
    upButton->setRotation(-90.f);
    menu->addChild(upButton);
    
    MenuItem * downButton = MenuItemImage::create("ArrowNormal.png", "ArrowSelected.png", CC_CALLBACK_1(FractalScene::moveDownCallback, this));
    downButton->setPosition(Point(keyboardCenterPoint.x, keyboardCenterPoint.y - buttonSize));
    downButton->setRotation(90.f);
    menu->addChild(downButton);
    
    
    // Back button
    MenuItem * backButton = MenuItemImage::create("BackNormal.png", "BackSelected.png", CC_CALLBACK_1(FractalScene::backCallback, this));
    backButton->setPosition(Point(visibleRect.size.width - buttonSize - 32.f, 32.f));
    menu->addChild(backButton);
    
    
    // Zoom
    const Point zoomCenterPoint = Point(visibleRect.size.width - 32.f - buttonSize, visibleRect.size.height / 2.f);
       
    MenuItem * zoomInButton = MenuItemImage::create("ZoomInNormal.png", "ZoomInSelected.png", CC_CALLBACK_1(FractalScene::zoomInCallback, this));
    zoomInButton->setPosition(Point(zoomCenterPoint.x, keyboardCenterPoint.y + buttonSize));
    menu->addChild(zoomInButton);
    
    MenuItem * zoomOutButton = MenuItemImage::create("ZoomOutNormal.png", "ZoomOutSelected.png", CC_CALLBACK_1(FractalScene::zoomOutCallback, this));
    zoomOutButton->setPosition(Point(zoomCenterPoint.x, keyboardCenterPoint.y - buttonSize));
    menu->addChild(zoomOutButton);
    
    
    // OSD
    m_osdLabel = LabelTTF::create("", "Arial", 24);
    m_osdLabel->setAnchorPoint(Point(0.f, 1.f));
    m_osdLabel->setPosition(Point(10.f, visibleRect.size.height - 10.f));
    this->addChild(m_osdLabel);
    
    this->updateOSD();
    
    
    return true;
}

void FractalScene::updateOSD()
{
    if (!m_fractal) {
        return;
    }
    
    std::stringstream ss;
    ss << "X: " << m_fractal->getCenter().x << "\n";
    ss << "Y: " << m_fractal->getCenter().y << "\n";
    ss << "Scale: " << m_fractal->getScaleFactor();
    
    m_osdLabel->setString(ss.str());
}

void FractalScene::moveLeftCallback(Object * sender)
{
    if (!m_fractal) {
        return;
    }
    
    Point center = m_fractal->getCenter();
    center.x += 0.05f * m_fractal->getScaleFactor();
    m_fractal->setCenter(center);
    
    this->updateOSD();
}


void FractalScene::moveRightCallback(Object * sender)
{
    if (!m_fractal) {
        return;
    }
    
    Point center = m_fractal->getCenter();
    center.x -= 0.05f * m_fractal->getScaleFactor();
    m_fractal->setCenter(center);
    
    this->updateOSD();
}


void FractalScene::moveUpCallback(Object * sender)
{   
    if (!m_fractal) {
        return;
    }
    
    Point center = m_fractal->getCenter();
    center.y += 0.05f * m_fractal->getScaleFactor();
    m_fractal->setCenter(center);
    
    this->updateOSD();
}


void FractalScene::moveDownCallback(Object * sender)
{ 
    if (!m_fractal) {
        return;
    }
    
    Point center = m_fractal->getCenter();
    center.y -= 0.05f * m_fractal->getScaleFactor();
    m_fractal->setCenter(center);
    
    this->updateOSD();
}


void FractalScene::zoomInCallback(Object * sender)
{
    if (!m_fractal) {
        return;
    }
    
    float scaleFactor = m_fractal->getScaleFactor();
    scaleFactor *= 0.9f;
    m_fractal->setScaleFactor(scaleFactor);
    
    this->updateOSD();
}


void FractalScene::zoomOutCallback(Object * sender)
{
    if (!m_fractal) {
        return;
    }
    
    float scaleFactor = m_fractal->getScaleFactor();
    scaleFactor *= 1.1f;
    m_fractal->setScaleFactor(scaleFactor);
    
    this->updateOSD();
}


void FractalScene::backCallback(Object * sender)
{
    CCDirector::getInstance()->popScene();
}