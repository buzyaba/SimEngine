#pragma once

#include "SimEngine/Sensor.h"
#include "RoadLane.h"

class TCarNumberSensor : public TSensor
{
    
public:
    TCarNumberSensor(std::string _name) : TSensor(_name) {}

    TDataPacket& GetDataPacket() override {
        if (packet != nullptr) {
            delete packet;
        }

        packet = new TDataPacket(objects.size()*sizeof(double));

        double* data = packet->GetData<double>();
        for (std::size_t i = 0; i < objects.size(); ++i) {
            auto roadLane = static_cast<RoadLane*>(objects[i]);
            for (std::size_t road_iter = 0; road_iter < roadLane->roads.size(); ++road_iter) {
                auto road = roadLane->roads[road_iter]->GetParentObject();
                auto roadElems = road->GetChildObjects();
                auto observedRoadElem = roadLane->roads[road_iter];
                if ((observedRoadElem->GetProperty("RoadState").GetValue("Blocked") || road->GetProperty("HasJam").GetValue("HasJam")) && observedRoadElem->GetChildObjects().size() > 0) {
                    for (auto elem : roadElems) {
                        if (elem->GetProperty("RoadState").GetValue("Busy"))
                            data[i]++;
                    }
                }
            }
        }
        // if (data[0] != 0) {
            // for (size_t i = 0; i < objects.size(); ++i)
            //     printf("%f ", data[i]);
            // printf("\n");
        // }
        return *packet;
    }
};
