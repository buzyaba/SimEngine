#pragma once

#include "WindowManager.hpp"
#include <vector>
#include <atomic>
#include <map>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "Engine/FirstPersonView.hpp"
#include "Engine/IsometricView.hpp"

#include <Engine/Model.hpp>
#include <Engine/Shader.hpp>

#include "SimEngine/Object.h"
#include "Engine/GObject.hpp"
#include "Engine/GObjectProperties.hpp"

class TGraphicPresenter;

class TGraphicManager {
private:
    friend class TGraphicPresenter;
    WindowManager *_window;
    std::map<std::string, Model*> modelMap;
    std::vector<TGObject*> graphicObjects;
    Shader _shader;
    Model* createModel(const std::string name);
    WindowManager* createWindow(const int type, const int width, const int height, const std::string name);
    std::atomic<bool> needUpdateFlag{ false };

    void updateLRU();
public:
    TGraphicManager(const int type, std::string windowName);
    void addNewObject(TObject *obj);
    void startDraw();
    void stopDraw();
};