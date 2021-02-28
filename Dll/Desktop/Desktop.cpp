#include "Desktop.hpp"

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

  int newIsWork = static_cast<int>(properties["IsWork"]->GetValues()["IsWork"]);

  switch(newIsWork) {
    case 0:
      isWork = newIsWork;
      properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0.0}}); // sleep
      textures[0][2] = "monitorOFF.png";
      break;
    case 1:
      isWork = newIsWork;
      properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0.00217}}); // full
      textures[0][2] = "monitorON.png";
      break;
  }
}

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TDesktop("TDesktop");
}
