#pragma once

#include "BasicExamples/SmartThing.h"
#include "TrafficSim/Barrage.hpp"
#include "TrafficSim/CarNumberSensor.hpp"

class TTrafficLight : public TSmartThing
{
public:
    TTrafficLight(std::string _name = "", TObjectOfObservation* _blockedRoad) :
        TSmartThing(_name, { new TMachineNumberSensor(_name + "MachineNumberSensor") }, { new TBarrage(_name + "Barrage", _blockedRoad) }) {}
    void initBuffer() override {}
    unsigned int getMeshBuffer() override { return -1; };
#ifdef USE_OpenGL
    virtual void setScale(const glm::vec3& _size) override {}
    virtual void setPosition(const glm::vec3& pos) override {}
#endif
    void drawElements(const std::vector<TObject*>& objects) {}
    void initDraw(const std::vector<TObject*>& objects) {}
    virtual TSmartThing* Clone() { return new TTrafficLight(); };
    virtual std::string ClassName() override { return std::string("TTrafficLight"); }
};