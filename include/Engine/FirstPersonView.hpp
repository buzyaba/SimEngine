#pragma once

#include "Engine/WindowManager.hpp"



class FirstPersonView : public WindowManager {
public:
    FirstPersonView(const std::uint32_t& screenWidth = 800, const std::uint32_t& screenHeight = 600,
                    const std::string winName = "Window", bool _visible = true); 
private:
    virtual void cameraMovement(float dt) override;
    static void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void updateMouse(GLFWwindow* window, double xpos, double ypos);
};
