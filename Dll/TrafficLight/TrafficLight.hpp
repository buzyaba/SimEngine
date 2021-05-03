#pragma once

#include "SimEngine/SmartThing.h"
#include "Barrage.hpp"
#include "CarNumberSensor.hpp"

class TTrafficLight : public TSmartThing
{
    std::vector<TObjectOfObservation*> getRoads(const std::vector<TObjectOfObservation*>& childs) {
        std::vector<TObjectOfObservation*> res;
        res.reserve(4);
        for (auto elem : childs) {
            if (elem->ClassName() == "TRoad") {
                res.push_back(elem);
            }
        }
        return res;
    }

    bool almost_equal(double x, double y) {
        return std::abs(x-y) <= 0.001 * std::abs(x+y);
    }
public:
    TTrafficLight(std::string _name = "") :
        TSmartThing(_name, { new TCarNumberSensor(_name + "CarSensor") },
            { new TBarrage(_name + "Barrage1"), new TBarrage(_name + "Barrage2")})
    {
        properties.insert(
        {"Scale", new TProperties({{"Width", 1}, {"Length", 1}, {"Height", 1}},
                                    false, "Scale")});
        properties.insert(
            {"Coordinate",
            new TProperties({{"X", 0}, {"Y", 20}, {"Z", 0}}, false, "Coordinate")});
        properties.insert(
            {"Rotate",
            new TProperties({{"X", 0.0}, {"Y", 0.0}, {"Z", 0.0}},
                            false, "Rotate")});
        properties.insert({ "NumberOfStandingCars", new TProperties(std::map<std::string, double>{ {"NumberOfStandingCars", 0}}, true, "NumberOfStandingCars") });
        properties.insert({ "Color", new TProperties(std::map<std::string, double>{ {"Color", 0}, }, true, "Color") });
    }
    void AddObject(TObjectOfObservation* object) override {
        std::vector<TObjectOfObservation*> xRoads;
        std::vector<TObjectOfObservation*> yRoads;

        auto allRoads = getRoads(object->GetChildObjects());

        auto crossr_x = object->GetProperty("Coordinate").GetValue("X");
        auto crossr_z = object->GetProperty("Coordinate").GetValue("Z");


        if (allRoads.size() == 1) {
            xRoads.push_back(allRoads[0]->GetChildObjects()[0]);
        } else if (allRoads.size() == 2) {

            auto i_road = allRoads[0]->GetChildObjects()[0];
            auto j_road = allRoads[1]->GetChildObjects()[0];

            xRoads.push_back(i_road);
            yRoads.push_back(j_road);
        } else if (allRoads.size() == 3) {
            std::vector<bool> pushed(3, 0);
            for (std::size_t i = 0; i < allRoads.size(); ++i) {
                for (std::size_t j = 0; j < allRoads.size(); ++j) {
                    if (i != j) {
                        auto i_road = allRoads[i]->GetChildObjects()[0];
                        auto j_road = allRoads[j]->GetChildObjects()[0];

                        auto crossr_x = object->GetProperty("Coordinate").GetValue("X");
                        auto crossr_z = object->GetProperty("Coordinate").GetValue("Z");

                        auto i_road_x = i_road->GetProperty("Coordinate").GetValue("X");
                        auto i_road_z = i_road->GetProperty("Coordinate").GetValue("Z");

                        auto j_road_x = j_road->GetProperty("Coordinate").GetValue("X");
                        auto j_road_z = j_road->GetProperty("Coordinate").GetValue("Z");

                        if (almost_equal(std::abs(i_road_x-crossr_x), 12.585812) && almost_equal(std::abs(j_road_x-crossr_x), 12.585812)) {
                            xRoads.push_back(i_road);
                            pushed[i] = true;
                        } else if (almost_equal(std::abs(i_road_z-crossr_z), 12.585812) && almost_equal(std::abs(j_road_z-crossr_z), 12.585812)) {
                            yRoads.push_back(i_road);
                            pushed[i] = true;
                        }
                    }
                }
            }
            auto not_pushed = std::find(pushed.begin(), pushed.end(), false);
            if (xRoads.size() == 2) {
                yRoads.push_back(allRoads[not_pushed-pushed.begin()]->GetChildObjects()[0]);
            } else if (yRoads.size() == 2) {
                xRoads.push_back(allRoads[not_pushed-pushed.begin()]->GetChildObjects()[0]);
            }
            
        } else if  (allRoads.size() == 4) {
            for (std::size_t i = 0; i < allRoads.size(); ++i) {
                for (std::size_t j = 0; j < allRoads.size(); ++j) {
                    if (i != j) {
                        auto i_road = allRoads[i]->GetChildObjects()[0];
                        auto j_road = allRoads[j]->GetChildObjects()[0];

                        auto crossr_x = object->GetProperty("Coordinate").GetValue("X");
                        auto crossr_z = object->GetProperty("Coordinate").GetValue("Z");

                        auto i_road_x = i_road->GetProperty("Coordinate").GetValue("X");
                        auto i_road_z = i_road->GetProperty("Coordinate").GetValue("Z");

                        auto j_road_x = j_road->GetProperty("Coordinate").GetValue("X");
                        auto j_road_z = j_road->GetProperty("Coordinate").GetValue("Z");

                        if (almost_equal(std::abs(i_road_x-crossr_x), 12.585812) && almost_equal(std::abs(j_road_x-crossr_x), 12.585812)) {
                            xRoads.push_back(i_road);
                        } else if (almost_equal(std::abs(i_road_z-crossr_z), 12.585812) && almost_equal(std::abs(j_road_z-crossr_z), 12.585812)) {
                            yRoads.push_back(i_road);
                        }
                    }
                }
            }

        }

        if (!xRoads.empty()) {
            auto roadLane = new RoadLane{ xRoads };
            actuators[0]->AddObject(roadLane);
            sensors[0]->AddObject(roadLane);
        }
        if (!yRoads.empty()) {
            auto roadLane = new RoadLane{ yRoads };
            actuators[1]->AddObject(roadLane);
            sensors[0]->AddObject(roadLane);
        }

        // for (int i = 0; i < sensors.size(); i++)
        //     if (sensors[i] != nullptr)
        //         sensors[i]->AddObject(object);
    }
    virtual TSmartThing* Clone() { return new TTrafficLight(); };
    virtual std::string ClassName() override { return std::string("TTrafficLight"); }
    bool isDrawable() { return true; }
};

extern "C" LIB_EXPORT_API TSmartThing* create();