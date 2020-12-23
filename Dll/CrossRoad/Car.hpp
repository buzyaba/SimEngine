#pragma once
#include "SimEngine/ObjectOfObservation.h"

enum class CarDirection {FORWARD, LEFT, RIGHT};

class TCar: public TObjectOfObservation {
    CarDirection direction;
public:
    TCar(std::string _name = "");
    TObjectOfObservation* Clone() { return new TCar(); }
    std::string ClassName() { return "TCar"; }
    void Update() override;
};
