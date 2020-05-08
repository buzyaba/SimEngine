#pragma once

#include <string>
#include <vector>

#include "BasicExamples/Sensor.h"
#include "BasicExamples/Actuator.h"
#include "BasicExamples/SmartThing.h"
#include "BasicExamples/ObjectOfObservation.h"
#include "BasicExamples/Properties.h"
#include "BasicExamples/StaticObject.h"
#include "BasicExamples/ManagementProgram.h"
#include "Core/DataStore.h"
#include "BasicExamples/DataPacket.h"
#include "Core/EnvironmentScript.h"
#include "Core/MainSet.h"

#include "Core/common.h"
#include "Core/Parameters.h"
#ifdef USE_OpenGL
#include <Engine/WindowManager.hpp>
#endif

/// Класс 
class TWorkManager
{
protected:
  ///
  std::vector<TObjectOfObservation*> objects;
  std::vector<TSmartThing*> things;
  std::vector<TStaticObject*> staticObjects;

  TEnvironmentScript* script;
  IManagementProgram* program;
  TDataStore* storage;

  unsigned int maxStep;
  TMainSet* mainSet;
  unsigned int timeStep;
  double fractionOfTimeStep;
  double delay;
  unsigned long int time;
  std::string xmlFile, xmlScript;
  std::chrono::time_point<std::chrono::steady_clock> startWork;
#ifdef USE_OpenGL
  WindowManager* window;
#endif

  void Step(unsigned int& t, std::chrono::milliseconds& delayTime, const unsigned short& _enableVisualisation);

public:

  TWorkManager(TParameters& param = parameters);

  ~TWorkManager();
  void Start(const unsigned short& _enableVisualisation = 1);
  void Stop();
  void SetTimeStep(unsigned int _milliseconds = 1000);
  void SetProgramStep(double _fractionOfTimeStep = -1.0);
  void Iteration(unsigned long int time);
  void InitDraw();
  void DrawElements();
};