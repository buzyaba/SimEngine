#pragma once

#include "SimEngine/ManagementProgram.h"

class TStreetPeakProgram : public TManagementProgram {
    TDataPacket sendPacket{1};
    int peakTime;
    int timeGreen;
    int timeRed;
    int waitingTime;
public:
    TStreetPeakProgram() : TManagementProgram()
    {
        tableHeader.push_back("carCount");
        double* packetVal = sendPacket.GetData<double>();
        packetVal[0] = 0;
        peakTime = 10;
        timeGreen = 30;
        timeRed = 120;
        waitingTime = 1;
    }

    virtual void Run();
    virtual void End();
};
extern "C" LIB_EXPORT_API IManagementProgram* create();
