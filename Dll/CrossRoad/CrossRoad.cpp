#include "CrossRoad.hpp"
#include <algorithm>
#include <random>
#include <iostream>

static std::random_device rd;
static std::mt19937 gen(rd());

TCrossRoad::TCrossRoad(std::string _name): TObjectOfObservation(_name) {
    properties.insert(
      {"Scale", new TProperties({{"Width", 1.1}, {"Length", 1}, {"Height", 1.1}},
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
    std::uniform_int_distribution<> d(1, 100);
    if (!neighboringObject.empty() && neighboringObject.size() != 1)
        for (std::size_t i = 0; i < childObjects.size(); ++i) {
            auto roadElem = childObjects[i]->GetChildObject().front();
            auto childs = roadElem->GetChildObject();
            if (childs.size() > 0) {
                std::size_t target_idx;
                do {
                    target_idx = d(gen) % neighboringObject.size();
                } while (target_idx == i);
                auto car = childs.front();
                childs.pop_back();
                auto crossroad = static_cast<TCrossRoad*>(neighboringObject[target_idx]);
                crossroad->sendCar(this, static_cast<TCar*>(car));
            }
        }
}

void TCrossRoad::sendCar(TCrossRoad* origin, TCar* car) {
    auto neighbour_it = std::find(neighboringObject.begin(), neighboringObject.end(), origin);
    std::size_t index = neighbour_it - neighboringObject.begin();

    auto&& roadElems = childObjects[index]->GetChildObject();
    for (auto elem : roadElems) {
        auto& road_property = elem->GetProperty("RoadState");
        auto& coord_prop = elem->GetProperty("Coordinate");
        auto& rotate_prop = elem->GetProperty("Rotate");
        if (!road_property.GetValue("Busy")) {
            elem->AddChildObject(*car);
            car->AddParentObject(*elem);
            road_property.SetValue("Busy", 1);
            break;
        }
    }
}

void TCrossRoad::AddNeighboringObject(TObjectOfObservation& obect) {
    neighboringObject.push_back(&obect);
    auto& first = GetProperty("Coordinate");
    auto& second = obect.GetProperty("Coordinate");
    childObjects.emplace_back(new TRoad("Road", first, second));
    childObjects.back()->AddParentObject(*this);
}
