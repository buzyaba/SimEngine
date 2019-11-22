#pragma once

#include <string>
#include <vector>
#include <stdio.h>

#include "Core/Sensor.h"
#include "Core/Actuator.h"
#include "Core/Object.h"
#include "Core/ObjectOfObservation.h"

/// Класс реализующий базовое хранение данных об объектах в базе данных
/// Пока заглушка
class TDataStore
{
protected:
  /// Имя базы данных
  std::string name;
  std::vector<IObject*> allObjects;
  std::vector<IProperties*> allObjectsProperties;
  std::vector<std::string> tableHeader;
  std::vector < std::vector<std::string>> table;

  bool isFirstPrintToConsole;

public:
  TDataStore(std::vector<IObject*> _allObjects, std::string _name)
  {
    isFirstPrintToConsole = true;
    allObjects = _allObjects;
    name = _name;
    int size = 0;
    for (int i = 0; i < allObjects.size(); i++)
    {
      size += allObjects[i]->GetProperties().size();
    }

    int k = 0;
    allObjectsProperties.resize(size);
    tableHeader.resize(size + 1);
    tableHeader[0] = "Time";

    for (int i = 0; i < allObjects.size(); i++)
    {
      std::vector<IProperties*>& tmp = allObjects[i]->GetProperties();
      for (int j = 0; j < tmp.size(); j++)
      {
        allObjectsProperties[k] = tmp[j];
        tableHeader[k + 1] = allObjects[i]->GetName() + "_" + tmp[j]->GetName();
        k++;
      }
    }

  };

  virtual void AddAllProperties(unsigned long time)
  {
    std::vector<std::string> str(allObjectsProperties.size() + 1);
    str[0] = std::to_string(time);
    for (int i = 0; i < allObjectsProperties.size(); i++)
    {      
      std::vector<double>& tmp = allObjectsProperties[i]->GetValues();
      str[i + 1] = std::to_string(tmp[0]);
      for (int j = 1; j < tmp.size(); j++)
        str[i + 1] = str[i + 1] + "_" + std::to_string(tmp[j]);
    }

    table.push_back(str);
  }


  virtual void AddPropertyForObject(const IProperties& property, unsigned long time)
  {
    ///
  }

  virtual std::vector<IProperties*> GddPropertyForObject(unsigned long time)
  {
    return allObjectsProperties;
  }

  virtual void PrintToFile()
  {
    FILE* file = fopen((name + ".csv").c_str(), "w");
    for (int j = 0; j < tableHeader.size(); j++)
      fprintf(file, "%s;\t", tableHeader[j].c_str());
    fprintf(file, "\n");

    for (int i = 0; i < table.size(); i++)
    {
      for (int j = 0; j < table[i].size(); j++)
        fprintf(file, "%s;", table[i][j].c_str());
      fprintf(file, "\n");
    }

    fclose(file);
  }

  virtual void PrintToConsole()
  {
    if (isFirstPrintToConsole)
    {
      for (int j = 0; j < tableHeader.size(); j++)
        printf("%s;\t", tableHeader[j].c_str());
      printf("\n");
      isFirstPrintToConsole = false;
    }
    if (table.size() > 0)
    {
      std::vector<std::string>& tmp = table[table.size() - 1];
      for (int j = 0; j < tmp.size(); j++)
        printf("%s;", tmp[j].c_str());
      printf("\n");
    }
  }
};