#include "BasicExamples/SmartHouse/Room.h"

TRoom::TRoom(std::string _name)
    : TStaticObject(_name) {
  properties.insert({std::string("Dimensions"),
                     new TProperties(
                         std::map<std::string, double>{
                             {"Width", 15}, {"Length", 15}, {"Height", 15}},
                         false, "Dimensions")}); 
}
