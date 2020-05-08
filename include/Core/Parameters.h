#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>
#ifdef USE_OpenGL
#include <Engine/FirstPersonView.hpp>
#endif
#include "Core/common.h"

class TParameters
{
protected:
  /// Установка значений по умолчанию
  void DefaultParameters();
  /// Загрузка параметров из XML
  void LoadXML();
public:
#ifdef USE_OpenGL
  /// Окно для отрисовки 
  WindowManager* _window;
#endif
  /* тип задачи
  <= 0 - дефолтная задача
  > 0 - загрузка из xml файлов
  **/
  int type = 0;
  /// Имя файла с расписанием для EnvironmentScript
  std::string xmlEnvironmentScriptName;
  /// Имя файла с конфигурацией сцены (описываются все объекты, умные вещи и прочее)
  std::string xmlMainSetConfigurationFile;
  /// Кол-во миллисекунд в одном шаге
  unsigned int millisecondsInTimeStep;
  /* Ускорение времени программы, 
  при = 0 программа работает с максимально возможной соростью, 
  при = 1 за одну итерацию проходит millisecondsInTimeStep времени **/
  double timeAcceleration;
  /// Максимальное число итераций
  unsigned long maxStep = 1000;

  /// Строка с адресом файла запустившего окно
  std::string cwd;

  TParameters(int argc = 0, char** argv = 0);

  /* Определение параметров запуска из консоли
  Если один параметр - то адрес xml с настройкой программы
  **/
  void LoadConsoleParameters(int argc = 0, char** argv = 0);
  /// Создает сроку со значениями текущей конфигурации параметров для печати
  std::string Print();
  /// Работа с консольным интерфейсом
  void ConsoleInterface();

};

extern TParameters GlobalParameters;