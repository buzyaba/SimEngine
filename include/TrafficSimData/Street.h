#pragma once

#include <stdlib.h>

#include "Core/Scene.h"
#include "Core/ObjectOfObservation.h"
#include "Core/SmartThing.h"
#include "Core/common.h"


#define TRoadIsBblockierenIndex 0
#define TRoadCoordinate 1
#define TRoadDimensions 2
#define TRoadIsBusy 3
#define TRoadIsHaveStandingCar 4

#define TCarWayIndex 0
#define TCarWayIndexCount 1
#define TCarCoordinate 2

#define TCarCreatorBblockierenIndex 0
#define TCarCreatorCoordinate 1
#define TCarCreatorDimensions 2
#define TCarCreatorIsBusy 3
#define TCarCreatorIsHaveStandingCar 4
#define TCarCreatorIsCreat 5


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
  /// Время последнего обновления
  unsigned long int oldGoTime;
  /// Соседние дороги
  std::vector < TRoad*> roadNeighboring;
  /// Можно ли ехать
  bool isCanGo;
public:
  TRoad(std::string _name) : TObjectOfObservation(_name)
  {
    this->properties.resize(5);
    this->properties[TRoadIsBblockierenIndex] = new TProperties({ 0 }, { "IsBblockieren" }, false, "IsBblockieren");
    this->properties[TRoadCoordinate] = new TProperties({ 10, 10 }, { "X", "Y" }, false, "Coordinate");
    this->properties[TRoadDimensions] = new TProperties({ 2, 2, 2 }, { "Width", "Length", "Height" }, false, "Dimensions");
    this->properties[TRoadIsBusy] = new TProperties({ 0 }, { "IsBusy" }, false, "IsBusy");
    this->properties[TRoadIsHaveStandingCar] = new TProperties({ 0 }, { "IsHaveStandingCar" }, true, "IsHaveStandingCar");

    oldGoTime = currentStep;
    isCanGo = true;
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
    /// Если есть потомки, это могут быть только машины, то проверяем можем ли ехать
    if (this->childObjects.size() == 0)
      return true;
    if (this->childObjects[0] == nullptr)
    {
      return true;
    }
    else
    {
      int roadIndex = this->childObjects[0]->GetProperties()[TCarWayIndex]->GetValues()[0];
      if (roadIndex >= 0 && roadIndex < this->roadNeighboring.size())
      {
        /// Если дорога заблокирована, то ехать нельзя
        if (this->roadNeighboring[roadIndex]->GetProperties()[TRoadIsBblockierenIndex]->GetValues()[0] == 1)
          return false;
        return this->roadNeighboring[roadIndex]->IsCanGo();
      }
      else
        throw - 1;
    }
    return false;
  }

  /// Уезжаем с этой клетки
  virtual void Go()
  {
    if (oldGoTime != currentStep)
    {
      oldGoTime = currentStep;
      isCanGo = true;
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

      isCanGo = IsCanGo();


      /// может ли машина уехать
      if (isCanGo)
      {
        //isBblockieren[0] = 0;
        //this->properties[TRoadIsBblockierenIndex]->SetValues(isBblockieren);
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

    }
  }

  virtual void Update()
  {
    TObjectOfObservation::Update();

    Go();

    std::vector<double>& isHaveStandingCar = this->properties[TRoadIsHaveStandingCar]->GetValues();
    if ((this->properties[TRoadIsBusy]->GetValues()[0] == 1) && !isCanGo)
    {
      isHaveStandingCar[0] = 1;
    }
    else
      isHaveStandingCar[0] = 0;
    this->properties[TRoadIsHaveStandingCar]->SetValues(isHaveStandingCar);
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

class TMachineNumberSensor : public TSensor
{
public:
  TMachineNumberSensor(std::string _name) : TSensor(_name)
  {
  }
};

class TBarrage : public TActuator
{
protected:
  /// блокируемая дорога
  TObjectOfObservation* blockedRoad;
public:
  TBarrage(std::string _name, TObjectOfObservation* _blockedRoad) : TActuator(_name)
  {
    if (_blockedRoad != nullptr)
      blockedRoad = _blockedRoad;
    else
      throw - 1;
  }

  virtual void SetDataPacket(TDataPacket& packet)
  {
    if (blockedRoad != nullptr)
    {
      if (packet.GetDoubles()[0] == 0)
        blockedRoad->SetProperty({ 0 }, "IsBblockieren");
      else
        blockedRoad->SetProperty({ 1 }, "IsBblockieren");
    }
  }
};

class TTrafficLight : public TSmartThing
{
public:

  TTrafficLight(std::string _name, TObjectOfObservation* _blockedRoad) :
    TSmartThing(_name, { new TMachineNumberSensor(_name + "MachineNumberSensor") }, { new TBarrage(_name + "Barrage", _blockedRoad) })
  {
    this->properties.resize(2);
    this->properties[0] = new TProperties({ 0 }, { "NumberOfStandingCars" }, true, "NumberOfStandingCars");
    this->properties[1] = new TProperties({ 0 }, { "Color" }, true, "Color"); //Зеленый 0; Желтый 1; Красный 2;

  }
};