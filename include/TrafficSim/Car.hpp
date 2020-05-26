#pragma once
#include <BasicExamples/ObjectOfObservation.h>

class TCar : public TObjectOfObservation {
protected:
    //GL
    static unsigned int meshBuffer;
    void initBuffer() override;
    unsigned int getMeshBuffer() override { return meshBuffer; };
public:
    explicit TCar(std::string _name = ""
#ifdef USE_OpenGL
        , const glm::vec3& _pos = glm::vec3(.0f), const glm::vec3& _scale = glm::vec3(1.0f)
#endif
    );
#ifdef USE_OpenGL
    virtual void setScale(const glm::vec3& _size) override;
    virtual void setPosition(const glm::vec3& pos) override;
    virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
#endif
    void drawElements(const std::vector<TObject*>& objects);
    void initDraw(const std::vector<TObject*>& objects);
    virtual TObjectOfObservation* Clone() { return new TCar(); }
    virtual std::string ClassName() override { return "TCar"; }
    virtual void Update() override;
};