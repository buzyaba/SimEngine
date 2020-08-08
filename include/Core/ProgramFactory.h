#pragma once

#include "Core/ManagementProgram.h"

class TProgramFactory
{
protected:
  static bool isLoadInDLL;
public:
  static IManagementProgram* Create(int a, std::vector<TSmartThing*>& _things);
};
