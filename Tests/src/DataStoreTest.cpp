
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

TEST(DataStoreTest, CanCreate)
{
  //TDataStore()
  //{};
  //virtual void AddPropertyForObject(const IProperties& property, unsigned long time) = 0;
  //virtual std::vector<IProperties*> GddPropertyForObject(unsigned long time) = 0;
  EXPECT_EQ(4, 2 + 2);
};