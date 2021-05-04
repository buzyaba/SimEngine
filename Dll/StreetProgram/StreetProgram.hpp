#pragma once

#include "SimEngine/ManagementProgram.h"

class TStreetProgram : public TManagementProgram
{
    TDataPacket sendPacket{2 * sizeof(double)};
    std::size_t summaryCarCount{0};

public:
    TStreetProgram() : TManagementProgram() {
        tableHeader.push_back("carCount");
    }

    virtual void Run(std::size_t time, std::size_t step);

    virtual void End();
};

extern "C" LIB_EXPORT_API IManagementProgram *create();