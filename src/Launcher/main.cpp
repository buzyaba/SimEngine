#define WITHOUT_NUMPY

#include "Core/WorkManager.h"
#include "Engine/GraphicPresenter.hpp"
#ifdef USE_OPENGL
#include "Engine/GraphicManager.hpp"
#include <thread>
#endif
#include <iostream>

int main(int argc, char **argv) {
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
  try {
    workManager = new TWorkManager(GlobalParameters, presenter);
  } catch (...) {
    std::cout << "Error Create WorkManager!!!" << std::endl;
  }

  int _enableVisualisation = 0;
#ifdef USE_OPENGL
  TGraphicManager *graphicManager =
      new TGraphicManager(GlobalParameters.type, "SimEngine");
  presenter->setGraphicManager(graphicManager);
  workManager->sendObjects();
  _enableVisualisation = 1;
  // what with error handling?
  std::thread(&TWorkManager::Start, workManager, _enableVisualisation).detach();
  graphicManager->startDraw();
  workManager->Stop();
  delete graphicManager;
#else
  try {
    workManager->Start(_enableVisualisation);
  } catch (...) {
    std::cout << "Error Start WorkManager!!!" << std::endl;
  }
#endif

  delete workManager;
  delete presenter;
  return 0;
}
