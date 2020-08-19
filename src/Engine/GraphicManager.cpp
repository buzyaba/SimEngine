#define STB_IMAGE_IMPLEMENTATION
#include "Engine/GraphicManager.hpp"

WindowManager *TGraphicManager::createWindow(const int type, const int width,
                                             const int height,
                                             const std::string name) {
  if (type <= 0)
    return new FirstPersonView(width, height, name);
  else
    return new IsometricView(width, height, name);
  return nullptr;
}

TGraphicManager::TGraphicManager(const int type, std::string windowName)
    : _shader(Renderer::getPath("/assets/shaders/VertexShader.vs").c_str(),
              Renderer::getPath("/assets/shaders/FragmentShader.fs").c_str()),
      _window(createWindow(type, 800, 600, windowName)) {}

Model *TGraphicManager::createModel(const std::string name) {
  return new Model(Renderer::getPath("/assets/models/" + name));
}

void TGraphicManager::addNewObject(TObject *obj) {
  TGObjectProperties *objectTransform = new TGObjectProperties(obj);
  auto name = objectTransform->getName();
  auto elem = modelMap.find(name);
  if (elem == modelMap.end()) {
    modelMap.insert({name, createModel(name)});
  }
  TGObject *object = new TGObject(objectTransform, modelMap.at(name), _shader);
  graphicObjects.push_back(object);
}

void TGraphicManager::startDraw() {
  double curTime = glfwGetTime(), prevTime = glfwGetTime(), deltaTime = prevTime - curTime;
  do {
    curTime = glfwGetTime();
    deltaTime = curTime - prevTime;
    _window->runWindow(deltaTime, [&]() {
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      for (auto *elem : graphicObjects)
        elem->draw();
    });
    prevTime = curTime;

    std::cout << "ELAPSED TIME RENDER: " << deltaTime << std::endl;
  } // Check if the ESC key was pressed or the window was closed
  while (glfwWindowShouldClose(_window->getWindow()) == 0);

  glfwTerminate();
}