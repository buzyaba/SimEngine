#pragma once
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/MeshRenderer.hpp>

class Road: public Primitive {
 private:
    static MeshRenderer* mesh;
    static GLuint texture;
    static unsigned int buffer;
    void initMesh();
    void setScale(const glm::vec3& _size) override {}
 public:
    explicit Road(const glm::vec3& pos=glm::vec3(0.0f));
    ~Road() {if(mesh) delete mesh;}
    static void drawElements(const std::vector<Road*> objects);
    static void initDraw(const std::vector<Road*> objects);
};