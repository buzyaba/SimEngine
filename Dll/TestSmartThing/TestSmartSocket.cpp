#include "TestSmartSocket.h"

TTestSmartSocket::TTestSmartSocket(std::string _name) :
  TSmartThing(_name, { new TTestElectricitySensor(_name + "TTestElectricitySensor") }, { new TTestSwitch(_name + "TTestSwitch") }) {}