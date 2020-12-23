#include "Road.hpp"
#include <cmath>

double TRoad::TRoadElem::roadElemLength = 45;

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
    double delimeter = 3.59;

    childObjects.reserve(capacity);
    double pos_x = first_crossr_x + 1.325*x_dir*TRoadElem::roadElemLength;
    double pos_y = first_crossr_y + 1.325*y_dir*TRoadElem::roadElemLength;
    for (int i = 0; i < capacity; ++i) {
        childObjects.push_back(new TRoadElem("RoadElem" + std::to_string(i)));
        double offset_x{0};
        double offset_y{0};
        double angle;

        if (y_dir == 0)
            if (x_dir > 0) {
                angle = -180;
                offset_y = -1.0*TRoadElem::roadElemLength/delimeter;
            }
            else {
                angle = 0;
                offset_y = TRoadElem::roadElemLength/delimeter;
            }
        else if (y_dir > 0) {
            angle = 90;
            offset_x = TRoadElem::roadElemLength/delimeter;
        }
        else {
            angle = -90;
            offset_x = -1.0*TRoadElem::roadElemLength/delimeter;
        }
        childObjects.back()->SetProperty({{"X", pos_x + offset_x}, {"Y", 0}, {"Z", pos_y + offset_y}}, "Coordinate");
        childObjects.back()->SetProperty({{"X", 0.0}, {"Y", angle}, {"Z", 0.0}}, "Rotate");

        pos_x += x_dir * 1.38*TRoadElem::roadElemLength/2;
        pos_y += y_dir * 1.38*TRoadElem::roadElemLength/2;
    }
}

TRoad::TRoadElem::TRoadElem(std::string _name): TObjectOfObservation(_name) {
    properties.insert(
      {"Scale", new TProperties({{"Width", 1}, {"Length", 1}, {"Height", 1}},
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
