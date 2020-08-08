#include <TrafficSim/Road.hpp>
#include <TrafficSim/Car.hpp>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>

std::vector<TRoad*> TRoad::allRoads = {};

TRoad::TRoad(std::string _name) : TObjectOfObservation(_name) {
	properties.insert({ "IsBblockieren", new TProperties(std::map<std::string, double>{ {"IsBblockieren", 0}}, false, "IsBblockieren") });
	properties.insert({ "Coordinate", new TProperties(std::map<std::string, double>{ {"X", 0}, {"Y", 1}, {"Z", 0}}, false, "Coordinate") });
	properties.insert({ "Dimensions", new TProperties{{{"Width", 20}, {"Length", 10}, {"Height", 1}}, false, "Dimensions"} });
	properties.insert({ "IsBusy", new TProperties(std::map<std::string, double>{ {"IsBusy", 0}}, false, "IsBusy") });
	properties.insert({ "Blocking", new TProperties(std::map<std::string, double>{ {"Blocking", 0}}, false, "Blocking") });
	properties.insert({ "IsHaveStandingCar", new TProperties(std::map<std::string, double>{ {"IsHaveStandingCar", 0}}, true, "IsHaveStandingCar") });

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
	/// ���� ���� �������, ��� ����� ���� ������ ������, �� ��������� ����� �� �����
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
			/// ���� ������ �������������, �� ����� ������
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


		/// ����� �� ������ ������
		if (isCanGo)
		{
			//isBblockieren[0] = 0;
			//this->properties[TRoadIsBblockierenIndex]->SetValues(isBblockieren);
			if (child != nullptr)
			{
				int roadIndex = child->GetProperties()["WayIndex"]->GetValues()["WayIndex"];
				if (roadIndex >= 0 && roadIndex < this->roadNeighboring.size())
				{
					this->ExcludeChildObject(*child); //�������� ������
					this->roadNeighboring[roadIndex]->Go(); // ������� �������
					this->roadNeighboring[roadIndex]->AddChildObject(*child); // �������� ������ ������
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


/// �������� �������� ������
int TRoad::AddChildObject(TObjectOfObservation& obect)
{
	auto&& isBusy = this->properties["IsBusy"]->GetValues();
	isBusy["IsBusy"] = 1;
	this->properties["IsBusy"]->SetValues(isBusy);

	return TObjectOfObservation::AddChildObject(obect);
}

/// ��������� �������� ������
void TRoad::ExcludeChildObject(TObjectOfObservation& obect)
{
	auto&& isBusy = this->properties["IsBusy"]->GetValues();
	isBusy["IsBusy"] = 0;
	this->properties["IsBusy"]->SetValues(isBusy);

	TObjectOfObservation::ExcludeChildObject(obect);
}

TCarDestroyer::TCarDestroyer(std::string _name) : TRoad(_name)
{

}

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

void TCarDestroyer::Update()
{
	auto&& isBblockieren = this->properties["IsBblockieren"]->GetValues();
	isBblockieren["IsBblockieren"] = 0;
	this->properties["IsBblockieren"]->SetValues(isBblockieren);

	for (int i = 0; i < this->childObjects.size(); i++)
	{
		TObjectOfObservation* child = this->childObjects[i];
		if (child != nullptr)
		{
			this->ExcludeChildObject(*child);
			delete child;
		}
	}
}