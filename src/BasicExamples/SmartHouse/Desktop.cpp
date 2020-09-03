#include "BasicExamples/SmartHouse/Desktop.hpp"

TDesktop::TDesktop(std::string _name) : TObjectOfObservation(_name) {
  properties.insert(
      {"IsWork", new TProperties({{"IsWork", 0}}, false, "IsWork")});
  properties.insert(
      {"PowerConsumption",
       new TProperties({{"PowerConsumption", 0}}, true, "PowerConsumption")});
  properties.insert(
      {"Scale", new TProperties({{"Width", 3}, {"Length", 3}, {"Height", 3}},
                                false, "Scale")});
  properties.insert(
      {"Coordinate",
       new TProperties({{"X", 0}, {"Y", 0}, {"Z", 0}}, false, "Coordinate")});
  properties.insert(
      {"Rotate",
       new TProperties({{"X", 0.0}, {"Y", 0.0}, {"Z", 0.0}},
                       false, "Rotate")});
  isWork = false;
}

void TDesktop::Update() {
  TObjectOfObservation::Update();

  if (!isWork && this->properties["IsWork"]->GetValues()["IsWork"] == 1)
    this->properties["PowerConsumption"]->SetValues(
        {{"PowerConsumption", 100}});

  if (this->properties["IsWork"]->GetValues()["IsWork"] != 0) {
    std::map<std::string, double> &tmp =
        this->properties["PowerConsumption"]->GetValues();
    //   tmp["PowerConsumption"] += (double(rand()) / RAND_MAX) *
    //   (tmp["PowerConsumption"] * 0.05) - tmp["PowerConsumption"] * 0.025;
    tmp["PowerConsumption"] = 0.00217;
    if (tmp["PowerConsumption"] <= 0)
      this->properties["PowerConsumption"]->SetValues(
          {{"PowerConsumption", 0}});
  } else
    this->properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0}});

  if (this->properties["PowerConsumption"]->GetValues()["PowerConsumption"] <=
      0) {
    this->properties["IsWork"]->SetValues({{"IsWork", 0}});
    this->properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0}});
  }

  isWork = this->properties["IsWork"]->GetValues()["IsWork"] == 1;
  /// ���������� ��������
}
