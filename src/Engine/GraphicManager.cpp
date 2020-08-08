#include "Engine/GraphicManager.hpp"

TGraphicManager::TGraphicManager(const int type, std::string windowName)
    : _shader(Utils::getPath("/assets/shaders/VertexShader.vs").c_str(),
              Utils::getPath("/assets/shaders/FragmentShader.fs").c_str())) {
  if (type <= 0)
       _window = new FirstPersonView(800, 600, windowName);
  else
      _window = new IsometricView(800, 600, windowName);
}

void TGraphicManager::addNewObject(TObject *obj) {
  GObjectProperties *objectTransform = new GObjectProperties(obj);
  TGObject *object = new TGObject(objectTransform, _tableModel, _shader);
  graphicObjects.push_back(object);
}

void TGraphicManager::startDraw() {
  do {

    _window->runWindow(0.01f, [&]() {
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto *elem : graphicObjects)
        elem->draw();
    });

  } // Check if the ESC key was pressed or the window was closed
  while (glfwWindowShouldClose(_window->getWindow()) == 0);

  glfwTerminate();
}