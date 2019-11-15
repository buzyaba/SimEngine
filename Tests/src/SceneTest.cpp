
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

TEST(SceneTest, CanCreate)
{
  //virtual void AddObject(IObjectOfObservation& obect) = 0;
  //virtual void AddThing(ISmartThing& obect) = 0;
  //virtual void ExcludeObject(IObjectOfObservation& obect) = 0;
  //virtual void AddSceneObject(IObjectOfObservation& obect) = 0;
  //virtual void ExcludeSceneObject(IScene& obect) = 0;
  EXPECT_EQ(4, 2 + 2);
};