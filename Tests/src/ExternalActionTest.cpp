#include <algorithm>
#include "gtest/gtest.h"
#include "SimEngine/common.h"
#include "SimEngine/ObjectOfObservation.h"
#include "Core/ExternalActionSchedule.h"

// TEST(ExternalActionScheduleTest, CanCreate)
// {
//   //virtual IProperties& GetObjectProperties(std::string name) = 0;
//   //virtual IProperties& GetObjectProperties(const IObject& object) = 0;
//   // EXPECT_EQ(4, 2 + 2);
// };

class DummyObject : public TObjectOfObservation {
public:
    DummyObject(std::string name) : TObjectOfObservation(name) {
        properties.insert(
            {"Property", new TProperties({{"Property", 2}}, false, "Property")});
    }
};

TEST(ExternalActionTest, Can_Create) {
    std::vector<TObjectOfObservation*> allObjects(15);
    std::for_each(allObjects.begin(), allObjects.end(), [](auto& elem) {elem = new DummyObject("dummy");} );

    ASSERT_NO_THROW(TExternalActionSchedule(allObjects, getPath("/Tests/src/actions.xml")));
}