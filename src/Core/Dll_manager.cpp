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
#ifdef WIN32
    #include <Windows.h>
#else
    #include <dirent.h>
#endif


std::string findDLLPath(const std::string& path) {
    std::string objPath;
#ifdef WIN32
    WIN32_FIND_DATA file_data;
    HANDLE h = FindFirstFile((path + "/*").c_str(), &file_data);
    if (h != INVALID_HANDLE_VALUE) {
      do {
        const std::string file_name = file_data.cFileName;
        const std::string full_file_name = path + "/" + file_name;
        if (full_file_name.find(".dll") != std::string::npos) {
          objPath = full_file_name;
        }
      } while (FindNextFile(h, &file_data));
    }
#else
    DIR *dir;
    dirent *ent;
    const char *dirPath = path.c_str();
    dir = opendir(dirPath);
    while ((ent = readdir(dir)) != NULL) {
      const std::string file_name = ent->d_name;
      const std::string full_file_name = path + "/" + file_name;
      if (full_file_name.find(".so") != std::string::npos) {
        objPath = full_file_name;
      }
    }
    closedir(dir);
#endif
    return objPath;
}

// ------------------------------------------------------------------------------------------------
// template<DLL_TYPE T>
// typename creator_type<T>::obj_type LoadDLLObject(const std::string& libPath)
// {
//   //if (mLibHandle)
//   //  FreeProblemLibrary();
// #ifdef WIN32
//   void *mLibHandle = LoadLibrary(TEXT(libPath.c_str()));
//   if (!mLibHandle)
//   {
//     std::cerr << "Cannot load library: " << TEXT(libPath.c_str()) << std::endl;
//   }
// #else
//   void *mLibHandle = dlopen(libPath.c_str(), RTLD_LAZY);
//   if (!mLibHandle)
//   {
//     std::cerr << dlerror() << std::endl;
//   }
// #endif
//     using type = typename creator_type<T>::type;
// #ifdef WIN32
//     auto createObject = (type*)GetProcAddress(mLibHandle, "create");
//     if (!createObject)
//     {
//       std::cerr << "Error load ManagementProgram. Cannot load symbols: " << GetLastError() << std::endl;
//       FreeLibHandler(mLibHandle);
//     }
// #else
//     dlerror();
//     auto createObject = (type*)dlsym(mLibHandle, "create");
//     char* dlsym_error = dlerror();
//     if (dlsym_error)
//     {
//       createObject = NULL;
//       std::cerr << dlsym_error << std::endl;
//       FreeLibHandler(mLibHandle);
//     }
//     dlsym_error = dlerror();
//     if (dlsym_error)
//     {
//       createObject = NULL;
//       std::cerr << dlsym_error << std::endl;
//       FreeLibHandler(mLibHandle);
//     }
// #endif
//     auto object = createObject();
//     if (!object)
//     {
//       FreeLibHandler(mLibHandle);
//       createObject = NULL;
//       object = nullptr;
//       std::cerr << "Cannot create management program instance" << std::endl;
//     }
//     FreeLibHandler(mLibHandle);
//     return object;
// }

// ------------------------------------------------------------------------------------------------
void FreeLibHandler(void* mLibHandle)
{
#ifdef WIN32
  FreeLibrary(mLibHandle);
#else
  dlclose(mLibHandle);
#endif
  mLibHandle = NULL;
}

// ------------------------------------------------------------------------------------------------