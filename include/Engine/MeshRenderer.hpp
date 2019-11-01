#pragma once

#include <vector>

#include <Engine/Camera.hpp>
#include <Engine/LightRenderer.hpp>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <btBulletDynamicsCommon.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
class MeshRenderer{
    public:
        MeshRenderer(MeshType modelType, Camera* _camera, btRigidBody* _rigidBody);
        ~MeshRenderer();
        void draw();
        void setPosition(glm::vec3 _position);
        void setScale(glm::vec3 _scale);
        void setProgram(GLuint _program);
        void setTexture(GLuint _textureID);

        btRigidBody* rigidBody;

    protected:
        std::vector<Vertex>vertices;
        std::vector<GLuint>indices;
        glm::mat4 modelMatrix;

        Camera* camera;

        glm::vec3 position, scale;
        GLuint vao, vbo, ebo, texture, program;
    
};