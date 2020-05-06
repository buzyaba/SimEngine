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

#ifdef USE_PLOTTER
#include "matplotlibcpp.h"
namespace plt=matplotlibcpp;
#endif

class TEmptyProgram : public IManagementProgram
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

  std::vector <double> xArray;
  std::vector < std::vector <double>> yArray;

  std::string title1;
  std::vector <std::string> title2;
  double minx, miny, maxx, maxy;

  void CreatePlotData()
  {
    if (yArray.size() < (tableHeader.size() - 1))
    {
     yArray.resize(tableHeader.size() - 1);
    }
    for (int j = 0; j < yArray.size(); j++)
    {
     yArray[j].clear();
     yArray[j].resize(0);
    }

    xArray.clear();
    xArray.resize(currentTime);
    for (unsigned long int t = 0; t < currentTime; t++)
    {
     xArray[t] = double(t);
    }

    maxx = double(currentTime + 1);

    double value;
    for (int u = 0; u < table.size() - 1; u++)
    {
     for (int i = 0; i < table[u].size() - 1; i++)
     {
       value = atof(table[u][i + 1].c_str());

       if (maxy < value)
         maxy = value;
       if (miny > value)
         miny = value;

       yArray[i].push_back(value);
     }
    }

    title2.resize(tableHeader.size() - 1);
    for (int u = tableHeader.size() - 1, j = 0; u >= 1; u--, j++)
    {
     title2[j] = tableHeader[u] + " = " + table[table.size() - 1][u] + "\n";
    }
  }

  void Plot()
  {
#ifdef USE_PLOTTER
    if (table.size() < 3)
     return;

    CreatePlotData();

    int count = yArray.size();
    int xn = yArray[0].size();

    if (maxx == minx)
     maxx += 1;
    if (maxy == miny)
     maxy += 1;

    //double xstep = (maxx - minx) / 4.0;
    //double ystep = (maxy - miny) / 4.0;
    //g.graf(minx, maxx, minx, xstep,
    //  miny - ((maxy - miny) * 0.1), maxy + ((maxy - miny) * 0.1), miny, ystep);

    for (int k = 0; k < count; k++)
      plt::plot(xArray, yArray[k]);
    plt::xlabel("Time");
    plt::ylabel("Values");
    plt::show();
    //g.sendbf();
#endif
  }

  void FinPlot()
  {
    //g.disfin();
  }

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

    Plot();

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

class TRoomProgram : public TEmptyProgram
{
public:
  TRoomProgram(std::vector<TSmartThing*>& _things) : TEmptyProgram(_things)
  {

  }

  virtual void Run()
  {
    TEmptyProgram::Run();

    double value = 0;
    double sum = 0;
    int u = table.size() - 1;
    for (int i = 0; i < table[u].size() - 1; i++)
    {
      value = atof(table[u][i + 1].c_str());
      sum += value;
    }
    /*
    std::string s = "curl -v -X POST -d \"{\\\"Power\\\": " +
      std::to_string(sum) +
      " }\" http://localhost:8080/api/v1/FISKOaCIWwS5dlpZtL4c/telemetry --header \"Content-Type:application/json\"";
    std::system(s.c_str());
    */
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

    std::cout << "Power consumption = " << sum << std::endl;

    TEmptyProgram::End();
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
    // TEmptyProgram::Run();
    // double carCount = 0;
    // if (sensors.size() > 0)
    // {
    //   double* val = sensors[0]->GetDataPacket().GetDoubles();
    //   int dataCount = int(sensors[0]->GetDataPacket().GetSize() / sizeof(double));
    //   for (int j = 0; j < dataCount; j++)
    //   {
    //     carCount += val[j];
    //   }
    //   table[table.size() - 1].push_back(std::to_string(carCount));
    // }
    // double* packetVal = sendPacket.GetDoubles();

    // bool isUpdate = false;

    // if (currentStep % 17 == 0)
    // {
    //   isUpdate = true;
    //   packetVal[0] = (int(packetVal[0]) + 1) % 2;
    // }

    // if (isUpdate)
    // {
    //   for (int i = 0; i < things.size(); i++)
    //   {
    //     things[i]->GetActuators()[0]->SetDataPacket(sendPacket);
    //     int IsNotGo = int(packetVal[0]);

    //     if (IsNotGo == 1)
    //       things[i]->SetProperty({ 2 }, "Color");
    //     else
    //       things[i]->SetProperty({ 0 }, "Color");
    //   }
    // }

    // for (int i = 0; i < things.size(); i++)
    //   things[i]->SetProperty({ carCount }, "NumberOfStandingCars");
  }
};

class TProgramFactory
{
public:
  static TEmptyProgram* Create(int a, std::vector<TSmartThing*>& _things)
  {
    if (a <= 0)
      return new TRoomProgram(_things);
    else
      return new TStreetProgram(_things);
  }
};
