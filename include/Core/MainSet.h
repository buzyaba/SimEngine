#pragma once
#include <map>
#include <stdexcept>
#include "SimEngine/ObjectOfObservation.h"
#include "SimEngine/SmartThing.h"
#include "SimEngine/StaticObject.h"
#include <map>

#include "../lib/pugixml/include/pugixml.hpp"

#ifdef USE_OPENGL
#include <Engine/WindowManager.hpp>
#endif

/// Возвращает набор элементов по базовому скрипту
class TMainSet {
protected:
    std::vector<TObjectOfObservation *> objects;
    std::vector<TStaticObject *> staticObjects;
    std::vector<TSmartThing *> things;

public:
    TMainSet() = default;
    TMainSet(std::string xmlMainSetConfigurationFile);
    void createObjects(const pugi::xml_node &config);
    void addDependentObjects(const pugi::xml_node &config);
    std::vector<TObjectOfObservation *> GetObjects();
    std::vector<TStaticObject *> GetStaticObjects();
    std::vector<TSmartThing *> GetThings();
};

class TSetFactory {
public:
  static TMainSet* Create(std::string xmlMainSetConfigurationFile = "")
  {
    if (xmlMainSetConfigurationFile != "")
      return new TMainSet(xmlMainSetConfigurationFile);
    else throw std::runtime_error("xmlMainSetConfigurationFile is empty");
  }
};