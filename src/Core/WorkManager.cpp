#include <chrono>
#include <thread>

#include "Core/WorkManager.h"
#include "Core/EmptyProgram.h"

#include "Core/common.h"

unsigned long int currentTime;
unsigned long int currentStep;

TWorkManager::TWorkManager(unsigned int _millisecondsOfTimeStep, double _delay,  double _fractionOfTimeStep, unsigned int _maxStep)
{
  currentTime = 0;
  currentStep = 0;
  mainSet = TSetFactory::Create(1);
    //new TMainSet();

  objects = mainSet->GetObject();
  things = mainSet->GetThing();
  scene = mainSet->GetScene();

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

  script = new TEnvironmentScript(allObject, "");
  program = TProgramFactory::Create(1, things);
  storage = new TDataStore(allObject, "A");
  maxStep = _maxStep;
}

TWorkManager::~TWorkManager()
{
  delete program;
}

void TWorkManager::Start()
{

  unsigned long int time = 0;
  std::chrono::milliseconds delayTime(static_cast<unsigned long int>(timeStep * delay));
  for (int t = 0; t < maxStep; t++)
  {
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    time = (t * timeStep) / 1000;
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

  storage->PrintToFile();
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
