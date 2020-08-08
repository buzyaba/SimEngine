#pragma once
#include <map>
#include "BasicExamples/ObjectOfObservation.h"
#include "BasicExamples/SmartThing.h"
#include "BasicExamples/StaticObject.h"
#ifdef USE_OpenGL
#include <Engine/WindowManager.hpp>
#endif

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
  TMainSet(std::string xmlMainSetConfigurationFile);
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
  static TMainSet* Create(int a = 0, std::string xmlMainSetConfigurationFile = "")
  {
    if (xmlMainSetConfigurationFile != "")
      return new TMainSet(xmlMainSetConfigurationFile);
    if (a <= 0)
      return new TRoomSet();
    else
      return new TStreetSet();
  }
};