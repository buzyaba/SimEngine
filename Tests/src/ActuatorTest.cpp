#include "gtest/gtest.h"
#include "BasicExamples/Actuator.h"
#include "SmartHouse/Terminal.h"
#include "BasicExamples/Properties.h"

TEST(ActuatorTest, Can_Create_Cnstance) {
    ASSERT_NO_THROW(TActuator("name"));
}

TEST(ActuatorTest, Add_Object_And_Change_Property) {
    TActuator actuator("name");
    TTerminal* terminal = new TTerminal("Terminal");

    auto property = TProperties(std::map<std::string, double>{{"PowerConsumption", 100}}, true, "PowerConsumption");

    actuator.AddObject(*terminal);
    actuator.ChangeProperty(property, "Terminal");

    auto real = terminal->GetProperty("PowerConsumption").GetValue("PowerConsumption");

    delete terminal;
    ASSERT_DOUBLE_EQ(100, real);
}

TEST(ActuatorTest, Change_Property_By_Reference) {
    TActuator actuator("name");
    TTerminal* terminal = new TTerminal("Terminal");

    auto property = TProperties(std::map<std::string, double>{{"PowerConsumption", 100}}, true, "PowerConsumption");

    actuator.AddObject(*terminal);
    actuator.ChangeProperty(property, *terminal);

    auto real = terminal->GetProperty("PowerConsumption").GetValue("PowerConsumption");

    delete terminal;
    ASSERT_DOUBLE_EQ(100, real);
}

TEST(ActuatorTest, Exclude_Object_By_Reference) {
    TActuator actuator("name");
    TTerminal* terminal = new TTerminal("Terminal");

    actuator.AddObject(*terminal);
    actuator.ExcludeObject(*terminal);

    auto property = TProperties(std::map<std::string, double>{{"PowerConsumption", 100}}, true, "PowerConsumption");
    actuator.ChangeProperty(property, *terminal);

    auto real = terminal->GetProperty("PowerConsumption").GetValue("PowerConsumption");

    delete terminal;
    ASSERT_NE(100, real);
}

TEST(ActuatorTest, Exclude_Object_By_Name) {
    TActuator actuator("name");
    TTerminal* terminal = new TTerminal("Terminal");

    actuator.AddObject(*terminal);
    actuator.ExcludeObject("Terminal");

    auto property = TProperties(std::map<std::string, double>{{"PowerConsumption", 100}}, true, "PowerConsumption");
    actuator.ChangeProperty(property, "Terminal");

    auto real = terminal->GetProperty("PowerConsumption").GetValue("PowerConsumption");

    delete terminal;
    ASSERT_NE(100, real);
}

TEST(ActuatorTest, Copying_Constructor) {
    TActuator actuator1("a1");
    
    TTerminal* terminal = new TTerminal("Terminal");
    actuator1.AddObject(*terminal);

    TActuator actuator2(actuator1);

    auto property = TProperties(std::map<std::string, double>{{"PowerConsumption", 100}}, true, "PowerConsumption");
    actuator2.ChangeProperty(property, "Terminal");

    auto real = terminal->GetProperty("PowerConsumption").GetValue("PowerConsumption");

    delete terminal;
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
