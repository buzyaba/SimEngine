#pragma once
#include "SimEngine/ObjectOfObservation.h"

class TMonoblock : public TObjectOfObservation
{
protected:
    ///Был ли включен терминал
    double isWork;
public:
    explicit TMonoblock(std::string _name = "");
    virtual void Update() override;
    virtual TObjectOfObservation* Clone() { return new TMonoblock(); };
    virtual std::string ClassName() override { return std::string("TMonoblock"); }
};

extern "C" LIB_EXPORT_API TObjectOfObservation* create();
