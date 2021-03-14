#include "gtest/gtest.h"

#include "SimEngine/Actuator.h"
#include "SimEngine/Object.h"
#include "SimEngine/Properties.h"

TEST(ActuatorTest, Can_Create_Instance) {
    ASSERT_NO_THROW(TActuator("name"));
}

TEST(ActuatorTest, Add_Object_And_Change_Property) {
    TActuator actuator("name");
    TObjectOfObservation* object = new TObjectOfObservation("Object");
    auto property = TProperties(std::map<std::string, double>{{"Property", 50}}, true, "Property");
    object->AddProperty(property);

    auto new_property = TProperties(std::map<std::string, double>{{"Property", 100}}, true, "Property");

    actuator.AddObject(object);
    actuator.ChangeProperty(new_property, "Object");

    double real = object->GetProperty("Property").GetValue("Property");

    delete object;
    ASSERT_DOUBLE_EQ(100, real);
}

TEST(ActuatorTest, Change_Property_By_Reference) {
    TActuator actuator("name");
    TObjectOfObservation* object = new TObjectOfObservation("Object");
    auto property = TProperties(std::map<std::string, double>{{"Property", 50}}, true, "Property");
    object->AddProperty(property);

    auto new_property = TProperties(std::map<std::string, double>{{"Property", 100}}, true, "Property");

    actuator.AddObject(object);
    actuator.ChangeProperty(new_property, object);

    double real = object->GetProperty("Property").GetValue("Property");

    delete object;
    ASSERT_DOUBLE_EQ(100, real);
}

TEST(ActuatorTest, Exclude_Object_By_Reference) {
    TActuator actuator("name");
    TObjectOfObservation* object = new TObjectOfObservation("Object");
    auto property = TProperties(std::map<std::string, double>{{"Property", 50}}, true, "Property");
    object->AddProperty(property);

    actuator.AddObject(object);
    actuator.ExcludeObject(object);

    auto new_property = TProperties(std::map<std::string, double>{{"Property", 100}}, true, "Property");
    actuator.ChangeProperty(new_property, object);

    auto real = object->GetProperty("Property").GetValue("Property");

    delete object;
    ASSERT_NE(100, real);
}

TEST(ActuatorTest, Exclude_Object_By_Name) {
    TActuator actuator("name");
    TObjectOfObservation* object = new TObjectOfObservation("Object");
    auto property = TProperties(std::map<std::string, double>{{"Property", 50}}, true, "Property");
    object->AddProperty(property);


    actuator.AddObject(object);
    actuator.ExcludeObject("Object");

    auto new_property = TProperties(std::map<std::string, double>{{"Property", 100}}, true, "Property");
    actuator.ChangeProperty(new_property, "Object");

    auto real = object->GetProperty("Property").GetValue("Property");

    delete object;
    ASSERT_NE(100, real);
}

TEST(ActuatorTest, Copying_Constructor) {
    TActuator actuator1("a1");
    
    TObjectOfObservation* object = new TObjectOfObservation("Object");
    auto property = TProperties(std::map<std::string, double>{{"Property", 50}}, true, "Property");
    object->AddProperty(property);

    actuator1.AddObject(object);

    TActuator actuator2(actuator1);

    auto new_property = TProperties(std::map<std::string, double>{{"Property", 100}}, true, "Property");
    actuator2.ChangeProperty(new_property, "Object");

    auto real = object->GetProperty("Property").GetValue("Property");

    delete object;
    ASSERT_EQ(100, real);
}

TEST(ActuatorTest, Get_Actuator_Name) {
    TActuator actuator("sample text");

    ASSERT_EQ("sample text", actuator.GetName());
}

TEST(ActuatorTest, Set_Actuator_Name) {
    TActuator actuator("sample text");

    actuator.SetName("new text");

    ASSERT_EQ("new text", actuator.GetName());
}
