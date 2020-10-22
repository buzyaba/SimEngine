#pragma once

#include <string>
#include <vector>

#include "SimEngine/DataPacket.h"
#include "SimEngine/ObjectOfObservation.h"

/// Интерфейс сенсор который может наблюдать за объектами
class ISensor
{
public:
  virtual TDataPacket& GetDataPacket() = 0;
  virtual void AddObject(TObjectOfObservation& object) = 0;
  virtual void ExcludeObject(TObjectOfObservation& object) = 0;
  virtual void ExcludeObject(std::string objectName) = 0;
  virtual size_t getObjectsCount() = 0;
  virtual std::string GetName() = 0;
  virtual void SetName(std::string _name) = 0;
  virtual int getPropertyCount() = 0;
};

class TSensor : public ISensor
{
protected:
  /// Имя сенсора
  std::string name;
  /// наблюдаемые объекты
  std::vector<TObjectOfObservation*> objects;
  /// Последнее количество объектов наблюдения
  size_t oldObjectCount;
  /// Свойства всех наблюдаемых объектов
  std::vector<std::map<std::string, IProperties*>> objectsProperties;
  /// используемый пакет
  TDataPacket* packet;
  /// Свойства объектов
  std::vector<std::vector<std::vector<double>*>> vals;
  /// Количество свойств
  int propertyCount;
public:
  TSensor(std::string _name);
  TSensor(const TSensor& sensor);

  virtual TDataPacket& GetDataPacket();
  virtual void AddObject(TObjectOfObservation& object);
  virtual void ExcludeObject(TObjectOfObservation& object);
  virtual void ExcludeObject(std::string objectName);
  virtual std::string GetName();
  virtual void SetName(std::string _name);
  virtual size_t getObjectsCount() { return oldObjectCount; }
  virtual int getPropertyCount() { return propertyCount; }
};

