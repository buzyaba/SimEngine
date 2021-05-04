#include <algorithm>
#include "gtest/gtest.h"
#include "SimEngine/common.h"
#include "SimEngine/ObjectOfObservation.h"
#include "Core/ExternalActionSchedule.h"

class DummyObject : public TObjectOfObservation {
public:
    DummyObject(std::string name) : TObjectOfObservation(name) {
        properties.insert(
            {"Property", new TProperties({{"Property", 2}}, false, "Property")});
    }
};

TEST(ExternalActionTest, Can_Create) {
    std::vector<TObjectOfObservation*> allObjects(15);
    std::generate(allObjects.begin(), allObjects.end(), [] {static int a = 1; return new DummyObject("DummyObject"+std::to_string(a++));} );

    ASSERT_NO_THROW(TExternalActionSchedule(allObjects, getPath("/Tests/common/actions.xml")));
    for(auto& elem : allObjects)
        delete(elem);
}

TEST(ExternalActionTest, GetObjectProperties_string) {
    std::vector<TObjectOfObservation*> allObjects(1);
    allObjects[0] = new DummyObject("DummyObject1");

    TExternalActionSchedule schedule(allObjects, getPath("/Tests/common/actions.xml"));
    auto property = schedule.GetObjectProperties("DummyObject1", 0ull);
    ASSERT_DOUBLE_EQ(property["Property"]->GetValue("Property"), 0.0);

    property = schedule.GetObjectProperties("DummyObject1", 1000ull);
    ASSERT_DOUBLE_EQ(property["Property"]->GetValue("Property"), 1.0);
    free(allObjects[0]);
}

TEST(ExternalActionTest, GetObjectProperties_reference) {
    std::vector<TObjectOfObservation*> allObjects(1);
    allObjects[0] = new DummyObject("DummyObject1");

    TExternalActionSchedule schedule(allObjects, getPath("/Tests/common/actions.xml"));
    auto property = schedule.GetObjectProperties(allObjects[0], 0ull);
    ASSERT_DOUBLE_EQ(property["Property"]->GetValue("Property"), 0.0);

    property = schedule.GetObjectProperties(allObjects[0], 1000ull);
    ASSERT_DOUBLE_EQ(property["Property"]->GetValue("Property"), 1.0);
    free(allObjects[0]);
}

TEST(ExternalActionTest, UpdateObjectProperties) {
    std::vector<TObjectOfObservation*> allObjects(15);
    std::generate(allObjects.begin(), allObjects.end(), [] {
        static int a = 1; 
        return new DummyObject("DummyObject"+std::to_string(a++));
    } );

    TExternalActionSchedule schedule(allObjects, getPath("/Tests/common/actions.xml"));
    schedule.UpdateObjectsProperties(0ull);
    ASSERT_DOUBLE_EQ(allObjects[0]->GetProperty("Property").GetValue("Property"), 0.0);

    schedule.UpdateObjectsProperties(500ull);
    ASSERT_DOUBLE_EQ(allObjects[0]->GetProperty("Property").GetValue("Property"), 0.0);

    schedule.UpdateObjectsProperties(1000ull);
    ASSERT_DOUBLE_EQ(allObjects[0]->GetProperty("Property").GetValue("Property"), 1.0);
    for(auto& elem : allObjects)
        delete(elem);
}