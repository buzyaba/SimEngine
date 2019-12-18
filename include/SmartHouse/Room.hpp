#pragma once
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/MeshRenderer.hpp>


class Room : public Primitive {
    private: 
        static void initBuffer();
    protected:
        static MeshRenderer* mesh;
        static GLuint wallTexture;
        GLuint floorTexture;
        GLuint ceilingTexture;
        Transform leftWall;
        Transform rightWall;
        Transform frontWall;
        Transform backWall;
        Transform floor;
        Transform ceiling;
        static unsigned int meshBuffer;
        void initMesh();
        
    public:
        explicit Room(const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
        void setScale(const glm::vec3& _size) override;
        void setPosition(const glm::vec3& pos) override;
        void setWallTexture(GLuint _text) {wallTexture = _text;}
        void setFloorTexture(GLuint _text) {floorTexture = _text;}
        void setCeilingTexture(GLuint _text) {ceilingTexture = _text;}
        void static drawElements(const std::vector<Room*> objects);
        void static initDraw(const std::vector<Room*> objects);
};
