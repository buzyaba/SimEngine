#pragma once

#include "SimEngine/Sensor.h"

class TElectricitySensor : public TSensor
{
public:
  TElectricitySensor(std::string _name) : TSensor(_name) {}
};
