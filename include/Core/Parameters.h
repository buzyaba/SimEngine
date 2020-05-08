#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>
#ifdef USE_OpenGL
#include <Engine/FirstPersonView.hpp>
#endif
#include "Core/common.h"

class TParameters
{
public:
#ifdef USE_OpenGL
  WindowManager* _window;
#endif
  int type = 0;
  std::string _script = "";
  std::string _xmlFile = "";
  unsigned int _millisecondsOfTimeStep = 1000;
  double _delay = 0;
  double _fractionOfTimeStep = -1.0;
  unsigned long _maxStep = 1000;

  int tick = 0;
  bool windowFlag = false;

  std::string cwd;
  size_t i;

  TParameters(int argc = 0, char** argv = 0);
  void LoadParameters(int argc = 0, char** argv = 0);

};

extern TParameters parameters;