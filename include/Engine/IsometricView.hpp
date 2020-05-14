#pragma once

#include <Engine/WindowManager.hpp>

class IsometricView: public WindowManager {
 public:
    IsometricView(const std::uint32_t& screenWidth = 800, const std::uint32_t& screenHeight = 600,
                    const std::string winName = "Window", bool _visible = true);
 private:
    static glm::vec3 cartesianToSpherical(glm::vec3 vec);
    static glm::vec3 sphericalToCartesian(glm::vec3 vec);

    virtual void cameraMovement(float dt) override;
    static void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void initMousePosition(GLfloat x, GLfloat y);
    static void updateMouse(GLFWwindow* window, double xpos, double ypos);
    static void updateMouseButtons(GLFWwindow* window, int button, int action, int mods);
    static void updateScroll(GLFWwindow* window, double xoffset, double yoffset);
};