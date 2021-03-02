#include "Core/ProgramFactory.h"
#include "Core/Parameters.h"
#include "SimEngine/ManagementProgram.h"

IManagementProgram* TProgramFactory::Create(std::vector<TSmartThing*>& _things)
{
  if (GlobalParameters.managementProgramDllFile != "")
  {
    IManagementProgram* mp = GlobalParameters.managementProgram;
    mp->SetSmartThing(_things);
    mp->SetSchedule(_things, GlobalParameters.xmlSmartThingScheduleName);
    return mp;
  }
}
