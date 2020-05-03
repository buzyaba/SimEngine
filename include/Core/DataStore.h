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
    tableHeader.push_back("Time");
    for (int i = 0; i < allObjects.size(); i++)
    {
      std::map<std::string, IProperties*>& tmp = allObjects[i]->GetProperties();
      for (auto& elem : tmp) {
        allObjectsProperties.push_back(elem.second);
        tableHeader.push_back(allObjects[i]->GetName() + "_" + elem.first);
      }
    }
  };

  virtual void AddAllProperties(unsigned long time)
  {
    std::vector<std::string> str(allObjectsProperties.size() + 1);
    str[0] = std::to_string(time);
    size_t iter = 1;
    for (auto& elem : allObjectsProperties)
    {      
      std::map<std::string, double>& tmp = elem->GetValues();
      auto it = tmp.begin();
      str[iter] = std::to_string(it->second);
      it++;
      while (it != tmp.end()) {
        str[iter] = str[iter] + "_" + std::to_string(it->second);
        it++;
      }
      iter++;
    }
    table.push_back(str);
  }


  virtual void AddPropertyForObject(const IProperties& property, unsigned long time)
  {
    ///
  }

  virtual std::vector<IProperties*> AddPropertyForObject(unsigned long time)
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