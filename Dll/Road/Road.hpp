#pragma once
#include "SimEngine/ObjectOfObservation.h"
#include "SimEngine/common.h"

class TRoad: public TObjectOfObservation {
protected:
    std::size_t oldGoTime;
    std::vector <TRoad*> roadNeighboring;
    bool isCanGo;
public:
    explicit TRoad(std::string _name="");
   virtual TObjectOfObservation* Clone() { return new TRoad();}
   virtual std::string ClassName() override { return "TRoad";}
   // FIX THAT LATER
   virtual void AddNeighboringObject(TObjectOfObservation* object);
   virtual int AddChildObject(TObjectOfObservation* object);
   virtual void ExcludeChildObject(TObjectOfObservation* object);
   virtual void Go();
   virtual bool IsCanGo();
   virtual void Update() override;
};

inline std::vector<TRoad*>& getAllRoads() {
    static std::vector<TRoad*> allRoads;
    return allRoads;
}

extern "C" LIB_EXPORT_API TObjectOfObservation* create();