#pragma once

#define WITHOUT_NUMPY

#include "BasicExamples/EmptyProgram.h"

#ifdef USE_PLOTTER
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
#endif

class TTestProgram : public TEmptyProgram
{
public:
  TTestProgram() {};

  TTestProgram(std::vector<TSmartThing*>& _things);

  virtual void Run();

  virtual void End();
};

extern "C" LIB_EXPORT_API IManagementProgram * create();
extern "C" LIB_EXPORT_API void destroy(IManagementProgram * ptr);