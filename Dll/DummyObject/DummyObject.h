#pragma once
#include "SimEngine/ObjectOfObservation.h"

class TDummyObject : public TObjectOfObservation
{
public:
    explicit TDummyObject(std::string _name = "");
    virtual TObjectOfObservation* Clone() { return new TDummyObject(); };
    virtual std::string ClassName() override { return std::string("TDummyObject"); }
};

extern "C" LIB_EXPORT_API TObjectOfObservation* create();
