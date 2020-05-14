#pragma once

#include "BasicExamples/Actuator.h"

class TTestSwitch : public TActuator
{
public:
  TTestSwitch(std::string _name) : TActuator(_name) {}

  virtual void SetDataPacket(TDataPacket& packet)
  {
    // for (int i = 0; i < objects.size(); i++)
    // {
    //   if (objects[i] != nullptr)
    //   {
    //     if (packet.GetDoubles()[0] == 0)
    //       objects[i]->SetProperty({ 0 }, "IsWork");
    //     else
    //       objects[i]->SetProperty({ 1 }, "IsWork");
    //   }
    // }
  }
};