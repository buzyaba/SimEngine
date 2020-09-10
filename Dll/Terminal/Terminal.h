#pragma once
#include "Core/ObjectOfObservation.h"

class TTerminal : public TObjectOfObservation
{
protected:
    ///Был ли включен терминал
    bool isWork;
public:
    explicit TTerminal(std::string _name = "");
    virtual void Update() override;
    virtual TObjectOfObservation* Clone() { return new TTerminal(); };
    virtual std::string ClassName() override { return std::string("TTerminal"); }
};

extern "C" LIB_EXPORT_API TObjectOfObservation* create();
