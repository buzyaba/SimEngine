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