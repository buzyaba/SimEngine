#include "Core/ProgramFactory.h"
#include "Core/Parameters.h"
#include "BasicExamples/EmptyProgram.h"

bool TProgramFactory::isLoadInDLL = false;

IManagementProgram* TProgramFactory::Create(int a, std::vector<TSmartThing*>& _things)
{
  if (GlobalParameters.managementProgramDllFile != "")
  {
    isLoadInDLL = true;
    IManagementProgram* mp = GlobalParameters.problemManager.GetManagementProgram();
    mp->SetSmartThing(_things);
    return mp;
  }
  else
  {
    isLoadInDLL = false;
    if (a <= 0)
      if (a == -2)
        return new TRoomAutoProgram(_things);
      else
        return new TRoomProgram(_things);
    else
      return new TStreetProgram(_things);
  }
}
