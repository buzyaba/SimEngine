#include "messages.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <time.h>
#include <stdexcept>

bool TOutputMessage::mIsInit = false;
std::vector<bool> TOutputMessage::mIsPrintToFile = std::vector<bool>();
bool TOutputMessage::mOldIsPrintToFile = false;
std::string* TOutputMessage::mErrorsName = 0;
int* TOutputMessage::mErrorsCode = 0;
int TOutputMessage::mErrorsCount = 0;
std::vector<std::string> TOutputMessage::mLogFileName = std::vector<std::string>();
int TOutputMessage::rootNumber = 0;
std::vector<std::fstream> TOutputMessage::mLogOutputStream = std::vector<std::fstream>();
int TOutputMessage::streamCount = 0;
int TOutputMessage::ImportantMessageNumber = -1;
bool TOutputMessage::mIsPrintToConsole = true;

/// Глобальная переменная для выода информации на экран, в debug печатает в лог файл
TOutputMessage printMessage;
/**
Глобальная переменная для выода информации на экран только из первого процесса,
в debug печатает в лог файл
*/
TOutputMessage printMessageInFirstProcess(1);
/**
Глобальная переменная для выода информации на экран в корне,
в debug печатает в лог файл
*/
TOutputMessage printMessageInRoot(true);

// ------------------------------------------------------------------------------------------------
void TOutputMessage::SetDefaultErrors()
{
  mErrorsCount = 4;
  if (mErrorsName != 0)
    delete[] mErrorsName;
  if (mErrorsCode != 0)
    delete[] mErrorsCode;
  mErrorsName = new std::string[mErrorsCount];
  mErrorsName[0] = "";
  mErrorsName[1] = "SYSTEM CRASH";
  mErrorsName[2] = "INCORRECT ARGUMENT SIZE";
  mErrorsName[3] = "INCORRECT DIM IN TASK LEVEL";
  mErrorsCode = new int[mErrorsCount];
  mErrorsCode[0] = SYSTEM_OK;
  mErrorsCode[1] = SYSTEM_CRASH;
  mErrorsCode[2] = ERROR_ARGUMENT_SIZE;
  mErrorsCode[3] = ERROR_DIM_IN_TASK_LEVEL;
}

// ------------------------------------------------------------------------------------------------
TOutputMessage::TOutputMessage(int printPocessNumber)
{
  mPrintPocessNumber = printPocessNumber;
  output = "";
}

// ------------------------------------------------------------------------------------------------
TOutputMessage::TOutputMessage(bool printInRoot)
{
  mPrintPocessNumber = rootNumber;
  output = "";
}

// ------------------------------------------------------------------------------------------------
void TOutputMessage::Init(std::string logFileName, bool isPrintToFile, std::string* errorsName,
  int* errorsCode, int errorsCount)
{
  streamCount = 2;
  mIsPrintToFile.resize(streamCount);
#ifdef _DEBUG
  mIsPrintToFile[0] = isPrintToFile;
  mIsPrintToFile[1] = false;
#else
  mIsPrintToFile[0] = false;
  mIsPrintToFile[1] = isPrintToFile;
#endif
  std::string log = logFileName + "_process_" + toString(1);

  mLogFileName.resize(streamCount);
  mLogFileName[0] = log + "_Debug.txt";
  mLogFileName[1] = log + ".txt";
  TLogger::init(mLogFileName[0]);

  //mLogOutputStream.resize(streamCount);
  if (mIsPrintToFile[1])
  {
    mLogOutputStream[1].open(mLogFileName[1].c_str(), std::fstream::out);
    if (!mLogOutputStream[1].is_open())
      throw std::runtime_error("Unable to create a log file\n");
    mLogOutputStream[1].flush();
  }

  mErrorsCount = errorsCount;

  if ((mErrorsName == 0) || (mErrorsCount == 0) || (mErrorsCode == 0))
    SetDefaultErrors();
  else
  {
    if (mErrorsName != 0)
      delete[] mErrorsName;
    if (mErrorsCode != 0)
      delete[] mErrorsCode;

    mErrorsName = new std::string[mErrorsCount];
    mErrorsCode = new int[mErrorsCount];

    for (int i = 0; i < mErrorsCount; i++)
    {
      mErrorsName[i] = errorsName[i];
      mErrorsCode[i] = errorsCode[i];
    }
  }

  rootNumber = 0;
  mIsInit = true;

  printMessage << "";
  printMessageInFirstProcess << "";
  printMessageInRoot << "";
}

// ------------------------------------------------------------------------------------------------
std::string TOutputMessage::ErrorName(int error)
{
  for (int i = 0; i < mErrorsCount; i++)
  {
    if (mErrorsCode[i] == error)
      return mErrorsName[i];
  }
  return toString(error);
}

// ------------------------------------------------------------------------------------------------
void TOutputMessage::PrintError(int error, std::string file, int line, std::string expression)
{
  if (error != SYSTEM_OK)
  {
    if (!mIsInit)
    {
      time_t t = time(0);
      Init("Erorlog" + toString(t) + ".txt", true);
      ImportantMessageAppears();
    }
    else
    {
      time_t t = time(0);
      ImportantMessageAppears("Erorlog_process_" + toString(1) + "_" + toString(t) + ".txt");
    }
    printMessage << "Expression: " << expression << "\n" << file << "\t" << line << "\n";
    printMessage << "\n!!! Error " << ErrorName(error) << " !!!\n";
    ImportantMessageEnded();
    exit(error);
  }
}

// ------------------------------------------------------------------------------------------------
void TOutputMessage::PrintImportantMessage(std::string expression,
  std::string file, int line, std::string fileName)
{
  if (!mIsInit)
  {

    time_t t = time(0);
    Init("Erorlog" + toString(t) + ".txt", true);
  }
  ImportantMessageAppears(fileName);
  if ((file != "") || (line != -1))
    printMessage << "Message: " << expression << "\n" << file << "\t" << line << "\n";
  else
    printMessage << "Message: " << expression << "\n";
  ImportantMessageEnded();
}

// ------------------------------------------------------------------------------------------------
void TOutputMessage::PrintMessageToFile(std::string expression, std::string file,
  int line, std::string fileName)
{
  mIsPrintToConsole = false;
  ImportantMessageAppears(fileName);
  if ((file != "") || (line != -1))
    printMessage << "Message: " << expression << "\n" << file << "\t" << line << "\n";
  else
    printMessage << "Message: " << expression << "\n";

  mIsPrintToConsole = true;
  ImportantMessageEnded();
}

// ------------------------------------------------------------------------------------------------
void TOutputMessage::ImportantMessageAppears(std::string importantMessageFile)
{
  if (importantMessageFile == "")
  {
#ifdef _DEBUG
    importantMessageFile = mLogFileName[0];
#else
    importantMessageFile = mLogFileName[1];
#endif
  }
  bool isImportantMessageFileOpen = false;
  for (int i = 0; i < streamCount; i++)
  {
    if (mLogFileName[i] == importantMessageFile)
    {
      isImportantMessageFileOpen = true;
      mOldIsPrintToFile = mIsPrintToFile[i];
      ImportantMessageNumber = i;
      mIsPrintToFile[i] = true;
      break;
    }
  }
  if (!isImportantMessageFileOpen)
  {
    streamCount++;
    mLogFileName.resize(streamCount);
    mLogFileName[streamCount - 1] = importantMessageFile;

    //mLogOutputStream.resize(streamCount);
    mLogOutputStream[streamCount - 1].open(mLogFileName[streamCount - 1].c_str(),
      std::fstream::out);
    if (!mLogOutputStream[streamCount - 1].is_open())
      throw std::runtime_error("Unable to create a log file\n");
    mLogOutputStream[streamCount - 1].flush();
    mIsPrintToFile.resize(streamCount);
    mIsPrintToFile[streamCount - 1] = true;
    ImportantMessageNumber = streamCount - 1;
    mOldIsPrintToFile = false;
  }
}

// ------------------------------------------------------------------------------------------------
void TOutputMessage::OpenFileStream(std::string fileName)
{
  if (fileName == "")
  {
#ifdef _DEBUG
    fileName = mLogFileName[0];
#else
    fileName = mLogFileName[1];
#endif
  }

  bool isFileOpen = false;
  for (int i = 0; i < streamCount; i++)
  {
    if (mLogFileName[i] == fileName)
    {
      isFileOpen = true;
      mIsPrintToFile[i] = true;
      break;
    }
  }
  if (!isFileOpen)
  {
    streamCount++;
    mLogFileName.resize(streamCount);
    mLogFileName[streamCount - 1] = fileName;

    //mLogOutputStream.resize(streamCount);
    mLogOutputStream[streamCount - 1].open(mLogFileName[streamCount - 1].c_str(),
      std::fstream::out);
    if (!mLogOutputStream[streamCount - 1].is_open())
      throw std::runtime_error("Unable to create a log file\n");
    mLogOutputStream[streamCount - 1].flush();
    mIsPrintToFile.resize(streamCount);
    mIsPrintToFile[streamCount - 1] = true;
  }
}

// ------------------------------------------------------------------------------------------------
void TOutputMessage::BreakFileStream(std::string fileName)
{
  if (fileName == "")
  {
#ifdef _DEBUG
    fileName = mLogFileName[0];
#else
    fileName = mLogFileName[1];
#endif
  }

  for (int i = 0; i < streamCount; i++)
  {
    if (mLogFileName[i] == fileName)
    {
      mIsPrintToFile[i] = false;
      break;
    }
  }
}

// ------------------------------------------------------------------------------------------------
void TOutputMessage::ImportantMessageEnded()
{
  mIsPrintToFile[ImportantMessageNumber] = mOldIsPrintToFile;
  mOldIsPrintToFile = false;
}