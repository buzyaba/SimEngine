/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2013 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      messages.h                                                  //
//                                                                         //
//  Purpose:   Header file for method class                                //
//                                                                         //
//  Author(s): Sysoyev A., Barkalov K.                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <stdio.h>
#include <string>
#include <vector>

#include "output_system.h"

/**
* коды ошибок
**/

#define SYSTEM_OK          0
#define SYSTEM_CRASH       1
#define ERROR_ARGUMENT_SIZE -1
#define ERROR_DIM_IN_TASK_LEVEL -2

// ------------------------------------------------------------------------------------------------
/**
Базовый класс, реализует вывод на консоль информации, в debug версии также печатает в файл
Инициализирующий систему вывода
*/
class TOutputMessage
{
protected:
  /// Были ли проинициализированы статические параметры
  static bool mIsInit;
  /// Печатать ли в лог файл
  static std::vector<bool> mIsPrintToFile;
  /**
  Печатать ли в лог файл,
  переменная в которую сохраняется значение флага во время печати важного сообщения
  */
  static bool mOldIsPrintToFile;
  /// Кописания ошибок
  static std::string* mErrorsName;
  /// Коды ошибок
  static int* mErrorsCode;
  /// Число ошибок
  static int mErrorsCount;
  /// Имя лог файла
  static std::vector<std::string> mLogFileName;
  /// Номер главного процесса
  static int rootNumber;
  /// Номер процесса для которого будет выводиться
  int mPrintPocessNumber;
  /// строки вывода
  std::string output;
  /// Потоки вывода в файл
  static std::vector<std::fstream> mLogOutputStream;
  /// Количество потоков вывода
  static int streamCount;
  /// Номер потока для вывода важного сообщения
  static int ImportantMessageNumber;
  /// Печатать ли на конслоь
  static bool mIsPrintToConsole;
  /// Устанавливает ошибки по умолчанию
  static void SetDefaultErrors();
  /// Функция печати
  template<typename T>
  inline void Print(const T& value);
  /// Включает печать в файл
  static void ImportantMessageAppears(std::string importantMessageFile = "");
  /// Выключает печать в файл если она раньше была выключена
  static void ImportantMessageEnded();
public:
  /**
  \param[in] printPocessNumber - номер процесса который должен выводить сообщение
  Если -1 то выводят все
  */
  TOutputMessage(int printPocessNumber = -1);
  TOutputMessage(bool printInRoot);
  /**
  Инициализация систем вывода
  \param[in] isMPIInit - Проинициализирован ли MPI,
  требуется для корректной печати в файл в многопроцессорном режиме
  \param[in] mLogFileName - имя (префикс) лог файла
  \param[in] processCount - число процессов
  \param[in] processNumber - номер текущего процесса
  \param[in] isPrintToFile - печатать ли в файл все сообщения в debug, в release не печатается
  \param[in] errorsName - имена (расшифровка) ошибок
  \param[in] errorsCode - коды ошибок
  \param[in] errorsCount - число ошибок
  последние три параметра инициализируются по умолчанию в методе SetDefaultErrors
  */
  static void Init(std::string mLogFileName = "", bool isPrintToFile = false, std::string* errorsName = 0,
    int* errorsCode = 0, int errorsCount = 0);
  /// Приводит код ошибки к описанию
  static std::string ErrorName(int error);

  /// Напечатать подробную информацию об ошибке
  static void PrintError(int error, std::string file, int line, std::string expression);
  /// Печать важного сообщения
  static void PrintImportantMessage(std::string expression, std::string file = "", int line = -1,
    std::string fileName = "");
  /// Печать сообщения в файл
  static void PrintMessageToFile(std::string expression, std::string file = "", int line = -1,
    std::string fileName = "");
  /// Начать печать в файл
  static void OpenFileStream(std::string fileName = "");
  /// Прервать печать в файл
  static void BreakFileStream(std::string fileName = "");
  /// Вывод сообщений
  template<typename T>
  friend inline TOutputMessage& operator<<(TOutputMessage& incomingHelper, const T& value);
};

// ------------------------------------------------------------------------------------------------
template<typename T> inline
TOutputMessage& operator<<(TOutputMessage& incomingHelper, const T& value)
{
  if (!incomingHelper.mIsInit)
  {
    incomingHelper.output = incomingHelper.output + toString(value);
  }
  else
  {
    if (incomingHelper.output != "")
    {
      incomingHelper.Print(incomingHelper.output);
      incomingHelper.output = "";
    }

    incomingHelper.Print(value);
  }
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T> inline
void TOutputMessage::Print(const T& value)
{
  if (mIsPrintToFile[0])
  {
#ifdef _DEBUG
    print_dbg_file << value;
#endif
  }
  for (int i = 1; i < streamCount; i++)
  {
    if ((mLogFileName[i] != "") && (mIsPrintToFile[i]))
    {
      if (!mLogOutputStream[i].is_open())
        mLogOutputStream[i].open(mLogFileName[i].c_str(), std::fstream::out);
      mLogOutputStream[i] << value;
    }
  }
  if (mIsPrintToConsole)
    print << value;
}

// ------------------------------------------------------------------------------------------------
/// Глобальная переменная для выода информации на экран, в debug печатает в лог файл
extern TOutputMessage printMessage;
/**
Глобальная переменная для выода информации на экран только из первого процесса,
в debug печатает в лог файл
*/
extern TOutputMessage printMessageInFirstProcess;
/**
Глобальная переменная для выода информации на экран в корне,
в debug печатает в лог файл
*/
extern TOutputMessage printMessageInRoot;

// ------------------------------------------------------------------------------------------------
/// Приводим выражение в строку
#define O_TO_S(x) #x
/// В случае если errorCode != SYSTEM_OK печатаем сообщение об ошибке и выходим
#define _ERROR_(errorCode) \
TOutputMessage::PrintError(errorCode,__FILE__,__LINE__,O_TO_S(errorCode!=SYSTEM_OK));
/**
Если errorCode != SYSTEM_OK то приводит errorCode к описанию,
выводит сообщиние об ошибке и завершает работу программы
*/
#define _ASSERT_ERROR_CODE_(errorCode) if(errorCode!=SYSTEM_OK) \
TOutputMessage::PrintError(errorCode,__FILE__,__LINE__,O_TO_S(errorCode!=SYSTEM_OK));
/// Если expression==false выводит сообщение об ошибке и завершает работу программы
#define _ASSERT_(expression) if(expression==false) \
TOutputMessage::PrintError(1,__FILE__,__LINE__,O_TO_S(expression));
/// Печатаем важное сообщение, важные сообщения всегда дублируются в файл
#define _IMPORTANT_MESSAGE_(message) \
TOutputMessage::PrintImportantMessage(toString(message),__FILE__,__LINE__);
#endif //__MESSAGES_H__
