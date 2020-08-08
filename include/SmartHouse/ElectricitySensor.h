#pragma once

#include "BasicExamples/Sensor.h"

class TElectricitySensor : public TSensor
{
public:
  TElectricitySensor(std::string _name) : TSensor(_name) {}
};
