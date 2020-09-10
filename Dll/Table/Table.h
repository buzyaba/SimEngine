#pragma once
#include "Core/StaticObject.h"

class TTable : public TStaticObject {
public:
    explicit TTable(std::string _name = "");
    virtual TStaticObject* Clone() { return new TTable(); };
    virtual std::string ClassName() override { return std::string("TTable"); }
};

extern "C" LIB_EXPORT_API TStaticObject* create();