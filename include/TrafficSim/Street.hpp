#pragma once

#include "BasicExamples/StaticObject.h"

class TStreet: public TStaticObject {
 public:
    explicit TStreet(std::string _name = "");
    virtual std::string ClassName() noexcept override {return "TStreet";}
    virtual TStaticObject* Clone() {return new TStreet;}
};
