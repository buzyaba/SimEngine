#pragma once
#include <map>
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
    std::map<std::string, std::vector<Primitive*>> allGObject;
public:
  TMainSet();

  std::vector<TObjectOfObservation*> GetObject();
  std::vector<TScene*> GetScene();
  std::vector<TSmartThing*> GetThing();
  const std::map<std::string, std::vector<Primitive*>>& GetAllGObject() {return allGObject;}
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
    if (a == 0)
      return new TRoomSet();
    else
      return new TStreetSet();
  }
};