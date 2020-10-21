#pragma once

#include "SimEngine/ManagementProgram.h"

class TSmartTerminalClassProgram : public TManagementProgram
{
public:
  TSmartTerminalClassProgram() : deltaT(1800.0), sendPacket(10) {}
  
  virtual void Run(unsigned long time, unsigned long step);
  virtual void End();
  virtual void SetSmartThing(std::vector<TSmartThing*> _things);
  
  private: 
    double deltaT; // Time in power safe required for shutdown  
    std::vector<size_t> waitTime;
    TDataPacket sendPacket;
};

extern "C" LIB_EXPORT_API IManagementProgram* create();