#include <SmartHouse/SmartHouse.hpp>

int main(int argc, char **argv){
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, 
    "SmartHouse", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    while(!glfwWindowShouldClose(window)){
        renderScene();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
