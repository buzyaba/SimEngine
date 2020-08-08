#pragma once
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Engine/Mesh.hpp>

class MeshRenderer{
    public:
        explicit MeshRenderer(MeshType modelType);
        GLuint getVAO(){return vao;}
        std::vector<GLuint> getIndices() {return indices;}        
    private:
        std::vector<Vertex>vertices;
        std::vector<GLuint>indices;

        GLuint vao, vbo, ebo;
};

class MeshContainer {
    private:
        static MeshContainer* instance;
        MeshRenderer* cubeMesh;
        MeshRenderer* sphereMesh;
        MeshRenderer* triangleMesh;
        MeshRenderer* quadMesh;
        explicit MeshContainer();
        MeshContainer(const MeshContainer&) = delete;
        MeshContainer& operator=(const MeshContainer&) = delete;
        ~MeshContainer();
    public:
        static MeshContainer* getInstance();
        MeshRenderer* getMesh(MeshType type);
};
