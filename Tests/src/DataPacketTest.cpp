
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

TEST(DataPacketTest, CanCreate)
{
  //TDataPacket(int* data, int size = 1);
  //TDataPacket(double* data, int size = 1);
  //TDataPacket(char* data, int size = 1);
  //TDataPacket(const TDataPacket& packet);
  //~TDataPacket();

  //virtual char* GetData();
  //virtual int GetSize();
  //virtual void Setdata(char*);
  //virtual void SetSize(int);
  //virtual int* GetInts();
  //virtual double* GetDoubles();
  EXPECT_EQ(4, 2 + 2);
};