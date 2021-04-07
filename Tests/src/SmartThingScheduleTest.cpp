#include <algorithm>
#include "gtest/gtest.h"
#include "SimEngine/common.h"
#include "SimEngine/SmartThing.h"
#include "SimEngine/SmartThingSchedule.hpp"

class DummyActuator: public TActuator {
public:
  DummyActuator(std::string _name) : TActuator(_name) {}

  virtual void SetDataPacket(TDataPacket* packet)
  {
    for (int i = 0; i < objects.size(); i++)
    {
      if (objects[i] != nullptr)
      {
        switch (static_cast<int>(packet->GetData<double>()[i])) {
          case 0:
            objects[i]->SetProperty({{"Property", 0}}, "Property");
            break;
          case 1:
            objects[i]->SetProperty({{"Property", 1}}, "Property");
            break;
          case 2:
            objects[i]->SetProperty({{"Property", 2}}, "Property");
            break;
        }
      }
    }
  }
};

class DummySensor: public TSensor {
public:
    DummySensor(std::string _name) : TSensor(_name) {}
};

class DummyThing : public TSmartThing {
public:
    DummyThing(std::string name) : TSmartThing(name, { new DummySensor("DummySensor") }, { new DummyActuator("DummyActuator") }) {}
    TSmartThing* Clone() { return new DummyThing("DummyThing"); };
    std::string ClassName() override { return std::string("DummyThing"); }
};

class DummyObject : public TObjectOfObservation {
public:
    DummyObject(std::string name) : TObjectOfObservation(name) {
        properties.insert(
            {"Property", new TProperties({{"Property", 2}}, false, "Property")});
    }
};

TEST(SmartThingScheduleTest, Can_Create) {
    std::vector<TObjectOfObservation*> objects(15);
    std::generate(objects.begin(), objects.end(), [] {static int a = 1; return new DummyObject("DummyObject"+std::to_string(a++));} );

    std::vector<TSmartThing*> things(15);
    std::generate(things.begin(), things.end(), [&] {
        static int a = 1;
        auto Thing = new DummyThing("DummyThing"+std::to_string(a));
        Thing->AddObject(objects[a-1]);
        a++;
        return Thing;
    } );

    ASSERT_NO_THROW(TSmartThingSchedule(things, getPath("/Tests/common/things.xml")));
}

TEST(SmartThingScheduleTest, UpdateThingsProperties) {
    std::vector<TObjectOfObservation*> objects(15);
    std::generate(objects.begin(), objects.end(), [] {static int a = 1; return new DummyObject("DummyObject"+std::to_string(a++));} );

    std::vector<TSmartThing*> things(15);
    std::generate(things.begin(), things.end(), [&] {
        static int a = 1;
        auto Thing = new DummyThing("DummyThing"+std::to_string(a));
        Thing->AddObject(objects[a-1]);
        a++;
        return Thing;
    } );

    TSmartThingSchedule thingsSchedule(things, getPath("/Tests/common/things.xml"));

    thingsSchedule.UpdateThingsProperties(0ull);
    ASSERT_DOUBLE_EQ(objects[0]->GetProperty("Property").GetValue("Property"), 0.0);

    thingsSchedule.UpdateThingsProperties(500ull);
    ASSERT_DOUBLE_EQ(objects[0]->GetProperty("Property").GetValue("Property"), 0.0);

    thingsSchedule.UpdateThingsProperties(1000ull);
    ASSERT_DOUBLE_EQ(objects[0]->GetProperty("Property").GetValue("Property"), 1.0);
}