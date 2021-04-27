#include "Street.hpp"


TStreet::TStreet(std::string _name): TStaticObject(_name) {
    properties.insert(
      {"Coordinate",
       new TProperties({{"X", 0}, {"Y", 0}, {"Z", 0}}, false, "Coordinate")});
  properties.insert(
      {"Rotate",
       new TProperties({{"X", 0.0}, {"Y", 0.0}, {"Z", 0.0}},
                       false, "Rotate")});
  properties.insert(
      {"Scale", new TProperties({{"Width", 1}, {"Length", 1}, {"Height", 1}},
                                false, "Scale")});
  }

LIB_EXPORT_API TStaticObject* create()
{
    return new TStreet("TStreet");
}
