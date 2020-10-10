#define _CRT_SECURE_NO_WARNINGS

#include "Core/EnvironmentScript.h"
#include "../lib/pugixml/include/pugixml.hpp"

#include <string.h>

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

  int isWorkIndex = -1;
  objectPropertyIntervals.resize(objects.size());
  for (int i = 0; i < objects.size(); i++)
  {
    bool isHaveIsWork = false;
    for (auto& aa : objects[i]->GetProperties())
    {
      if (aa.second->GetName() == "IsWork")
      {
        isHaveIsWork = true;
        isWorkIndex = i;
      }
    }
    if (isHaveIsWork)
    {
      // А где инициализация objectPropertyIntervals? Нужен скрипт
      objectPropertyIntervals[i].insert({ {"IsWork", TPropertyInterval()} });

      for (auto& elem : objectPropertyIntervals[i])
      {
        elem.second.SetProperty(objects[i]->GetProperty("IsWork"), intervalCount, startTime, endTime);
      }
    }
  }
  if (isWorkIndex != -1)
  {
    objectPropertyIntervals[isWorkIndex]["IsWork"].isSet = true;
    for (int i = 0; i < intervalCount; i++)
    {
      objectPropertyIntervals[isWorkIndex]["IsWork"].value[i]["IsWork"] = rand() % 2;
    }
  }
}

void TEnvironmentScript::LoadXML(unsigned long int& maxTime)
{
  if (xmlEnvironmentScriptName == "")
    return;
  int intervalCount = 0;

  objectPropertyIntervals.resize(objects.size());

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(xmlEnvironmentScriptName.c_str());
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
      std::vector<double> tt(intervalCount + 1);
      ParseString(value, tt);

      for (int i = 0; i < intervalCount; i++)
      {
        startTime[i] = tt[i];
        endTime[i] = tt[i + 1];
      }

      for (int i = 0; i < objects.size(); i++)
      {
        for (auto& elem : objects[i]->GetProperties())
          if(elem.first != "Name" && elem.first != "Object")
              objectPropertyIntervals[i][elem.first].SetProperty(*elem.second, intervalCount, startTime, endTime);
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

          for (auto & elem : objectPropertyIntervals[i]) {
            if (elem.first == nameProperty) {
              elem.second.isSet = true;
              std::vector<double> tt(intervalCount);
              ParseString(valueProperty, tt);

              for (int k = 0; k < intervalCount; k++)
              {
                elem.second.value[k][nameProperty] = tt[k];
              }
            }
          }
        }
      }
    }
  }
}

void TEnvironmentScript::ParseString(std::string str, std::vector<double>& tt)
{
  size_t intervalCount = tt.size();
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

TEnvironmentScript::TEnvironmentScript(std::vector<IObject*> _objects, std::string xmlEnvironmentScriptName,
  unsigned long int& maxTime)
{

  this->objects = _objects;
  this->xmlEnvironmentScriptName = xmlEnvironmentScriptName;

  if (xmlEnvironmentScriptName != "")
  {
    LoadXML(maxTime);
  }
  else
  {
    RandomGen(maxTime);
  }

  //Добавить построение objectPropertyIntervals по скрипту.
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
      if (objectPropertyIntervals.size() > 0)
      {
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
}
