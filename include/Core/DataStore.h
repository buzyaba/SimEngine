#pragma once

#include <string>
#include <vector>
#include <stdio.h>

#include "SimEngine/Sensor.h"
#include "SimEngine/Actuator.h"
#include "SimEngine/Object.h"
#include "SimEngine/ObjectOfObservation.h"

/// Класс реализующий базовое хранение данных об объектах в базе данных
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

  virtual void AddAllProperties(std::size_t time)
  {
    std::vector<std::string> str(allObjectsProperties.size() + 1);
    char str_tmp[256];
    sprintf_s(str_tmp, "%llu", time);
    str[0] = str_tmp;
    size_t iter = 1;
    for (auto& elem : allObjectsProperties)
    {      
      std::map<std::string, double>& tmp = elem->GetValues();
      auto it = tmp.begin();
      sprintf_s(str_tmp, "%f", it->second);
      str[iter] = str_tmp;
      it++;
      while (it != tmp.end()) {
        sprintf_s(str_tmp, "%f", it->second);
        str[iter] = str[iter] + "_" + str_tmp;
        it++;
      }
      iter++;
    }
    table.push_back(str);
  }


  virtual void AddPropertyForObject(const IProperties& property, std::size_t time)
  {
    ///
  }

  virtual std::vector<IProperties*> AddPropertyForObject(std::size_t time)
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