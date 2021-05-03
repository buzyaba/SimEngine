#include "StreetProgram.hpp"

void TStreetProgram::Run(std::size_t time, std::size_t step) {
    TManagementProgram::Run(time, step);

    std::size_t carCount{0};
    for (std::size_t iter = 0; iter < things.size(); ++iter) {
        auto thingSensors = things[iter]->GetSensors();
        auto thingActuators = things[iter]->GetActuators();
        
        double* val = thingSensors[0]->GetDataPacket().GetData<double>();
        carCount += val[0] + val[1];

        double* packetVal = sendPacket.GetData<double>();

    }


      // double carCount = 0;
      // if (sensors.size() > 0)
      // {
      //   double* val = sensors[0]->GetDataPacket().GetData<double>();
      //   int dataCount = val[0];
      //   for (int j = 0; j < dataCount; j++)
      //   {
      //     carCount += val[j];
      //   }
      //   table[table.size() - 1].push_back(std::to_string(carCount));
      // }
    // double* packetVal = sendPacket.GetData<double>();



    // bool isUpdate = false;

    // if (currentStep % waitingTime == 0) {
    //     isUpdate = true;
    //     packetVal[0] = (int(packetVal[0]) + 1) % 2;
    //     if (packetVal[0]) {
    //         waitingTime = timeRed;
    //     }
    //     else {
    //         waitingTime = timeGreen;
    //     }
    // }

    // if (isUpdate)
    // {
    //     for (int i = 0; i < things.size(); i++)
    //     {
    //         things[i]->GetActuators()[0]->SetDataPacket(sendPacket);
    //         int IsNotGo = int(packetVal[0]);

    //         if (IsNotGo == 1)
    //             things[i]->SetProperty({ {"Color", 2} }, "Color");
    //         else
    //             things[i]->SetProperty({ {"Color", 0} }, "Color");
    //     }
    // }

    // for (int i = 0; i < things.size(); i++) {
    //    things[i]->SetProperty({ {"NumberOfStandingCars", carCount} }, "NumberOfStandingCars");
    // }
  }

void TStreetProgram::End() {
    double value = 0;
    double sum = 0;

    // for (int u = 0; u < table.size() - 1; u++)
    // {
    //   for (int i = 0; i < table[u].size() - 1; i++)
    //   {
    //     value = atof(table[u][i + 1].c_str());
    //     sum += value;
    //   }
    // }

    std::cout << "Car count = " << sum << std::endl;

    TManagementProgram::End();
}

LIB_EXPORT_API IManagementProgram* create()
{
    return new TStreetProgram();
}
