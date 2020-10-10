#pragma once

#include "SimEngine/ManagementProgram.h"

class TProgramFactory
{
public:
  static IManagementProgram* Create(std::vector<TSmartThing*>& _things);
};
