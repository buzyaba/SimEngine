#include "BasicExamples/SmartHouse/Table.h"

TTable::TTable(std::string _name) : TStaticObject(_name) {
  properties.insert(
      {"Coordinate",
       new TProperties({{"X", 0}, {"Y", 0}, {"Z", 0}}, false, "Coordinate")});
  properties.insert(
      {"Rotate",
       new TProperties({{"X", 0.0}, {"Y", 0.0}, {"Z", 0.0}},
                       false, "Rotate")});
  properties.insert(
      {"Scale", new TProperties({{"Width", 3}, {"Length", 3}, {"Height", 3}},
                                false, "Scale")});
  //   textures.push_back({{"Стол_Куб.004"}, {"table.jpg"}, {"table.jpg"}});
}
