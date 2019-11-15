
#include "gtest/gtest.h"
#include "Core/Object.h"
#include "Core/Scene.h"
#include "Core/ObjectOfObservation.h"
#include "Core/Sensor.h"
#include "Core/Properties.h"
#include "Core/Actuator.h"
#include "Core/SmartThing.h"
#include "Core/DataStore.h"
#include "Core/WorkManager.h"
#include "Core/DataPacket.h"
#include "Core/ManagementProgram.h"
#include "Core/EnvironmentScript.h"

TEST(ObjectOfObservationTest, CanCreate)
{
  //virtual void AddParentObject(IObjectOfObservation& obect) = 0;
  //virtual void AddChildObject(IObjectOfObservation& obect) = 0;
  //virtual void AddNeighboringObject(IObjectOfObservation& obect) = 0;
  //virtual void ExcludeChildObject(IObjectOfObservation& obect) = 0;
  EXPECT_EQ(4, 2 + 2);
};