#pragma once

#include "WindowManager.hpp"
#include <vector>
#include <map>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "Engine/FirstPersonView.hpp"
#include "Engine/IsometricView.hpp"

#include <Engine/Model.hpp>
#include <Engine/Shader.hpp>

#include "Core/Object.h"
#include "Engine/GObject.hpp"
#include "Engine/GObjectProperties.hpp"

class TGraphicManager {
private:
  WindowManager *_window;
  std::map<std::string, Model&> modelMap;  
  std::vector<TGObject*> graphicObjects;
  Shader _shader;

public:
  TGraphicManager(const int type, std::string windowName);
  void addNewObject(TObject *obj);
  void startDraw();
};