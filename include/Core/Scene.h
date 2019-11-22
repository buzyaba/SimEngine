#pragma once
#include "Core/ObjectOfObservation.h"
#include "Core/SmartThing.h"
/// Базовый элемент сцены
class TScene : public TObject
{
protected:
  /// Объекты размещенные на этом элементе сцены
  std::vector<TObjectOfObservation*> objectsOfObservation;
  /// Вещи размещенные на этом элементе сцены
  std::vector<TSmartThing*> smartThings;
  /// Другие элементы сцены размещенные в этом элементе
  std::vector<TScene*> scenes;
public:
  TScene(std::string _name);
  TScene(const TScene& _scene);
  virtual void AddObject(TObjectOfObservation& obect);
  virtual void AddThing(TSmartThing& obect);
  virtual void ExcludeObject(TObjectOfObservation& obect);
  virtual void AddSceneObject(TScene& obect);
  virtual void ExcludeSceneObject(TScene& obect);
};

