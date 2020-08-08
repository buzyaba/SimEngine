#include "GObjectProperties.hpp"

TGObjectProperties::TGObjectProperties(TObject *obj) : pos(obj->GetProperty("Coordinate")), scale(obj->GetProperty("Dimensions")),
  className(obj->ClassName()) {}
  
glm::vec3 TGObjectProperties::getPos() {
  return glm::vec3(pos->GetValues()["X"], pos->GetValues()["Y"],
                   pos->GetValues()["Z"]);
}

glm::vec3 TGObjectProperties::getScale() {
  return glm::vec3(scale->GetValues()["Width"], scale->GetValues()["Length"],
                   scale->GetValues()["Height"]);
}