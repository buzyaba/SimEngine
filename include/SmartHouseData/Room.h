#pragma once
#include <stdlib.h>

#include "Core/Scene.h"
#include "Core/ObjectOfObservation.h"
#include "Core/SmartThing.h"

class TRoom : public TScene
{
public:
  TRoom(std::string _name):  TScene(_name)
  {
    this->properties.resize(1);
    this->properties[0] = new TProperties({ 20, 20, 20 }, { "Width", "Length", "Height" }, "Dimensions");
  }
};

class TTerminal : public TObjectOfObservation
{
protected:
  ///Был лши включен терминал
  bool isWork;
public:
  TTerminal(std::string _name) : TObjectOfObservation(_name)
  {
    this->properties.resize(3);
    this->properties[0] = new TProperties({ 0 }, { "IsWork" }, "IsWork");
    this->properties[1] = new TProperties({ 0 }, { "PowerConsumption" }, "PowerConsumption");
    this->properties[2] = new TProperties({ 10, 10}, { "X", "Y" }, "Coordinate"); 
    isWork = false;
  }

  virtual void Update()
  {
    TObjectOfObservation::Update();

    if (!isWork && this->properties[0]->GetValues()[0] == 1)
      this->properties[1]->SetValues({ 100 });

    if (this->properties[0]->GetValues()[0] != 0)
    {
      std::vector<double>& tmp = this->properties[1]->GetValues();
      tmp[0] += (double(rand()) / RAND_MAX) * (tmp[0] * 0.05) - tmp[0] * 0.025;
      if (tmp[0] <= 0)
        this->properties[0]->SetValues({ 0 });
    }
    else
      this->properties[1]->SetValues({ 0 });

    if (this->properties[1]->GetValues()[0] <= 0)
    {
      this->properties[0]->SetValues({ 0 });
      this->properties[1]->SetValues({ 0 });
    }

    isWork = this->properties[0]->GetValues()[0] == 1;
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
    if (packet.GetDoubles()[0] == 0)
    {
      for (int i = 0; i < objects.size(); i++)
      {
        if (objects[i] != nullptr)
        {
          objects[i]->SetProperty({ 0 }, "IsWork");
        }
      }
    }
  }
};

class TSmartSocket : public TSmartThing
{
public:
  TSmartSocket(std::string _name) : 
    TSmartThing(_name, { new TElectricitySensor(_name + "ElectricitySensor") }, {new TSwitch (_name + "Switch")})
  {
  }
};