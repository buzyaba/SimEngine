#include "BasicExamples/SmartHouse/Room.h"

TRoom::TRoom(std::string _name) : TStaticObject(_name) {
  properties.insert(
      {"Scale", new TProperties({{"Width", 1.2}, {"Length", 1.2}, {"Height", 1.2}},
                                false, "Scale")});
  properties.insert(
      {"Coordinate",
       new TProperties({{"X", 0}, {"Y", 0}, {"Z", 0}}, false, "Coordinate")});
  properties.insert(
      {"Rotate",
       new TProperties({{"X", 0.0}, {"Y", 0.0}, {"Z", 0.0}},
                       false, "Rotate")});
}
