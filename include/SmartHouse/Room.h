#pragma once

#include "Engine/Renderer.hpp"
#include "Core/StaticObject.h"

class TRoom : public TStaticObject {
private:
    void initBuffer() override {};
    unsigned int getMeshBuffer() override { return -1;}
public:
    explicit TRoom(std::string _name = "", const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
    virtual void setScale(const glm::vec3& _size) override;
    virtual void setPosition(const glm::vec3& pos) override;
    virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
    void setScreenTexture(GLuint _text) { otherTextures["screen"] = _text; }
    void drawElements(const std::vector<TObject*>& objects);
    void initDraw(const std::vector<TObject*>& objects) {}
    virtual TStaticObject* Clone() { return new TRoom(*this); };
    // virtual std::vector<glm::mat4> getModelMatrixes() override;
};
