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
    ASSERT_NO_THROW(copyObjOfObservation.GetName(), "ourBestObjectOfObservation");
};

