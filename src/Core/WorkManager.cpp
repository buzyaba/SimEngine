#include <chrono>
#include <thread>
#include <iostream>

#include "Core/WorkManager.h"
#include "Core/ProgramFactory.h"

#include "BasicExamples/common.h"
#ifdef USE_OpenGL
#include <Engine/FirstPersonView.hpp>
#include <Engine/IsometricView.hpp>
#endif

TWorkManager::TWorkManager(TParameters& param) : parameters(param)
{
#ifdef USE_OpenGL
  window = parameters._window;
#endif

  currentTime = 0;
  currentStep = 0;
  mainSet = TSetFactory::Create(parameters.type, parameters.xmlMainSetConfigurationFile);

  objects = mainSet->GetObjects();
  things = mainSet->GetThings();
  staticObjects = mainSet->GetStaticObjects();

  if (parameters.millisecondsInTimeStep < 0)
    parameters.millisecondsInTimeStep = 0;

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

  script = new TEnvironmentScript(allObject, parameters.xmlEnvironmentScriptName, parameters.maxStep, parameters.type);
  program = TProgramFactory::Create(parameters.type, things);
  storage = new TDataStore(allObject, "../../A");

  startWork = std::chrono::steady_clock::now();
}


TWorkManager::~TWorkManager()
{
#ifdef USE_OpenGL
  delete window;
#endif
}

void TWorkManager::Iteration(unsigned long int& t, std::chrono::milliseconds& delayTime, const unsigned short& _enableVisualisation)
{
  std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
  time = (t * parameters.millisecondsInTimeStep) / 1000;
  currentTime = time;
  currentStep = t;
  script->UpdateObjectsProperties(time);
  for (int i = 0; i < objects.size(); i++)
  {
    objects[i]->Update();
  }
  storage->AddAllProperties(time);

  program->Run();

  //storage->PrintToConsole();
  std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
  std::chrono::milliseconds delta =
    std::chrono::duration_cast<std::chrono::milliseconds>(delayTime - (end - start));
#ifdef USE_OpenGL
  start = std::chrono::steady_clock::now();
  auto lastFrame = glfwGetTime();
  do {
    auto currentFrame = glfwGetTime();
    auto dt = currentFrame - lastFrame;
    window->runWindow(dt, [&]() {glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    this->DrawElements(); });
    lastFrame = currentFrame;
    end = std::chrono::steady_clock::now();
  } while((end - start) < delta);
#endif
  if (_enableVisualisation == 0)
    std::this_thread::sleep_for(delta);
}

void TWorkManager::Start(const unsigned short& _enableVisualisation)
{
  std::cout << "Start\n Max Iter = " << parameters.maxStep<< std::endl;
  std::cout << "Max Time = " << double(parameters.maxStep * parameters.millisecondsInTimeStep) / 1000.0 << " seconds" << std::endl;
  std::cout << "time acceleration = " << parameters.timeAcceleration << " X" << std::endl;

  startWork = std::chrono::steady_clock::now();

#ifdef USE_OpenGL
  if (_enableVisualisation) {
    window->setVisibility(true);
  } else {
    window->setVisibility(false);
  }
#endif

  time = 0;
   std::chrono::milliseconds delayTime(static_cast<unsigned long int>(parameters.millisecondsInTimeStep / parameters.timeAcceleration));
#ifdef USE_OpenGL
  for (unsigned long int t = 0; t < parameters.maxStep && !window->isWindowShouldClose(); t++)
#else
  for (unsigned long int t = 0; t < parameters.maxStep; t++)
#endif
  {
    Iteration(t, delayTime, _enableVisualisation);
  }

  std::chrono::time_point<std::chrono::steady_clock> endWork = std::chrono::steady_clock::now();
  std::chrono::milliseconds deltaWork =
    std::chrono::duration_cast<std::chrono::milliseconds>(endWork - startWork);
  std::cout << "End Work\n Time Work = \t" << deltaWork.count() << " ms.\n "<< 
  "Simulation time = \t" << static_cast<double>(parameters.maxStep * parameters.millisecondsInTimeStep) / 60000 <<" minutes\n" << std::endl;

  // storage->PrintToFile();

#ifdef USE_OpenGL
  window->setCursor(true); // enable cursor
#endif

  program->End();
}

void TWorkManager::Stop()
{
  parameters.maxStep = -1;
}

void TWorkManager::SetMillisecondsInTimeStep(unsigned int _milliseconds)
{
  if (_milliseconds > 0)
    parameters.millisecondsInTimeStep = _milliseconds;
  else
    parameters.millisecondsInTimeStep = 0;
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
