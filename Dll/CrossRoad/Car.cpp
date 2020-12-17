#include "Car.hpp"

TCar::TCar(std::string _name): TObjectOfObservation(_name) {
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

void TCar::Update() {
    TObjectOfObservation::Update();
}
