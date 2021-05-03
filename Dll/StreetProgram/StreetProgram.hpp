#pragma once

#include "SimEngine/ManagementProgram.h"

class TStreetProgram : public TManagementProgram
{
  TDataPacket sendPacket{2*sizeof(double)};
  int timeGreen{30000};
  int timeRed{120000};
  std::vector<size_t> waitTime;
public:
  TStreetProgram() : TManagementProgram()
  {
    tableHeader.push_back("carCount");
    waitTime.resize(things.size());
  }

  virtual void Run(std::size_t time, std::size_t step);

  virtual void End();
};

extern "C" LIB_EXPORT_API IManagementProgram* create();