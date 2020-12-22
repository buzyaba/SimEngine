#include "CarManager.hpp"
#include <algorithm>

TCarManager::TCarManager(std::string _name): TCrossRoad(_name) {
    properties.insert(
      {"PoolSize", new TProperties({{"PoolSize", 250}}, false, "PoolSize")});
    car_pool.resize(static_cast<std::size_t>(this->GetProperty("PoolSize").GetValue("PoolSize")));
    std::generate(car_pool.begin(), car_pool.end(), [] { 
        static std::size_t i = 0; 
        return new TCar("TCar" + std::to_string(i));
    });
}

void TCarManager::Update() {
    TObjectOfObservation::Update();
}

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TCarManager("TCarManager");
}
