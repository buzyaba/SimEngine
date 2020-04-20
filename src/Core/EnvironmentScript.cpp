#include "Core/EnvironmentScript.h"

std::map<std::string, IProperties*>& TEnvironmentScript::ChangeProperties(int objectIndex, 
                std::map<std::string, IProperties*>& properties, unsigned long int time)
{
  for (auto& elem : objectPropertyIntervals[objectIndex]) {
    if (properties[elem.first]) {
      properties[elem.first]->SetValues(elem.second.GetValue(time));
    }
  }
  return properties;
}

TEnvironmentScript::TEnvironmentScript(std::vector<IObject*> _objects, std::string _script, unsigned long int maxTime)
{
  this->objects = _objects;
  this->script = _script;

  int intervalCount = 200;
  std::vector<unsigned long int> startTime;
  std::vector<unsigned long int> endTime;
  unsigned long int interval = maxTime / (intervalCount - 1);
  startTime.resize(intervalCount);
  endTime.resize(intervalCount);

  startTime[0] = 0;
  endTime[0] = startTime[0] + interval;

  for (int i = 1; i < intervalCount; i++)
  {
    startTime[i] = endTime[i - 1];
    endTime[i] = startTime[i] + interval;
  }

  objectPropertyIntervals.resize(objects.size());
  for (int i = 0; i < objects.size(); i++)
  {
    // А где инициализация objectPropertyIntervals? Нужен скрипт
    objectPropertyIntervals[i].insert({{"IsWork", TPropertyInterval()}});
    for (auto& elem : objectPropertyIntervals[i])
    {
      elem.second.SetProperty(objects[i]->GetProperty("IsWork"), intervalCount, startTime, endTime);
    }
  }
  objectPropertyIntervals[0]["IsWork"].isSet = true;
  for (int i = 0; i < intervalCount; i++)
  {
    objectPropertyIntervals[0]["IsWork"].value[i]["IsWork"] = rand() % 2;
  }

  //Добвать построение objectPropertyIntervals по скрипту.
}

std::map<std::string, IProperties*>& TEnvironmentScript::GetObjectProperties(std::string name, unsigned long int time)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] != nullptr)
    {
      if (objects[i]->GetName() == name)
      {        
        return ChangeProperties(i, objects[i]->GetProperties(), time);
      }
    }
  }
  throw - 1;
}

std::map<std::string, IProperties*>& TEnvironmentScript::GetObjectProperties(IObject& object, unsigned long int time)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] != nullptr)
    {
      if (objects[i]->GetName() == object.GetName())
      {
        return ChangeProperties(i, objects[i]->GetProperties(), time);
      }
    }
  }
  throw - 1;
}

void TEnvironmentScript::UpdateObjectsProperties(unsigned long int time)
{
  
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] != nullptr)
    {
      std::map<std::string, IProperties*>& properties = objects[i]->GetProperties();
      for (auto& elem : objectPropertyIntervals[i])
      {
        if (elem.second.isSet)
        {
          std::map<std::string, double>& tmp = elem.second.GetValue(time);
          properties[elem.first]->SetValues(tmp);
        }
      }
    }
  }
}
