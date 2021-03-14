#include "Car.hpp"
#include <random>
#include <chrono>

TCar::TCar(std::string _name) : TObjectOfObservation(_name) {
	properties.insert({ "WayIndex", new TProperties(std::map<std::string, double>{ {"WayIndex", -1}}, true, "WayIndex") });
	properties.insert({ "Coordinate", new TProperties(std::map<std::string, double>{ {"X", 0}, {"Y", 1}, {"Z", 0}}, false, "Coordinate") });
	properties.insert({ "WayIndexCount", new TProperties(std::map<std::string, double>{ {"WayIndexCount", 0}}, false, "WayIndexCount") });

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
}

void TCar::Update()
{
	TObjectOfObservation::Update();
	auto&& val = this->properties["WayIndex"]->GetValues();
	std::default_random_engine generator;
	generator.seed(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	std::poisson_distribution<int> poisson;
	val["WayIndex"] = poisson(generator) % static_cast<int>(this->properties["WayIndexCount"]->GetValues()["WayIndexCount"]);
	this->properties["WayIndex"]->SetValues(val);
}
