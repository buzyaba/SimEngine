#include "Car.hpp"
#include "SimEngine/common.h"
#include <cmath>
#include <iostream>
#include <thread>
#include <algorithm>

double TCar::dt = 0.05;

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
    properties.insert({ "Moving", new TProperties({{ "Moving", 0 }}, false, "Moving") });
}

void TCar::Update() {
    TObjectOfObservation::Update();
    auto& car_coord = GetProperty("Coordinate");
    auto& car_rotate = GetProperty("Rotate");

    auto& road_coord = parentObject->GetProperty("Coordinate");
    auto& road_rotate = parentObject->GetProperty("Rotate");

    if (oldRoad != parentObject) {
        car_rotate_y = car_rotate.GetValue("Y");
        road_rotate_y = road_rotate.GetValue("Y");
        rotate_diff = road_rotate_y - car_rotate_y;

        car_coord_x = car_coord.GetValue("X");
        car_coord_y = car_coord.GetValue("Z");

        road_coord_x = road_coord.GetValue("X");
        road_coord_y = road_coord.GetValue("Z");


        x_diff = road_coord_x - car_coord_x;
        y_diff = road_coord_y - car_coord_y;

        length = std::sqrt(x_diff * x_diff + y_diff * y_diff);

        x_dir = x_diff / length;
        y_dir = y_diff / length;
        oldRoad = parentObject;
    }

    if ( abs(car_coord_x-road_coord_x) > dt || abs(car_coord_y - road_coord_y) > dt || abs(car_rotate_y - road_rotate_y) > dt) {
        if (abs(car_rotate_y - road_rotate_y) > dt)
            car_rotate_y += dt*rotate_diff;
        if (abs(car_coord_x - road_coord_x) > dt)
            car_coord_x += dt*x_dir;
        if (abs(car_coord_y - road_coord_y) > dt)
            car_coord_y += dt*y_dir;
        GetProperty("Moving").SetValue("Moving", 1);
        car_coord.SetValue("X", car_coord_x);
        car_coord.SetValue("Z", car_coord_y);
        car_rotate.SetValue("Y", car_rotate_y);
    }
    else {
        car_coord.SetValue("X", road_coord_x);
        car_coord.SetValue("Z", road_coord_y);
        car_rotate.SetValue("Y", road_rotate_y);
        GetProperty("Moving").SetValue("Moving", 0);
    }

}
