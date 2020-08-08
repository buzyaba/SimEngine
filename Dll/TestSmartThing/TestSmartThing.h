#pragma once

#include "BasicExamples/SmartThing.h"
#include <vector>

extern "C" LIB_EXPORT_API std::vector <TSmartThing*>*  create();
extern "C" LIB_EXPORT_API void destroy(std::vector <TSmartThing*>);