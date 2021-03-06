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

  virtual void Run(std::size_t time, std::size_t step) override
  {
      TManagementProgram::Run(time, step);
  }

  virtual void End();
};

extern "C" LIB_EXPORT_API IManagementProgram* create();