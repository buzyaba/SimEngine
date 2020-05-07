#pragma once

#include "Core/ObjectOfObservation.h"

class TCoordinateObject : public TObjectOfObservation
{
protected:

public:

  TCoordinateObject(std::string _name) : TObjectOfObservation(_name)
  {
    this->name = "CoordinateObject";
    properties.resize(1, nullptr);
    properties[0] = new TProperties({ 0, 0 }, { "x", "y" }, "coordinate");
  }

};