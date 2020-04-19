#pragma once

#include "Engine/Renderer.hpp"
#include "Core/StaticObject.h"

class TRoom : public TStaticObject {
private:
    void initBuffer() override {};
    unsigned int getMeshBuffer() override { return -1;}
    // unsigned int getMeshBuffer() override {return meshBuffer;};
// protected:
//     static unsigned int meshBuffer;
public:
    explicit TRoom(std::string _name = "", const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
    virtual void setScale(const glm::vec3& _size) override;
    virtual void setPosition(const glm::vec3& pos) override;
    virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
    void setScreenTexture(GLuint _text) { otherTextures["screen"] = _text; }
    void drawElements(const std::vector<TObject*>& objects);
    void initDraw(const std::vector<TObject*>& objects) {}
    // virtual std::vector<glm::mat4> getModelMatrixes() override;
};


// class Room : public Primitive {
//     private: 
//         static void initBuffer();
//     protected:
//         static MeshRenderer* mesh;
//         static GLuint wallTexture;
//         GLuint floorTexture;
//         GLuint ceilingTexture;
//         Transform leftWall;
//         Transform rightWall;
//         Transform frontWall;
//         Transform backWall;
//         Transform floor;
//         Transform ceiling;
//         static unsigned int meshBuffer;
//         void initMesh();
        
//     public:
//         explicit Room(const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
//         void setScale(const glm::vec3& _size) override;
//         void setPosition(const glm::vec3& pos) override;
//         void setWallTexture(GLuint _text) {wallTexture = _text;}
//         void setFloorTexture(GLuint _text) {floorTexture = _text;}
//         void setCeilingTexture(GLuint _text) {ceilingTexture = _text;}
//         void static drawElements(const std::vector<Room*> objects);
//         void static initDraw(const std::vector<Room*> objects);
// };
