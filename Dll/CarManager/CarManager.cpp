#include "CarManager.hpp"
#include <algorithm>
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

std::vector<TCar*> TCarManager::car_pool = {};

TCarManager::TCarManager(std::string _name): TCrossRoad(_name) {
    properties.insert(
      {"PoolSize", new TProperties({{"PoolSize", 50}}, false, "PoolSize")});
    car_pool.resize(static_cast<std::size_t>(this->GetProperty("PoolSize").GetValue("PoolSize")));
    std::generate(car_pool.begin(), car_pool.end(), [] { 
        static std::size_t i = 0; 
        return new TCar("TCar" + std::to_string(i));
    });
}

std::vector<TObjectOfObservation*>& TCarManager::GetChildObjects() {
    if (my_child_objects.empty()) {
        my_child_objects.insert(my_child_objects.end(), childObjects.begin(), childObjects.end());
        my_child_objects.insert(my_child_objects.end(), car_pool.begin(), car_pool.end());
    }
    return my_child_objects;
}

void TCarManager::Update() {
    TObjectOfObservation::Update();
    std::uniform_int_distribution<> d(1, 100);

    if (!car_pool.empty()) {
        if (d(gen)) {
            size_t count = 1;
            for (size_t i = 0; i < count; ++i) {
                std::size_t target_idx = d(gen) % neighboringObjects.size();
                auto crossroad = static_cast<TCrossRoad*>(neighboringObjects[target_idx]);
                auto car = car_pool.back();
                int res = crossroad->sendCar(this, car);
                if (!res) {
                    car->GetProperty("Coordinate").SetValue("X", GetProperty("Coordinate").GetValue("X"));
                    car->GetProperty("Coordinate").SetValue("Z", GetProperty("Coordinate").GetValue("Z"));
                    car_pool.pop_back();
                }
            }
        }
    }

    for (std::size_t i = 0; i < childObjects.size(); ++i) {
        auto roadElem = childObjects[i]->GetChildObjects().front();
        auto childs = roadElem->GetChildObjects();
        if (childs.size() > 0) {
            auto car = childs.front();
            if (!car->GetProperty("Moving").GetValue("Moving")) {
                car->GetProperty("Coordinate").SetValue("X", -10000);
                car->GetProperty("Coordinate").SetValue("Z", -10000);
                roadElem->ExcludeChildObject(car);
                roadElem->GetProperty("RoadState").SetValue("Busy", 0);
                car_pool.push_back(static_cast<TCar*>(car));
            }
        }
    }

}

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TCarManager("TCarManager");
}
