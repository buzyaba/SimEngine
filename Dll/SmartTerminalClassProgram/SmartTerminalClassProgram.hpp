#pragma once

#include "SimEngine/ManagementProgram.h"

class TSmartTerminalClassProgram : public TManagementProgram
{
public:
  TSmartTerminalClassProgram() : deltaT(1800.0), sendPacket(new TDataPacket(10)), timePeriod(0), sheduleIsWork(true) {}
  ~TSmartTerminalClassProgram() { delete sendPacket; }
  
  virtual void Run(std::size_t time, std::size_t step);
  virtual void End();
  virtual void SetSmartThing(std::vector<TSmartThing*> _things);
  
  private: 
    double deltaT; // Time in power safe required for shutdown  
    std::vector<size_t> waitTime;
    TDataPacket* sendPacket;
    double timePeriod;
    bool sheduleIsWork;
};

extern "C" LIB_EXPORT_API IManagementProgram* create();