#pragma once

#include "BasicExamples/Sensor.h"

class TMachineNumberSensor : public TSensor
{
public:
    TMachineNumberSensor(std::string _name) : TSensor(_name) {}
};
