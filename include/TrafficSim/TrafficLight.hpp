#pragma once

#include "BasicExamples/SmartThing.h"
#include "TrafficSim/Road.hpp"
#include "TrafficSim/Barrage.hpp"
#include "TrafficSim/CarNumberSensor.hpp"

class TTrafficLight : public TSmartThing
{
public:
    TTrafficLight(std::string _name = "") :
        TSmartThing(_name, { new TMachineNumberSensor(_name + "MachineNumberSensor") }, { new TBarrage(_name + "Barrage") }) {
        properties.insert({ "NumberOfStandingCars", new TProperties(std::map<std::string, double>{ {"NumberOfStandingCars", 0}}, true, "NumberOfStandingCars") });
        properties.insert({ "Color", new TProperties(std::map<std::string, double>{ {"Color", 0}, }, true, "Color") });
    }
    void initBuffer() override {}
    unsigned int getMeshBuffer() override { return -1; };
#ifdef USE_OpenGL
    virtual void setScale(const glm::vec3& _size) override {}
    virtual void setPosition(const glm::vec3& pos) override {}
#endif
    void AddObject(TObjectOfObservation& object) override {
        auto& prop = object.GetProperty("Blocking").GetValues();
        prop["Blocking"] = true;
        object.GetProperty("Blocking").SetValues(prop);
        TSmartThing::AddObject(object);
    }
    void drawElements(const std::vector<TObject*>& objects) {}
    void initDraw(const std::vector<TObject*>& objects) {}
    virtual TSmartThing* Clone() { return new TTrafficLight(); };
    virtual std::string ClassName() override { return std::string("TTrafficLight"); }
};