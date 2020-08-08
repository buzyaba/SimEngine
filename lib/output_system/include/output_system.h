#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� �� �������

*/
class TOutputHelper { };

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� �� ������� ������� ������� ������

����� ���������� ������ ���� ���������� ��������� EXAMIN_OUTPUT_L1 ��� EXAMIN_OUTPUT_L2
*/
class TOutputLevel1Helper { };

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� �� ������� ������� ������� ������

����� ���������� ������ ���� ���������� ��������� EXAMIN_OUTPUT_L2
*/
class TOutputLevel2Helper { };

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� �� ������� ���������� ����������

����� ���������� ������ � debug ������ (�.�. ���� ���������� ��������� _DEBUG)
*/
class TOutputDebugHelper { };

// ------------------------------------------------------------------------------------------------
class TLogDebugHelper;

// ------------------------------------------------------------------------------------------------
/**
�������� �����, ��������� ����� � ����
������ ������ � debug ������������
*/
class TLogger
{
protected:
  /// ����� ������ � ����
  std::fstream mLogOutputStream;
  /// ��� ��� �����
  static std::string mLogFileName;
  /// ���� �� ������������������� �������
  static bool mIsInitialized;

  ~TLogger() {}
  TLogger();
  TLogger(const TLogger&) {}
  TLogger& operator=(const TLogger&) {}

  template<typename T>
  friend inline TLogDebugHelper& operator<<(TLogDebugHelper& incomingHelper, const T& value);
public:
  /// ������� ������ ������ � ����
  void flush();
  /**
  ������������� ������, ���������� ������� ����� �������, ��������� ��� ��� �����
  \param[in] logFileName - ��� ����� � ������� ����� ������������� ������
  \param[in] isFlush - ������� �� ����
  */
  static void init(const std::string& logFileName);
  /// ���������� ��������� �������
  static TLogger& instance();
};

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� � ���� ���������� ����������

����� ���������� ������ � debug ������ (�.�. ���� ���������� ��������� _DEBUG)
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
/// ���������� ���������� ��� ������ ���������� ���������� (������ cout)
extern TOutputDebugHelper print_dbg;
/// ���������� ���������� ��� ������ �� ������� (������ cout)
extern TOutputHelper print;
/// ���������� ���������� ��� ����� ���������� ���������� ������� � ������� ������
extern TOutputLevel1Helper print_l1;
/// ���������� ���������� ��� ����� ���������� ���������� ������� ������
extern TOutputLevel2Helper print_l2;
/// ���������� ���������� ��� ������ ���������� ���������� � ���
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
