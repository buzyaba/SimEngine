/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      problem_manager.h                                           //
//                                                                         //
//  Purpose:   Header file for dynamic libraries manager class             //
//                                                                         //
//                                                                         //
//  Author(s): Sovrasov V.                                                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/**
\file problem_manager.h

\authors Соврасов В.
\date 2016
\copyright ННГУ им. Н.И. Лобачевского

\brief Объявление класса #TProblemManager

*/

#ifndef __PROBLEMMANAGER_H__
#define __PROBLEMMANAGER_H__

#include "SimEngine/ManagementProgram.h"
#include "SimEngine/ObjectOfObservation.h"
#include "SimEngine/SmartThing.h"
#include "SimEngine/StaticObject.h"

#include <iostream>
#include <memory>
#include <string>

#ifdef WIN32
#include <direct.h>
#include <windows.h>
#else
#include <dlfcn.h>
#include <sys/types.h>

#endif

/**
Класс, реализующий загрузку и выгрузку подключамеых библиотек с задачами

В классе #TProblemManager реализованы основные функции, для загрузки\выгрузки
библиотек с задачами
*/

enum DLL_TYPE {
  MANAGEMENT_PROGRAM = 0,
  OBJECT_OF_OBSERVATION = 1,
  SMART_THING = 2,
  STATIC_OBJECT = 3
};

template <DLL_TYPE T> struct creator_type {};

template <> struct creator_type<MANAGEMENT_PROGRAM> {
  using type = CreateManagementProgram;
  using obj_type = IManagementProgram *;
};

template <> struct creator_type<OBJECT_OF_OBSERVATION> {
  using type = CreateObjectOfObservation;
  using obj_type = TObjectOfObservation *;
};

template <> struct creator_type<SMART_THING> {
  using type = CreateSmartThing;
  using obj_type = TSmartThing *;
};

template <> struct creator_type<STATIC_OBJECT> {
  using type = CreateStaticObject;
  using obj_type = TStaticObject *;
};

class Dll_Manager {
public:
  static std::string findDLLPath(const std::string &path);

  /** Метод, загружающий библиотеку, находящуюся по указанному пути

  Метод загружает библиотеку, импортирует из неё функции,
  создающие задачу, а затем создаёт задачу

  \param[in] libPath Путь к загружаемой библиотеке
  \return Код ошибки
  */
  template <DLL_TYPE T>
  static typename creator_type<T>::obj_type
  LoadDLLObject(const std::string &libPath) {
#ifdef WIN32
    mLibHandles.push_back(LoadLibrary(TEXT(libPath.c_str())));
    HINSTANCE mLibHandle = mLibHandles.back();
    if (!mLibHandle) {
      std::cerr << "Cannot load library: " << TEXT(libPath.c_str())
                << std::endl;
    }
#else
    mLibHandles.push_back(dlopen(libPath.c_str(), RTLD_LAZY));
    void *mLibHandle = mLibHandles.back();
    if (!mLibHandle) {
      std::cerr << dlerror() << std::endl;
    }
#endif
    using type = typename creator_type<T>::type;
#ifdef WIN32
    auto createObject = (type *)GetProcAddress(mLibHandle, "create");
    if (!createObject) {
      std::cerr << "Error load ManagementProgram. Cannot load symbols: "
                << GetLastError() << std::endl;
      FreeDllManager();
    }
#else
    dlerror();
    auto createObject = (type *)dlsym(mLibHandle, "create");
    char *dlsym_error = dlerror();
    if (dlsym_error) {
      createObject = NULL;
      std::cerr << dlsym_error << std::endl;
      FreeDllManager();
    }
    dlsym_error = dlerror();
    if (dlsym_error) {
      createObject = NULL;
      std::cerr << dlsym_error << std::endl;
      FreeDllManager();
    }
#endif
    auto object = createObject();
    if (!object) {
      FreeDllManager();
      createObject = NULL;
      object = nullptr;
      std::cerr << "Cannot create management program instance" << std::endl;
    }
    return object;
  }

  ///Служебный метод, освобождающий #mLibHandles
  static void FreeDllManager();

private:
#ifdef WIN32
  static std::vector<HINSTANCE> mLibHandles;
#else
  static std::vector<void *> mLibHandles;
#endif
};
#endif
// - end of file
// ----------------------------------------------------------------------------------
