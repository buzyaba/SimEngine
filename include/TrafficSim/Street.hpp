#pragma once

#include <Core/StaticObject.h>

class TStreet: public TStaticObject {
 private:
    void initBuffer() noexcept override {};
    unsigned int getMeshBuffer() noexcept override { return -1;}
 public:
    explicit TStreet(std::string _name = "", const glm::vec3& _pos = glm::vec3(0.0f), 
                                             const glm::vec2& _scale = glm::vec2(1.f));
    virtual std::string ClassName() noexcept override {return "TStreet";}
    virtual TStaticObject* Clone() {return new TStreet;}
    virtual void setScale(const glm::vec3& _size) override;
    virtual void setPosition(const glm::vec3& pos) override;
    virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
    virtual void drawElements(const std::vector<TObject*>& objects) override;
    virtual void initDraw(const std::vector<TObject*>& objects) override {};
};
