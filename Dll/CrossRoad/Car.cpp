#include "Car.hpp"
#include "SimEngine/common.h"
#include <cmath>
#include <iostream>
#include <thread>
#include <algorithm>

template<typename T>
bool compare_fp(T a, T b) { 
    return abs(a - b) <= static_cast<T>(0.005) * std::max(abs(a), abs(b));
}

TCar::TCar(std::string _name): TObjectOfObservation(_name) {
    properties.insert(
      {"Scale", new TProperties({{"Width", 1}, {"Length", 1}, {"Height", 1}},
                                false, "Scale")});
    properties.insert(
        {"Coordinate",
        new TProperties({{"X", -10000}, {"Y", 3}, {"Z", -10000}}, false, "Coordinate")});
    properties.insert(
        {"Rotate",
        new TProperties({{"X", 0.0}, {"Y", 0.0}, {"Z", 0.0}},
                        false, "Rotate")});
}

void TCar::Update() {
    TObjectOfObservation::Update();
    auto& car_coord = GetProperty("Coordinate");
    auto& car_rotate = GetProperty("Rotate");

    auto& road_coord = parentObject->GetProperty("Coordinate");
    auto& road_rotate = parentObject->GetProperty("Rotate");

    road_coord_x = road_coord.GetValue("X");
    road_coord_y = road_coord.GetValue("Z");
    road_rotate_y = road_rotate.GetValue("Y");

    car_coord.SetValue("X", road_coord_x);
    car_coord.SetValue("Z", road_coord_y);
    car_rotate.SetValue("Y", road_rotate_y);
}
