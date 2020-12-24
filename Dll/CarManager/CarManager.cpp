#include "CarManager.hpp"
#include <algorithm>
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

TCarManager::TCarManager(std::string _name): TCrossRoad(_name) {
    properties.insert(
      {"PoolSize", new TProperties({{"PoolSize", 1}}, false, "PoolSize")});
    car_pool.resize(static_cast<std::size_t>(this->GetProperty("PoolSize").GetValue("PoolSize")));
    std::generate(car_pool.begin(), car_pool.end(), [] { 
        static std::size_t i = 0; 
        return new TCar("TCar" + std::to_string(i));
    });
}

std::vector<TObjectOfObservation*> TCarManager::GetChildObject() {
    std::vector<TObjectOfObservation*> res;
    res.insert(res.end(), childObjects.begin(), childObjects.end());
    res.insert(res.end(), car_pool.begin(), car_pool.end());
    return res;
}

void TCarManager::Update() {
    TObjectOfObservation::Update();
    std::uniform_int_distribution<> d(1, 100);

    if (!car_pool.empty()) {
        if (d(gen) <= 25) {
            std::size_t target_idx = d(gen) % neighboringObject.size();
            auto crossroad = static_cast<TCrossRoad*>(neighboringObject[target_idx]);
            auto car = car_pool.back();
            crossroad->sendCar(this, car);
            car_pool.pop_back();
        }
    }

}

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TCarManager("TCarManager");
}
