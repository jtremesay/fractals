#include "ShaderSprite.h"

USING_NS_CC;

ShaderSprite::ShaderSprite()
{
}

ShaderSprite::~ShaderSprite()
{
}

void ShaderSprite::setBackgroundNotification()
{
    #if CC_ENABLE_CACHE_TEXTURE_DATA
    auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
        this->setShaderProgram(nullptr);
        this->initShader();
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    #endif
}

void ShaderSprite::initShader()
{
    GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(
        FileUtils::getInstance()->fullPathForFilename(_fragSourceFile).c_str())->getCString();
        auto program = new GLProgram();
        program->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
        setShaderProgram(program);
        program->release();
        
        CHECK_GL_ERROR_DEBUG();
        
        program->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        program->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        program->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        
        CHECK_GL_ERROR_DEBUG();
        
        program->link();
        
        CHECK_GL_ERROR_DEBUG();
        
        program->updateUniforms();
        
        CHECK_GL_ERROR_DEBUG();
        
        buildCustomUniforms();
        
        CHECK_GL_ERROR_DEBUG();
}

void ShaderSprite::draw()
{
    _renderCommand.init(_globalZOrder);
    _renderCommand.func = CC_CALLBACK_0(ShaderSprite::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_renderCommand);
    
}

void ShaderSprite::onDraw()
{
    CC_NODE_DRAW_SETUP();
    
    setCustomUniforms();
    
    GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    GL::bindTexture2D( getTexture()->getName());
    
    //
    // Attributes
    //
    #define kQuadSize sizeof(_quad.bl)
    size_t offset = (size_t)&_quad;
    
    // vertex
    int diff = offsetof( V3F_C4B_T2F, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( V3F_C4B_T2F, texCoords);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( V3F_C4B_T2F, colors);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
