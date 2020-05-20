#pragma once

#include "BasicExamples/Actuator.h"

class TBarrage : public TActuator
{
protected:
    TObjectOfObservation* blockedRoad;
public:
    TBarrage(std::string _name, TObjectOfObservation* _br) : TActuator(_name) {
        if (_br != nullptr) {
            blockedRoad = _br;
        }
        else {
            throw - 1;
        }
    }

    virtual void SetDataPacket(TDataPacket& packet)
    {
        if (blockedRoad != nullptr) {
            if (packet.GetDoubles()[0] == 0)
                blockedRoad->SetProperty({{"IsBlockieren", 0}}, "IsBlockieren");
            else
                blockedRoad->SetProperty({{"IsBlockieren", 1}}, "IsBlockieren");
        }
    }
};