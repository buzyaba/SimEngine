#pragma once

#include "BasicExamples/Actuator.h"

class TBarrage : public TActuator
{
protected:
public:
    TBarrage(std::string _name) : TActuator(_name) {
        //if (_br != nullptr) {
        //    blockedRoad = _br;
        //}
    }

    virtual void SetDataPacket(TDataPacket& packet)
    {
        if (objects.size()) {
            if (packet.GetDoubles()[0] == 0)
                objects[0]->SetProperty({{"IsBblockieren", 0}}, "IsBblockieren");
            else
                objects[0]->SetProperty({{"IsBblockieren", 1}}, "IsBblockieren");
        }
    }
};