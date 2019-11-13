#include "output_system.h"

#include <stdexcept>

// ------------------------------------------------------------------------------------------------
TOutputDebugHelper print_dbg;
TOutputHelper print;
TLogDebugHelper print_dbg_file;
TOutputLevel1Helper print_l1;
TOutputLevel2Helper print_l2;

// ------------------------------------------------------------------------------------------------
bool TLogger::mIsInitialized = false;
std::string TLogger::mLogFileName = std::string();

// ------------------------------------------------------------------------------------------------
void TLogger::init(const std::string& logFileName)
{
#ifdef _DEBUG
  if(logFileName.empty())
    throw std::runtime_error("Empty log file name in TLogger");
  mIsInitialized = true;
  mLogFileName = logFileName;
  TLogger& instance = TLogger::instance();
  instance.flush();
#endif
}

// ------------------------------------------------------------------------------------------------
void TLogger::flush()
{
  mLogOutputStream.flush();
}

// ------------------------------------------------------------------------------------------------
TLogger& TLogger::instance()
{
  static TLogger instance;
  return instance;
}

// ------------------------------------------------------------------------------------------------
TLogger::TLogger()
{
#ifdef _DEBUG
  if(mIsInitialized)
  {
    if (!mLogOutputStream.is_open())
    {
      mLogOutputStream.open(mLogFileName.c_str(), std::fstream::out);
      if (!mLogOutputStream.is_open())
        throw std::runtime_error("Unable to create a debug log file\n");
    }
  }
  else
  {
    throw std::runtime_error("TLogger singleton instance is not initialized\n");
  }
#endif
}