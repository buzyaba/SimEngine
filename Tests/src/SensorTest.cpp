#include "gtest/gtest.h"

#include "SimEngine/Sensor.h"

TEST(SensorTest, Can_Create_Instance) {
    ASSERT_NO_THROW(TSensor("name"));
}

TEST(SensorTest, Can_Copy_Instance) {
    TSensor sensor("ourBestSensor");
    TSensor copySensor(sensor);
    ASSERT_EQ(copySensor.GetName(), "ourBestSensor");
};

TEST(SensorTest, Get_Name) {
    TSensor sensor("Sensor");

    ASSERT_EQ(sensor.GetName(), "Sensor");
};

TEST(SensorTest, Set_Name) {
    TSensor sensor("Sensor");
    sensor.SetName("NewSensor");

    ASSERT_EQ(sensor.GetName(), "NewSensor");
};

TEST(SensorTest, Add_Objects) {
    TSensor* sensor = new TSensor("Sensor");
    TObjectOfObservation* obj1 = new TObjectOfObservation("Object1");
    TObjectOfObservation* obj2 = new TObjectOfObservation("Object2");

    sensor->AddObject(obj1);
    sensor->AddObject(obj2);

    ASSERT_EQ(sensor->GetObjectsCount(), 2);

    free(sensor);
    free(obj1);
    free(obj2);
};

TEST(SensorTest, Exclude_Object_By_Name) {
    TSensor* sensor = new TSensor("Sensor");
    TObjectOfObservation* obj1 = new TObjectOfObservation("Object1");
    TObjectOfObservation* obj2 = new TObjectOfObservation("Object2");

    sensor->AddObject(obj1);
    sensor->AddObject(obj2);
    sensor->ExcludeObject("Object2");

    ASSERT_EQ(sensor->GetObjectsCount(), 1);

    free(sensor);
    free(obj1);
    free(obj2);
};

TEST(SensorTest, Exclude_Object_By_Pointer) {
    TSensor* sensor = new TSensor("Sensor");
    TObjectOfObservation* obj1 = new TObjectOfObservation("Object1");
    TObjectOfObservation* obj2 = new TObjectOfObservation("Object2");

    sensor->AddObject(obj1);
    sensor->AddObject(obj2);
    sensor->ExcludeObject(obj1);

    ASSERT_EQ(sensor->GetObjectsCount(), 1);

    free(sensor);
    free(obj1);
    free(obj2);
};

TEST(SensorTest, Get_Property_Count) {
    TSensor* sensor = new TSensor("Sensor");
    TObjectOfObservation* obj1 = new TObjectOfObservation("Object1");
    auto property1 = TProperties(std::map<std::string, double>{{"Property1", 50}}, true, "Property1");
    obj1->AddProperty(property1);
    auto property2 = TProperties(std::map<std::string, double>{{"Property2", 100}}, true, "Property2");
    obj1->AddProperty(property2);
    TObjectOfObservation* obj2 = new TObjectOfObservation("Object2");
    auto property3 = TProperties(std::map<std::string, double>{{"Property3", 150}}, true, "Property3");
    obj2->AddProperty(property3);

    sensor->AddObject(obj1);
    sensor->AddObject(obj2);

    ASSERT_EQ(sensor->GetPropertyCount(), 3);

    free(sensor);
    free(obj1);
    free(obj2);
};

TEST(SensorTest, Get_Data_Packet) {
    TSensor* sensor = new TSensor("Sensor");
    TObjectOfObservation* obj1 = new TObjectOfObservation("Object1");
    auto property1 = TProperties(std::map<std::string, double>{{"Property1", 50}}, true, "Property1");
    obj1->AddProperty(property1);
    auto property2 = TProperties(std::map<std::string, double>{{"Property2", 100}}, true, "Property2");
    obj1->AddProperty(property2);
    TObjectOfObservation* obj2 = new TObjectOfObservation("Object2");
    auto property3 = TProperties(std::map<std::string, double>{{"Property3", 150}}, true, "Property3");
    obj2->AddProperty(property3);

    sensor->AddObject(obj1);
    sensor->AddObject(obj2);
    auto packet = sensor->GetDataPacket()->GetData<double>();

    double ref[3] = { 50, 100, 150 };

    for (size_t i = 0; i < 3; i++) {
        ASSERT_EQ(ref[i], packet[i]);
    }

    free(sensor);
    free(obj1);
    free(obj2);
};