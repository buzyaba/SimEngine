/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      exception.cpp                                               //
//                                                                         //
//  Purpose:   Source file for Exception class                             //
//                                                                         //
//  Author(s): Sysoyev A.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include "exception.h"

#include <cstdio>
#include <cstdlib>
#include <cstring> 

// ------------------------------------------------------------------------------------------------
TException::TException(const char *_File, int _Line, const char *_Function,
  const char *_Description)
{
  File = new char[strlen(_File) + 1];
  strcpy(File, _File);
  Line = _Line;
  Function = new char[strlen(_Function) + 1];
  strcpy(Function, _Function);
  Description = new char[strlen(_Description) + 1];
  strcpy(Description, _Description);

  TOutputMessage::PrintImportantMessage("EXCEPTION in file : " + toString(File) + ", line : " +
    toString(Line) + ", function : " + toString(Function)  +
    "\nDESCRIPTION: " + toString(Description) + "\n");
}

// ------------------------------------------------------------------------------------------------
TException::TException(const TException &e)
{
  File = new char[strlen(e.File) + 1];
  strcpy(File, e.File);
  Line = e.Line;
  Function = new char[strlen(e.Function) + 1];
  strcpy(Function, e.Function);
  Description = new char[strlen(e.Description) + 1];
  strcpy(Description, e.Description);
}

// ------------------------------------------------------------------------------------------------
TException::~TException()
{
  delete [] File;
  delete [] Function;
  delete [] Description;
}

// ------------------------------------------------------------------------------------------------
const char* TException::GetFile() const
{
  return File;
}

// ------------------------------------------------------------------------------------------------
int TException::GetLine() const
{
  return Line;
}

// ------------------------------------------------------------------------------------------------
const char* TException::GetFunction() const
{
  return Function;
}

// ------------------------------------------------------------------------------------------------
const char* TException::GetDescription() const
{
  return Description;
}

// ------------------------------------------------------------------------------------------------
void TException::PrintToFile(const char* fileName) const
{
  TOutputMessage::PrintMessageToFile("EXCEPTION in file : " + toString(File) +
    ", line : " + toString(Line) + ", function : " + toString(Function) +
    "\nDESCRIPTION: " + toString(Description) + "\n", "", -1, fileName);
}

// ------------------------------------------------------------------------------------------------
void TException::PrintToConsole() const
{
  print << "EXCEPTION in file : " + toString(File) + ", line : " +
    toString(Line) + ", function : " + toString(Function) +
    "\nDESCRIPTION: " + toString(Description) + "\n";
}

// ------------------------------------------------------------------------------------------------
void TException::Print(const char* fileName) const
{
  TOutputMessage::PrintImportantMessage("EXCEPTION in file : " + toString(File) +
    ", line : " + toString(Line) + ", function : " + toString(Function) +
    "\nDESCRIPTION: " + toString(Description) + "\n", "", -1, fileName);
}

// ------------------------------------------------------------------------------------------------
void Unexpected()
{
  printf("\nUNEXPECTED EXCEPTION !!!");
  throw 0;
}

// ------------------------------------------------------------------------------------------------
void Terminate()
{
  printf("\nUNEXPECTED EXCEPTION !!!");
  abort();
}
// - end of file ----------------------------------------------------------------------------------
