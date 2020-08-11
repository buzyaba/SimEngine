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
    std::string className;
  public:
    TGObjectProperties(TObject *obj);
    glm::vec3 getPos();
    glm::vec3 getScale();
    std::string getName() {return className;}
};