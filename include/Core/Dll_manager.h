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

#include "Core/ManagementProgram.h"
#include "Core/ObjectOfObservation.h"
#include "Core/SmartThing.h"
#include "Core/StaticObject.h"

#include <string>

#ifdef WIN32
  #include <direct.h>
  #include <windows.h>
#else
  #include <sys/types.h>
  #include <dlfcn.h>
#endif



/**
Класс, реализующий загрузку и выгрузку подключамеых библиотек с задачами

В классе #TProblemManager реализованы основные функции, для загрузки\выгрузки библиотек с задачами
*/
class TProblemManager
{
protected:

  enum DLL_TYPE
  {
    ManagementProgram = 0,
    ObjectOfObservation = 1,
    SmartThing = 2,
    StaticObject = 3
  };

  ///Указатель на дескриптор загруженной библиотеки
  #ifdef WIN32
    HINSTANCE mLibHandle;
  #else
    void *mLibHandle;
  #endif

  ///Указатель на созданный объект, описывающий упровляющую программу
  IManagementProgram* managementProgram;
  ///Указатель на функцию-фабрику упровляющих программ
  CreateManagementProgram* createManagementProgram;
  ///Указатель на функцию-деструктор упровляющих программ
  DestroyManagementProgram* destroyDestroyManagementProgram;

  ///Указатель на созданный объект, описывающий объекты
  std::vector <TObjectOfObservation*> objectOfObservations;
  ///Указатель на функцию-фабрику объектов
  CreateObjectOfObservation* createObjectOfObservation;
  ///Указатель на функцию-деструктор объектов
  DestroyObjectOfObservation* destroyObjectOfObservation;

  ///Указатель на созданный объект, описывающий умные вещи
  std::vector <TSmartThing*> smartThings;
  ///Указатель на функцию-фабрику умных вещей
  CreateSmartThing* createSmartThing;
  ///Указатель на функцию-деструктор умных вещей
  DestroySmartThing* destroySmartThing;

  ///Указатель на созданный объект, описывающий статичные объекты
  std::vector <TStaticObject*> staticObjects;
  ///Указатель на функцию-фабрику статических объектов
  CreateStaticObject* createStaticObject;
  ///Указатель на функцию-деструктор статических объектов
  DestroyStaticObject* destroyStaticObject;

  /// Метод, освобождающий загруженную библиотеку. Будет вызван в деструкторе
  int FreeProblemLibrary();

  ///Служебный метод, освобождающий #mLibHandle
  void FreeLibHandler();

public:

  /**
  Код ошибки, возвращаемый методами #LoadProblemLibrary и #FreeProblemLibrary
  при успешном выполнении операций
  */
  static const int OK_ = 0;
  /**
  Код ошибки, возвращаемый методами #LoadProblemLibrary и #FreeProblemLibrary
  при ошибке во время выполнении операций
  */
  static const int ERROR_ = -2;

  ///Конструктор
  TProblemManager();
  ///Деструктор, в нём вызывается #FreeProblemLibrary
  ~TProblemManager();

  /** Метод, загружающий библиотеку, находящуюся по указанному пути

  Метод загружает библиотеку, пытается импортировать из неё функции,
  создающие и уничтожающие задачу, а затем создаёт задачу

  \param[in] libPath Путь к загружаемой библиотеке
  \return Код ошибки
  */
  int LoadProblemLibrary(const std::string& libPath, DLL_TYPE type);

  /** Метод возвращает указатель IManagementProgram
  */
  IManagementProgram* GetManagementProgram() const;

  /** Метод возвращает множество объектов
  */
  std::vector <TObjectOfObservation*> GetObjectOfObservations() const;

  /** Метод возвращает множество умных вещей
  */
  std::vector <TSmartThing*> GetSmartThing() const;

  /** Метод возвращает множество статических объектов
*/
  std::vector <TStaticObject*> GetStaticObject() const;
};

#endif
// - end of file ----------------------------------------------------------------------------------
