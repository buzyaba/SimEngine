#pragma once

#include "Core/SmartThing.h"
#include "Switch.h"
#include "ElectricitySensor.h"

class TSmartSocket : public TSmartThing
{
public:
  TSmartSocket(std::string _name = "") :
    TSmartThing(_name, { new TElectricitySensor(_name + "ElectricitySensor") }, { new TSwitch(_name + "Switch") }) {}
    virtual TSmartThing* Clone() { return new TSmartSocket(); };
  virtual std::string ClassName() override { return std::string("TSmartSocket"); }
};

extern "C" LIB_EXPORT_API TSmartThing* create();
