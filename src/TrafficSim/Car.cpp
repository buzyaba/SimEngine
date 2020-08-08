#include <TrafficSim/Car.hpp>
#include <random>
#include <chrono>

TCar::TCar(std::string _name) : TObjectOfObservation(_name) {
	properties.insert({ "WayIndex", new TProperties(std::map<std::string, double>{ {"WayIndex", -1}}, true, "WayIndex") });
	properties.insert({ "Coordinate", new TProperties(std::map<std::string, double>{ {"X", 0}, {"Y", 1}, {"Z", 0}}, false, "Coordinate") });
	properties.insert({ "Dimensions", new TProperties{{{"Width", 8}, {"Length", 15}, {"Height", 4}}, false, "Dimensions"} });
	properties.insert({ "WayIndexCount", new TProperties(std::map<std::string, double>{ {"WayIndexCount", 0}}, false, "WayIndexCount") });
}

void TCar::Update()
{
	TObjectOfObservation::Update();
	auto&& val = this->properties["WayIndex"]->GetValues();
	std::default_random_engine generator;
	generator.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::poisson_distribution<int> poisson;
	val["WayIndex"] = poisson(generator) % static_cast<int>(this->properties["WayIndexCount"]->GetValues()["WayIndexCount"]);
	this->properties["WayIndex"]->SetValues(val);
}
