#include "TestProgram.h"

TTestProgram::TTestProgram(std::vector<TSmartThing*>& _things) : TManagementProgram(_things)
{

}

void TTestProgram::Run()
{
  TManagementProgram::Run();

  double value = 0;
  double sum = 0;
  size_t u = table.size() - 1;
  for (size_t i = 0; i < table[u].size() - 1; i++)
  {
    value = atof(table[u][i + 1].c_str());
    sum += value;
  }
  /*
  std::string s = "curl -v -X POST -d \"{\\\"Power\\\": " +
    std::to_string(sum) +
    " }\" http://localhost:8080/api/v1/FISKOaCIWwS5dlpZtL4c/telemetry --header \"Content-Type:application/json\"";
  std::system(s.c_str());
  */
}

void TTestProgram::End()
{
  double value = 0;
  double sum = 0;

  for (size_t u = 0; u < table.size() - 1; u++)
  {
    for (size_t i = 0; i < table[u].size() - 1; i++)
    {
      value = atof(table[u][i + 1ull].c_str());
      sum += value;
    }
  }

  std::cout << "Power consumption = " << sum << std::endl;

  TManagementProgram::End();
}

// ------------------------------------------------------------------------------------------------
LIB_EXPORT_API IManagementProgram* create()
{
  return new TTestProgram();
}

// ------------------------------------------------------------------------------------------------
LIB_EXPORT_API void destroy(IManagementProgram* ptr)
{
  delete ptr;
}