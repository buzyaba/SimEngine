#include "StreetAutoProgram.hpp"

void TStreetAutoProgram::Run(std::size_t time, std::size_t step) {
    TManagementProgram::Run(time, step);

    std::size_t carCount{0};
    for (std::size_t iter = 0; iter < things.size(); ++iter) {
        auto thingSensors = things[iter]->GetSensors();
        auto thingActuators = things[iter]->GetActuators();

        double* val = thingSensors[0]->GetDataPacket()->GetData<double>();
        carCount += val[0] + val[1];

        double* packetVal = sendPacket.GetData<double>(); 
        for(std::size_t actuatorIter = 0; actuatorIter < thingActuators.size(); ++actuatorIter) {
            if (val[actuatorIter] >= carThreshold) {
                packetVal[0] = 0;
                packetVal[1] = 0;
                thingActuators[actuatorIter]->SetDataPacket(&sendPacket);
                packetVal[0] = 1;
                packetVal[1] = 1;
                thingActuators[thingActuators.size()-1-actuatorIter]->SetDataPacket(&sendPacket);
            }
        }
        
    }
    summaryCarCount += carCount;
    table[table.size() - 1].push_back(std::to_string(carCount));
}


void TStreetAutoProgram::End()
{
    std::cout << "Car count = " << summaryCarCount << std::endl;

    TManagementProgram::End();
}

LIB_EXPORT_API IManagementProgram* create()
{
    return new TStreetAutoProgram();
}
