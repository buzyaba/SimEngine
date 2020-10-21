#include <chrono>
#include <thread>
#include <iostream>

#include "Core/WorkManager.h"
#include "Core/ProgramFactory.h"

#include "SimEngine/common.h"

TWorkManager::TWorkManager(TParameters& parameters_, IGraphicPresenter* presenter_) : parameters(parameters_), presenter(presenter_)
{
  currentTime = 0;
  currentStep = 0;
  mainSet = TSetFactory::Create(parameters.xmlMainSetConfigurationFile);

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

  script = new TEnvironmentScript(allObject, parameters.xmlEnvironmentScriptName, parameters.maxStep);
  program = TProgramFactory::Create(things);
  storage = new TDataStore(allObject, "../../A");

  startWork = std::chrono::steady_clock::now();
}


TWorkManager::~TWorkManager()
{
  Dll_Manager::FreeDllManager();
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
  std::this_thread::sleep_for(delta);
}

void TWorkManager::Start(const unsigned short& _enableVisualisation)
{
  std::cout << "Start\n Max Iter = " << parameters.maxStep<< std::endl;
  std::cout << "Max Time = " << static_cast<double>(parameters.maxStep) * parameters.millisecondsInTimeStep / 1000.0 << " seconds" << std::endl;
  std::cout << "time acceleration = " << parameters.timeAcceleration << " X" << std::endl;

  startWork = std::chrono::steady_clock::now();


  time = 0;
   std::chrono::milliseconds delayTime(static_cast<unsigned long int>(parameters.millisecondsInTimeStep / parameters.timeAcceleration));

  for (unsigned long int t = 0; t < parameters.maxStep; t++)
  {
    Iteration(t, delayTime, _enableVisualisation);
  }

  std::chrono::time_point<std::chrono::steady_clock> endWork = std::chrono::steady_clock::now();
  std::chrono::milliseconds deltaWork =
    std::chrono::duration_cast<std::chrono::milliseconds>(endWork - startWork);
  std::cout << "End Work\n Time Work = \t" << deltaWork.count() << " ms.\n "<< 
  "Simulation time = \t" << static_cast<double>(parameters.maxStep) * parameters.millisecondsInTimeStep / 60000 <<" minutes\n" << std::endl;

  // storage->PrintToFile();
  presenter->stopGraphicManager();
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

void TWorkManager::sendObjects() {
    for (auto& vec : mainSet->GetAllGObjects()) {
        for (auto elem : vec.second) {
            presenter->addTObject(elem);
        }
    }
}