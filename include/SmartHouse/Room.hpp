// #pragma once
// #include <Engine/Object.hpp>
// #include <Engine/Renderer.hpp>
// #include <Engine/MeshRenderer.hpp>


// class Room : public Primitive {
//     private: 
//         static void initBuffer();
//     protected:
//         static MeshRenderer* mesh;
//         Transform leftWall;
//         Transform rightWall;
//         Transform frontWall;
//         Transform backWall;
//         Transform floor;
//         Transform ceiling;
//         static unsigned int meshBuffer;
//         void initMesh();
        
//     public:
//         explicit Room(const glm::vec3& pos=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));
//         void setScale(const glm::vec3& _size) override;
//         void static drawElements(const std::vector<Room*> objects);
//         void static initDraw(const std::vector<Room*> objects);
// };
