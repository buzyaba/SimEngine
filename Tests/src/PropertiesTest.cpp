
#include "gtest/gtest.h"
#include "BasicExamples/Properties.h"

TEST(PropertiesTest, Default_Constructor) {
    ASSERT_NO_THROW(TProperties prop);
};

TEST(PropertiesTest, Constructor_With_Right_Name) {
    ASSERT_EQ(TProperties("Position").GetName(), std::string("Position"));
}

TEST(PropertiesTest, Copy_Constructor) {
    TProperties pos("Pos");
    ASSERT_EQ(TProperties(pos).GetName(), std::string("Pos"));
}

TEST(PropertiesTest, Constructor_With_All_Parameters) {
    TProperties pos(std::map<std::string, double>({
        { "X", 1 }, { "Y", 1}, { "Z", 15 } }), false, "Pos");
    ASSERT_NEAR(pos.GetValue("Z"), 15, 0.001);
}

TEST(PropertiesTest, Can_Set_Map) {
    TProperties pos;
    pos.SetValues({ { "X", 1 }, { "Y", 1}, { "Z", 15 } });
    ASSERT_NEAR(pos.GetValue("X"), 1, 0.001);
}

TEST(PropertiesTest, Can_Set_Value) {
    TProperties pos(std::map<std::string, double>({
        { "X", 1 }, { "Y", 1}, { "Z", 15 } }), false, "Pos");
    pos.SetValue("Z", 22);
    ASSERT_NEAR(pos.GetValue("Z"), 22, 0.001);
}

TEST(PropertiesTest, Get_Property_What_Dont_Exist) {
    TProperties pos;
    ASSERT_ANY_THROW(pos.GetValue("G"));
}

TEST(PropertiesTest, Set_Property_What_Dont_Exist) {
    TProperties pos(std::map<std::string, double>({
        { "X", 1 }, { "Y", 1}, { "Z", 15 } }), false, "Pos");
    ASSERT_ANY_THROW(pos.SetValue("F", 200));
}

TEST(PropertiesTest, Can_Set_IsObserved) {
    TProperties pos;
    pos.SetIsObserved(true);
    ASSERT_EQ(pos.IsObserved(), true);
}

TEST(PropertiesTest, Can_Get_String_Value) {
    TProperties pos(std::map<std::string, double>({
        { "X", 1 }, { "Y", 1}, { "Z", 15 } }), false, "Pos");
    ASSERT_EQ("1.000000_1.000000_15.000000", pos.GetStringValue());
}

TEST(PropertiesTest, Can_Set_String_Value) {
    TProperties pos; 
    pos.SetStringValue("GoodString");
    ASSERT_EQ(pos.GetStringValue(), std::string("GoodString"));
}
