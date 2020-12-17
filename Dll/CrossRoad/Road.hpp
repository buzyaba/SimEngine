#pragma once
#include "SimEngine/ObjectOfObservation.h"
#include "Car.hpp"

class TRoad: public TObjectOfObservation {
private:
    class TRoadElem: public TObjectOfObservation {
    public:
        static int roadElemLength;
        TRoadElem(std::string _name = "");
        void Update() override;
        TObjectOfObservation* Clone() { return new TRoadElem(); }
        std::string ClassName() { return "TRoadElem"; }
    };
    int capacity;
public:
    TRoad(std::string _name = "");
    TRoad(std::string _name, IProperties& first_crossr, IProperties& second_crossr);
    void Update() override;
    TObjectOfObservation* Clone() { return new TRoad(); }
    std::string ClassName() { return "TRoad"; }
};
