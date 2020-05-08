/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      problem_manager.cpp                                         //
//                                                                         //
//  Purpose:   Source file for dynamic libraries manager class             //
//                                                                         //
//                                                                         //
//  Author(s): Sovrasov V.                                                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include "Core/Dll_manager.h"
#include <iostream>

// ------------------------------------------------------------------------------------------------
TProblemManager::TProblemManager() : mLibHandle(NULL), managementProgram(NULL),
createManagementProgram(NULL), destroyDestroyManagementProgram(NULL)
{

}

// ------------------------------------------------------------------------------------------------
TProblemManager::~TProblemManager()
{
  FreeProblemLibrary();
}

// ------------------------------------------------------------------------------------------------
int TProblemManager::LoadProblemLibrary(const std::string& libPath, DLL_TYPE type)
{
  if (mLibHandle)
    FreeProblemLibrary();
#ifdef WIN32
  mLibHandle = LoadLibrary(TEXT(libPath.c_str()));
  if (!mLibHandle)
  {
    std::cerr << "Cannot load library: " << TEXT(libPath.c_str()) << std::endl;
    return TProblemManager::ERROR_;
  }
#else
  mLibHandle = dlopen(libPath.c_str(), RTLD_LAZY);
  if (!mLibHandle)
  {
    std::cerr << dlerror() << std::endl;
    return TProblemManager::ERROR_;
  }
#endif

  if (type == TProblemManager::ManagementProgram)
  {
#ifdef WIN32
    createManagementProgram = (CreateManagementProgram*)GetProcAddress(mLibHandle, "create");
    destroyDestroyManagementProgram = (DestroyManagementProgram*)GetProcAddress(mLibHandle, "destroy");
    if (!createManagementProgram || !destroyDestroyManagementProgram)
    {
      std::cerr << "Error load ManagementProgram. Cannot load symbols: " << GetLastError() << std::endl;
      FreeLibHandler();
      return TProblemManager::ERROR_;
    }
#else
    dlerror();
    createManagementProgram = (CreateManagementProgram*)dlsym(mLibHandle, "create");
    char* dlsym_error = dlerror();
    if (dlsym_error)
    {
      createManagementProgram = NULL;
      std::cerr << dlsym_error << std::endl;
      FreeLibHandler();
      return TProblemManager::ERROR_;
    }
    destroyDestroyManagementProgram = (DestroyManagementProgram*)dlsym(mLibHandle, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error)
    {
      createManagementProgram = NULL;
      destroyDestroyManagementProgram = NULL;
      std::cerr << dlsym_error << std::endl;
      FreeLibHandler();
      return TProblemManager::ERROR_;
    }
#endif
  }
  else if (type == TProblemManager::ObjectOfObservation)
  {
#ifdef WIN32
    createObjectOfObservation = (CreateObjectOfObservation*)GetProcAddress(mLibHandle, "create");
    destroyObjectOfObservation = (DestroyObjectOfObservation*)GetProcAddress(mLibHandle, "destroy");
    if (!createObjectOfObservation || !destroyObjectOfObservation)
    {
      std::cerr << "Error load ManagementProgram. Cannot load symbols: " << GetLastError() << std::endl;
      FreeLibHandler();
      return TProblemManager::ERROR_;
    }
#else
    dlerror();
    createObjectOfObservation = (CreateObjectOfObservation*)dlsym(mLibHandle, "create");
    char* dlsym_error = dlerror();
    if (dlsym_error)
    {
      createObjectOfObservation = NULL;
      std::cerr << dlsym_error << std::endl;
      FreeLibHandler();
      return TProblemManager::ERROR_;
    }
    destroyObjectOfObservation = (DestroyObjectOfObservation*)dlsym(mLibHandle, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error)
    {
      createObjectOfObservation = NULL;
      destroyObjectOfObservation = NULL;
      std::cerr << dlsym_error << std::endl;
      FreeLibHandler();
      return TProblemManager::ERROR_;
    }
#endif
  }
  else if (type == TProblemManager::SmartThing)
  {
#ifdef WIN32
    createSmartThing = (CreateSmartThing*)GetProcAddress(mLibHandle, "create");
    destroySmartThing = (DestroySmartThing*)GetProcAddress(mLibHandle, "destroy");
    if (!createSmartThing || !destroySmartThing)
    {
      std::cerr << "Error load ManagementProgram. Cannot load symbols: " << GetLastError() << std::endl;
      FreeLibHandler();
      return TProblemManager::ERROR_;
    }
#else
    dlerror();
    createSmartThing = (CreateSmartThing*)dlsym(mLibHandle, "create");
    char* dlsym_error = dlerror();
    if (dlsym_error)
    {
      createSmartThing = NULL;
      std::cerr << dlsym_error << std::endl;
      FreeLibHandler();
      return TProblemManager::ERROR_;
    }
    destroySmartThing = (DestroySmartThing*)dlsym(mLibHandle, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error)
    {
      createSmartThing = NULL;
      destroySmartThing = NULL;
      std::cerr << dlsym_error << std::endl;
      FreeLibHandler();
      return TProblemManager::ERROR_;
    }
#endif
  }
  else if (type == TProblemManager::StaticObject)
  {
#ifdef WIN32
  createStaticObject = (CreateStaticObject*)GetProcAddress(mLibHandle, "create");
  destroyStaticObject = (DestroyStaticObject*)GetProcAddress(mLibHandle, "destroy");
  if (!createStaticObject || !destroyStaticObject)
  {
    std::cerr << "Error load ManagementProgram. Cannot load symbols: " << GetLastError() << std::endl;
    FreeLibHandler();
    return TProblemManager::ERROR_;
  }
#else
  dlerror();
  createStaticObject = (CreateStaticObject*)dlsym(mLibHandle, "create");
  char* dlsym_error = dlerror();
  if (dlsym_error)
  {
    createStaticObject = NULL;
    std::cerr << dlsym_error << std::endl;
    FreeLibHandler();
    return TProblemManager::ERROR_;
  }
  destroyStaticObject = (DestroyStaticObject*)dlsym(mLibHandle, "destroy");
  dlsym_error = dlerror();
  if (dlsym_error)
  {
    createStaticObject = NULL;
    destroyStaticObject = NULL;
    std::cerr << dlsym_error << std::endl;
    FreeLibHandler();
    return TProblemManager::ERROR_;
  }
#endif
  }

  if (type == TProblemManager::ManagementProgram)
  {
    managementProgram = createManagementProgram();
    if (!managementProgram)
    {
      FreeLibHandler();
      createManagementProgram = NULL;
      destroyDestroyManagementProgram = NULL;
      std::cerr << "Cannot create management program instance" << std::endl;
    }
  }
  else if (type == TProblemManager::ObjectOfObservation)
  {
    objectOfObservations = createObjectOfObservation();
    if (objectOfObservations.size() == 0)
    {
      FreeLibHandler();
      createObjectOfObservation = NULL;
      destroyObjectOfObservation = NULL;
      std::cerr << "Cannot create object of observation instance" << std::endl;
    }
  }
  else if (type == TProblemManager::SmartThing)
  {
    smartThings = createSmartThing();
    if (smartThings.size() == 0)
    {
      FreeLibHandler();
      createSmartThing = NULL;
      destroySmartThing = NULL;
      std::cerr << "Cannot create object of observation instance" << std::endl;
    }
  }
  else if (type == TProblemManager::StaticObject)
  {
    staticObjects = createStaticObject();
    if (staticObjects.size() == 0)
    {
      FreeLibHandler();
      createStaticObject = NULL;
      destroyStaticObject = NULL;
      std::cerr << "Cannot create object of observation instance" << std::endl;
    }
  }

  return TProblemManager::OK_;
}

// ------------------------------------------------------------------------------------------------
void TProblemManager::FreeLibHandler()
{
#ifdef WIN32
  FreeLibrary(mLibHandle);
#else
  dlclose(mLibHandle);
#endif
  mLibHandle = NULL;
}

// ------------------------------------------------------------------------------------------------
int TProblemManager::FreeProblemLibrary()
{
  if (managementProgram)
    destroyDestroyManagementProgram(managementProgram);
  if (mLibHandle)
    FreeLibHandler();
  mLibHandle = NULL;
  managementProgram = NULL;
  createManagementProgram = NULL;
  destroyDestroyManagementProgram = NULL;
  return TProblemManager::OK_;
}

// ------------------------------------------------------------------------------------------------
IManagementProgram* TProblemManager::GetManagementProgram() const
{
  if (managementProgram)
    return managementProgram;
  else
    return NULL;
}
std::vector<TObjectOfObservation*> TProblemManager::GetObjectOfObservations() const
{

  if (objectOfObservations.size() != 0)
    return objectOfObservations;
  else
    return std::vector<TObjectOfObservation*>();
}
std::vector<TSmartThing*> TProblemManager::GetSmartThing() const
{
  if (smartThings.size() != 0)
    return smartThings;
  else
  return std::vector<TSmartThing*>();
}
std::vector<TStaticObject*> TProblemManager::GetStaticObject() const
{
  if (staticObjects.size() != 0)
    return staticObjects;
  else
  return std::vector<TStaticObject*>();
}
// - end of file ----------------------------------------------------------------------------------