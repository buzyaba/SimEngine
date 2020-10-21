#include "SmartTerminalClassProgram.hpp"

void TSmartTerminalClassProgram::Run() {
  size_t terminal_count = 0;
  bool sheduleIsWork = true;
  bool sheduleActive = false;
  double timePeriod = 0;
  for (size_t iter = 0; iter < things.size(); ++iter) {
      auto thingSensors = things[iter]->GetSensors();
      auto thingActuators = things[iter]->GetActuators();
      for (size_t iterSensors = 0; iterSensors < thingSensors.size(); ++iterSensors) {
        TDataPacket& dataPacket = thingSensors[iterSensors]->GetDataPacket();
        size_t packetSize = dataPacket.GetSize();
        double* data = dataPacket.GetDoubles();
        double* packetVal = sendPacket.GetDoubles();
        for (int i = 0; i < thingSensors[iterSensors]->getObjectsCount(); ++i) {
          if ((currentTime >= 32400) && ((currentTime-32400) / 43200) == timePeriod) {
            packetVal[i] = static_cast<double>(sheduleIsWork);
            sheduleActive = true;
          } else {
            double isWork = data[i * (packetSize / thingSensors[iterSensors]->getObjectsCount())];
            if (isWork == 0)
              waitTime[terminal_count]++;
            else
              waitTime[terminal_count] = 0;
            if (waitTime[terminal_count] >= deltaT) {
              packetVal[i] = 2;
              waitTime[terminal_count] = 0;
            } else {
              packetVal[i] = isWork;
            }
            terminal_count++;
          }
        }
        thingActuators[iterSensors]->SetDataPacket(sendPacket);
      }
    }
    if (sheduleActive) {
      sheduleIsWork = !sheduleIsWork;
      timePeriod++;
    }
    TManagementProgram::Run();
  }

void TSmartTerminalClassProgram::End() {
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
    if (sum > 50)
      std::cout << "Electricity bill = " << sum * 6.45 <<" rub\n";
    else
      std::cout << "Electricity bill = " << sum * 3.71 <<" rub\n";

    TManagementProgram::End();
}

void TSmartTerminalClassProgram::SetSmartThing(std::vector<TSmartThing*> _things) {
  TManagementProgram::SetSmartThing(_things);
  size_t objectsCount = 0;
  for (auto sens : sensors)
    objectsCount += sens->getObjectsCount();
  waitTime.resize(objectsCount);
}

LIB_EXPORT_API IManagementProgram* create()
{
    return new TSmartTerminalClassProgram();
}
