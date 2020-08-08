#pragma once
#include "BasicExamples/StaticObject.h"

class TTable : public TStaticObject {
public:
    explicit TTable(std::string _name = "");
    virtual TStaticObject* Clone() { return new TTable(); };
    virtual std::string ClassName() override { return std::string("TTable"); }
};
