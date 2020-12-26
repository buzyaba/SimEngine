#pragma once
#include "../CrossRoad/CrossRoad.hpp"

class TCarManager: public TCrossRoad {
private:
   static std::vector<TCar*> car_pool;
public:
    TCarManager(std::string _name = "");
    void Update() override;
    std::vector<TObjectOfObservation*> GetChildObject() override;
    TObjectOfObservation* Clone() { return new TCarManager(); }
    std::string ClassName() { return "TCarManager"; }
};

extern "C" LIB_EXPORT_API TObjectOfObservation* create();
