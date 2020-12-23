#include "Road.hpp"
#include <cmath>

int TRoad::TRoadElem::roadElemLength = 25;

TRoad::TRoad(std::string _name): TObjectOfObservation(_name) {}

TRoad::TRoad(std::string _name, IProperties& first_crossr, IProperties& second_crossr): TObjectOfObservation(_name) {
    auto first_crossr_x = first_crossr.GetValue("X");
    auto first_crossr_y = first_crossr.GetValue("Z");

    auto second_crossr_x = second_crossr.GetValue("X");
    auto second_crossr_y = second_crossr.GetValue("Z");

    auto x_diff = second_crossr_x-first_crossr_x;
    auto y_diff = second_crossr_y-first_crossr_y;

    auto length = std::sqrt(x_diff*x_diff+y_diff*y_diff);

    auto x_dir = x_diff / length;
    auto y_dir = y_diff / length;

    capacity = length / TRoadElem::roadElemLength;

    childObjects.reserve(capacity);
    double pos_x = first_crossr_x;
    double pos_y = first_crossr_y;
    for (int i = 0; i < capacity; ++i) {
        childObjects.push_back(new TRoadElem("RoadElem"+std::to_string(i)));
        double offset_x{0};
        double offset_y{0};
        double angle;
        if (y_dir == 0)
            if (x_dir > 0) {
                angle = -180;
                offset_y = -1*TRoadElem::roadElemLength/2;
            }
            else {
                angle = 0;
                offset_y = TRoadElem::roadElemLength/2;
            }
        else if (y_dir > 0) {
            angle = 90;
            offset_x = TRoadElem::roadElemLength/2;
        }
        else {
            angle = -90;
            offset_x = -1*TRoadElem::roadElemLength/2;
        }
        childObjects[i]->SetProperty({{"X", pos_x + offset_x}, {"Y", -20}, {"Z", pos_y+offset_y}}, "Coordinate");
        childObjects[i]->SetProperty({{"X", 0.0}, {"Y", angle}, {"Z", 0.0}}, "Rotate");
        pos_x += x_dir * TRoadElem::roadElemLength;
        pos_y += y_dir * TRoadElem::roadElemLength;
    }
}

TRoad::TRoadElem::TRoadElem(std::string _name): TObjectOfObservation(_name) {
    properties.insert(
      {"Scale", new TProperties({{"Width", 2}, {"Length", 1}, {"Height", 6}},
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
