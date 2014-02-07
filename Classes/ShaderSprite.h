#ifndef __SHADER_SPRITE_H__
#define __SHADER_SPRITE_H__

#include "cocos2d.h"

class ShaderSprite : public cocos2d::Sprite
{
public:
    ShaderSprite();
    ~ShaderSprite();
    
    virtual void initShader();
    void setBackgroundNotification();
    
    void draw();
    void listenBackToForeground(cocos2d::Object *obj);
    
protected:
    virtual void buildCustomUniforms() = 0;
    virtual void setCustomUniforms() = 0;
    
protected:
    std::string _fragSourceFile;
    
protected:
    cocos2d::CustomCommand _renderCommand;
    void onDraw();
    
};

#endif // __SHADER_SPRITE_H__