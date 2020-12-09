#pragma once

#include "SimEngine/ManagementProgram.h"

class TSmartTerminalClassDummyProgram : public TManagementProgram
{
public:
  TSmartTerminalClassDummyProgram() : sendPacket(10), timePeriod(0), sheduleIsWork(true) {}
  
  virtual void Run(unsigned long time, unsigned long step);
  virtual void End();
  
  private: 
    TDataPacket sendPacket;
    double timePeriod;
    bool sheduleIsWork;
};

extern "C" LIB_EXPORT_API IManagementProgram* create();