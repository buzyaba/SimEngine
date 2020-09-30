#pragma once
#define WITHOUT_NUMPY
#include "Core/ManagementProgram.h"
#include "Core/common.h"
#include "Core/SmartThing.h"
#include <string>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <iostream>

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
        int dataCount = int(things[i]->GetSensors()[0]->GetDataPacket().GetSize() / sizeof(double));
        for (int k = 0; k < dataCount; k++)
          tableHeader.push_back(things[i]->GetName() + "_" + sensor[j]->GetName() + "_" + std::to_string(k));
      }
    }

    title1 = fileName;
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

    for (int i = 0; i < sensors.size(); i++)
    {
      double* val = sensors[i]->GetDataPacket().GetDoubles();
      int dataCount = int(sensors[i]->GetDataPacket().GetSize() / sizeof(double));
      for (int j = 0; j < dataCount; j++)
      {
        str.push_back(std::to_string(val[j]));
      }
    }
    table.push_back(str);
  }
};

class TRoomProgram : public TManagementProgram
{
public:
  TRoomProgram(std::vector<TSmartThing*>& _things) : TManagementProgram(_things){}

  virtual void Run()
  {
    TManagementProgram::Run();
  }

  virtual void End()
  {
    double value = 0;
    double sum = 0;

    for (size_t u = 0; u < table.size() - 1; u++)
    {
      for (size_t i = 0; i < table[u].size() - 1; i++)
      {
        value = atof(table[u][i + 1ull].c_str());
        sum += value;
      }
    }

    std::cout << "Power consumption = " << sum << std::endl;
    if (sum > 50)
      std::cout << "Electricity bill = " << sum * 6.45 <<" rub\n";
    else 
      std::cout << "Electricity bill = " << sum * 3.71 <<" rub\n";

    //DELETE THIS AFTER ALL PLS
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
    //ENDS HERE
    // TManagementProgram::End();
  }
};

class TRoomAutoProgram : public TManagementProgram
{
public:
  TRoomAutoProgram(std::vector<TSmartThing*>& _things) : TManagementProgram(_things)
  {
    P = 100;
    dailyLimit = P / 30;
    dailyPowerConsumption = 0;
  }

  virtual void Run()
  {
    if ((currentTime % 86400) == 0)
      dailyPowerConsumption = 0;
    std::vector<std::string> str(1);
    str[0] = std::to_string(currentTime);

    for (int i = 0; i < sensors.size(); i++)
    {
      double* val = sensors[i]->GetDataPacket().GetDoubles();
      int dataCount = int(sensors[i]->GetDataPacket().GetSize() / sizeof(double));
      for (int j = 0; j < dataCount; j++)
      {
        if (dailyPowerConsumption > dailyLimit - 0.05)
          str.push_back(std::to_string(0));
        else 
          str.push_back(std::to_string(val[j]));
        dailyPowerConsumption += val[j];
      }
    }
    table.push_back(str);
  }

  virtual void End()
  {
    double value = 0;
    double sum = 0;

    for (size_t u = 0; u < table.size() - 1; u++)
    {
      for (size_t i = 0; i < table[u].size() - 1; i++)
      {
        value = atof(table[u][i + 1ull].c_str());
        sum += value;
      }
    }

    std::cout << "Power consumption = " << sum << std::endl;
    if (sum > P)
      std::cout << "Electricity bill = " << sum * 6.45 <<" rub\n";
    else 
      std::cout << "Electricity bill = " << sum * 3.71 <<" rub\n";

    //DELETE THIS AFTER ALL PLS
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
    //ENDS HERE
    // TManagementProgram::End();
  }
  private: 
    double P;
    double dailyPowerConsumption;
    double dailyLimit;
};

class TStreetProgram : public TManagementProgram
{
  TDataPacket sendPacket;
  int timeGreen;
  int timeRed;
  int waitingTime;
public:
  TStreetProgram(std::vector<TSmartThing*>& _things) : TManagementProgram(_things)
  {
    tableHeader.push_back("carCount");
    double* packetVal = sendPacket.GetDoubles();
    packetVal[0] = 0;
    timeGreen = 30;
    timeRed = 120;
    waitingTime = 1;
  }

  virtual void Run()
  {
    TManagementProgram::Run();

    double carCount = 0;
    if (sensors.size() > 0)
    {
      double* val = sensors[0]->GetDataPacket().GetDoubles();
      int dataCount = int(sensors[0]->GetDataPacket().GetSize() / sizeof(double));
      for (int j = 0; j < dataCount; j++)
      {
        carCount += val[j];
      }
      table[table.size() - 1].push_back(std::to_string(carCount));
    }

    double* packetVal = sendPacket.GetDoubles();

    bool isUpdate = false;

    if (currentStep % waitingTime == 0) {
        isUpdate = true;
        packetVal[0] = (int(packetVal[0]) + 1) % 2;
        if (packetVal[0]) {
            waitingTime = timeRed;
        }
        else {
            waitingTime = timeGreen;
        }
    }

    if (isUpdate)
    {
        for (int i = 0; i < things.size(); i++)
        {
            things[i]->GetActuators()[0]->SetDataPacket(sendPacket);
            int IsNotGo = int(packetVal[0]);

            if (IsNotGo == 1)
                things[i]->SetProperty({ {"Color", 2} }, "Color");
            else
                things[i]->SetProperty({ {"Color", 0} }, "Color");
        }
    }

    for (int i = 0; i < things.size(); i++) {
       things[i]->SetProperty({ {"NumberOfStandingCars", carCount} }, "NumberOfStandingCars");
  }
};

  virtual void End()
  {
    double value = 0;
    double sum = 0;

    for (int u = 0; u < table.size() - 1; u++)
    {
      for (int i = 0; i < table[u].size() - 1; i++)
      {
        value = atof(table[u][i + 1].c_str());
        sum += value;
      }
    }

    std::cout << "Car count = " << sum << std::endl;

    TManagementProgram::End();
  }
};

class TStreetPeakProgram : public TManagementProgram {
    TDataPacket sendPacket;
    int peakTime;
    int timeGreen;
    int timeRed;
    int waitingTime;
public:
    TStreetPeakProgram(std::vector<TSmartThing*>& _things) : TManagementProgram(_things)
    {
        tableHeader.push_back("carCount");
        double* packetVal = sendPacket.GetDoubles();
        packetVal[0] = 0;
        peakTime = 10;
        timeGreen = 30;
        timeRed = 120;
        waitingTime = 1;
    }

    virtual void Run()
    {
        TManagementProgram::Run();

        double carCount = 0;
        if (sensors.size() > 0)
        {
            double* val = sensors[0]->GetDataPacket().GetDoubles();
            int dataCount = int(sensors[0]->GetDataPacket().GetSize() / sizeof(double));
            for (int j = 0; j < dataCount; j++)
            {
                carCount += val[j];
            }
            table[table.size() - 1].push_back(std::to_string(carCount));
        }

        double* packetVal = sendPacket.GetDoubles();

        bool isUpdate = false;

        if (currentStep % waitingTime == 0 || (currentStep / 60) % peakTime == 0 ||
                                              (currentStep / 60) % (peakTime+8) == 0) 
        {
            isUpdate = true;
            if ((currentStep / 60) % peakTime == 0 || (currentStep / 60) % (peakTime + 8) == 0)
                packetVal[0] = 0;
            else
                packetVal[0] = (int(packetVal[0]) + 1) % 2;
            if (packetVal[0]) {
                waitingTime = timeRed;
            }
            else {
                waitingTime = timeGreen;
            }
        }

        if (isUpdate)
        {
            for (int i = 0; i < things.size(); i++)
            {
                things[i]->GetActuators()[0]->SetDataPacket(sendPacket);
                int IsNotGo = int(packetVal[0]);

                if (IsNotGo == 1)
                    things[i]->SetProperty({ {"Color", 2} }, "Color");
                else
                    things[i]->SetProperty({ {"Color", 0} }, "Color");
            }
        }

        for (int i = 0; i < things.size(); i++) {
            things[i]->SetProperty({ {"NumberOfStandingCars", carCount} }, "NumberOfStandingCars");
        }
    }

    virtual void End()
    {
        double value = 0;
        double sum = 0;

        for (int u = 0; u < table.size() - 1; u++)
        {
            for (int i = 0; i < table[u].size() - 1; i++)
            {
                value = atof(table[u][i + 1].c_str());
                sum += value;
            }
        }

        std::cout << "Car count = " << sum << std::endl;

        TManagementProgram::End();
    }
};

class TStreetAutoProgram : public TManagementProgram {
    TDataPacket sendPacket;
    int carThreshold;
    int timeGreen;
    int timeRed;
    int waitingTime;
public:
    TStreetAutoProgram(std::vector<TSmartThing*>& _things) : TManagementProgram(_things)
    {
        tableHeader.push_back("carCount");
        double* packetVal = sendPacket.GetDoubles();
        packetVal[0] = 0;
        carThreshold = 10;
        timeGreen = 30;
        timeRed = 120;
        waitingTime = 1;
    }

    virtual void Run()
    {
        TManagementProgram::Run();

        double carCount = 0;
        if (sensors.size() > 0)
        {
            double* val = sensors[0]->GetDataPacket().GetDoubles();
            int dataCount = int(sensors[0]->GetDataPacket().GetSize() / sizeof(double));
            for (int j = 0; j < dataCount; j++)
            {
                carCount += val[j];
            }
            table[table.size() - 1].push_back(std::to_string(carCount));
        }
        double* packetVal = sendPacket.GetDoubles();

        bool isUpdate = false;

        if (currentStep % waitingTime == 0 || carCount >= carThreshold) {
            isUpdate = true;
            if (carCount < carThreshold)
                packetVal[0] = (int(packetVal[0]) + 1) % 2;
            else
                packetVal[0] = 0;

            if (packetVal[0]) {
                waitingTime = timeRed;
            }
            else {
                waitingTime = timeGreen;
            }
        }

        if (isUpdate)
            for (int i = 0; i < things.size(); i++)
            {
                things[i]->GetActuators()[0]->SetDataPacket(sendPacket);
                int IsNotGo = int(packetVal[0]);

                if (IsNotGo == 1)
                    things[i]->SetProperty({ {"Color", 2} }, "Color");
                else
                    things[i]->SetProperty({ {"Color", 0} }, "Color");
            }

        for (int i = 0; i < things.size(); i++) {
            things[i]->SetProperty({ {"NumberOfStandingCars", carCount} }, "NumberOfStandingCars");
        }
    };

    virtual void End()
    {
        double value = 0;
        double sum = 0;

        for (int u = 0; u < table.size() - 1; u++)
        {
            for (int i = 0; i < table[u].size() - 1; i++)
            {
                value = atof(table[u][i + 1].c_str());
                sum += value;
            }
        }

        std::cout << "Car count = " << sum << std::endl;

        TManagementProgram::End();
    }
};
