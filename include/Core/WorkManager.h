#pragma once

#include <string>
#include <vector>

#include "Core/Sensor.h"
#include "Core/Actuator.h"
#include "Core/SmartThing.h"
#include "Core/ObjectOfObservation.h"
#include "Core/Properties.h"
#include "Scene.h"
#include "Core/ManagementProgram.h"
#include "Core/DataStore.h"
#include "Core/DataPacket.h"
#include "Core/EnvironmentScript.h"

class TWorkManager
{
protected:
  std::vector<IObjectOfObservation*> objects;
  std::vector<ISmartThing*> things;
  std::vector<IScene*> scene;
  unsigned int timeStep;
  double _fractionOfTimeStep;
  TEnvironmentScript* script;
  IManagementProgram* program;
  TDataStore* storage;
  
public:
  TWorkManager(unsigned int _millisecondsOfTimeStep = 1000, double _fractionOfTimeStep = -1.0);
  ~TWorkManager();
  void Start();
  void Stop();
  void SetTimeStep(unsigned int _milliseconds = 1000);
  void SetProgramStep(double _fractionOfTimeStep = -1.0);
};