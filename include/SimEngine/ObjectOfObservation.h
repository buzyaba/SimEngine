#pragma once

#include "SimEngine/Object.h"

/// Базовая реализация для наблюдаемых объектов
class TObjectOfObservation : public TObject {
protected:
    /// предок данного объекта
    TObjectOfObservation* parentObject;
    /// Потомки данного объекта, если потомков несколько, тоНужно оставить только одного
    std::vector<TObjectOfObservation*> childObjects;
    /// Соседние потомки
    std::vector<TObjectOfObservation*> neighboringObjects;
    /// Все свойства объекта начиная с себя самого
    std::vector<IProperties*> allProperties;

public:
    TObjectOfObservation(std::string _name,
                         std::vector<TObjectOfObservation*> _neighboringObject = { nullptr },
                         TObjectOfObservation* _parentObject = nullptr,
                         TObjectOfObservation* _childObject = nullptr);
    TObjectOfObservation(const TObjectOfObservation& obj);

    /// Добавить объект который является хранилищем текущего объекта
    virtual void AddParentObject(TObjectOfObservation* object);
    /// Добавить дочерний объект
    virtual int AddChildObject(TObjectOfObservation* object);
    /// Возвращает вектор дочерних объектов
    virtual std::vector<TObjectOfObservation*> GetChildObjects();
    virtual TObjectOfObservation* GetChildObjects(std::string name);
    virtual std::vector<TObjectOfObservation*> GetNeighboringObjects();
    virtual TObjectOfObservation* GetNeighboringObject(std::string name);
    virtual TObjectOfObservation* GetParentObject();
    /// Добавить соседний объект, между ними может происходить объмен дочерними объектами
    virtual void AddNeighboringObject(TObjectOfObservation* object);
    /// Исключить дочерний объект
    virtual void ExcludeChildObject(TObjectOfObservation* object);
    /// Обновляет свойства данного объекта
    virtual void Update();
    /// Возвращает все свойства объекта
    virtual std::vector<IProperties*>& GetAllProperties(); //maybe something wrong???
    /// Создание клона объекта
    virtual TObjectOfObservation* Clone() {
        return new TObjectOfObservation("ObjectOfObservation");
    }

    virtual bool isDrawable() { return true; }
};

///Тип функции-фабрики, которая экспортируется подключаемой библиотекой с объектами
typedef TObjectOfObservation* CreateObjectOfObservation();

///Префикс для фуккций, экспортируемых подключаемой библиотекой
#ifdef WIN32
#define LIB_EXPORT_API __declspec(dllexport)
#else
#define LIB_EXPORT_API
#endif