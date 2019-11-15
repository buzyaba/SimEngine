#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// ------------------------------------------------------------------------------------------------
/**
Базовый класс, реализует вывод на консоль

*/
class TOutputHelper { };

// ------------------------------------------------------------------------------------------------
/**
Базовый класс, реализует вывод на консоль справки первого уровня

Вывод происходит только если определены константы EXAMIN_OUTPUT_L1 или EXAMIN_OUTPUT_L2
*/
class TOutputLevel1Helper { };

// ------------------------------------------------------------------------------------------------
/**
Базовый класс, реализует вывод на консоль справки второго уровня

Вывод происходит только если определена константа EXAMIN_OUTPUT_L2
*/
class TOutputLevel2Helper { };

// ------------------------------------------------------------------------------------------------
/**
Базовый класс, реализует вывод на консоль отладочной информации

Вывод происходит только в debug версии (т.е. если определена константа _DEBUG)
*/
class TOutputDebugHelper { };

// ------------------------------------------------------------------------------------------------
class TLogDebugHelper;

// ------------------------------------------------------------------------------------------------
/**
Основной класс, реализует вывод в файл
Печать только в debug конфигурации
*/
class TLogger
{
protected:
  /// Поток вывода в файл
  std::fstream mLogOutputStream;
  /// Имя лог файла
  static std::string mLogFileName;
  /// Была ли проинициализирована иситема
  static bool mIsInitialized;

  ~TLogger() {}
  TLogger();
  TLogger(const TLogger&) {}
  TLogger& operator=(const TLogger&) {}

  template<typename T>
  friend inline TLogDebugHelper& operator<<(TLogDebugHelper& incomingHelper, const T& value);
public:
  /// Очистка потока вывода в файл
  void flush();
  /**
  Инициализация класса, необходимо вызвать перед работой, принимает имя лог файла
  \param[in] logFileName - имя файла в который будет произвадиться печать
  \param[in] isFlush - очищать ли файл
  */
  static void init(const std::string& logFileName);
  /// Возвращает экземпляр объекта
  static TLogger& instance();
};

// ------------------------------------------------------------------------------------------------
/**
Базовый класс, реализует вывод в файл отладочной информации

Вывод происходит только в debug версии (т.е. если определена константа _DEBUG)
*/
class TLogDebugHelper
{
  public:
    void flush()
    {
      TLogger::instance().flush();
    }
};

// ------------------------------------------------------------------------------------------------
/// Глобальная переменная для вывода отладочной информации (всесто cout)
extern TOutputDebugHelper print_dbg;
/// Глобальная переменная для вывода на консоль (всесто cout)
extern TOutputHelper print;
/// Глобальная переменная для выода отладочной информации первого и второго уровня
extern TOutputLevel1Helper print_l1;
/// Глобальная переменная для выода отладочной информации второго уровня
extern TOutputLevel2Helper print_l2;
/// Глобальная переменная для печати отладочной информации в лог
extern TLogDebugHelper print_dbg_file;

// ------------------------------------------------------------------------------------------------
template<typename T> inline
TOutputHelper& operator<<(TOutputHelper& incomingHelper, const T& value)
{
  std::cout << value;
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T> inline
TOutputLevel1Helper& operator<<(TOutputLevel1Helper& incomingHelper, const T& value)
{
#if defined(EXAMIN_OUTPUT_L1) || defined(EXAMIN_OUTPUT_L2)
  std::cout << value;
#endif
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T> inline
TOutputLevel2Helper& operator<<(TOutputLevel2Helper& incomingHelper, const T& value)
{
#ifdef EXAMIN_OUTPUT_L2
  std::cout << value;
#endif
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T> inline
TOutputDebugHelper& operator<<(TOutputDebugHelper& incomingHelper, const T& value)
{
#ifdef _DEBUG
  std::cout << value;
#endif
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T> inline
TLogDebugHelper& operator<<(TLogDebugHelper& incomingHelper, const T& value)
{
#ifdef _DEBUG
  TLogger::instance().mLogOutputStream << value;
#endif
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T>
std::string toString (T value)
{
  std::ostringstream oss;
  oss << value;
  return oss.str();
}
