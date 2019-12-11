// #pragma once
// #include <Engine/Object.hpp>
// #include <Engine/Renderer.hpp>
// #include <Engine/MeshRenderer.hpp>

class Ground: public Primitive {
    protected:
        static MeshRenderer* mesh;
        static unsigned int buffer;
        void initMesh();
    public:
        explicit Ground(const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
        ~Ground() {if (mesh) delete mesh;}
        void setScale(const glm::vec3& _size) override;
        void static drawElements(const std::vector<Ground*> objects);
        void static initDraw(const std::vector<Ground*> objects);
};
