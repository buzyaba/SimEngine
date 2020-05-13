#include "TestSmartThing.h"
#include "TestSmartSocket.h"

// ------------------------------------------------------------------------------------------------
LIB_EXPORT_API std::vector <TSmartThing*>* create()
{
  TSmartThing* obj = new TTestSmartSocket("TTestRoom_");
  std::vector <TSmartThing*>* so = new std::vector <TSmartThing*>();
  so->push_back(obj);
  return so;
}

// ------------------------------------------------------------------------------------------------
LIB_EXPORT_API void destroy(std::vector <TSmartThing*> so)
{
  for (auto& obj : so)
    delete obj;
}