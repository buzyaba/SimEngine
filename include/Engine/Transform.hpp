#pragma once
#include <Engine/Camera.hpp>
#include <Engine/ShaderLoader.hpp>
#include <Engine/TextureLoader.hpp>


class Transform {
    private:
        glm::vec3 pos, scale;
        glm::vec3 rotation;
        glm::mat4 modelMatrix;
    public:
        explicit Transform();
        glm::mat4 getModelMatrix() {return modelMatrix;};
        void setModelMatrix(glm::mat4 _modelMatrix) { modelMatrix = _modelMatrix; }
        glm::vec3 getRotation() {return rotation;}
        glm::vec3 getPosition() { return pos; }
        glm::vec3 getScale() { return scale; }
};
