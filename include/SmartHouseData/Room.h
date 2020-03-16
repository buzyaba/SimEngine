#pragma once
#include <stdlib.h>

#include "Core/Scene.h"
#include "Core/ObjectOfObservation.h"
#include "Core/SmartThing.h"

class TRoom : public TScene
{
public:
  TRoom(std::string _name) : TScene(_name)
  {
    // this->properties.resize(1);
    // this->properties[0] = new TProperties({ 20, 20, 20 }, { "Width", "Length", "Height" }, false, "Dimensions");
  }
};


class TElectricitySensor : public TSensor
{
public:
  TElectricitySensor(std::string _name) : TSensor(_name)
  {
  }
};

class TSwitch : public TActuator
{
public:
  TSwitch(std::string _name) : TActuator(_name)
  {
  }

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

class TSmartSocket : public TSmartThing
{
public:
  TSmartSocket(std::string _name) :
    TSmartThing(_name, { new TElectricitySensor(_name + "ElectricitySensor") }, { new TSwitch(_name + "Switch") })
  {
  }
};