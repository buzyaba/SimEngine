#define WITHOUT_NUMPY

#include "Core/WorkManager.h"


int main(int argc, char** argv) {

  try
  {
    parameters.LoadParameters(argc, argv);
  }
  catch (...)
  {
    std::cout << "Error Load Parameters!!!" << std::endl;
  }
  TWorkManager* workManager;

  try
  {
    workManager = new TWorkManager(parameters);
    workManager->InitDraw();
  }
  catch (...)
  {
    std::cout << "Error Create WorkManager!!!" << std::endl;
  }

  try
  {
    workManager->Start(1);
  }
  catch (...)
  {
    std::cout << "Error Start WorkManager!!!" << std::endl;
  }
  delete workManager;
  return 0;
}
