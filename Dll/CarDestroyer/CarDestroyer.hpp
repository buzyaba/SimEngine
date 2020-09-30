#pragma once
#include "../Road/Road.hpp"

class TCarDestroyer: public TRoad {
public:
    TCarDestroyer(std::string _name="");
    virtual bool IsCanGo() const noexcept { return true; }
    virtual void Go() override {}
    virtual std::string ClassName() override { return "TCarDestroyer"; }
    virtual TObjectOfObservation* Clone() { return new TCarDestroyer(); }
    virtual void Update() override;
};
