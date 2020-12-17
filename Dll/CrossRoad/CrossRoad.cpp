#include "CrossRoad.hpp"

TCrossRoad::TCrossRoad(std::string _name): TObjectOfObservation(_name) {
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

void TCrossRoad::Update() {
    TObjectOfObservation::Update();
}

void TCrossRoad::AddNeighboringObject(TObjectOfObservation& obect) {
    // neighboringObject.push_back(&obect);
    // auto& first = GetProperty("Coordinate");
    // auto& second = obect.GetProperty("Coordinate");
    // childObjects.emplace_back(new TRoad("blyar", first, second));
}

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TCrossRoad("TCrossRoad");
}
