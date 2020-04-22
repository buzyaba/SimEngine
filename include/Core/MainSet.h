﻿#pragma once
#include <map>
#include "Core/ObjectOfObservation.h"
#include "Core/SmartThing.h"
#include "Core/StaticObject.h"
#include <Engine/WindowManager.hpp>


/// Возвращает набор элементов по базовому скрипту
class TMainSet
{
protected:
  std::vector<TObjectOfObservation*> objects;
  std::vector<TStaticObject*> staticObjects;
  std::vector<TSmartThing*> things;
  std::map<std::string, std::vector<TObject*>> allGObjects;
public:
  TMainSet() = default;
  TMainSet(std::string xmlFile);
  std::vector<TObjectOfObservation*> GetObjects();
  std::vector<TStaticObject*> GetStaticObjects();
  std::vector<TSmartThing*> GetThings();
  const std::map<std::string, std::vector<TObject*>>& GetAllGObjects() {return allGObjects;}

};

class TRoomSet : public TMainSet
{
public:
  TRoomSet();
};

class TStreetSet : public TMainSet
{
public:
  TStreetSet();
};

class TSetFactory
{
public:
  static TMainSet* Create(int a = 0, std::string xmlFile = "")
  {
    if (xmlFile != "")
      return new TMainSet(xmlFile);
    if (a <= 0)
      return new TRoomSet();
    else
      return new TStreetSet();
  }
};