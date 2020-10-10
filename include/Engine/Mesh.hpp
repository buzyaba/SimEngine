#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Shader.hpp"

#include <string>
#include <vector>
using namespace std;

struct Vertex {

  glm::vec3 Position;

  glm::vec3 Normal;

  glm::vec2 TexCoords;

  glm::vec3 Tangent;

  glm::vec3 Bitangent;
};

struct Texture {
  unsigned int id;
  string type;
};

class Mesh {
public:
  vector<Vertex> _vertices;
  vector<unsigned int> _indices;
  std::map<std::string, Texture> _textures;
  unsigned int VAO;

  Mesh(vector<Vertex> vertices, vector<unsigned int> indices,
       std::map<std::string, Texture> textures)
      : _vertices(vertices), _indices(indices), _textures(textures) {
    setupMesh();
  }

  void Draw(Shader &shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    size_t iter = 0;
    for (auto&  text : _textures) {
      glActiveTexture(GL_TEXTURE0 + iter);

      string number;
      string name = text.second.type;
      if (name == "texture_diffuse")
        number = std::to_string(diffuseNr++);
      else if (name == "texture_specular")
        number = std::to_string(specularNr++);
      else if (name == "texture_normal")
        number = std::to_string(normalNr++);
      else if (name == "texture_height")
        number = std::to_string(heightNr++);

      glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), iter++);

      glBindTexture(GL_TEXTURE_2D, text.second.id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
  }

private:
  unsigned int VBO, EBO;

  void setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex),
                 &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 _indices.size() * sizeof(unsigned int), &_indices[0],
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, TexCoords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, Tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
  }
};
