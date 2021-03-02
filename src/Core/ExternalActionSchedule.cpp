#define _CRT_SECURE_NO_WARNINGS

#include "Core/ExternalActionSchedule.h"
#include "../lib/pugixml/include/pugixml.hpp"
#include <SimEngine/common.h>

#include <string.h>

std::map<std::string, IProperties*>& TExternalActionSchedule::ChangeProperties(int objectIndex, 
                std::map<std::string, IProperties*>& properties, std::size_t time)
{
  for (auto& elem : objectPropertyIntervals[objectIndex]) {
    if (properties[elem.first]) {
      properties[elem.first]->SetValues(elem.second.GetValue(time));
    }
  }
  return properties;
}

void TExternalActionSchedule::LoadXML()
{
  if (xmlName == "")
    return;
  int intervalCount = 0;

  objectPropertyIntervals.resize(objects.size());

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(xmlName.c_str());
  if (result.status != pugi::status_ok)
    return;
  pugi::xml_node config = doc.child("config");
  std::vector<std::size_t> timePoint;

  for (pugi::xml_node iter = config.first_child(); iter != 0; iter = iter.next_sibling())
  {
    std::string name = iter.name();
    std::string value = iter.child_value();

    if (name == "intervalCount")
      intervalCount = atoi(value.c_str());
    else if (name == "time")
    {
      timePoint.resize(intervalCount);
      std::vector<std::size_t> tt = ParseString<std::size_t>(value, "_");

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
              std::vector<double> tt = ParseString<double>(valueProperty, "_");

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

TExternalActionSchedule::TExternalActionSchedule(std::vector<IObject*> _objects, std::string xmlName)
{

  this->objects = _objects;
  this->xmlName = xmlName;

  if (xmlName != "")
  {
    LoadXML();
  }
}

std::map<std::string, IProperties*>& TExternalActionSchedule::GetObjectProperties(std::string name, std::size_t time)
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

std::map<std::string, IProperties*>& TExternalActionSchedule::GetObjectProperties(IObject& object, std::size_t time)
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

void TExternalActionSchedule::UpdateObjectsProperties(std::size_t time)
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
