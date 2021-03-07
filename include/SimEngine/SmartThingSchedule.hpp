#pragma once

#include <string>
#include <vector>

#include "SimEngine/SmartThing.h"
#include "../lib/pugixml/include/pugixml.hpp"
#include "SimEngine/common.h"
#include <stdexcept>

class TSmartThingSchedule {
public:
  TSmartThingSchedule() = default;
  TSmartThingSchedule(std::vector<TSmartThing*>& _things, std::string xmlName);
  void UpdateThingsProperties(std::size_t time);
private:
  void LoadXML(std::string xmlName);
  size_t GetTimePointIndex(size_t time);

  std::vector<TSmartThing*> things;
  std::vector<size_t> time_points;
  std::vector<std::vector<std::vector<double>>> actuatorsValues;
  bool created;
};
