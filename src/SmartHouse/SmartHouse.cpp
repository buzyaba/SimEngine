#include <SmartHouse/SmartHouse.hpp>

Camera* camera;
LightRenderer* light;

MeshRenderer* sphere;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.f, 1.f, 0.f, 1.f);
    //Drawing objects here
    light->draw();
    sphere->draw();
}

void initApplication() {
    glEnable(GL_DEPTH_TEST);

    ShaderLoader shader;
    ShaderLoader shader2;

    GLuint flatShaderProgram = shader.CreateProgram("../../assets/shaders/VertexShader.vs", 
    "../../assets/shaders/FragmentShader.fs");
    GLuint texturedShaderProgram = shader.CreateProgram("../../assets/shaders/texturedModel.vs",
    "../../assets/shaders/texturedModel.fs");
    camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(7.0f, 4.0f, 5.0f));
    light = new LightRenderer(MeshType::kCube, camera); 
    light->setProgram(flatShaderProgram);
    light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    TextureLoader tLoader;
    GLuint sphereTexture = tLoader.getTextureID("../assets/textures/globe.jpg");

	// Sphere Mesh

	sphere = new MeshRenderer(MeshType::kSphere, camera);
	sphere->setProgram(texturedShaderProgram);
	sphere->setTexture(sphereTexture);
    sphere->setPosition(glm::vec3(2.0f, 2.0f, 2.0f));
	sphere->setScale(glm::vec3(1.0f));
}