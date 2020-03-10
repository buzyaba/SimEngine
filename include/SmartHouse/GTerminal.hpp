#pragma once
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/MeshRenderer.hpp>


class GTerminal : public Primitive {
    private: 
        static void initBuffer();
    protected:
        static MeshRenderer* mesh;
        static GLuint mainTexture;
        GLuint screenTexture;
        Transform monitor;
        Transform stand1;
        Transform stand2;
        Transform screen;
        static unsigned int meshBuffer;
        void initMesh();
    public:
        explicit GTerminal(const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
        void setScale(const glm::vec3& _size) override;
        void setPosition(const glm::vec3& pos) override;
        void setScreenTexture(GLuint _text) {screenTexture = _text;}
        void drawElements(const std::vector<Primitive*> objects) override;
        void initDraw(const std::vector<Primitive*> objects) override;
};
