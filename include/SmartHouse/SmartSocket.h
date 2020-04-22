#pragma once

#include "Core/SmartThing.h"
#include "SmartHouse/Switch.h"
#include "SmartHouse/ElectricitySensor.h"

class TSmartSocket : public TSmartThing
{
public:
  TSmartSocket(std::string _name) :
    TSmartThing(_name, { new TElectricitySensor(_name + "ElectricitySensor") }, { new TSwitch(_name + "Switch") }) {}
  void initBuffer() override {}
  unsigned int getMeshBuffer() override { return -1; };
  virtual void setScale(const glm::vec3& _size) override {}
  virtual void setPosition(const glm::vec3& pos) override {}
  void drawElements(const std::vector<TObject*>& objects) {}
  void initDraw(const std::vector<TObject*>& objects) {}
  virtual TSmartThing* Clone() { return new TSmartSocket(*this); };
};