#include "Core/WorkManager.h"
#include "Core/Dll_manager.h"
#include "Engine/GraphicPresenter.hpp"
#ifdef USE_OPENGL
#include "Engine/GraphicManager.hpp"
#include <thread>
#endif
#include <iostream>

int main(int argc, const char **argv) {
  try {
    GlobalParameters.LoadConsoleParameters(argc, argv);
  } catch (...) {
    std::cout << "Error Load Parameters!!!" << std::endl;
  }
  IGraphicPresenter *presenter;
  TWorkManager *workManager;
#ifdef USE_OPENGL
  presenter = new TGraphicPresenter();
#else
  presenter = new IGraphicPresenter();
#endif
  workManager = new TWorkManager(GlobalParameters, presenter);

#ifdef USE_OPENGL
  TGraphicManager *graphicManager =
      new TGraphicManager(GlobalParameters.type, "SimEngine");
  presenter->setGraphicManager(graphicManager);
  workManager->sendObjects();
  // what with error handling?
  std::thread(&TWorkManager::Start, workManager).detach();
  graphicManager->startDraw();
  workManager->Stop();
  delete graphicManager;
#else
  try {
    workManager->Start();
  } catch (...) {
    std::cout << "Error Start WorkManager!!!" << std::endl;
  }
#endif
  delete presenter;
  delete workManager;
  return 0;
}
