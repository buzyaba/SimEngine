#pragma once
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Mesh.hpp"

class MeshRenderer{
    public:
        MeshRenderer(MeshType modelType);
        GLuint getVAO(){return vao;}
        std::vector<GLuint> getIndices() {return indices;}        
    private:
        std::vector<Vertex>vertices;
        std::vector<GLuint>indices;

        GLuint vao, vbo, ebo;
};