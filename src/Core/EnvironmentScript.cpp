#include "Core/EnvironmentScript.h"

std::vector <IProperties*>& TEnvironmentScript::ChangeProperties(int objectIndex, std::vector<IProperties*>& properties, unsigned long int time)
{
  for (int i = 0; i < objectPropertyIntervals[objectIndex].size(); i++)
  {
    if (objectPropertyIntervals[objectIndex][i].nameProperty == properties[i]->GetName())
    {
      properties[i]->SetValues(objectPropertyIntervals[objectIndex][i].GetValue(time));
    }
  }
  return properties;
}

TEnvironmentScript::TEnvironmentScript(std::vector<IObject*> _objects, std::string _script)
{
  this->objects = _objects;
  this->script = _script;

  //Добвать построение objectPropertyIntervals по скрипту.
}

std::vector <IProperties*>& TEnvironmentScript::GetObjectProperties(std::string name, unsigned long int time)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] != nullptr)
    {
      if (objects[i]->GetName() == name)
      {        
        return  ChangeProperties(i, objects[i]->GetProperties(), time);
      }
    }
  }
  throw - 1;
}

std::vector <IProperties*>& TEnvironmentScript::GetObjectProperties(IObject& object, unsigned long int time)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] == nullptr)
    {
      if (objects[i]->GetName() == object.GetName())
      {
        return  ChangeProperties(i, objects[i]->GetProperties(), time);
      }
    }
  }
  throw - 1;
}
