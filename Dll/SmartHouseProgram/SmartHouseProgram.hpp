#pragma once

#include "SimEngine/ManagementProgram.h"

class TSmartHouseProgram : public TManagementProgram
{
public:
  TSmartHouseProgram() : TManagementProgram(){}

  virtual void Run()
  {
    TManagementProgram::Run();
  }

  virtual void End();
};

extern "C" LIB_EXPORT_API IManagementProgram* create();