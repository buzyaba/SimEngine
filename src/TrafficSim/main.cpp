#define WITHOUT_NUMPY
#include <chrono>
#include <algorithm>
#include <vector>
#include <Core/WorkManager.h>

int main(int argc, char** argv) {
  try
  {
    GlobalParameters.LoadConsoleParameters(argc, argv);
  }
  catch (...)
  {
    std::cout << "Error Load Parameters!!!" << std::endl;
  }
  TWorkManager* workManager;

  try
  {
    workManager = new TWorkManager(GlobalParameters);
    workManager->InitDraw();
  }
  catch (...)
  {
    std::cout << "Error Create WorkManager!!!" << std::endl;
  }

  try
  {
    int _enableVisualisation = 1;
#ifdef USE_OpenGL
    _enableVisualisation = 1;
#else
    _enableVisualisation = 0;
#endif
    workManager->Start(_enableVisualisation);
  }
  catch (...)
  {
    std::cout << "Error Start WorkManager!!!" << std::endl;
  }
  delete workManager;
  return 0;
}
