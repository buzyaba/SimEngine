#pragma once

#include "Engine/GObjectProperties.hpp"
#include "Engine/Model.hpp"
#include "Engine/Shader.hpp"

class TGObject {
private:
  TGObjectProperties *_transform;
  Model *_model;
  Shader &_shader;

public:
  TGObject(TGObjectProperties *transform, Model *model, Shader &shader)
      : _transform(transform), _model(model), _shader(shader) {}
  void updateLRU() { _transform->updateLRUProp(); }
  void draw();
};
