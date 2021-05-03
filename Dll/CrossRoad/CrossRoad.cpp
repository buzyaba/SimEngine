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
    if (!neighboringObjects.empty() && neighboringObjects.size() != 1)
        for (std::size_t i = 0; i < childObjects.size(); ++i) {
            auto roadElem = childObjects[i]->GetChildObjects().front();
            auto childs = roadElem->GetChildObjects();
            if (childs.size() > 0 && !roadElem->GetProperty("RoadState").GetValue("Blocked")) {
                std::size_t target_idx;
                do {
                    target_idx = d(gen) % neighboringObjects.size();
                } while (target_idx == i);
                auto car = childs.front();
                if (!car->GetProperty("Moving").GetValue("Moving")) {
                    auto crossroad = static_cast<TCrossRoad*>(neighboringObjects[target_idx]);
                    int res = crossroad->sendCar(this, static_cast<TCar*>(car));
                    if (!res) {
                        roadElem->ExcludeChildObject(car);
                        roadElem->GetProperty("RoadState").SetValue("Busy", 0);
                    }
                }
            }
        }
}

int TCrossRoad::sendCar(TCrossRoad* origin, TCar* car) {
    auto neighbour_it = std::find(neighboringObjects.begin(), neighboringObjects.end(), origin);
    std::size_t index = neighbour_it - neighboringObjects.begin();

    auto&& roadElems = childObjects[index]->GetChildObjects();
    auto elem = roadElems.rbegin();
    auto& road_property = (*elem)->GetProperty("RoadState");
    auto& coord_prop = (*elem)->GetProperty("Coordinate");
    auto& rotate_prop = (*elem)->GetProperty("Rotate");
    if (!road_property.GetValue("Busy")) {
        (*elem)->AddChildObject(car);
        car->AddParentObject(*elem);
        car->GetProperty("Moving").SetValue("Moving", 1);
        road_property.SetValue("Busy", 1);
        return 0;
    }
    else return 1;
}

void TCrossRoad::AddNeighboringObject(TObjectOfObservation* obect) {
    neighboringObjects.push_back(obect);
    auto& first = GetProperty("Coordinate");
    auto& second = obect->GetProperty("Coordinate");
    childObjects.emplace_back(new TRoad("Road", first, second));
    childObjects.back()->AddParentObject(this);
}
