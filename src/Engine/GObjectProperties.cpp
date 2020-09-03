#include "Engine/GObjectProperties.hpp"

TGObjectProperties::TGObjectProperties(TObject *obj)
    : pos(obj->GetProperty("Coordinate")),
      scale(obj->GetProperty("Scale")),
      rotate(obj->GetProperty("Rotate")), className(obj->ClassName()),
      textures(obj->getTextures()) {}

glm::vec3 TGObjectProperties::getPos() {
  return glm::vec3(pos.GetValue("X"), pos.GetValue("Y"),
                   pos.GetValue("Z"));
}

glm::vec3 TGObjectProperties::getScale() {
  return glm::vec3(scale.GetValue("Width"), scale.GetValue("Length"),
                   scale.GetValue("Height"));
}

glm::vec3 TGObjectProperties::getAngles() {
  return glm::vec3(glm::radians(rotate.GetValue("X")), glm::radians(rotate.GetValue("Y")), glm::radians(rotate.GetValue("Z")));
}
