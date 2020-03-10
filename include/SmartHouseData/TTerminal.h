#pragma once

#include "Core/ObjectOfObservation.h"
#include "SmartHouse/GTerminal.hpp"

class TTerminal : public TObjectOfObservation
{
protected:
  ///Был лши включен терминал
  bool isWork;
public:
  TTerminal(std::string _name) : TObjectOfObservation(_name)
  {
    this->properties.resize(3);
    this->properties[0] = new TProperties({ 0 }, { "IsWork" }, false, "IsWork");
    this->properties[1] = new TProperties({ 0 }, { "PowerConsumption" }, true, "PowerConsumption");
    this->properties[2] = new TProperties({ 10, 10 }, { "X", "Y" }, false, "Coordinate");
    isWork = false;
    GObject = new GTerminal(glm::vec3(0.0f, 3.1f, 0.0f));
  }

  virtual void Update()
  {
    TObjectOfObservation::Update();

    if (!isWork && this->properties[0]->GetValues()[0] == 1)
      this->properties[1]->SetValues({ 100 });

    if (this->properties[0]->GetValues()[0] != 0)
    {
      std::vector<double>& tmp = this->properties[1]->GetValues();
      tmp[0] += (double(rand()) / RAND_MAX) * (tmp[0] * 0.05) - tmp[0] * 0.025;
      if (tmp[0] <= 0)
        this->properties[0]->SetValues({ 0 });
    }
    else
      this->properties[1]->SetValues({ 0 });

    if (this->properties[1]->GetValues()[0] <= 0)
    {
      this->properties[0]->SetValues({ 0 });
      this->properties[1]->SetValues({ 0 });
    }

    isWork = this->properties[0]->GetValues()[0] == 1;
  }

};
