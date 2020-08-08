#pragma once

#include "BasicExamples/SmartThing.h"
#include "TestSwitch.h"
#include "TestElectricitySensor.h"

class TTestSmartSocket : public TSmartThing
{
public:
  TTestSmartSocket(std::string _name = "");
  void initBuffer() override {}
  unsigned int getMeshBuffer() override { return -1; };
#ifdef USE_OpenGL
  virtual void setScale(const glm::vec3& _size) override {}
  virtual void setPosition(const glm::vec3& pos) override {}
#endif
  void drawElements(const std::vector<TObject*>& objects) {}
  void initDraw(const std::vector<TObject*>& objects) {}
  virtual TSmartThing* Clone() { return new TTestSmartSocket(); };
  virtual std::string ClassName() override { return std::string("TTestSmartSocket"); }
};