#pragma once

#include "SimEngine/ManagementProgram.h"

class TStreetAutoProgram : public TManagementProgram {
    TDataPacket sendPacket{2 * sizeof(double)};
    std::size_t summaryCarCount{0};
    std::size_t carThreshold{5};

public:
    TStreetAutoProgram() : TManagementProgram() {
        tableHeader.push_back("carCount");
    }

    virtual void Run(std::size_t time, std::size_t step);

    virtual void End();
};

extern "C" LIB_EXPORT_API IManagementProgram* create();
