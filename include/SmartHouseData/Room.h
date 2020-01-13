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
    this->properties.resize(1);
    this->properties[0] = new TProperties({ 20, 20, 20 }, { "Width", "Length", "Height" }, false, "Dimensions");
  }

  /// Возвращает имя класса (используется для динамического создания модели)
  virtual std::string ClassName()
  {
    return "TRoom";
  }

  /// Создание клона объекта
  virtual TRoom* Clone()
  {
    return new TRoom(*this);
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
    this->properties[0] = new TProperties({ 0 }, { "IsWork" }, false, "IsWork");
    this->properties[1] = new TProperties({ 0 }, { "PowerConsumption" }, true, "PowerConsumption");
    this->properties[2] = new TProperties({ 10, 10 }, { "X", "Y" }, false, "Coordinate");
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

  /// Возвращает имя класса (используется для динамического создания модели)
  virtual std::string ClassName()
  {
    return "TTerminal";
  }

  /// Создание клона объекта
  virtual TTerminal* Clone()
  {
    return new TTerminal(*this);
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
    for (int i = 0; i < objects.size(); i++)
    {
      if (objects[i] != nullptr)
      {
        if (packet.GetDoubles()[0] == 0)
          objects[i]->SetProperty({ 0 }, "IsWork");
        else
          objects[i]->SetProperty({ 1 }, "IsWork");
      }
    }
  }
};

class TSmartSocket : public TSmartThing
{
public:
  TSmartSocket(std::string _name) :
    TSmartThing(_name, { new TElectricitySensor(_name + "ElectricitySensor") }, { new TSwitch(_name + "Switch") })
  {
  }

  /// Возвращает имя класса (используется для динамического создания модели)
  virtual std::string ClassName()
  {
    return "TSmartSocket";
  }

  /// Создание клона объекта
  virtual TSmartSocket* Clone()
  {
    return new TSmartSocket(*this);
  }
};