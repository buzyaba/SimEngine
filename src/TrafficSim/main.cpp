#define WITHOUT_NUMPY
#include <chrono>
#include <algorithm>
#include <vector>
#include <Core/WorkManager.h>

int main(int argc, char** argv) {
	// window = new IsometricView(800, 600, "TrafficSim");
	// auto cwd = Renderer::getCWD();
    // auto c_cwd = cwd;
    // std::transform(c_cwd.begin(), c_cwd.end(), c_cwd.begin(), toupper);
    // auto i = c_cwd.find("SIMENGINE");
	// workManager = new TWorkManager(window, 1, cwd.substr(0,i+9) + "/ConfigFiles/conf_traffic.xml",
	// 	cwd.substr(0,i+9) + "/ConfigFiles/Street.xml");
	// workManager->InitDraw();
	// workManager->Start();
	// delete workManager;
	// return 0;
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
