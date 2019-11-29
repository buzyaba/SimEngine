#pragma once
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/MeshRenderer.hpp>


class Table : public Primitive {
    private: 
        static void initBuffer();
    protected:
        static MeshRenderer* mesh;
        Transform countertop;
        Transform tableLeg1;
        Transform tableLeg2;
        Transform tableLeg3;
        Transform tableLeg4;
        static unsigned int meshBuffer;
        void initMesh();
    public:
        explicit Table(const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
        void setScale(const glm::vec3& _size) override;
        void static drawElements(const std::vector<Table*> objects);
        void static initDraw(const std::vector<Table*> objects);
};
