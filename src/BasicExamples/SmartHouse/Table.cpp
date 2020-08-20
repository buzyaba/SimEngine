#include "BasicExamples/SmartHouse/Table.h"

TTable::TTable(std::string _name) : TStaticObject(_name) {
  properties.insert(
      {std::string("Coordinate"),
       new TProperties(
           std::map<std::string, double>{{"X", 0}, {"Y", 0}, {"Z", 0}}, false,
           "Coordinate")});
  properties.insert(
      {std::string("Rotate"),
       new TProperties(
           std::map<std::string, double>{{"Yaw", 0}, {"Pitch", 0}, {"Roll", 0}},
           false, "Rotate")});
  properties.insert({std::string("Dimensions"),
                     new TProperties(
                         std::map<std::string, double>{
                             {"Width", 1}, {"Length", 1}, {"Height", 1}},
                         false, "Dimensions")});
//   properties.insert(
//       {std::string("Textures"),
//        new TProperties(
//            std::map<std::string, std::string>{{"MeshName", "Стол_Куб.004"},
//                                               {"Original", "table.jpg"},
//                                               {"Change", "table.jpg"}},
//            false, "Textures")});
}
