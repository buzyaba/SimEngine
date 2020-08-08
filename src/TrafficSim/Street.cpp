#include <TrafficSim/Street.hpp>


TStreet::TStreet(std::string _name): TStaticObject(_name) {
    properties.insert({"Dimensions", new TProperties{{{"Width", 500}, {"Length", 500}, {"Height", 1}}, false, "Dimensions"}});
  }