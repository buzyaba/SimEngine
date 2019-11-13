#pragma once
#include "Core/ObjectOfObservation.h"
#include "Core/SmartThing.h"
class IScene
{
protected:
public:
  virtual void AddObject(IObjectOfObservation& obect) = 0;
  virtual void AddThing(ISmartThing& obect) = 0;
  virtual void ExcludeObject(IObjectOfObservation& obect) = 0;
  virtual void AddSceneObject(IObjectOfObservation& obect) = 0;
  virtual void ExcludeSceneObject(IScene& obect) = 0;
};