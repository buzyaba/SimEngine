#include "SmartEnergyAutoProgram.hpp"

void TSmartEnergyAutoProgram::Run() {
    if ((currentTime % 86400) == 0)
      dailyPowerConsumption = 0;
    std::vector<std::string> str(1);
    str[0] = std::to_string(currentTime);

    for (int i = 0; i < sensors.size(); i++)
    {
      double* val = sensors[i]->GetDataPacket().GetDoubles();
      int dataCount = int(sensors[i]->GetDataPacket().GetSize() / sizeof(double));
      for (int j = 0; j < dataCount; j++)
      {
        if (dailyPowerConsumption > dailyLimit - 0.05)
          str.push_back(std::to_string(0));
        else 
          str.push_back(std::to_string(val[j]));
        dailyPowerConsumption += val[j];
      }
    }
    table.push_back(str);
  }

void TSmartEnergyAutoProgram::End() {
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
    if (sum > P)
      std::cout << "Electricity bill = " << sum * 6.45 <<" rub\n";
    else 
      std::cout << "Electricity bill = " << sum * 3.71 <<" rub\n";

    //DELETE THIS AFTER ALL PLS
    file = fopen((fileName + ".csv").c_str(), "w");

    for (int j = 0; j < tableHeader.size(); j++)
      fprintf(file, "%s;\t", tableHeader[j].c_str());
    fprintf(file, "\n");

    for (int i = 0; i < table.size(); i++)
    {
      for (int j = 0; j < table[i].size(); j++)
        fprintf(file, "%s;", table[i][j].c_str());
      fprintf(file, "\n");
    }
    fclose(file);
    //ENDS HERE
    // TManagementProgram::End();
}

LIB_EXPORT_API IManagementProgram* create()
{
    return new TSmartEnergyAutoProgram();
}
