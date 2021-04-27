#pragma once

#include "SimEngine/ManagementProgram.h"

class TStreetAutoProgram : public TManagementProgram {
    TDataPacket* sendPacket;
    int carThreshold;
    int timeGreen;
    int timeRed;
    int waitingTime;
public:
    TStreetAutoProgram() : TManagementProgram()
    {
        tableHeader.push_back("carCount");
        sendPacket = new TDataPacket(sizeof(double));
        double* packetVal = sendPacket->GetData<double>();
        packetVal[0] = 0;
        carThreshold = 10;
        timeGreen = 30;
        timeRed = 120;
        waitingTime = 1;
    }

    ~TStreetAutoProgram() { delete sendPacket; }

    virtual void Run();

    virtual void End();
};

extern "C" LIB_EXPORT_API IManagementProgram* create();