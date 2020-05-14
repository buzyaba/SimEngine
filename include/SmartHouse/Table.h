#pragma once
#ifdef USE_OpenGL
#include "Engine/Renderer.hpp"
#endif
#include "BasicExamples/StaticObject.h"

class TTable : public TStaticObject {
private:
    void initBuffer() override;
    unsigned int getMeshBuffer() override { return meshBuffer;}
protected:
#ifdef USE_OpenGL
    static GLuint mainTexture;
#endif
    static unsigned int meshBuffer;
public:
    explicit TTable(std::string _name = ""
#ifdef USE_OpenGL
      , const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f)
#endif
    );
#ifdef USE_OpenGL
    virtual void setScale(const glm::vec3& _size) override;
    virtual void setPosition(const glm::vec3& pos) override;
    virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
#endif
    void drawElements(const std::vector<TObject*>& objects);
    void initDraw(const std::vector<TObject*>& objects);
    virtual TStaticObject* Clone() { return new TTable(); };
    virtual std::string ClassName() override { return std::string("TTable"); }
};
