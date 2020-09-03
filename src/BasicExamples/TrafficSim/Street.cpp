#include <BasicExamples/TrafficSim/Street.hpp>


TStreet::TStreet(std::string _name): TStaticObject(_name) {
    properties.insert({"Scale", new TProperties{{{"Width", 500}, {"Length", 500}, {"Height", 1}}, false, "Scale"}});
  }