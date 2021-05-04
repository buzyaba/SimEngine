#include "Core/MainSet.h"
#include "SimEngine/common.h"
#include "gtest/gtest.h"

TEST(MainSetTest, Throw_If_Empty_Name) { ASSERT_ANY_THROW(TMainSet("")); }

TEST(MainSetTest, Throw_Wrong_Name) {
  ASSERT_ANY_THROW(TMainSet("wrongName.xml"));
}

TEST(MainSetTest, Throw_If_Empty_Name_In_Fabric) {
  ASSERT_ANY_THROW(TSetFactory::Create(""));
}

TEST(MainSetTest, Can_Create) {
  TMainSet *set;
  ASSERT_NO_THROW(
      set = TSetFactory::Create(getPath("/Tests/common/MainSet.xml")));
  free(set);
}

TEST(MainSetTest, Load_Valid_Objects) {
  TMainSet *set = TSetFactory::Create(getPath("/Tests/common/MainSet.xml"));
  auto objects = set->GetObjects();
  ASSERT_EQ(objects.size(), 3);
  ASSERT_EQ(objects[0]->GetProperty("Property1").GetValue("Property1"), 4);
  free(set);
}

TEST(MainSetTest, Load_Valid_Static_Objects) {
  TMainSet *set = TSetFactory::Create(getPath("/Tests/common/MainSet.xml"));
  auto staticObjects = set->GetStaticObjects();
  ASSERT_EQ(staticObjects.size(), 2);
  ASSERT_EQ(staticObjects[1]
                ->GetProperty("StaticProperty1")
                .GetValue("StaticProperty1"),
            17);
  free(set);
}

TEST(MainSetTest, Load_Valid_Things) {
  TMainSet *set = TSetFactory::Create(getPath("/Tests/common/MainSet.xml"));
  auto things = set->GetThings();
  ASSERT_EQ(things.size(), 2);
  ASSERT_EQ(things[0]->GetName(), "DummyStaticObject1");
  ASSERT_EQ(things[0]->GetSensors().size(), 1);
  ASSERT_EQ(things[0]->GetActuators().size(), 1);
  ASSERT_EQ(things[1]->GetName(), "DummyStaticObject2");
  ASSERT_EQ(things[0]->GetSensors()[0]->GetObjectsCount(), 2);
  ASSERT_EQ(things[1]->GetSensors()[0]->GetObjectsCount(), 1);
  free(set);
}
