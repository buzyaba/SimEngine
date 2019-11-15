#pragma once
#include "Core/DataPacket.h"

class IManagementProgram
{
protected:
public:
  virtual void Run() = 0;
};