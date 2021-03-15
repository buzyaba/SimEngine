#include "gtest/gtest.h"
#include "SimEngine/ObjectOfObservation.h"

TEST(ObjectOfObservationTest, Can_Create_Default_Instance) {
    ASSERT_NO_THROW(TObjectOfObservation("ourBestObjectOfObservation"));
};

TEST(ObjectOfObservationTest, Can_Create_With_All_Objects) {
    TObjectOfObservation parent("parent");
    TObjectOfObservation child("child");
    TObjectOfObservation neighbour1("neighbour1");
    TObjectOfObservation neighbour2("neighbour2");
    ASSERT_NO_THROW(TObjectOfObservation("ourBestObjectOfObservation",
                                         { &neighbour1, &neighbour2 },
                                         &parent,
                                         &child));
};

TEST(ObjectOfObservationTest, Can_Copy_Instance) {
    TObjectOfObservation objOfObservation("ourBestObjectOfObservation");
    TObjectOfObservation copyObjOfObservation(objOfObservation);
    ASSERT_EQ(copyObjOfObservation.GetName(), "ourBestObjectOfObservation");
};

TEST(ObjectOfObservationTest, Add_Parent_Object) {
    TObjectOfObservation* parent = new TObjectOfObservation("Parent");
    TObjectOfObservation* child = new TObjectOfObservation("Child");

    child->AddParentObject(parent);

    ASSERT_EQ(child->GetParentObject()->GetName(), "Parent");

    free(parent);
    free(child);
};

TEST(ObjectOfObservationTest, Add_Child_Objects) {
    TObjectOfObservation* parent = new TObjectOfObservation("Parent");
    TObjectOfObservation* child1 = new TObjectOfObservation("Child1");
    TObjectOfObservation* child2 = new TObjectOfObservation("Child2");

    parent->AddChildObject(child1);
    parent->AddChildObject(child2);

    ASSERT_EQ(parent->GetChildObjects().size(), 2);

    free(parent);
    free(child1);
    free(child2);
};

TEST(ObjectOfObservationTest, Add_Neighbour_Objects) {
    TObjectOfObservation* obj = new TObjectOfObservation("Object");
    TObjectOfObservation* neighbouring1 = new TObjectOfObservation("Neighbouring1");
    TObjectOfObservation* neighbouring2 = new TObjectOfObservation("Neighbouring2");

    obj->AddNeighboringObject(neighbouring1);
    obj->AddNeighboringObject(neighbouring2);

    ASSERT_EQ(obj->GetNeighboringObjects().size(), 2);

    free(obj);
    free(neighbouring1);
    free(neighbouring2);
};

TEST(ObjectOfObservationTest, Exclude_Child_Object) {
    TObjectOfObservation* parent = new TObjectOfObservation("Parent");
    TObjectOfObservation* child1 = new TObjectOfObservation("Child1");
    TObjectOfObservation* child2 = new TObjectOfObservation("Child2");

    parent->AddChildObject(child1);
    parent->AddChildObject(child2);

    parent->ExcludeChildObject(child2);

    ASSERT_EQ(parent->GetChildObjects().size(), 1);

    free(parent);
    free(child1);
    free(child2);
};

TEST(ObjectOfObservationTest, Get_Neighbour_Object_By_Name) {
    TObjectOfObservation* obj = new TObjectOfObservation("Object");
    TObjectOfObservation* neighbouring1 = new TObjectOfObservation("Neighbouring1");
    TObjectOfObservation* neighbouring2 = new TObjectOfObservation("Neighbouring2");

    obj->AddNeighboringObject(neighbouring1);
    obj->AddNeighboringObject(neighbouring2);

    TObjectOfObservation* tmp = obj->GetNeighboringObject("Neighbouring2");

    ASSERT_EQ(tmp->GetName(), "Neighbouring2");

    free(obj);
    free(neighbouring1);
    free(neighbouring2);
};

TEST(ObjectOfObservationTest, Get_Child_Object_By_Name) {
    TObjectOfObservation* parent = new TObjectOfObservation("Parent");
    TObjectOfObservation* child1 = new TObjectOfObservation("Child1");
    TObjectOfObservation* child2 = new TObjectOfObservation("Child2");

    parent->AddChildObject(child1);
    parent->AddChildObject(child2);

    TObjectOfObservation* tmp = parent->GetChildObject("Child1");

    ASSERT_EQ(tmp->GetName(), "Child1");

    free(parent);
    free(child1);
    free(child2);
};

TEST(ObjectOfObservationTest, Throw_If_Get_Invalid_Child_Name) {
    TObjectOfObservation* parent = new TObjectOfObservation("Parent");
    TObjectOfObservation* child1 = new TObjectOfObservation("Child1");
    TObjectOfObservation* child2 = new TObjectOfObservation("Child2");

    parent->AddChildObject(child1);
    parent->AddChildObject(child2);
    ASSERT_ANY_THROW(parent->GetChildObject("child"));

    free(parent);
    free(child1);
    free(child2);
};

TEST(ObjectOfObservationTest, Throw_If_Get_Invalid_Neighbour_Name) {
    TObjectOfObservation* obj = new TObjectOfObservation("Object");
    TObjectOfObservation* neighbouring1 = new TObjectOfObservation("Neighbouring1");
    TObjectOfObservation* neighbouring2 = new TObjectOfObservation("Neighbouring2");

    obj->AddNeighboringObject(neighbouring1);
    obj->AddNeighboringObject(neighbouring2);

    ASSERT_ANY_THROW(obj->GetNeighboringObject("neighbour"));

    free(obj);
    free(neighbouring1);
    free(neighbouring2);
};
