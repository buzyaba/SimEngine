#pragma once

#include <stdlib.h>

#include "Core/Scene.h"
#include "Core/ObjectOfObservation.h"
#include "Core/SmartThing.h"

#define TRoadIsBblockierenIndex 0
#define TRoadCoordinate 1
#define TRoadDimensions 2
#define TRoadIsBusy 3

#define TCarWayIndex 0
#define TCarWayIndexCount 1
#define TCarCoordinate 2

#define TCarCreatorBblockierenIndex 0
#define TCarCreatorCoordinate 1
#define TCarCreatorDimensions 2
#define TCarCreatorIsBusy 3
#define TCarCreatorIsCreat 4


class TStreet : public TScene
{
public:
  TStreet(std::string _name) : TScene(_name)
  {
    this->properties.resize(1);
    this->properties[0] = new TProperties({ 200, 200, 200 }, { "Width", "Length", "Height" }, false, "Dimensions");
  }
};



class TRoad : public TObjectOfObservation
{
protected:
  /// Был лши включен терминал
  bool isUpdate;
  /// Соседние дороги
  std::vector < TRoad*> roadNeighboring;
public:
  TRoad(std::string _name) : TObjectOfObservation(_name)
  {
    this->properties.resize(4);
    this->properties[TRoadIsBblockierenIndex] = new TProperties({ 0 }, { "IsBblockieren" }, true, "IsBblockieren");
    this->properties[TRoadCoordinate] = new TProperties({ 10, 10 }, { "X", "Y" }, false, "Coordinate");
    this->properties[TRoadDimensions] = new TProperties({ 2, 2, 2 }, { "Width", "Length", "Height" }, false, "Dimensions");
    this->properties[TRoadIsBusy] = new TProperties({ 0 }, { "IsBusy" }, false, "IsBusy");

    isUpdate = false;
  }

  /// Добавить соседний объект, между ними может происходить объмен дочерними объектами
  virtual void AddNeighboringObject(TObjectOfObservation& obect)
  {
    TObjectOfObservation::AddNeighboringObject(obect);

    TRoad* road = dynamic_cast<TRoad*>(&obect);
    if (road != NULL)
    roadNeighboring.push_back(road);
  }
  /// Может ли машина уехать с этой клетки дороги
  virtual bool IsCanGo()
  {
    /// Если дорога заблокирована, то ехать нельзя
    if (this->properties[TRoadIsBblockierenIndex]->GetValues()[0] == 1)
      return false;

    /// Если есть потомки, это могут быть только машины, то проверяем можем ли ехать
    if (this->childObjects.size() == 0)
      return true;
    if (this->childObjects[0] == nullptr)
    {
      return true;
    }
    else
    {
      bool isCanGo = true;
      int roadIndex = this->childObjects[0]->GetProperties()[TCarWayIndex]->GetValues()[0];
      if (roadIndex >= 0 && roadIndex < this->roadNeighboring.size())
        isCanGo = this->roadNeighboring[roadIndex]->IsCanGo();
      else
        throw - 1;
      return isCanGo;
    }
    return false;
  }

  /// Уезжаем с этой клетки
  virtual void Go()
  {
    TObjectOfObservation* child = nullptr;
    if (this->childObjects.size() > 0)
      child = this->childObjects[0];

    if (child != nullptr)
    {
      std::vector<double>& maxWayIndex = child->GetProperties()[TCarWayIndexCount]->GetValues();
      maxWayIndex[0] = static_cast<double>(this->roadNeighboring.size());
      child->GetProperties()[TCarWayIndexCount]->SetValues(maxWayIndex);
      child->Update();
    }

    isUpdate = true;
    bool isCanGo = IsCanGo();

    std::vector<double>& isBblockieren = this->properties[TRoadIsBblockierenIndex]->GetValues();
    /// может ли машина уехать
    if (isCanGo)
    {
      isBblockieren[0] = 0;
      this->properties[TRoadIsBblockierenIndex]->SetValues(isBblockieren);
      if (child != nullptr)
      {
        int roadIndex = child->GetProperties()[TCarWayIndex]->GetValues()[0];
        if (roadIndex >= 0 && roadIndex < this->roadNeighboring.size())
        {
          this->ExcludeChildObject(*child); //извлекли машину
          this->roadNeighboring[roadIndex]->Go(); // сходили соседом
          this->roadNeighboring[roadIndex]->AddChildObject(*child); // добавили машину соседу
          child->GetProperties()[TCarCoordinate]->SetValues(
            this->roadNeighboring[roadIndex]->GetProperties()[TRoadCoordinate]->GetValues());
        }
        else
          throw - 1;
      }
    }
    else
    {
      isBblockieren[0] = 1;
      this->properties[TRoadIsBblockierenIndex]->SetValues(isBblockieren);
    }
  }

  virtual void Update()
  {
    TObjectOfObservation::Update();

    if (!isUpdate)
    {
      Go();
    }
    isUpdate = false;
  }

  /// Добавить дочерний объект
  virtual int AddChildObject(TObjectOfObservation& obect)
  {
    std::vector<double>& isBusy = this->properties[TRoadIsBusy]->GetValues();
    isBusy[0] = 1;
    this->properties[TRoadIsBusy]->SetValues(isBusy);

    return TObjectOfObservation::AddChildObject(obect);
  }

  /// Исключить дочерний объект
  virtual void ExcludeChildObject(TObjectOfObservation& obect)
  {
    std::vector<double>& isBusy = this->properties[TRoadIsBusy]->GetValues();
    isBusy[0] = 0;
    this->properties[TRoadIsBusy]->SetValues(isBusy);

    TObjectOfObservation::ExcludeChildObject(obect);
  }
};

class TCar : public TObjectOfObservation
{
public:
  TCar(std::string _name) : TObjectOfObservation(_name)
  {
    this->properties.resize(3);
    this->properties[TCarWayIndex] = new TProperties({ -1 }, { "WayIndex" }, true, "WayIndex");
    this->properties[TCarWayIndexCount] = new TProperties({ 0 }, { "WayIndexCount" }, false, "WayIndexCount");
    this->properties[TCarCoordinate] = new TProperties({ 10, 10 }, { "X", "Y" }, false, "Coordinate");
  }

  virtual void Update()
  {
    TObjectOfObservation::Update();
    std::vector<double>& val = this->properties[TCarWayIndex]->GetValues();
    val[0] = rand() % static_cast<int>(this->properties[TCarWayIndexCount]->GetValues()[0]);
    this->properties[TCarWayIndex]->SetValues(val);
  }
};


class TCarCreator : public TRoad
{
public:
  TCarCreator(std::string _name) : TRoad(_name)
  {
    this->properties.push_back(new TProperties({ 1 }, { "IsCreat" }, true, "IsCreat"));
  }

  virtual void Update()
  {
    TRoad::Update();
    TObjectOfObservation* child = nullptr;
    if (this->childObjects.size() > 0)
      child = this->childObjects[0];
    if ((child == nullptr) && (properties[TCarCreatorIsCreat]->GetValues()[0] == 1))
    {
      TCar* car = new TCar("Car");
      car->GetProperties()[TCarCoordinate]->SetValues(properties[TCarCreatorCoordinate]->GetValues());
      this->AddChildObject(*car);
    }
  }
};

class TCarDestroyer : public TRoad
{
public:
  TCarDestroyer(std::string _name) : TRoad(_name)
  {

  }

  virtual bool IsCanGo()
  {
    return true;
  }

  /// Уезжаем с этой клетки
  virtual void Go()
  {

  }

  virtual void Update()
  {
    std::vector<double>& isBblockieren = this->properties[TRoadIsBblockierenIndex]->GetValues();
    isBblockieren[0] = 0;
    this->properties[TRoadIsBblockierenIndex]->SetValues(isBblockieren);

    for (int i = 0; i < this->childObjects.size(); i++)
    {
      TObjectOfObservation* child = this->childObjects[i];
      if (child != nullptr)
      {
        this->ExcludeChildObject(*child);
        delete child;
      }
    }
  }
};

//class TElectricitySensor : public TSensor
//{
//public:
//  TElectricitySensor(std::string _name) : TSensor(_name)
//  {
//  }
//};
//
//class TSwitch : public TActuator
//{
//public:
//  TSwitch(std::string _name) : TActuator(_name)
//  {
//  }
//
//  virtual void SetDataPacket(TDataPacket& packet)
//  {
//    if (packet.GetDoubles()[0] == 0)
//    {
//      for (int i = 0; i < objects.size(); i++)
//      {
//        if (objects[i] != nullptr)
//        {
//          objects[i]->SetProperty({ 0 }, "IsWork");
//        }
//      }
//    }
//  }
//};
//
//class TSmartSocket : public TSmartThing
//{
//public:
//  TSmartSocket(std::string _name) :
//    TSmartThing(_name, { new TElectricitySensor(_name + "ElectricitySensor") }, { new TSwitch(_name + "Switch") })
//  {
//  }
//};