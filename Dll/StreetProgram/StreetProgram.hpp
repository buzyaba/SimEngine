#pragma once

#include "SimEngine/ManagementProgram.h"

class TStreetProgram : public TManagementProgram
{
    TDataPacket* sendPacket;
  int timeGreen;
  int timeRed;
  int waitingTime;
public:
  TStreetProgram() : TManagementProgram()
  {
    tableHeader.push_back("carCount");
    double* packetVal = sendPacket->GetData<double>();
    packetVal[0] = 0;
    timeGreen = 30;
    timeRed = 120;
    waitingTime = 1;
  }

  virtual void Run();

  virtual void End();
};

extern "C" LIB_EXPORT_API IManagementProgram* create();