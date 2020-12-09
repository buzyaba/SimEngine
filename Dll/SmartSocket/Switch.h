#pragma once

#include "SimEngine/Actuator.h"

class TSwitch : public TActuator
{
public:
  TSwitch(std::string _name) : TActuator(_name) {}

  virtual void SetDataPacket(TDataPacket& packet)
  {
    for (int i = 0; i < objects.size(); i++)
    {
      if (objects[i] != nullptr)
      {
        switch (static_cast<int>(packet.GetDoubles()[i])) {
          case 0:
            objects[i]->SetProperty({{"IsWork", 0}}, "IsWork");
            break;
          case 1:
            objects[i]->SetProperty({{"IsWork", 1}}, "IsWork");
            break;
          case 2:
            objects[i]->SetProperty({{"IsWork", 2}}, "IsWork");
            break;
        }
      }
    }
  }
};