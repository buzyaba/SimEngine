#pragma once

#include "SimEngine/ManagementProgram.h"

class TSmartEnergyProgram : public TManagementProgram
{
public:
  TSmartEnergyProgram() : TManagementProgram(){}

  virtual void Run()
  {
    TManagementProgram::Run();
  }

  virtual void End();
};

extern "C" LIB_EXPORT_API IManagementProgram* create();