#pragma once

#include "BasicExamples/ObjectOfObservation.h"

extern "C" LIB_EXPORT_API std::vector <TObjectOfObservation*> create();
extern "C" LIB_EXPORT_API void destroy(std::vector <TObjectOfObservation*>);