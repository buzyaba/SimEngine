#include "Road.hpp"
#include <cmath>
#include <thread>

TRoad::TRoad(std::string _name): TObjectOfObservation(_name) {
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


TRoad::TRoad(std::string _name, IProperties& first_crossr, IProperties& second_crossr): TObjectOfObservation(_name) {
    auto first_crossr_x = first_crossr.GetValue("X");
    auto first_crossr_y = first_crossr.GetValue("Z");

    auto second_crossr_x = second_crossr.GetValue("X");
    auto second_crossr_y = second_crossr.GetValue("Z");

    auto x_diff = second_crossr_x-first_crossr_x;
    auto y_diff = second_crossr_y-first_crossr_y;

    auto x_center = x_diff/2;
    auto y_center = y_diff/2;

    auto length = std::sqrt(x_diff*x_diff+y_diff*y_diff);

    auto x_dir = x_diff / length;
    auto y_dir = y_diff / length;

    double offset_x{0};
    double offset_y{0};
    double angle{0};

    double delimeter = 4.37;

    if (y_dir == 0)
        if (x_dir > 0) {
            angle = -180;
            offset_y = -1.0*55/delimeter;
        }
        else {
            angle = 0;
            offset_y = 55/delimeter;
        }
    else if (y_dir > 0) {
        angle = 90;
        offset_x = 55/delimeter;
    }
    else {
        angle = -90;
        offset_x = -1.0*55/delimeter;
    }

    properties.insert(
        { "Scale", new TProperties({{"Width", length/55}, {"Length", 1}, {"Height", 1}},
                                  false, "Scale") });
    properties.insert(
        { "Coordinate",
        new TProperties({{"X", first_crossr_x + x_center + offset_x}, {"Y", 0}, {"Z", first_crossr_y + y_center + offset_y}}, false, "Coordinate") });
    properties.insert(
        { "Rotate",
        new TProperties({{"X", 0.0}, {"Y", angle}, {"Z", 0.0}},
                        false, "Rotate") });

    auto prop1 = GetProperty("Coordinate").GetValue("X");
    auto prop2 = GetProperty("Coordinate").GetValue("Z");
}

void TRoad::Update() {
    //  for (std::size_t i = 0; i < childObjects.size(); ++i) {
    //      if (!childObjects[i]->GetProperty("RoadState").GetValue("Busy")) {
    //          std::size_t k = i;
    //          for (; k < childObjects.size() && !childObjects[k]->GetProperty("RoadState").GetValue("Busy"); ++k);
    //          if (k < childObjects.size()) {
    //              auto car = childObjects[k]->GetChildObjects().front();
    //              if (!car->GetProperty("Moving").GetValue("Moving")) {
    //                  childObjects[k]->ExcludeChildObject(car);
    //                  childObjects[k]->GetProperty("RoadState").SetValue("Busy", 0);
    //                  childObjects[i]->AddChildObject(car);
    //                  car->AddParentObject(childObjects[i]);
    //                  childObjects[i]->GetProperty("RoadState").SetValue("Busy", 1);
    //              }
    //          }
    //      }
    //  }
    // TObjectOfObservation::Update();
}
