#pragma once

#include "SimEngine/Sensor.h"

class TMachineNumberSensor : public TSensor
{
public:
    TMachineNumberSensor(std::string _name) : TSensor(_name) {}

    //TDataPacket& GetDataPacket() override {
    //    if (oldObjectCount < objects.size())
    //    {
    //        oldObjectCount = objects.size();
    //        vals.resize(oldObjectCount);
    //        propertyCount = 0;
    //        for (size_t i = 0; i < objects.size(); ++i)
    //        {
    //            if (objects[i] != nullptr)
    //            {
    //                objectsProperties[i] = objects[i]->GetProperties();
    //                for (auto& elem : objectsProperties[i])
    //                    if (elem.second != nullptr && elem.second->IsObserved())
    //                        for (auto& iter : elem.second->GetValues())
    //                            ++propertyCount;
    //            }
    //        }
    //    }

    //    if (packet == nullptr)
    //        packet = new TDataPacket(propertyCount * sizeof(double));

    //    packet->SetSize(propertyCount * sizeof(double));
    //    double* data = packet->GetData<double>();
    //    size_t t = 0;
    //    for (size_t i = 0; i < objectsProperties.size(); ++i)
    //    {
    //        for (auto& elem : objectsProperties[i])
    //            if (elem.second != nullptr && elem.second->IsObserved())
    //                for (auto& iter : elem.second->GetValues()) {
    //                    data[t++] = iter.second;
    //                }
    //    }

    //    return *packet;
    //}
};
