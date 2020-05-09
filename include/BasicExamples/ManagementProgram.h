#pragma once
#include "BasicExamples/DataPacket.h"
#include "BasicExamples/SmartThing.h"

/// Интерфейс запускаемой программы
class IManagementProgram
{
protected:
public:
  virtual void Run() = 0;
  virtual void End() = 0;
  virtual void SetSmartThing(std::vector<TSmartThing*> _things) = 0;
};

///Тип функции-фабрики, которая экспортируется подключаемой библиотекой с упровляющей программой
typedef IManagementProgram* CreateManagementProgram();
///Тип функции-деструктора, которая экспортируется подключаемой библиотекой с упровляющей программой
typedef void DestroyManagementProgram(IManagementProgram*);

///Префикс для фуккций, экспортируемых подключаемой библиотекой
#ifdef WIN32
#define LIB_EXPORT_API __declspec(dllexport)
#else
#define LIB_EXPORT_API
#endif