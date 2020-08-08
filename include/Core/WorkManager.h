#pragma once

#include <string>
#include <vector>

#include "BasicExamples/Sensor.h"
#include "BasicExamples/Actuator.h"
#include "BasicExamples/SmartThing.h"
#include "BasicExamples/ObjectOfObservation.h"
#include "BasicExamples/Properties.h"
#include "BasicExamples/StaticObject.h"
#include "BasicExamples/ManagementProgram.h"
#include "Core/DataStore.h"
#include "BasicExamples/DataPacket.h"
#include "Core/EnvironmentScript.h"
#include "Core/MainSet.h"

#include "BasicExamples/common.h"
#include "Core/Parameters.h"


/// Класс 
class TWorkManager
{
protected:
  /// Параметры работы программы
  TParameters& parameters;

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

  TWorkManager(TParameters& param = GlobalParameters);
  ~TWorkManager();
  /// Начало работы программы
  void Start(const unsigned short& _enableVisualisation = 1);
  /// Исскуственная остановка работы (для многопоточной версии)
  void Stop();
  /// Изменить текущую задержку
  void SetMillisecondsInTimeStep(unsigned int _milliseconds = 1000);
};