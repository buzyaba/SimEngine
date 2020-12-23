#pragma once
#include "SimEngine/ObjectOfObservation.h"
#include "Road.hpp"

class TCrossRoad: public TObjectOfObservation {
public:
    TCrossRoad(std::string _name = "");
    void AddNeighboringObject(TObjectOfObservation& obect) override;
    void Update() override;
    void sendCar(TCar* car);
    TObjectOfObservation* Clone() { return new TCrossRoad(); }
    std::string ClassName() { return "TCrossRoad"; }
};

extern "C" LIB_EXPORT_API TObjectOfObservation* create();
