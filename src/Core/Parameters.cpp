#include "Core/Parameters.h"

TParameters GlobalParameters;

void TParameters::DefaultParameters()
{
#ifdef USE_OpenGL
  cwd = Renderer::getCWD();
  auto c_cwd = cwd;
  std::transform(c_cwd.begin(), c_cwd.end(), c_cwd.begin(), toupper);
  size_t i = c_cwd.find("SIMENGINE");

  _window = new FirstPersonView(800, 600, "Smart House");;

  xmlEnvironmentScriptName = cwd.substr(0, i + 9) + "/ConfigFiles/conf.xml";
  xmlMainSetConfigurationFile = cwd.substr(0, i + 9) + "/ConfigFiles/Room.xml";
#else
  xmlEnvironmentScriptName = "";
  xmlMainSetConfigurationFile = "";
#endif
  type = -1;
  millisecondsInTimeStep = 1000;
  timeAcceleration = 0.0;
  maxStep = 1000; ////60*60*24*30//~месяц
}

void TParameters::LoadXML()
{
}

TParameters::TParameters(int argc, char** argv)
{
  LoadConsoleParameters(argc, argv);
}

void TParameters::LoadConsoleParameters(int argc, char** argv)
{
  DefaultParameters();
}

std::string TParameters::Print()
{
  return std::string();
}

void TParameters::ConsoleInterface()
{
}
