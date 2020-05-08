#include <chrono>
#include <thread>
#include <iostream>

#include "Core/WorkManager.h"
#include "BasicExamples/EmptyProgram.h"

#include "Core/common.h"
#ifdef USE_OpenGL
#include <Engine/FirstPersonView.hpp>
#include <Engine/IsometricView.hpp>
#endif

unsigned long int currentTime;
unsigned long int currentStep;

TWorkManager::TWorkManager(TParameters& param)
{
#ifdef USE_OpenGL
  window = parameters._window;
#endif

  parameters = param;
  
  xmlScript = parameters._script;
  xmlFile = parameters._xmlFile;
  currentTime = 0;
  currentStep = 0;
  mainSet = TSetFactory::Create(parameters.type, xmlFile);

  objects = mainSet->GetObjects();
  things = mainSet->GetThings();
  staticObjects = mainSet->GetStaticObjects();

  if (parameters._millisecondsOfTimeStep > 0)
    timeStep = parameters._millisecondsOfTimeStep;
  else
    timeStep = 0;
  if (parameters._fractionOfTimeStep > 0)
    fractionOfTimeStep = parameters._fractionOfTimeStep;
  else
    fractionOfTimeStep = 0;

  delay = parameters._delay;

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

  script = new TEnvironmentScript(allObject, xmlScript, parameters._maxStep, parameters.type);
  program = TProgramFactory::Create(parameters.type, things);
  storage = new TDataStore(allObject, "../../A");
  maxStep = parameters._maxStep;

  startWork = std::chrono::steady_clock::now();
}


TWorkManager::~TWorkManager()
{
#ifdef USE_OpenGL
  delete window;
#endif
  delete program;
}

void TWorkManager::Step(unsigned int& t, std::chrono::milliseconds& delayTime, const unsigned short& _enableVisualisation)
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
  float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(end - start).count();

#ifdef USE_OpenGL
  window->runWindow(dt, [&]() {glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.2f, 1.f, 0.f, 1.f);
  this->DrawElements(); });
#endif
  if (_enableVisualisation == 0)
    std::this_thread::sleep_for(delta);
}

void TWorkManager::Start(const unsigned short& _enableVisualisation)
{
  std::cout << "Start\n Max Iter = " << maxStep<< std::endl;
  std::cout << "Max Time = " << double(maxStep * timeStep) / 1000.0 << " seconds" << std::endl;
  std::cout << "time acceleration = " << delay << " X" << std::endl;

  startWork = std::chrono::steady_clock::now();

#ifdef USE_OpenGL
  if (_enableVisualisation) {
    window->setVisibility(true);
  } else {
    window->setVisibility(false);
  }
#endif

  time = 0;
  std::chrono::milliseconds delayTime(static_cast<unsigned long int>(timeStep * delay));
#ifdef USE_OpenGL
  for (int t = 0; t < maxStep && !window->isWindowShouldClose(); t++)
#else
  for (unsigned int t = 0; t < maxStep; t++)
#endif
  {
    Step(t, delayTime, _enableVisualisation);
  }

  std::chrono::time_point<std::chrono::steady_clock> endWork = std::chrono::steady_clock::now();
  std::chrono::milliseconds deltaWork =
    std::chrono::duration_cast<std::chrono::milliseconds>(endWork - startWork);
  std::cout << "End\n" << deltaWork.count() << std::endl;

  storage->PrintToFile();

#ifdef USE_OpenGL
  glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); // enable cursor
#endif

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
