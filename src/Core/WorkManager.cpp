#include "Core/WorkManager.h"
#include "Core/EmptyProgram.h"

TWorkManager::TWorkManager(unsigned int _millisecondsOfTimeStep, double _fractionOfTimeStep, unsigned int _maxStep)
{
//objects;
// things;
// scene;
//

 if (_millisecondsOfTimeStep > 0)
   timeStep = _millisecondsOfTimeStep;
 else
   timeStep = 0;
 if (_fractionOfTimeStep > 0)
   fractionOfTimeStep = _fractionOfTimeStep;
 else
   fractionOfTimeStep = 0;
 
 std::vector<IObject*> allObject(objects.size() + things.size() + scene.size());
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
 for (int i = 0; i < scene.size(); i++)
 {
   allObject[j] = scene[i];
   j++;
 }

 script = new TEnvironmentScript(allObject, "");
 program = new TEmptyProgram();
 storage = new TDataStore();
 maxStep = _maxStep;
}

TWorkManager::~TWorkManager()
{
}

void TWorkManager::Start()
{
  while (1)
  {

  }
}

void TWorkManager::Stop()
{
}

void TWorkManager::SetTimeStep(unsigned int _milliseconds)
{
}

void TWorkManager::SetProgramStep(double _fractionOfTimeStep)
{
}
