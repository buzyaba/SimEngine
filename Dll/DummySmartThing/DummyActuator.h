#pragma once

#include "SimEngine/Actuator.h"

class DummyActuator: public TActuator {
public:
  DummyActuator(std::string _name) : TActuator(_name) {}

  virtual void SetDataPacket(TDataPacket& packet)
  {
    for (int i = 0; i < objects.size(); i++)
    {
      if (objects[i] != nullptr)
      {
        switch (static_cast<int>(packet.GetData<double>()[i])) {
          case 0:
            objects[i]->SetProperty({{"Property", 0}}, "Property");
            break;
          case 1:
            objects[i]->SetProperty({{"Property", 1}}, "Property");
            break;
          case 2:
            objects[i]->SetProperty({{"Property", 2}}, "Property");
            break;
        }
      }
    }
  }
};
