#include "Car.hpp"
#include <cmath>
#include <iostream>
#include <thread>
#include <algorithm>

double TCar::dt = 0.0005;

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

    auto car_rotate_y = car_rotate.GetValue("Y");
    auto road_rotate_y = road_rotate.GetValue("Y");
    auto rotate_diff = road_rotate_y - car_rotate_y;

    auto car_coord_x = car_coord.GetValue("X");
    auto car_coord_y = car_coord.GetValue("Z");

    auto road_coord_x = road_coord.GetValue("X");
    auto road_coord_y = road_coord.GetValue("Z");


    auto x_diff = road_coord_x - car_coord_x;
    auto y_diff = road_coord_y - car_coord_y;

    auto length = std::sqrt(x_diff*x_diff+y_diff*y_diff);

    auto x_dir = x_diff / length;
    auto y_dir = y_diff / length;

    while (!compare_fp(car_coord_x, road_coord_x) || !compare_fp(car_coord_y, road_coord_y) || !compare_fp(car_rotate_y, road_rotate_y)) {
        if (!compare_fp(car_rotate_y, road_rotate_y))
            car_rotate_y += 100*dt*rotate_diff;
        if (!compare_fp(car_coord_x, road_coord_x))
            car_coord_x += dt*x_dir;
        if (!compare_fp(car_coord_y, road_coord_y))  
            car_coord_y += dt*y_dir;

        car_coord.SetValue("X", car_coord_x);
        car_coord.SetValue("Z", car_coord_y);
        car_rotate.SetValue("Y", car_rotate_y);

    }

}
