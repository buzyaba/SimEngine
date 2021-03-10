#include "gtest/gtest.h"
#include "SimEngine/Object.h"

TEST(ObjectTest, Can_Create_Instance) {
    ASSERT_NO_THROW(TObject("ourBestObject"));
};

TEST(ObjectTest, Get_Object_Name) {
    TObject obj("ourBestObject");
    ASSERT_EQ(obj.GetName(), "ourBestObject");
}

TEST(ObjectTest, Set_Object_Name) {
    TObject obj("ourBestObject");
    obj.SetName("AwesomeObject");
    ASSERT_EQ(obj.GetName(), "AwesomeObject");
}

TEST(ObjectTest, Get_Class_Name) {
    TObject obj("ourBestObject");
    ASSERT_EQ(obj.ClassName(), "TObject");
}

TEST(ObjectTest, Add_Property) {
    TObject obj("ourBestObject");
    auto property =
        TProperties(std::map<std::string, double>{ { "Property", 50 } }, true, "Property");
    obj.AddProperty(property);
    double val = obj.GetProperty("Property").GetValue("Property");
    ASSERT_DOUBLE_EQ(50, val);
}

TEST(ObjectTest, Set_Property_By_Reference) {
    TObject obj("ourBestObject");
    auto property =
        TProperties(std::map<std::string, double>{ { "Property", 50 } }, true, "Property");
    obj.AddProperty(property);

    auto new_property =
        TProperties(std::map<std::string, double>{ { "Property", 100 } }, true, "Property");

    obj.SetProperty(new_property);

    double val = obj.GetProperty("Property").GetValue("Property");
    ASSERT_DOUBLE_EQ(100, val);
}

TEST(ObjectTest, Set_Property_By_Name) {
    TObject obj("ourBestObject");
    auto property =
        TProperties(std::map<std::string, double>{ { "Property", 50 } }, true, "Property");
    obj.AddProperty(property);

    auto new_property =
        TProperties(std::map<std::string, double>{ { "Property", 100 } }, true, "Property");

    obj.SetProperty(std::map<std::string, double>{ { "Property", 100 }}, "Property");

    double val = obj.GetProperty("Property").GetValue("Property");
    ASSERT_DOUBLE_EQ(100, val);
}

TEST(ObjectTest, Get_All_Properties) {
    TObject obj("ourBestObject");
    auto property1 =
        TProperties(std::map<std::string, double>{ { "Property1", 50 } }, true, "Property1");
    obj.AddProperty(property1);

    auto property2 =
        TProperties(std::map<std::string, double>{ { "Property2", 100 } }, true, "Property2");
    obj.AddProperty(property2);

    auto property3 =
        TProperties(std::map<std::string, double>{ { "Property3", 100 } }, true, "Property3");
    obj.AddProperty(property3);

    ASSERT_DOUBLE_EQ(obj.GetProperties().size(), 3);
}
