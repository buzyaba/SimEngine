#pragma once

#include "SimEngine/Actuator.h"
#include "RoadLane.h"

class TBarrage : public TActuator
{
protected:
    std::string coord_property;
public:
    TBarrage(std::string _name) : TActuator(_name) {}

    virtual void SetDataPacket(TDataPacket& packet)
    {
        for (std::size_t i = 0; i < objects.size(); ++i) {
            for (auto elem : static_cast<RoadLane*>(objects[i])->roads) {
                elem->GetProperty("RoadState").SetValue("Blocked", packet.GetData<double>()[i]);
            }
        }
    }
};
