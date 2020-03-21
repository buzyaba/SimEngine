#pragma once

#include "Engine/Renderer.hpp"
#include "Core/ObjectOfObservation.h"

class TTerminal : public TObjectOfObservation
{
private:
    void initBuffer() override;
protected:
    ///Был ли включен терминал
    bool isWork;
    static GLuint mainTexture;
    static unsigned int meshBuffer;
public:
    explicit TTerminal(std::string _name = "", const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
    virtual void Update() override;
    void setScale(const glm::vec3& _size) override;
    void setPosition(const glm::vec3& pos) override;
    void setScreenTexture(GLuint _text) { otherTextures["screen"] = _text; }
    unsigned int getMeshBuffer() override;
    void drawElements(const std::vector<TObject&>& objects);
    void initDraw(const std::vector<TObject&>& objects);
    virtual std::vector<glm::mat4> getModelMatrixes() override;
};
