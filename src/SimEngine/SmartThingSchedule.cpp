#include "SimEngine/SmartThingSchedule.hpp"
#include "../lib/pugixml/include/pugixml.hpp"
#include "SimEngine/common.h"
#include <stdexcept>

TSmartThingSchedule::TSmartThingSchedule(std::vector<TSmartThing*>& _things, std::string xmlName) : things(_things){
  LoadXML(xmlName);
}

void TExternalActionSchedule::LoadXML(std::string xmlName)
{
  if (xmlName == "")
    throw std::invalid_argument("Empty xmlName");
  
  int timePointCount = 0;

  actuatorsValues.resize(things.size());

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(xmlName.c_str());
  if (result.status != pugi::status_ok)
    throw std::logic_error("Error while reading xml file " + std::to_string(result.status));
  pugi::xml_node config = doc.child("config");

  for (pugi::xml_node iter = config.first_child(); iter != 0; iter = iter.next_sibling())
  {
    std::string name = iter.name();
    std::string value = iter.child_value();

    if (name == "timePointCount")
      timePointCount = std::stoi(value);
    else if (name == "time")
    {
      time_points = ParseString<double>(value, "_");
    } else {
      for (size_t i = 0; i < thing.size(); i++)
        if (thing[i]->GetName() == name)
          actuatorsValues[i] = ParseString<std::vector<double>>(iter2.child_value(), "_");
    }
  }
}

void TSmartThingSchedule::UpdateThingsProperties(std::size_t time)
{
  for (size_t i = 0; i < things.size(); i++)
    if (actuatorsValues[i].size() > 0 && things[i] != nullptr)
    {
      auto& thingActuators = things[i]->GetActuators();
      for (for size_t j = 0; j < thingActuators.size(); j++)
      {
        size_t objectsCount = thingActuators[j]->GetObjectsCount();
        TDataPacket sendPacket;
        double* packetVal = sendPacket.GetDoubles();
        std::memset(packetVal, actuatorsValues[i][j], objectsCount);
        thingActuators[j]->SetDataPacket(sendPacket);
      }
    }
}