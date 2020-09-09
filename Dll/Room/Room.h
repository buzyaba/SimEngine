#pragma once
#include "Core/StaticObject.h"

class TRoom : public TStaticObject {
public:
    explicit TRoom(std::string _name = "");
    virtual TStaticObject* Clone() { return new TRoom(); };
    virtual std::string ClassName() override { return std::string("TRoom"); }
};

extern "C" LIB_EXPORT_API TStaticObject* create();
