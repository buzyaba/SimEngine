#pragma once
#include "SimEngine/ObjectOfObservation.h"

class TCar: public TObjectOfObservation {
    static double dt;
    TObjectOfObservation* oldRoad;
    double car_rotate_y;
    double road_rotate_y;
    double rotate_diff;
    double car_coord_x;
    double car_coord_y;
    double road_coord_x;
    double road_coord_y;
    double x_diff;
    double y_diff;
    double length;
    double x_dir;
    double y_dir;
public:
    TCar(std::string _name = "");
    TObjectOfObservation* Clone() { return new TCar(); }
    std::string ClassName() { return "TCar"; }
    void Update() override;
};
