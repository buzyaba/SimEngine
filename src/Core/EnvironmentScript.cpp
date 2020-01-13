#include "Core/EnvironmentScript.h"
#include "../lib/pugixml/include/pugixml.hpp"
//"pugixml.hpp"

std::vector <IProperties*>& TEnvironmentScript::ChangeProperties(int objectIndex,
  std::vector<IProperties*>& properties, unsigned long int time)
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

void TEnvironmentScript::RandomGen(unsigned long int maxTime)
{
  int intervalCount = 200;
  if (maxTime < 200)
    intervalCount = maxTime / 10 + 1;
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
    objectPropertyIntervals[i].resize(objects[i]->GetProperties().size());
    for (int j = 0; j < objects[i]->GetProperties().size(); j++)
    {
      objectPropertyIntervals[i][j].SetProperty(*(objects[i]->GetProperties()[j]), intervalCount, startTime, endTime);
    }
  }
  objectPropertyIntervals[0][0].isSet = true;
  for (int i = 0; i < intervalCount; i++)
  {
    objectPropertyIntervals[0][0].value[i][0] = rand() % 2;
  }
}



void TEnvironmentScript::LoadXML(unsigned long int& maxTime)
{
  if (script == "")
    return;
  int intervalCount = 0;

  objectPropertyIntervals.resize(objects.size());

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(script.c_str());
  if (result.status != pugi::status_ok)
    return;
  pugi::xml_node config = doc.child("config");
  std::vector<unsigned long int> startTime;
  std::vector<unsigned long int> endTime;

  for (pugi::xml_node iter = config.first_child(); iter != 0; iter = iter.next_sibling())
  {
    std::string name = iter.name();
    std::string value = iter.child_value();

    if (name == "intervalCount")
      intervalCount = atoi(value.c_str());
    else if (name == "maxStep")
      maxTime = atoi(value.c_str());
    else if (name == "time")
    {
      startTime.resize(intervalCount);
      endTime.resize(intervalCount);
      std::vector<int> tt(intervalCount + 1);
      ParseString(value, tt);

      for (int i = 0; i < intervalCount; i++)
      {
        startTime[i] = tt[i];
        endTime[i] = tt[i + 1];
      }

      for (int i = 0; i < objects.size(); i++)
      {
        objectPropertyIntervals[i].resize(objects[i]->GetProperties().size());
        for (int j = 0; j < objects[i]->GetProperties().size(); j++)
        {
          objectPropertyIntervals[i][j].SetProperty(*(objects[i]->GetProperties()[j]), intervalCount, startTime, endTime);
        }
      }
    }

    for (int i = 0; i < objects.size(); i++)
    {
      if (objects[i]->GetName() == name)
      {
        for (pugi::xml_node iter2 = iter.first_child(); iter2 != 0; iter2 = iter2.next_sibling())
        {
          std::string nameProperty = iter2.name();
          std::string valueProperty = iter2.child_value();

          for (int j = 0; j < objectPropertyIntervals[i].size(); i++)
          {
            if (objectPropertyIntervals[i][j].nameProperty == nameProperty)
            {
              objectPropertyIntervals[i][j].isSet = true;
              std::vector<int> tt(intervalCount);
              ParseString(valueProperty, tt);

              for (int k = 0; k < intervalCount; k++)
              {
                objectPropertyIntervals[i][j].value[k][0] = tt[k];
              }
            }
          }
        }


      }
    }
  }
}

void TEnvironmentScript::ParseString(std::string str, std::vector<int>& tt)
{
  int intervalCount = tt.size();
  char* s = new char[str.length() + 1];
  int l = 0;
  strcpy(s, str.c_str());

  char* pp = strtok(s, "_");

  double t = 0;
  while ((pp != 0) && (l < intervalCount))
  {
    sscanf(pp, "%lf", &t);
    tt[l] = t;
    pp = strtok(NULL, "_");
    l++;
  }

  delete[] s;
}

TEnvironmentScript::TEnvironmentScript(std::vector<IObject*> _objects, std::string _script,
  unsigned long int& maxTime, int type)
{

  this->objects = _objects;
  this->script = _script;

  if (type == -1)
  {
    LoadXML(maxTime);
  }
  else
  {
    RandomGen(maxTime);
  }

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
    if (objects[i] != nullptr)
    {
      if (objects[i]->GetName() == object.GetName())
      {
        return  ChangeProperties(i, objects[i]->GetProperties(), time);
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
      std::vector<IProperties*>& properties = objects[i]->GetProperties();

      for (int j = 0; j < objectPropertyIntervals[i].size(); j++)
      {
        if (objectPropertyIntervals[i][j].isSet)
        {
          std::vector<double>& tmp = objectPropertyIntervals[i][j].GetValue(time);
          properties[j]->SetValues(tmp);
        }
      }
    }
  }
}
