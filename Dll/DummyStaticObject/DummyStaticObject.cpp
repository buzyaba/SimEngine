#include "DummyStaticObject.h"

TDummyStaticObject::TDummyStaticObject(std::string _name)
    : TStaticObject(_name) {
  properties.insert(
      {"StaticProperty1", new TProperties({{"StaticProperty1", 6}}, false, "StaticProperty1")});
  properties.insert(
      {"StaticProperty2", new TProperties({{"StaticProperty2", 5}}, false, "StaticProperty2")});
}

LIB_EXPORT_API TStaticObject *create() {
  return new TDummyStaticObject("TDummyStaticObject");
}
