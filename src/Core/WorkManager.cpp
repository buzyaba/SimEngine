﻿#include <chrono>
#include <thread>
#include <iostream>

#include "Core/WorkManager.h"
#include "Core/EmptyProgram.h"

#include "Core/common.h"
#include <Engine/FirstPersonView.hpp>
#include <Engine/IsometricView.hpp>

unsigned long int currentTime;
unsigned long int currentStep;

TWorkManager::TWorkManager(WindowManager* _window, TMainSet* _mainSet, unsigned int _millisecondsOfTimeStep, 
  double _delay, double _fractionOfTimeStep, unsigned long _maxStep) {
  currentTime = 0;
  currentStep = 0;
  mainSet = _mainSet;
  window = _window;
  objects = mainSet->GetObjects();
  things = mainSet->GetThings();
  staticObjects = mainSet->GetStaticObjects();

  if (_millisecondsOfTimeStep > 0)
    timeStep = _millisecondsOfTimeStep;
  else
    timeStep = 0;
  if (_fractionOfTimeStep > 0)
    fractionOfTimeStep = _fractionOfTimeStep;
  else
    fractionOfTimeStep = 0;

  delay = _delay;

  // !! Не забыть переделать
  std::vector<IObject*> allObject(objects.size());
  int j = 0;
  for (int i = 0; i < objects.size(); i++)
  {
    allObject[j] = objects[i];
    j++;
  }

  // std::vector<IObject*> allObject(objects.size() + things.size());
  // int j = 0;
  // for (int i = 0; i < objects.size(); i++)
  // {
  //   allObject[j] = objects[i];
  //   j++;
  // }
  // for (int i = 0; i < things.size(); i++)
  // {
  //   allObject[j] = things[i];
  //   j++;
  // }

  script = new TEnvironmentScript(allObject, static_cast<std::string>("TestScript"), _maxStep, 1);
  program = TProgramFactory::Create(0, things);
  storage = new TDataStore(allObject, "DataStore");
    maxStep = _maxStep;
}

TWorkManager::TWorkManager(WindowManager* _window, int type, std::string _script, std::string _xmlFile, unsigned int _millisecondsOfTimeStep,
  double _delay,  double _fractionOfTimeStep, unsigned long int _maxStep)
{
  xmlScript = _script;
  xmlFile = _xmlFile;
  currentTime = 0;
  currentStep = 0;
  mainSet = TSetFactory::Create(type, xmlFile);
  window = _window;
  objects = mainSet->GetObjects();
  things = mainSet->GetThings();
  staticObjects = mainSet->GetStaticObjects();

  if (_millisecondsOfTimeStep > 0)
    timeStep = _millisecondsOfTimeStep;
  else
    timeStep = 0;
  if (_fractionOfTimeStep > 0)
    fractionOfTimeStep = _fractionOfTimeStep;
  else
    fractionOfTimeStep = 0;

  delay = _delay;

  std::vector<IObject*> allObject(objects.size() + things.size());
  int j = 0;
  for (int i = 0; i < objects.size(); i++)
  {
    allObject[j] = objects[i];
    j++;
  }
  for (int i = 0; i < things.size(); i++)
  {
    allObject[j] = things[i];
    j++;
  }

  script = new TEnvironmentScript(allObject, xmlScript, _maxStep, type);
  program = TProgramFactory::Create(type, things);
  storage = new TDataStore(allObject, "../../A");
  maxStep = _maxStep;
}

TWorkManager::~TWorkManager()
{
  delete window;
  delete program;
}

void TWorkManager::Start(const unsigned short& _enableVisualisation)
{
  std::cout << "Start\n Max Iter = " << maxStep<< std::endl;
  std::cout << "Max Time = " << double(maxStep * timeStep) / 1000.0 << " seconds" << std::endl;
  std::cout << "time acceleration = " << delay << " X" << std::endl;

  std::chrono::time_point<std::chrono::steady_clock> startWork = std::chrono::steady_clock::now();

  if (_enableVisualisation) {
    window->setVisibility(true);
  } else {
    window->setVisibility(false);
  }

  unsigned long int time = 0;
  std::chrono::milliseconds delayTime(static_cast<unsigned long int>(timeStep * delay));
  for (int t = 0; t < maxStep && !window->isWindowShouldClose(); t++)
  {
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    time = (t * timeStep) / 1000;
    currentTime = time;
    currentStep = t;
    // TODO: FIX COMMENTED STUFF
    script->UpdateObjectsProperties(time);
    for (int i = 0; i < objects.size(); i++)
    {      
      objects[i]->Update();      
    }
    storage->AddAllProperties(time);
    
    program->Run();  

    storage->PrintToConsole();
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::milliseconds delta =
      std::chrono::duration_cast<std::chrono::milliseconds>(delayTime - (end - start));
    float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(end-start).count();
    window->runWindow(dt, [&](){glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	                                              glClearColor(0.2f, 1.f, 0.f, 1.f);
                                                this->DrawElements();});
    if (_enableVisualisation == 0)
      std::this_thread::sleep_for(delta);
  }
  std::chrono::time_point<std::chrono::steady_clock> endWork = std::chrono::steady_clock::now();
  std::chrono::milliseconds deltaWork =
    std::chrono::duration_cast<std::chrono::milliseconds>(endWork - startWork);
  std::cout << "End\n" << deltaWork.count() << std::endl;

  storage->PrintToFile();
  window->setCursor(true);
  program->End();
}

void TWorkManager::Stop()
{
}

void TWorkManager::SetTimeStep(unsigned int _milliseconds)
{
  if (_milliseconds > 0)
    timeStep = _milliseconds;
  else
    timeStep = 0;
}

void TWorkManager::SetProgramStep(double _fractionOfTimeStep)
{
  if (_fractionOfTimeStep > 0)
    fractionOfTimeStep = _fractionOfTimeStep;
  else
    fractionOfTimeStep = 0;
}

void TWorkManager::Iteration(unsigned long int time){
    currentTime=time;
    currentStep++;
    script->UpdateObjectsProperties(time);

    for (int i = 0; i < objects.size(); i++)
    {      
      objects[i]->Update();      
    }  

    storage->AddAllProperties(time);
    std::cout<<program<<std::endl;
    program->Run();  
}

void TWorkManager::InitDraw() {
    for(const auto& elem : mainSet->GetAllGObjects()){
        elem.second[0]->initDraw(elem.second);
    }
}

void TWorkManager::DrawElements() {
    for(const auto& elem : mainSet->GetAllGObjects()) {
        elem.second[0]->drawElements(elem.second);
    }
}
