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

#include <Engine/WindowManager.hpp>


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
  std::string xmlFile, xmlScript;

  WindowManager* window;

public:
  // TWorkManager(WindowManager* _window, unsigned int _millisecondsOfTimeStep = 1000, double _delay = 0,
  //              double _fractionOfTimeStep = -1.0, unsigned long _maxStep = 1000);
  TWorkManager(TParameters param = parameters);
  TWorkManager(WindowManager* _window, TMainSet* _mainSet, unsigned int _millisecondsOfTimeStep = 1000,
    double _delay = 0, double _fractionOfTimeStep = -1.0,
    unsigned long _maxStep = 1000);
  TWorkManager(WindowManager* _window, int type = 0, std::string _script = "", std::string _xmlFile = "", unsigned int _millisecondsOfTimeStep = 1000,
    double _delay = 0, double _fractionOfTimeStep = -1.0, unsigned long _maxStep = 1000);
  ~TWorkManager();
  void Start(const unsigned short& _enableVisualisation = 1);
  void Stop();
  void SetTimeStep(unsigned int _milliseconds = 1000);
  void SetProgramStep(double _fractionOfTimeStep = -1.0);
  void Iteration(unsigned long int time);
  void InitDraw();
  void DrawElements();
};