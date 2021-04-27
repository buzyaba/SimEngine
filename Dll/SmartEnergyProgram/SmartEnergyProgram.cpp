#include "SmartEnergyProgram.hpp"

void TSmartEnergyProgram::End() {
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

    sum = sum / 1000;

    std::cout << "Power consumption = " << sum << " kW/h" << std::endl;
    if (sum > 50)
      std::cout << "Electricity bill = " << sum * 6.45 <<" rub\n";
    else 
      std::cout << "Electricity bill = " << sum * 3.71 <<" rub\n";

    TManagementProgram::End();
}

LIB_EXPORT_API IManagementProgram* create()
{
    return new TSmartEnergyProgram();
}
