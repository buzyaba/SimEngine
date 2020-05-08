#include "Core/Parameters.h"

TParameters parameters;

TParameters::TParameters(int argc, char** argv)
{
  LoadParameters(argc, argv);
}

void TParameters::LoadParameters(int argc, char** argv)
{
  cwd = Renderer::getCWD();
  auto c_cwd = cwd;
  std::transform(c_cwd.begin(), c_cwd.end(), c_cwd.begin(), toupper);
  i = c_cwd.find("SIMENGINE");

  _window = new FirstPersonView(800, 600, "Smart House");;
  type = -1;
  _script = cwd.substr(0, i + 9) + "/ConfigFiles/conf.xml";
  _xmlFile = cwd.substr(0, i + 9) + "/ConfigFiles/Room.xml";
  _millisecondsOfTimeStep = 1000;
  _delay = 0.0;
  _fractionOfTimeStep = -1.0;
  _maxStep = 1000; ////60*60*24*30//~месяц
}
