#pragma once

#include <string>
#include <vector>

#include "Core/DataPacket.h"
#include "Core/Properties.h"
#include "Core/ObjectOfObservation.h"

/// Базовый интерфейс актуатора
class IActuator
{
public:

  virtual void AddObject(TObjectOfObservation& object) = 0;
  virtual void ExcludeObject(TObjectOfObservation& object) = 0;
  virtual void ExcludeObject(std::string objectName) = 0;

  virtual void ChangeActuatorProperty(IProperties& _property) = 0;
  virtual void ChangeProperty(IProperties& property, TObjectOfObservation& object) = 0;
  virtual void ChangeProperty(IProperties& property, std::string _objectName) = 0;
  virtual void SetDataPacket(TDataPacket& packet) = 0;

  virtual std::string GetName() = 0;
  virtual void SetName(std::string _name) = 0;
};

/// Базовый актуатор
class TActuator : public IActuator
{
protected:
  /// Имя
  std::string name;
  /// Набор объектов на которые может быть оказано воздействие
  std::vector<TObjectOfObservation*> objects;
  /// Набор свойств объектов
  IProperties* property;
  /// Используемый пакет
  TDataPacket* packet;
public:
  TActuator(std::string _name);
  TActuator(const TActuator& actuator);

  virtual void AddObject(TObjectOfObservation& object);
  virtual void ExcludeObject(TObjectOfObservation& object);
  virtual void ExcludeObject(std::string objectName);

  virtual void ChangeActuatorProperty(IProperties& _property);
  virtual void ChangeProperty(IProperties& property, TObjectOfObservation& object);
  virtual void ChangeProperty(IProperties& property, std::string _objectName);
  virtual void SetDataPacket(TDataPacket& packet);
  
  virtual std::string GetName();
  virtual void SetName(std::string _name);
};

