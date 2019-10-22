#include <TrafficSim/TrafficSim.hpp>

Camera* camera;
LightRenderer* light;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.f, 1.f, 1.f, 1.f);
    //Drawing objects here
    light->draw();
}

void initApplication() {
    glEnable(GL_DEPTH_TEST);

    ShaderLoader shader;

    GLuint flatShaderProgram = shader.CreateProgram("../assets/shaders/VertexShader.vs", 
    "../assets/shaders/FragmentShader.fs");

    camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 6.0f));
    light = new LightRenderer(MeshType::kTriangle, camera); 
    light->setProgram(flatShaderProgram);
    light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}