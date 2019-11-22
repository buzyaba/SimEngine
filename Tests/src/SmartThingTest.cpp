
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

TEST(SmartThingTest, CanCreate)
{

  //virtual std::vector<ISensor*> GetSensors() = 0;
  //virtual std::vector<IActuator*> GetActuators() = 0;

  //virtual void AddObject(TObjectOfObservation& object) = 0;
  //virtual void ExcludeObject(TObjectOfObservation& object) = 0;
  //virtual void ExcludeObject(std::string _name) = 0;
  EXPECT_EQ(4, 2 + 2);


};