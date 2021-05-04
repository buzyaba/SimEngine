#pragma once

#include "SimEngine/Sensor.h"

class DummySensor: public TSensor {
public:
    DummySensor(std::string _name) : TSensor(_name) {}
};
