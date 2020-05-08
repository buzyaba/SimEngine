#pragma once

#include "BasicExamples/Object.h"

// #include "BasicExamples/ObjectOfObservation.h"
// #include "BasicExamples/SmartThing.h"

class TStaticObject : public TObject {
public:
    // What should we do here? Idk...
    TStaticObject(std::string _name);
    /// Создание клона объекта
  virtual TStaticObject* Clone() = 0;
};

///Тип функции-фабрики, которая экспортируется подключаемой библиотекой со статичными объектами
typedef std::vector <TStaticObject*>* CreateStaticObject();
///Тип функции-деструктора, которая экспортируется подключаемой библиотекой со статичными объектами
typedef void DestroyStaticObject(std::vector <TStaticObject*>);

///Префикс для фуккций, экспортируемых подключаемой библиотекой
#ifdef WIN32
#define LIB_EXPORT_API __declspec(dllexport)
#else
#define LIB_EXPORT_API
#endif
