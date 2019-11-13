#pragma once

#include "Core/Object.h"

class IObjectOfObservation : public IObject
{
protected:

public:
  virtual void AddParentObject(IObjectOfObservation& obect) = 0;
  virtual void AddChildObject(IObjectOfObservation& obect) = 0;
  virtual void AddNeighboringObject(IObjectOfObservation& obect) = 0;
  virtual void ExcludeChildObject(IObjectOfObservation& obect) = 0;
};