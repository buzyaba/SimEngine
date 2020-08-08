#include "BasicExamples/SmartHouse/Terminal.h"

TTerminal::TTerminal(std::string _name) : TObjectOfObservation(_name) {
    properties.insert({std::string("IsWork"), new TProperties(std::map<std::string, double>{{"IsWork", 0}}, false, "IsWork")});
    properties.insert({std::string("PowerConsumption"), new TProperties(std::map<std::string, double>{
        {"PowerConsumption", 0}}, true, "PowerConsumption")});
    properties.insert({std::string("Coordinate"), new TProperties(std::map<std::string, double>{
        {"X", 0 }, {"Y", 0 }, {"Z", 0 } }, false, "Coordinate")});
    properties.insert({std::string("Rotate"), new TProperties(std::map<std::string, double>{
        {"Yaw", 0 }, {"Pitch", 0 }, {"Roll", 0 } }, false, "Rotate")});
    isWork = false;
}
   
void TTerminal::Update() {
    TObjectOfObservation::Update();

    if (!isWork && this->properties["IsWork"]->GetValues()["IsWork"] == 1)
      this->properties["PowerConsumption"]->SetValues({{ "PowerConsumption", 100 }});

    if (this->properties["IsWork"]->GetValues()["IsWork"] != 0)
    {
      std::map<std::string, double>& tmp = this->properties["PowerConsumption"]->GetValues();
    //   tmp["PowerConsumption"] += (double(rand()) / RAND_MAX) * (tmp["PowerConsumption"] * 0.05) - tmp["PowerConsumption"] * 0.025;
      tmp["PowerConsumption"] = 0.00134;
      if (tmp["PowerConsumption"] <= 0)
        this->properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0 }});
    }
    else
      this->properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0 }});

    if (this->properties["PowerConsumption"]->GetValues()["PowerConsumption"] <= 0)
    {
      this->properties["IsWork"]->SetValues({{"IsWork", 0}});
      this->properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0 }});
    }

    isWork = this->properties["IsWork"]->GetValues()["IsWork"] == 1;
    /// ���������� ��������
}
