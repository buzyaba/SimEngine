#pragma once

#include "SimEngine/ManagementProgram.h"

class TSmartEnergyAutoProgram : public TManagementProgram
{
public:
  TSmartEnergyAutoProgram() : TManagementProgram()
  {
    P = 100;
    dailyLimit = P / 30;
    dailyPowerConsumption = 0;
  }

  virtual void Run();
  virtual void End();
  
  private: 
    double P;
    double dailyPowerConsumption;
    double dailyLimit;
};

extern "C" LIB_EXPORT_API IManagementProgram* create();