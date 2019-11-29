#pragma once
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/MeshRenderer.hpp>


class Monitor : public Primitive {
    private: 
        static void initBuffer();
    protected:
        static MeshRenderer* mesh;
        Transform monitor;
        Transform stand1;
        Transform stand2;
        Transform screen;
        static unsigned int meshBuffer;
        static unsigned int meshScreenBuffer;
        void initMesh();
    public:
        MeshRenderer* meshScreen;
        explicit Monitor(const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
        void setScale(const glm::vec3& _size) override;
        void static drawElements(const std::vector<Monitor*> objects);
        void static initDraw(const std::vector<Monitor*> objects);
};
