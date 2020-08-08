#pragma once
#ifdef USE_OpenGL
#include "Engine/Renderer.hpp"
#endif
#include "Core/StaticObject.h"

class TTestRoom : public TStaticObject {
private:
    void initBuffer() override {};
    unsigned int getMeshBuffer() override { return -1;}
public:
    explicit TTestRoom(std::string _name = ""
#ifdef USE_OpenGL
      , const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f)
#endif
    );
#ifdef USE_OpenGL
    virtual void setScale(const glm::vec3& _size) override;
    virtual void setPosition(const glm::vec3& pos) override;
    virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
    void setScreenTexture(GLuint _text) { otherTextures["screen"] = _text; }
#endif
    void drawElements(const std::vector<TObject*>& objects);
    void initDraw(const std::vector<TObject*>& objects) {}
    virtual TStaticObject* Clone() { return new TTestRoom(); };
    // virtual std::vector<glm::mat4> getModelMatrixes() override;
    virtual std::string ClassName() override { return std::string("TTestRoom"); }
};
