#pragma once

#include "Core/Sensor.h"

class TElectricitySensor : public TSensor
{
public:
  TElectricitySensor(std::string _name) : TSensor(_name) {}
};
