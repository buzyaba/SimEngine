#pragma once

#include "SimEngine/SmartThing.h"
#include "Barrage.hpp"
#include "CarNumberSensor.hpp"

class TTrafficLight : public TSmartThing
{
public:
    TTrafficLight(std::string _name = "") :
        TSmartThing(_name, {  }, {  }) {
                properties.insert(
      {"Scale", new TProperties({{"Width", 1}, {"Length", 1}, {"Height", 1}},
                                false, "Scale")});
    properties.insert(
        {"Coordinate",
        new TProperties({{"X", 0}, {"Y", 20}, {"Z", 0}}, false, "Coordinate")});
    properties.insert(
        {"Rotate",
        new TProperties({{"X", 0.0}, {"Y", 0.0}, {"Z", 0.0}},
                        false, "Rotate")});
        properties.insert({ "NumberOfStandingCars", new TProperties(std::map<std::string, double>{ {"NumberOfStandingCars", 0}}, true, "NumberOfStandingCars") });
        properties.insert({ "Color", new TProperties(std::map<std::string, double>{ {"Color", 0}, }, true, "Color") });
    }
    void AddObject(TObjectOfObservation* object) override {
        auto& prop = object->GetProperty("Blocking").GetValues();
        prop["Blocking"] = true;
        object->GetProperty("Blocking").SetValues(prop);
        TSmartThing::AddObject(object);
    }
    virtual TSmartThing* Clone() { return new TTrafficLight(); };
    virtual std::string ClassName() override { return std::string("TTrafficLight"); }
    bool isDrawable() { return true; }
};

extern "C" LIB_EXPORT_API TSmartThing* create();