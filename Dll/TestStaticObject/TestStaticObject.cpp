#include "TestStaticObject.h"
#include "TestRoom.h"

// ------------------------------------------------------------------------------------------------
LIB_EXPORT_API std::vector <TStaticObject*>* create()
{
  TStaticObject* obj = new TTestRoom("TTestRoom_");
  std::vector <TStaticObject*>* so = new std::vector <TStaticObject*>();
  so->push_back(obj);
  return so;
}

// ------------------------------------------------------------------------------------------------
LIB_EXPORT_API void destroy(std::vector <TStaticObject*> so)
{
  for (auto& obj : so)
    delete obj;
}