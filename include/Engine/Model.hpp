#pragma once

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Mesh.hpp"
#include "Engine/Shader.hpp"

#ifdef WIN32
#include <Windows.h>
#else
#include <dirent.h>
#endif

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Model {
public:
  Model(string const &dir) : _directory(dir) {
    _texture_formats = std::vector<std::string>{".jpg", ".png"};
    loadModel();
  }

  void Draw(Shader shader) {
    for (unsigned int i = 0; i < _meshes.size(); i++)
      _meshes[i].Draw(shader);
  }

private:
  void loadModel() {
    Assimp::Importer importer;
    std::string objPath;
#ifdef WIN32
    WIN32_FIND_DATA file_data;
    HANDLE h = FindFirstFile((_directory + "/*").c_str(), &file_data);
    if (h != INVALID_HANDLE_VALUE) {
      do {
        const std::string file_name = file_data.cFileName;
        const std::string full_file_name = _directory + "/" + file_name;
        if (full_file_name.find(".obj") != std::string::npos) {
          path = full_file_name;
        }
        for (auto string_type : _texture_formats) {
          if (full_file_name.find(string_type) != std::string::npos) {
            Texture texture;
            texture.id = TextureFromFile(full_file_name.c_str());
            _textures_loaded.insert({file_name, texture});
            break;
          }
        }
      } while (FindNextFile(h, &file_data));
    }
#else
    DIR *dir;
    dirent *ent;
    const char *dirPath = _directory.c_str();
    dir = opendir(dirPath);
    while ((ent = readdir(dir)) != NULL) {
      const std::string file_name = ent->d_name;
      const std::string full_file_name = _directory + "/" + file_name;
      if (full_file_name.find(".obj") != std::string::npos) {
        objPath = full_file_name;
      }
      for (auto string_type : _texture_formats) {
        if (full_file_name.find(string_type) != std::string::npos) {
          Texture texture;
          texture.id = TextureFromFile(full_file_name.c_str());
          _textures_loaded.insert({file_name, texture});
          break;
        }
      }
    }
    closedir(dir);
#endif
    const aiScene *scene =
        importer.ReadFile(objPath, aiProcess_Triangulate | aiProcess_FlipUVs |
                                       aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
      cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
      return;
    }
    processNode(scene->mRootNode, scene);
  }

  void processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      _meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
      processNode(node->mChildren[i], scene);
    }
  }

  Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    std::map<std::string, Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      Vertex vertex;
      glm::vec3 vector;

      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.Position = vector;

      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;

      if (mesh->mTextureCoords[0]) {
        glm::vec2 vec;

        vec.x = mesh->mTextureCoords[0][i].x;
        vec.y = mesh->mTextureCoords[0][i].y;
        vertex.TexCoords = vec;
      } else
        vertex.TexCoords = glm::vec2(0.0f, 0.0f);

      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
      vertex.Tangent = vector;

      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
      vertex.Bitangent = vector;
      vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];

      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    loadMaterialTextures(textures, material, aiTextureType_DIFFUSE,
                         "texture_diffuse");

    loadMaterialTextures(textures, material, aiTextureType_SPECULAR,
                         "texture_specular");

    loadMaterialTextures(textures, material, aiTextureType_HEIGHT,
                         "texture_normal");

    loadMaterialTextures(textures, material, aiTextureType_AMBIENT,
                         "texture_height");

    return Mesh(vertices, indices, textures);
  }

  void loadMaterialTextures(std::map<std::string, Texture> &textures,
                            aiMaterial *mat, aiTextureType type,
                            string typeName) {
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
      aiString str;
      mat->GetTexture(type, i, &str);
      std::string textureName{str.C_Str()};
      _textures_loaded[textureName].type = typeName;
      textures.insert({textureName, _textures_loaded[textureName]});
    }
  }

  unsigned int TextureFromFile(const string &path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    int width, height, nrComponents;
    unsigned char *data =
        stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
      GLenum format;
      if (nrComponents == 1)
        format = GL_RED;
      else if (nrComponents == 3)
        format = GL_RGB;
      else if (nrComponents == 4)
        format = GL_RGBA;

      glBindTexture(GL_TEXTURE_2D, textureID);
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                      GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      stbi_image_free(data);
    } else {
      std::cout << "Texture failed to load at path: " << path << std::endl;
      stbi_image_free(data);
    }
    return textureID;
  }

private:
  std::map<std::string, Texture> _textures_loaded;
  vector<Mesh> _meshes;
  string _directory;
  std::vector<std::string> _texture_formats;
};
