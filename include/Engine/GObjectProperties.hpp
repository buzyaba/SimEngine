#pragma once

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include "Core/Object.h"
#include "Core/Properties.h"

class TGObjectProperties {
  private:
    IProperties &pos;
    IProperties &scale;
    IProperties &rotate;
    std::vector<std::vector<std::string>>& textures;
    std::string className;
  public:
    TGObjectProperties(TObject *obj);
    glm::vec3 getPos();
    glm::vec3 getScale();
    glm::vec3 getAngles();
    std::vector<std::vector<std::string>>& getTextures() { return textures; }
    std::string getName() {return className;}
};