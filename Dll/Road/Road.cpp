#include "Road.hpp"
#include "Car.hpp"
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>

std::vector<TRoad*> TRoad::allRoads = {};

TRoad::TRoad(std::string _name) : TObjectOfObservation(_name) {
	properties.insert({ "IsBblockieren", new TProperties(std::map<std::string, double>{ {"IsBblockieren", 0}}, false, "IsBblockieren") });
	properties.insert({ "IsBusy", new TProperties(std::map<std::string, double>{ {"IsBusy", 0}}, false, "IsBusy") });
	properties.insert({ "Blocking", new TProperties(std::map<std::string, double>{ {"Blocking", 0}}, false, "Blocking") });
	properties.insert({ "IsHaveStandingCar", new TProperties(std::map<std::string, double>{ {"IsHaveStandingCar", 0}}, true, "IsHaveStandingCar") });
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

	isCanGo = true;
	oldGoTime = currentStep;

	if (allRoads.size() == 0) {
		allRoads.push_back(this);
	}
	else {
		AddNeighboringObject(*allRoads.back());
		allRoads.push_back(this);
	}
}

void TRoad::Update()
{
	TObjectOfObservation::Update();

	Go();

	auto&& isHaveStandingCar = properties["IsHaveStandingCar"]->GetValues();

	if ((this->properties["IsBusy"]->GetValues()["IsBusy"] == 1) && !isCanGo)
		isHaveStandingCar["IsHaveStandingCar"] = 1;
	else
		isHaveStandingCar["IsHaveStandingCar"] = 0;

	this->properties["IsHaveStandingCar"]->SetValues(isHaveStandingCar);

	auto blocked = properties["IsBblockieren"]->GetValue("IsBblockieren");
	int sum = 0;
	auto&& it = allRoads.rbegin();
	if (blocked) {
		for (; (*it) != this; ++it);
		auto res = 
			std::accumulate(allRoads.rbegin(), it, 0,
				[&](auto a, auto b) {
					return a + b->GetProperty("IsHaveStandingCar").GetValue("IsHaveStandingCar");
				});
		isHaveStandingCar = properties["IsHaveStandingCar"]->GetValues();
		isHaveStandingCar["IsHaveStandingCar"] = res;
		properties["IsHaveStandingCar"]->SetValues(isHaveStandingCar);
	}
}

bool TRoad::IsCanGo()
{
	if (this->childObjects.size() == 0)
		return true;
	if (this->childObjects[0] == nullptr)
	{
		return true;
	}
	else
	{
		int roadIndex = this->childObjects[0]->GetProperties()["WayIndex"]->GetValues()["WayIndex"];
		if (roadIndex >= 0 && roadIndex < this->roadNeighboring.size())
		{
			if (this->roadNeighboring[roadIndex]->GetProperties()["IsBblockieren"]->GetValues()["IsBblockieren"] == 1)
				return false;
			return this->roadNeighboring[roadIndex]->IsCanGo();
		}
		else
			throw - 1;
	}
	return false;
}

void TRoad::Go()
{
	if (oldGoTime != currentStep)
	{
		oldGoTime = currentStep;
		isCanGo = true;
		TObjectOfObservation* child = nullptr;
		if (this->childObjects.size() > 0)
			child = this->childObjects[0];

		if (child != nullptr)
		{
			auto&& maxWayIndex = child->GetProperties()["WayIndexCount"]->GetValues();
			maxWayIndex["WayIndexCount"] = static_cast<double>(this->roadNeighboring.size());
			child->GetProperties()["WayIndexCount"]->SetValues(maxWayIndex);
			child->Update();
		}

		isCanGo = IsCanGo();


		if (isCanGo)
		{
			//isBblockieren[0] = 0;
			//this->properties[TRoadIsBblockierenIndex]->SetValues(isBblockieren);
			if (child != nullptr)
			{
				int roadIndex = child->GetProperties()["WayIndex"]->GetValues()["WayIndex"];
				if (roadIndex >= 0 && roadIndex < this->roadNeighboring.size())
				{
					this->ExcludeChildObject(*child);
					this->roadNeighboring[roadIndex]->Go();
					this->roadNeighboring[roadIndex]->AddChildObject(*child);
					child->GetProperties()["Coordinate"]->SetValues(
						this->roadNeighboring[roadIndex]->GetProperties()["Coordinate"]->GetValues());
				}
				else
					throw - 1;
			}
		}

	}
}

void TRoad::AddNeighboringObject(TObjectOfObservation& obect)
{
	TObjectOfObservation::AddNeighboringObject(obect);

	TRoad* road = dynamic_cast<TRoad*>(&obect);
	if (road != NULL)
		roadNeighboring.push_back(road);
}


int TRoad::AddChildObject(TObjectOfObservation& obect)
{
	auto&& isBusy = this->properties["IsBusy"]->GetValues();
	isBusy["IsBusy"] = 1;
	this->properties["IsBusy"]->SetValues(isBusy);

	return TObjectOfObservation::AddChildObject(obect);
}

void TRoad::ExcludeChildObject(TObjectOfObservation& obect)
{
	auto&& isBusy = this->properties["IsBusy"]->GetValues();
	isBusy["IsBusy"] = 0;
	this->properties["IsBusy"]->SetValues(isBusy);

	TObjectOfObservation::ExcludeChildObject(obect);
}

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TRoad("TRoad");
}
