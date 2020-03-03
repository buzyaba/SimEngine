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


// TEST(ActuatorTest, CanCreate)
// {
//   //virtual void AddObject(TObjectOfObservation * object) = 0;
//   //virtual void ExcludeObject(TObjectOfObservation * object) = 0;
//   //virtual void ExcludeObject(std::string objectName) = 0;

//   //virtual void ChangeActuatorProperty(IProperties & _property) = 0;
//   //virtual void ChangeProperty(IProperties & property, TObjectOfObservation & object) = 0;
//   //virtual void ChangeProperty(IProperties & property, std::string _objectName) = 0;
//   //virtual void SetDataPacket(TDataPacket & packet) = 0;

//   //std::string GetName()


//   //void SetName(std::string _name)
//   // EXPECT_EQ(4, 2 + 2);
// }