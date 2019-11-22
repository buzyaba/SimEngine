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
#include "Core/MainSet.h"

/// Класс 
class TWorkManager
{
protected:
  ///
  std::vector<TObjectOfObservation*> objects;
  std::vector<TSmartThing*> things;
  std::vector<TScene*> scene;

  TEnvironmentScript* script;
  IManagementProgram* program;
  TDataStore* storage;

  unsigned int maxStep;
  TMainSet* mainSet;
  unsigned int timeStep;
  double fractionOfTimeStep;
  double delay;
  
public:
  TWorkManager(unsigned int _millisecondsOfTimeStep = 1000, double _delay = 0, double _fractionOfTimeStep = -1.0, unsigned int _maxStep = 1000);
  ~TWorkManager();
  void Start();
  void Stop();
  void SetTimeStep(unsigned int _milliseconds = 1000);
  void SetProgramStep(double _fractionOfTimeStep = -1.0);
};