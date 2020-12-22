#include "Road.hpp"
#include <cmath>

int TRoad::TRoadElem::roadElemLength = 5;

TRoad::TRoad(std::string _name): TObjectOfObservation(_name) {}

TRoad::TRoad(std::string _name, IProperties& first_crossr, IProperties& second_crossr): TObjectOfObservation(_name) {
    auto first_crossr_x = first_crossr.GetValue("X");
    auto first_crossr_y = first_crossr.GetValue("Y");

    auto second_crossr_x = second_crossr.GetValue("X");
    auto second_crossr_y = second_crossr.GetValue("Y");

    auto x_diff = second_crossr_x-first_crossr_x;
    auto y_diff = second_crossr_y-first_crossr_y;

    auto length = std::sqrt(x_diff*x_diff+y_diff*y_diff);

    capacity = length / TRoadElem::roadElemLength;

    childObjects.reserve(capacity);
    double pos_x = first_crossr_x + TRoadElem::roadElemLength/2;
    double pos_y = first_crossr_y + TRoadElem::roadElemLength/2;
    for (int i = 0; i < capacity; ++i) {
        childObjects.push_back(new TRoadElem("yoba"));
        childObjects[i]->SetProperty({{"X", pos_x}, {"Y", pos_y}, {"Z", 0}}, "Coordinate");
        pos_x += TRoadElem::roadElemLength;
        pos_y += TRoadElem::roadElemLength;
    }
}

TRoad::TRoadElem::TRoadElem(std::string _name): TObjectOfObservation(_name) {
    properties.insert(
      {"Scale", new TProperties({{"Width", 3}, {"Length", TRoadElem::roadElemLength}, {"Height", 1}},
                                false, "Scale")});
    properties.insert(
        {"Coordinate",
        new TProperties({{"X", 0}, {"Y", 0}, {"Z", 0}}, false, "Coordinate")});
    properties.insert(
        {"Rotate",
        new TProperties({{"X", 0.0}, {"Y", 0.0}, {"Z", 0.0}},
                        false, "Rotate")});
}

void TRoad::Update() {
    TObjectOfObservation::Update();
}


void TRoad::TRoadElem::Update() {
    TObjectOfObservation::Update();
}
