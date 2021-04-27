#pragma once
#include "SimEngine/StaticObject.h"

class TDummyStaticObject : public TStaticObject {
public:
    explicit TDummyStaticObject(std::string _name = "");
    virtual TStaticObject* Clone() { return new TDummyStaticObject(); };
    virtual std::string ClassName() override { return std::string("TDummyStaticObject"); }
};

extern "C" LIB_EXPORT_API TStaticObject* create();
