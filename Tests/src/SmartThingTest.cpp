#include "gtest/gtest.h"

#include "SimEngine/SmartThing.h"

class DummyActuator : public TActuator {
public:
    DummyActuator(std::string _name) : TActuator(_name) {}

    virtual void SetDataPacket(TDataPacket& packet) {
        for (int i = 0; i < objects.size(); i++) {
            if (objects[i] != nullptr) {
                switch (static_cast<int>(packet.GetData<double>()[i])) {
                    case 0: objects[i]->SetProperty({ { "Property", 0 } }, "Property"); break;
                    case 1: objects[i]->SetProperty({ { "Property", 1 } }, "Property"); break;
                    case 2: objects[i]->SetProperty({ { "Property", 2 } }, "Property"); break;
                }
            }
        }
    }
};

class DummySensor : public TSensor {
public:
    DummySensor(std::string _name) : TSensor(_name) {}
};

class DummyThing : public TSmartThing {
public:
    DummyThing(std::string name)
            : TSmartThing(name,
                          { new DummySensor("DummySensor") },
                          { new DummyActuator("DummyActuator") }) {}
    TSmartThing* Clone() {
        return new DummyThing("DummyThing");
    };
    std::string ClassName() override {
        return std::string("DummyThing");
    }
};

TEST(SmartThingTest, Can_Create_Instance) {
    ASSERT_NO_THROW(DummyThing("SmartThing"));
};

TEST(SmartThingTest, Can_Copy_Instance) {
    DummyThing thing("SmartThing");
    DummyThing copyThing(thing);
    ASSERT_EQ(copyThing.GetName(), "SmartThing");
};

TEST(SmartThingTest, Add_Object) {
    DummyThing thing("SmartThing");
    TObjectOfObservation* obj1 = new TObjectOfObservation("Object1");
    TObjectOfObservation* obj2 = new TObjectOfObservation("Object2");

    thing.AddObject(obj1);
    thing.AddObject(obj2);

    ASSERT_EQ(thing.GetSensors()[0]->GetObjectsCount(), 2);
    ASSERT_EQ(thing.GetActuators()[0]->GetObjectsCount(), 2);

    free(obj1);
    free(obj2);
};

TEST(SmartThingTest, Exclude_Object_By_Name) {
    DummyThing thing("SmartThing");
    TObjectOfObservation* obj1 = new TObjectOfObservation("Object1");
    TObjectOfObservation* obj2 = new TObjectOfObservation("Object2");

    thing.AddObject(obj1);
    thing.AddObject(obj2);
    thing.ExcludeObject("Object2");

    ASSERT_EQ(thing.GetSensors()[0]->GetObjectsCount(), 1);
    ASSERT_EQ(thing.GetActuators()[0]->GetObjectsCount(), 1);

    free(obj1);
    free(obj2);
};

TEST(SmartThingTest, Exclude_Object_By_Pointer) {
    DummyThing thing("SmartThing");
    TObjectOfObservation* obj1 = new TObjectOfObservation("Object1");
    TObjectOfObservation* obj2 = new TObjectOfObservation("Object2");

    thing.AddObject(obj1);
    thing.AddObject(obj2);
    thing.ExcludeObject(obj2);

    ASSERT_EQ(thing.GetSensors()[0]->GetObjectsCount(), 1);
    ASSERT_EQ(thing.GetActuators()[0]->GetObjectsCount(), 1);

    free(obj1);
    free(obj2);
};