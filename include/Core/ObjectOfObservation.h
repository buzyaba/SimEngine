#pragma once

#include "Core/Object.h"


/// Базовая реализация для наблюдаемых объектов
class TObjectOfObservation : public TObject
{
protected:

  /// предок данного объекта
  TObjectOfObservation* parentObject;
  /// Потомки данного объекта, если потомков несколько, тоНужно оставить только одного
  std::vector<TObjectOfObservation*> childObjects;
  /// Соседние потомки
  std::vector<TObjectOfObservation*> neighboringObject;
  /// Все свойства объекта начиная с себя самого
  std::vector<IProperties*> allProperties;
  
public:
  TObjectOfObservation(std::string _name, std::vector<TObjectOfObservation*> _neighboringObject = {nullptr},
    TObjectOfObservation* _parentObject = nullptr, TObjectOfObservation* _childObject = nullptr);
  TObjectOfObservation(const TObjectOfObservation& obj);

  /// Добавить объект который является хранилищем текущего объекта
  virtual void AddParentObject(TObjectOfObservation& obect);
  /// Добавить дочерний объект
  virtual int AddChildObject(TObjectOfObservation& obect);
  /// Возвращает вектор дочерних объектов, должен остаться только один потомок
  virtual std::vector<TObjectOfObservation*> GetChildObject();
  /// Добавить соседний объект, между ними может происходить объмен дочерними объектами
  virtual void AddNeighboringObject(TObjectOfObservation& obect);
  /// Исключить дочерний объект
  virtual void ExcludeChildObject(TObjectOfObservation& obect);
  /// Обновляет свойства данного объекта 
  virtual void Update();
  /// Возвращает все свойства объекта
  virtual std::vector<IProperties*>& GetProperties();

  /// Создание клона объекта
  virtual TObjectOfObservation* Clone();
};