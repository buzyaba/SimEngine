#pragma once
#include "SimEngine/ObjectOfObservation.h"

class TCar: public TObjectOfObservation {
    static double dt;
public:
    TCar(std::string _name = "");
    TObjectOfObservation* Clone() { return new TCar(); }
    std::string ClassName() { return "TCar"; }
    void Update() override;
};
