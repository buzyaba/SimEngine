#pragma once
#include "BasicExamples/ObjectOfObservation.h"

class TDesktop : public TObjectOfObservation
{
protected:
    ///Был ли включен терминал
    bool isWork;
public:
    explicit TDesktop(std::string _name = "");
    virtual void Update() override;
    virtual TObjectOfObservation* Clone() { return new TDesktop(); };
    virtual std::string ClassName() override { return std::string("TDesktop"); }
};
