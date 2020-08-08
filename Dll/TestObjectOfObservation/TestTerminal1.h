#pragma once
#ifdef USE_OpenGL
#include "Engine/Renderer.hpp"
#endif
#include "BasicExamples/ObjectOfObservation.h"

class TTestTerminal1 : public TObjectOfObservation
{
private:
    void initBuffer() override;
    unsigned int getMeshBuffer() override {return meshBuffer;};
protected:
    ///Был ли включен терминал
    bool isWork;
#ifdef USE_OpenGL
    static GLuint mainTexture;
#endif
    static unsigned int meshBuffer;
public:

    explicit TTestTerminal1(std::string _name = ""
#ifdef USE_OpenGL
      , const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f)
#endif
    );

    virtual void Update() override;

#ifdef USE_OpenGL
    virtual void setScale(const glm::vec3& _size) override;
    virtual void setPosition(const glm::vec3& pos) override;
    virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
    void setScreenTexture(GLuint _text) { otherTextures["screen"] = _text; }
#endif

    void drawElements(const std::vector<TObject*>& objects);
    void initDraw(const std::vector<TObject*>& objects);
    virtual TObjectOfObservation* Clone() { return new TTestTerminal1(); };
    virtual std::string ClassName() override { return std::string("TTestTerminal1"); }
    // virtual std::vector<glm::mat4> getModelMatrixes() override;
};
