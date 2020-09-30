#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "SimEngine/common.h"
#include "Core/Dll_manager.h"

class TParameters
{
protected:
  /// Загрузка параметров из XML
  void LoadXML();
  /// Строка с адресом файла запустившего окно
  std::string cwd;
  /// директория с файлами конфигурации
  std::string dirConfigFile;
  /// Разбиение строки на подстроки по пробелу
  void ParseString(std::string& str, std::vector<std::string>& tt);
public:
  /* тип камеры в графике
  <= 0 - FirstPerson view
  > 0 - Isometric view
  **/
  int type;
  /// Имя файла с текущей конфигурацией программы
  std::string xmlCurrentConfiguration;
  /// Имя файла с расписанием для EnvironmentScript
  std::string xmlEnvironmentScriptName;
  /// Имя файла с конфигурацией сцены (описываются все объекты, умные вещи и прочее)
  std::string xmlMainSetConfigurationFile;

  /// Имя dll с упровляемой программой
  std::string managementProgramDllFile;
  
  /// Кол-во миллисекунд в одном шаге
  unsigned int millisecondsInTimeStep;
  /* Ускорение времени программы, 
  при = 0 программа работает с максимально возможной соростью, 
  при = 1 за одну итерацию проходит millisecondsInTimeStep времени **/
  double timeAcceleration;
  /// Максимальное число итераций
  unsigned long maxStep;

  IManagementProgram* managementProgram;

  TParameters(int argc = -1, char** argv = 0);

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