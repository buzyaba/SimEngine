#pragma once

#include "Core/ManagementProgram.h"
#include "Core/common.h"
#include <string>
#include <stdio.h>

class TEmptyProgram : public IManagementProgram
{
protected:
  std::vector<TSmartThing*> things;
  /// Имя файла для сохранения
  std::string fileName;
  /// сам файл
  FILE* file;
  // сохраняемые данные
  std::vector<std::string> tableHeader;
  std::vector < std::vector<std::string>> table;

  std::vector <ISensor*> sensors;
public:
  TEmptyProgram(std::vector<TSmartThing*>& _things)
  {
    things = _things;
    fileName = "EmptyProgram";
    tableHeader.resize(1);
    tableHeader[0] = "Time";
    for (int i = 0; i < things.size(); i++)
    {
      std::vector <ISensor*> sensor = things[i]->GetSensors();
      for (int j = 0; j < sensor.size(); j++)
      {
        sensors.push_back(sensor[j]);
        int dataCount = int(things[i]->GetSensors()[0]->GetDataPacket().GetSize() / sizeof(double));
        for (int k = 0; k < dataCount; k++)
          tableHeader.push_back(things[i]->GetName() + "_" + sensor[j]->GetName() + "_" + std::to_string(k));
      }
    }


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

  virtual void Run()
  {
    std::vector<std::string> str(1);
    
    str[0] = std::to_string(currentTime);
    int valCount = 0;

    for (int i = 0; i < sensors.size(); i++)
    {
      double* val = sensors[i]->GetDataPacket().GetDoubles();
      int dataCount = int(sensors[i]->GetDataPacket().GetSize() / sizeof(double));
      for (int j = 0; j < dataCount; j++)
        str.push_back(std::to_string(val[j]));
    }
    table.push_back(str);
  }


};

class TRoomProgram : public TEmptyProgram
{
public:
  TRoomProgram(std::vector<TSmartThing*>& _things) : TEmptyProgram(_things)
  {
    
  }
};

class TStreetProgram : public TEmptyProgram
{
  TDataPacket sendPacket;
public:
  TStreetProgram(std::vector<TSmartThing*>& _things) : TEmptyProgram(_things)
  {
    tableHeader.push_back("carCount");
    double* packetVal = sendPacket.GetDoubles();
    packetVal[0] = 0;
  }

  virtual void Run()
  {
    TEmptyProgram::Run();
    if (sensors.size() > 0)
    {
      double* val = sensors[0]->GetDataPacket().GetDoubles();
      int dataCount = int(sensors[0]->GetDataPacket().GetSize() / sizeof(double));
      double carCount = 0;
      for (int j = 0; j < dataCount; j++)
      {
        carCount += val[j];
      }
      table[table.size() - 1].push_back(std::to_string(carCount));
    }
    double* packetVal = sendPacket.GetDoubles();
    
    if (currentStep % 17 == 0)
      packetVal[0] = (int(packetVal[0]) + 1) % 2;

    for (int i = 0; i < things.size(); i++)
    {
      things[i]->GetActuators()[0]->SetDataPacket(sendPacket);
    }
  }
};

class TProgramFactory
{
public:
  static TEmptyProgram* Create(int a, std::vector<TSmartThing*>& _things)
  {
    if (a == 0)
      return new TRoomProgram(_things);
    else
      return new TStreetProgram(_things);
  }
};
