#pragma once

#include "Core/SmartThing.h"
#include "Barrage.hpp"
#include "CarNumberSensor.hpp"

class TTrafficLight : public TSmartThing
{
public:
    TTrafficLight(std::string _name = "") :
        TSmartThing(_name, { new TMachineNumberSensor(_name + "MachineNumberSensor") }, { new TBarrage(_name + "Barrage") }) {
        properties.insert({ "NumberOfStandingCars", new TProperties(std::map<std::string, double>{ {"NumberOfStandingCars", 0}}, true, "NumberOfStandingCars") });
        properties.insert({ "Color", new TProperties(std::map<std::string, double>{ {"Color", 0}, }, true, "Color") });
    }
    void AddObject(TObjectOfObservation& object) override {
        auto& prop = object.GetProperty("Blocking").GetValues();
        prop["Blocking"] = true;
        object.GetProperty("Blocking").SetValues(prop);
        TSmartThing::AddObject(object);
    }
    virtual TSmartThing* Clone() { return new TTrafficLight(); };
    virtual std::string ClassName() override { return std::string("TTrafficLight"); }
};

extern "C" LIB_EXPORT_API TSmartThing* create();