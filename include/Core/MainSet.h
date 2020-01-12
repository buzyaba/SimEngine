#pragma once
#include "Core/ObjectOfObservation.h"
#include "Core/SmartThing.h"
#include "Core/Scene.h"


/// Возвращает набор элементов по базовому скрипту
class TMainSet
{
protected:
  std::vector<TObjectOfObservation*> objects;
  std::vector<TScene*> scene;
  std::vector<TSmartThing*> thing;
public:
  TMainSet();

  std::vector<TObjectOfObservation*> GetObject();
  std::vector<TScene*> GetScene();
  std::vector<TSmartThing*> GetThing();
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
  static TMainSet* Create(int a = 0)
  {
    if (a <= 0)
      return new TRoomSet();
    else
      return new TStreetSet();
  }
};