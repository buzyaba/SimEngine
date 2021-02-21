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
  std::vector<unsigned long int> timePoint;

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
      timePoint.resize(intervalCount);
      std::vector<double> tt(intervalCount + 1);
      ParseString(value, tt);

      for (int i = 0; i < intervalCount; i++)
      {
        timePoint[i] = tt[i];
      }

      for (int i = 0; i < objects.size(); i++)
      {
        for (auto& elem : objects[i]->GetProperties())
          if(elem.first != "Name" && elem.first != "Object")
              objectPropertyIntervals[i][elem.first].SetProperty(*elem.second, intervalCount, timePoint);
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
            try {
              std::map<std::string, double>& tmp = elem.second.GetValue(time);
              properties[elem.first]->SetValues(tmp);
            } catch (...) {}
          }
        }
      }
    }
  }
}
