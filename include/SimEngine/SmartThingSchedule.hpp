#pragma once

#include <string>
#include <vector>
#include <map>

#include "SimEngine/SmartThing.h"


class TSmartThingSchedule {
public:
  TSmartThingSchedule(std::vector<TSmartThing*>& _things, std::string xmlName);
  void UpdateObjectsProperties(std::size_t time);
  void LoadXML(std::string xmlName);
private:
  std::vector<TSmartThing*> things;
  std::vector<size_t> time_points;
  std::vector<std::vector<double>> actuatorsValues;
};