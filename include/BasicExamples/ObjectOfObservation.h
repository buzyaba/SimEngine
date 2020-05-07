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
  virtual std::vector<IProperties*>& GetAllProperties(); //maybe something wrong??? 
  /// Создание клона объекта
  virtual TObjectOfObservation* Clone() = 0;
};

///Тип функции-фабрики, которая экспортируется подключаемой библиотекой с объектами
typedef std::vector <TObjectOfObservation*> CreateObjectOfObservation();
///Тип функции-деструктора, которая экспортируется подключаемой библиотекой с объектами
typedef void DestroyObjectOfObservation(std::vector <TObjectOfObservation*>);

///Префикс для фуккций, экспортируемых подключаемой библиотекой
#ifdef WIN32
#define LIB_EXPORT_API __declspec(dllexport)
#else
#define LIB_EXPORT_API
#endif