#pragma once

#include <string>
#include <vector>


#include "Core/Object.h"
#include "Core/Properties.h"

class TEnvironmentScript
{
protected:

public:
  virtual IProperties& GetObjectProperties(std::string name) = 0;
  virtual IProperties& GetObjectProperties(const IObject& object) = 0;
};