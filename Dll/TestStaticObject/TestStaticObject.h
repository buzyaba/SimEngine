#pragma once

#include "Core/StaticObject.h"
#include <vector>

extern "C" LIB_EXPORT_API std::vector <TStaticObject*> * create();
extern "C" LIB_EXPORT_API void destroy(std::vector <TStaticObject*>);