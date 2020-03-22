#pragma once

#include "Engine/WindowManager.hpp"



class FirstPersonView : public WindowManager {
public:
    FirstPersonView(const uint& screenWidth = 800, const uint& screenHeight = 600,
                    const std::string winName = "Window"); 
private:
    virtual void cameraMovement(float dt) override;
    static void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void updateMouse(GLFWwindow* window, double xpos, double ypos);
};
