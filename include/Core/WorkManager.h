#pragma once

#include <string>
#include <vector>

#include "SimEngine/Sensor.h"
#include "SimEngine/Actuator.h"
#include "SimEngine/SmartThing.h"
#include "SimEngine/ObjectOfObservation.h"
#include "SimEngine/Properties.h"
#include "SimEngine/StaticObject.h"
#include "SimEngine/ManagementProgram.h"
#include "Core/DataStore.h"
#include "SimEngine/DataPacket.h"
#include "Core/ExternalActionSchedule.h"
#include "Core/MainSet.h"
#include "SimEngine/common.h"
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
  TExternalActionSchedule* script;
  /// Управляющая программа
  IManagementProgram* program;
  /// Хранилище информации получаемой на каждой итерации
  TDataStore* storage;
  /// набор всех элементов
  TMainSet* mainSet;

  /// текущее время работы программы 
  std::size_t time;
  /// Время начала работы
  std::chrono::time_point<std::chrono::steady_clock> startWork;


  /// Итерация работы программы
  void Iteration(const std::size_t step, const std::chrono::milliseconds& iterTime);
public:
  TWorkManager(TParameters& parameters_, IGraphicPresenter* presenter_);
  ~TWorkManager();
  /// Начало работы программы
  void Start();
  /// Исскуственная остановка работы (для многопоточной версии)
  void Stop();
  /// Изменить текущую задержку
  void SetMillisecondsInTimeStep(unsigned int _milliseconds = 1000);
  void sendObjects();
};