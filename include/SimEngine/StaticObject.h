#pragma once

#include "SimEngine/Object.h"

class TStaticObject : public TObject {
public:

    TStaticObject(std::string _name): TObject(_name) {}
    virtual TStaticObject* Clone() = 0;
    virtual bool isDrawable() { return true; }
};

///Тип функции-фабрики, которая экспортируется подключаемой библиотекой со статичными объектами
typedef TStaticObject* CreateStaticObject();

///Префикс для фуккций, экспортируемых подключаемой библиотекой
#ifdef WIN32
#define LIB_EXPORT_API __declspec(dllexport)
#else
#define LIB_EXPORT_API
#endif
