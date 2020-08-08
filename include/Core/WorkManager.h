#pragma once

#include <string>
#include <vector>

#include "Core/Sensor.h"
#include "Core/Actuator.h"
#include "Core/SmartThing.h"
#include "Core/ObjectOfObservation.h"
#include "Core/Properties.h"
#include "Core/StaticObject.h"
#include "Core/ManagementProgram.h"
#include "Core/DataStore.h"
#include "Core/DataPacket.h"
#include "Core/EnvironmentScript.h"
#include "Core/MainSet.h"
#include "Core/common.h"
#include "Core/Parameters.h"

#include "Engine/GraphicPresenter.hpp"

/// Класс 
class TWorkManager
{
protected:
  /// Параметры работы программы
  TParameters& parameters;

  IGraphicPresenter* presenter;

  /// множество всех наблюдаемых объектов
  std::vector<TObjectOfObservation*> objects;
  /// множество всех умных вещей
  std::vector<TSmartThing*> things;
  /// множество всех статичных объектов
  std::vector<TStaticObject*> staticObjects;

  /// расписание работы программы
  TEnvironmentScript* script;
  /// Управляющая программа
  IManagementProgram* program;
  /// Хранилище информации получаемой на каждой итерации
  TDataStore* storage;
  /// набор всех элементов
  TMainSet* mainSet;

  /// текущее время работы программы 
  unsigned long int time;
  /// Время начала работы
  std::chrono::time_point<std::chrono::steady_clock> startWork;


  /// Итерация работы программы
  void Iteration(unsigned long int& t, std::chrono::milliseconds& delayTime, const unsigned short& _enableVisualisation);
public:

  TWorkManager(TParameters& parameters_, IGraphicPresenter* presenter_);
  ~TWorkManager();
  /// Начало работы программы
  void Start(const unsigned short& _enableVisualisation = 1);
  /// Исскуственная остановка работы (для многопоточной версии)
  void Stop();
  /// Изменить текущую задержку
  void SetMillisecondsInTimeStep(unsigned int _milliseconds = 1000);
};