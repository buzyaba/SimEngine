#pragma once
#include "SimEngine/DataPacket.h"
#include "SimEngine/common.h"
#include "SimEngine/SmartThing.h"
#include "SimEngine/SmartThingSchedule.hpp"
#include <string>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <iostream>

/// Интерфейс запускаемой программы
class IManagementProgram
{
public:
  virtual void Run() {};
  virtual void Run(unsigned long time, unsigned long step) = 0;
  virtual void End() = 0;
  virtual void SetSmartThing(std::vector<TSmartThing*> _things) = 0;
  virtual void SetSchedule(std::vector<TSmartThing*> _things, std::string scheduleName) = 0;
};

class TManagementProgram : public IManagementProgram
{
protected:
  std::vector<TSmartThing*> things;
  /// Имя файла для сохранения
  std::string fileName;
  /// сам файл
  FILE* file;
  /// сохраняемые данные
  std::vector<std::string> tableHeader;
  ///Массисв данных
  std::vector < std::vector<std::string>> table;
  /// Набор наблюдаемых сенсоров
  std::vector <ISensor*> sensors;

  TSmartThingSchedule smartThingShedule; 

  std::string title1;
  
public:
  TManagementProgram() {};
  TManagementProgram(std::vector<TSmartThing*>& _things)
  {
    SetSmartThing(_things);
  }

  virtual void SetSmartThing(std::vector<TSmartThing*> _things)
  {
    things = _things;
    fileName = "ManagementProgram";
    tableHeader.resize(1);
    tableHeader[0] = "Time";
    sensors.clear();
    for (int i = 0; i < things.size(); i++)
    {
      std::vector <ISensor*> sensor = things[i]->GetSensors();
      for (int j = 0; j < sensor.size(); j++)
      {
        sensors.push_back(sensor[j]);
        int dataCount = int(sensor[j]->GetDataPacket().GetSize() / sizeof(double));
        for (int k = 0; k < dataCount; k++)
          tableHeader.push_back(things[i]->GetName() + "_" + sensor[j]->GetName() + "_" + std::to_string(k));
      }
    }

    title1 = fileName;
  }

  virtual void SetSchedule(std::vector<TSmartThing*> _things, std::string scheduleName) {
    smartThingShedule = TSmartThingSchedule(_things, scheduleName);
  }

virtual void Run()
{
  
  std::vector<std::string> str(1);
  str[0] = std::to_string(currentTime);

  for (int i = 0; i < sensors.size(); i++)
  {
    double* val = sensors[i]->GetDataPacket().GetData<double>();
    int dataCount = int(sensors[i]->GetDataPacket().GetSize() / sizeof(double));
    for (int j = 0; j < dataCount; j++)
    {
      str.push_back(std::to_string(val[j]));
    }
  }
  table.push_back(str);
}

  virtual void End()
  {
    file = fopen((fileName + ".csv").c_str(), "w");

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

  virtual void Run(unsigned long time, unsigned long step)
  {
    smartThingShedule.UpdateThingsProperties(time);
    std::vector<std::string> str(1);
    str[0] = std::to_string(currentTime);

    for (int i = 0; i < sensors.size(); i++)
    {
      double* val = sensors[i]->GetDataPacket().GetData<double>();
      int dataCount = int(sensors[i]->GetDataPacket().GetSize() / sizeof(double));
      for (int j = 0; j < dataCount; j++)
      {
        str.push_back(std::to_string(val[j]));
      }
    }
    table.push_back(str);
  }
};


///Тип функции-фабрики, которая экспортируется подключаемой библиотекой с упровляющей программой
typedef IManagementProgram* CreateManagementProgram();
///Тип функции-деструктора, которая экспортируется подключаемой библиотекой с упровляющей программой
typedef void DestroyManagementProgram(IManagementProgram*);

///Префикс для фуккций, экспортируемых подключаемой библиотекой
#ifdef WIN32
#define LIB_EXPORT_API __declspec(dllexport)
#else
#define LIB_EXPORT_API
#endif