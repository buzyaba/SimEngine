#include "CarCreator.hpp"
#include "../Road/Car.hpp"
#include <random>
#include <chrono>

TCarCreator::TCarCreator(std::string _name) : TRoad(_name) {
	properties.insert({ "IsCreat", new TProperties(std::map<std::string, double>{ {"IsCreat", 1}}, true, "IsCreat") });
}

void TCarCreator::Update()
{
	TRoad::Update();
	TObjectOfObservation* child = nullptr;
	std::default_random_engine generator;
	generator.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::poisson_distribution<int> poisson(100);
	if (this->childObjects.size() > 0)
		child = this->childObjects[0];
	if ((child == nullptr) && (properties["IsCreat"]->GetValues()["IsCreat"] == 1))
	{	
		if (poisson(generator)%100 == 0) {
			TCar* car = new TCar("Car");
			car->GetProperties()["Coordinate"]->SetValues(properties["Coordinate"]->GetValues());
			this->AddChildObject(*car);
		}
	}
}

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TCarCreator("TCarCreator");
}
