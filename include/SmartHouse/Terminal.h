#pragma once

#include "Engine/Renderer.hpp"
#include "Core/ObjectOfObservation.h"

class TTerminal : public TObjectOfObservation
{
private:
    void initBuffer() override;
    unsigned int getMeshBuffer() override {return meshBuffer;};
protected:
    ///Был ли включен терминал
    bool isWork;
    static GLuint mainTexture;
    static unsigned int meshBuffer;
public:
    explicit TTerminal(std::string _name = "", const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
    virtual void Update() override;
    virtual void setScale(const glm::vec3& _size) override;
    virtual void setPosition(const glm::vec3& pos) override;
    virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
    void setScreenTexture(GLuint _text) { otherTextures["screen"] = _text; }
    void drawElements(const std::vector<TObject*>& objects);
    void initDraw(const std::vector<TObject*>& objects);
    virtual TObjectOfObservation* Clone() { return new TTerminal(*this); };
    virtual std::string ClassName() override { return std::string("TTerminal"); }
    // virtual std::vector<glm::mat4> getModelMatrixes() override;
};
