#pragma once
#include "BasicExamples/ObjectOfObservation.h"
#include "BasicExamples/common.h"

class TRoad: public TObjectOfObservation {
protected:
    unsigned long int oldGoTime;
    std::vector <TRoad*> roadNeighboring;
    static std::vector<TRoad*> allRoads;
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
   std::vector<TRoad*> getAllRoads() const { return allRoads; }
};

class TCarDestroyer: public TRoad {
public:
    TCarDestroyer(std::string _name="");
    virtual bool IsCanGo() const noexcept { return true; }
    virtual void Go() override {}
    virtual std::string ClassName() override { return "TCarDestroyer"; }
    virtual TObjectOfObservation* Clone() { return new TCarDestroyer(); }
    // UPDATE
    virtual void Update() override;
};

class TCarCreator: public TRoad {
public:
    TCarCreator(std::string _name="");
    virtual TObjectOfObservation* Clone() { return new TCarCreator(); }
    virtual std::string ClassName() override { return "TCarCreator"; }
    // ADD UPDATE
    virtual void Update() override;
};