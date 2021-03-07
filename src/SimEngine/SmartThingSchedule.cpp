#include "SimEngine/SmartThingSchedule.hpp"

TSmartThingSchedule::TSmartThingSchedule(std::vector<TSmartThing*>& _things, std::string xmlName) : things(_things){
  LoadXML(xmlName);
}

void TSmartThingSchedule::LoadXML(std::string xmlName)
{
    if (xmlName == "") {
        created = false;
        return;
    }
  
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
      time_points = ParseString<std::size_t>(value, "_");
    } else {
      for (size_t i = 0; i < things.size(); i++)
        if (things[i]->GetName() == name)
          actuatorsValues[i] = ParseComplexString<double>(value, "_");
    }
  }
}

void TSmartThingSchedule::UpdateThingsProperties(std::size_t time)
{
  if (!created)
    return;
  size_t time_index = GetTimePointIndex(time);
  if (time_index == -1)
    return;
  for (size_t i = 0; i < things.size(); i++)
    if (actuatorsValues[i].size() > 0 && things[i] != nullptr)
    {
      auto& thingActuators = things[i]->GetActuators();
      for (size_t j = 0; j < thingActuators.size(); j++)
      {
        size_t objectsCount = thingActuators[j]->GetObjectsCount();
        TDataPacket sendPacket(objectsCount*sizeof(double));
        double* packetVal = sendPacket.GetData<double>();
        std::fill(packetVal, packetVal + objectsCount, actuatorsValues[i][time_index][j]);
        // std::memset(packetVal, actuatorsValues[i][time_index][j], sizeof(double)*objectsCount);
        thingActuators[j]->SetDataPacket(sendPacket);
      }
    }
}

size_t TSmartThingSchedule::GetTimePointIndex(size_t time) {
  auto time_iter = std::find(time_points.begin(), time_points.end(), time);
  if (time_iter == time_points.end())
    return -1;
  else
    return std::distance(time_points.begin(), time_iter);
}
