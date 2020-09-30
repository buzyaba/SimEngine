#pragma once
#include "Core/ObjectOfObservation.h"
#include "Core/common.h"

class TRoad: public TObjectOfObservation {
protected:
    unsigned long int oldGoTime;
    std::vector <TRoad*> roadNeighboring;
    bool isCanGo;
public:
    explicit TRoad(std::string _name="");
   virtual TObjectOfObservation* Clone() { return new TRoad();}
   virtual std::string ClassName() override { return "TRoad";}
   // FIX THAT LATER
   virtual void AddNeighboringObject(TObjectOfObservation& obect);
   virtual int AddChildObject(TObjectOfObservation& obect);
   virtual void ExcludeChildObject(TObjectOfObservation& obect);
   virtual void Go();
   virtual bool IsCanGo();
   virtual void Update() override;
};

inline std::vector<TRoad*>& getAllRoads() {
    static std::vector<TRoad*> allRoads;
    return allRoads;
}

extern "C" LIB_EXPORT_API TObjectOfObservation* create();