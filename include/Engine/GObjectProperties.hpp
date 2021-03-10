#pragma once

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include "SimEngine/Object.h"
#include "SimEngine/Properties.h"

class TGObjectProperties {

    struct LRUProperties {
        TProperties pos;
        TProperties scale;
        TProperties rotate;
        std::vector<std::vector<std::string>> textures;
    } LRUprop;
  
    IProperties &pos;
    IProperties &scale;
    IProperties &rotate;
    std::vector<std::vector<std::string>>& textures;
    std::string className;
  public:
    TGObjectProperties(TObject *obj);

    void updateLRUProp();

    glm::vec3 getPos();
    glm::vec3 getScale();
    glm::vec3 getAngles();
    std::vector<std::vector<std::string>>& getTextures() { return LRUprop.textures; }
    std::string getName() {return className;}
};