#pragma once

#include "BasicExamples/SmartThing.h"
#include "SmartHouse/Switch.h"
#include "SmartHouse/ElectricitySensor.h"

class TSmartSocket : public TSmartThing
{
public:
  TSmartSocket(std::string _name = "") :
    TSmartThing(_name, { new TElectricitySensor(_name + "ElectricitySensor") }, { new TSwitch(_name + "Switch") }) {}
    virtual TSmartThing* Clone() { return new TSmartSocket(); };
  virtual std::string ClassName() override { return std::string("TSmartSocket"); }
};