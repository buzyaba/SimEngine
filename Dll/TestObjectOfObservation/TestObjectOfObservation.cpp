#include "TestObjectOfObservation.h"
#include "TestTerminal1.h"

// ------------------------------------------------------------------------------------------------
LIB_EXPORT_API std::vector <TObjectOfObservation*> create()
{
  TObjectOfObservation* obj = new TTestTerminal1("TTestTerminal1_");
  std::vector <TObjectOfObservation*> voo;
  voo.push_back(obj);
  return voo;
}

// ------------------------------------------------------------------------------------------------
LIB_EXPORT_API void destroy(std::vector <TObjectOfObservation*> voo)
{
  for (auto& obj : voo)
    delete obj;
}