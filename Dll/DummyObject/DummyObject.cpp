#include "DummyObject.h"

TDummyObject::TDummyObject(std::string name) : TObjectOfObservation(name) {
        properties.insert(
            {"Property1", new TProperties({{"Property1", 2}}, false, "Property1")});
        properties.insert(
            {"Property2", new TProperties({{"Property2", 5}}, true, "Property2")});
    }

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TDummyObject("TDummyObject");
} 
