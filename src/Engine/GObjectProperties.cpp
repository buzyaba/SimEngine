#include "Engine/GObjectProperties.hpp"
#include <iostream>

TGObjectProperties::TGObjectProperties(TObject *obj)
    : pos(obj->GetProperty("Coordinate")),
      scale(obj->GetProperty("Scale")),
      rotate(obj->GetProperty("Rotate")), className(obj->ClassName()),
      textures(obj->getTextures()) 
{
     LRUprop.pos.SetValues(pos.GetValues());
     LRUprop.scale.SetValues(scale.GetValues());
     LRUprop.rotate.SetValues(rotate.GetValues());
     LRUprop.textures = textures;
}

glm::vec3 TGObjectProperties::getPos() {
  return glm::vec3(LRUprop.pos.GetValue("X"), LRUprop.pos.GetValue("Y"),
                   LRUprop.pos.GetValue("Z"));
}

glm::vec3 TGObjectProperties::getScale() {
  return glm::vec3(LRUprop.scale.GetValue("Width"), LRUprop.scale.GetValue("Length"),
                   LRUprop.scale.GetValue("Height"));
}

glm::vec3 TGObjectProperties::getAngles() {
  return glm::vec3(glm::radians(LRUprop.rotate.GetValue("X")), glm::radians(LRUprop.rotate.GetValue("Y")), glm::radians(LRUprop.rotate.GetValue("Z")));
}

void TGObjectProperties::updateLRUProp() {
    if (LRUprop.pos.GetValues() != pos.GetValues())
      LRUprop.pos.SetValues(pos.GetValues());
    
    if (LRUprop.scale.GetValues() != scale.GetValues())
      LRUprop.scale.SetValues(scale.GetValues());

    if (LRUprop.rotate.GetValues() != rotate.GetValues())
      LRUprop.rotate.SetValues(rotate.GetValues());
  
    if (LRUprop.textures != textures)
      LRUprop.textures = textures;
}