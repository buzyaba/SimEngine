#pragma once

#include "DummyActuator.h"
#include "DummySensor.h"
#include "SimEngine/SmartThing.h"


class TDummySmartThing : public TSmartThing {
public:
  TDummySmartThing(std::string name)
      : TSmartThing(name, {new DummySensor("DummySensor")},
                    {new DummyActuator("DummyActuator")}) {}
  virtual TSmartThing *Clone() {
    return new TDummySmartThing("TDummySmartThing");
  };
  virtual std::string ClassName() override {
    return std::string("TDummySmartThing");
  }
};

extern "C" LIB_EXPORT_API TSmartThing *create();
