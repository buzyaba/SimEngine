#define _CRT_SECURE_NO_WARNINGS

#include "Core/Parameters.h"

#include "../lib/pugixml/include/pugixml.hpp"

#include <iostream>
#include <string>
#include <string.h>

#ifdef WIN32
#include <Windows.h>
#else
#include <dirent.h>
#endif;


TParameters GlobalParameters;

void TParameters::DefaultParameters()
{
#ifdef USE_OpenGL
  cwd = Renderer::getCWD();
  auto c_cwd = cwd;
  std::transform(c_cwd.begin(), c_cwd.end(), c_cwd.begin(), toupper);
  size_t i = c_cwd.find("SIMENGINE");

  _window = new FirstPersonView(800, 600, "Smart House");;
  xmlEnvironmentScriptName = cwd.substr(0, i + 9) + "/ConfigFiles/default_task_3/conf.xml";
  xmlMainSetConfigurationFile = cwd.substr(0, i + 9) + "/ConfigFiles/default_task_3/Room.xml";
#else
  xmlEnvironmentScriptName = "";
  xmlMainSetConfigurationFile = "";
#endif

  xmlCurrentConfiguration = "";
  //objectOfObservationDllsFile;
  //
  //smartThingDllsFile;
  //
  //staticObjectDllsFile;

  std::string managementProgramDllFile = "";

  type = -1;
  millisecondsInTimeStep = 1000;
  timeAcceleration = 0.0;
  maxStep = 1000; ////60*60*24*30;//~месяц
}

void TParameters::ParseString(std::string& str, std::vector<std::string>& tt)
{
  char* s = new char[str.length() + 1];
  int l = 0;
  strcpy(s, str.c_str());

  char* pp = strtok(s, " ");

  double t = 0;
  while (pp != 0)
  {
    tt.push_back(pp);
    pp = strtok(NULL, " ");
    l++;
  }

  delete[] s;
}

void TParameters::LoadXML()
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(xmlCurrentConfiguration.c_str());
  if (result.status != pugi::status_ok)
    return;
  pugi::xml_node config = doc.child("config");
  std::vector<unsigned long int> startTime;
  std::vector<unsigned long int> endTime;

  for (pugi::xml_node iter = config.first_child(); iter != 0; iter = iter.next_sibling())
  {
    std::string name = iter.name();
    std::string value = iter.child_value();

    if (name == "xmlEnvironmentScriptName")
    {
      if (value != "")
      {
        if (value.find(":") != std::string::npos)
          xmlEnvironmentScriptName = value; //
        else
          xmlEnvironmentScriptName = dirConfigFile + "\\" + value;
      }
    }
    else if (name == "xmlMainSetConfigurationFile")
    {
      if (value != "")
      {
        if (value.find(":") != std::string::npos)
          xmlMainSetConfigurationFile = value; //
        else
          xmlMainSetConfigurationFile = dirConfigFile + "\\" + value;
      }
    }
    else if (name == "objectOfObservationDllsFile")
    {
      if (value != "")
      {
        ParseString(value, objectOfObservationDllsFile);
      }
      for (auto& v : objectOfObservationDllsFile)
        problemManager.LoadProblemLibrary(v, TProblemManager::OBJECT_OF_OBSERVATION);
    }
    else if (name == "smartThingDllsFile")
    {
      if (value != "")
      {
        ParseString(value, smartThingDllsFile);
      }
      for (auto& v : smartThingDllsFile)
        problemManager.LoadProblemLibrary(v, TProblemManager::SMART_THING);
    }
    else if (name == "staticObjectDllsFile")
    {
      if (value != "")
      {
        ParseString(value, staticObjectDllsFile);
      }
      for (auto& v: staticObjectDllsFile)
        problemManager.LoadProblemLibrary(v, TProblemManager::STATIC_OBJECT);
    }
    else if (name == "managementProgramDllFile")
    {
      managementProgramDllFile = value;
      problemManager.LoadProblemLibrary(managementProgramDllFile, TProblemManager::MANAGEMENT_PROGRAM);
    }
    else if (name == "type")
    {
      sscanf(value.c_str(), "%d", &type);
    }
    else if (name == "millisecondsInTimeStep")
    {
      sscanf(value.c_str(), "%d", &millisecondsInTimeStep);
    }
    else if (name == "timeAcceleration")
    {
      sscanf(value.c_str(), "%lf", &timeAcceleration);
    }
    else if (name == "maxStep")
    {
      sscanf(value.c_str(), "%d", &maxStep);
    }
  }
}

TParameters::TParameters(int argc, char** argv)
{
  LoadConsoleParameters(argc, argv);
}

void TParameters::LoadConsoleParameters(int argc, char** argv)
{
  if (argc == -1)
  {
    //DefaultParameters();
  }
  else if (argc >= 1)
  {
    exeFile = argv[0];
    std::cout << "Start program " << exeFile << std::endl;

    if (argc == 1)
    {
      dirConfigFile = "";
      for (size_t i = exeFile.length() - 1; i > 0; i--)
      {
        if (exeFile[i] == '\\')
        {
          for (unsigned int j = 0; j <= i; j++)
            dirConfigFile += exeFile[j];
          break;
        }
      }
      std::cout << "AAA\n";
      dirConfigFile += "../../../ConfigFiles";

      ConsoleInterface();
    }
    else
    {
      xmlCurrentConfiguration = argv[1];

      dirConfigFile = "";
      for (size_t i = xmlCurrentConfiguration.length() - 1; i > 0; i--)
      {
        if (xmlCurrentConfiguration[i] == '\\')
        {
          for (unsigned int j = 0; j < i; j++)
            dirConfigFile += xmlCurrentConfiguration[j];
          break;
        }
      }

      LoadXML();
      std::cout << "\n\n" << Print() << "\n" << std::endl;
    }
  }
}

std::string TParameters::Print()
{
  std::string result = "";
  result += "int type =\t" + std::to_string(type) + "\n";
  /// Имя файла с текущей конфигурацией программы
  result += "std::string xmlCurrentConfiguration = \t" + xmlCurrentConfiguration + "\n";
  /// Имя файла с расписанием для EnvironmentScript
  result += "std::string xmlEnvironmentScriptName = \t" + xmlEnvironmentScriptName + "\n";
  /// Имя файла с конфигурацией сцены (описываются все объекты, умные вещи и прочее)
  result += "std::string xmlMainSetConfigurationFile = \t" + xmlMainSetConfigurationFile + "\n";

  /// Имена dll с наблюдаемыми объектами
  result += "std::vector<std::string> objectOfObservationDllsFile = \t";
  for (auto& name : objectOfObservationDllsFile)
  {
    result += name + "\t";
  }
  result += "\n";
  /// Имена dll с умными вещами
  result += "std::vector<std::string> smartThingDllsFile = \t";
  for (auto& name : smartThingDllsFile)
  {
    result += name + "\t";
  }
  result += "\n";
  /// Имена dll со статичными объектами
  result += "std::vector<std::string> staticObjectDllsFile = \t";
  for (auto& name : staticObjectDllsFile)
  {
    result += name + "\t";
  }
  result += "\n";
  /// Имя dll с упровляемой программой
  result += "std::string managementProgramDllFile = \t" + managementProgramDllFile + "\n";

  /// Кол-во миллисекунд в одном шаге
  result += "unsigned int millisecondsInTimeStep = \t" + std::to_string(millisecondsInTimeStep) + "\n";
  /* Ускорение времени программы,
  при = 0 программа работает с максимально возможной соростью,
  при = 1 за одну итерацию проходит millisecondsInTimeStep времени **/
  result += "double timeAcceleration = \t" + std::to_string(timeAcceleration) + "\n";
  /// Максимальное число итераций
  result += "unsigned long maxStep = \t" + std::to_string(maxStep) + "\n";
  return result;
}

void TParameters::ConsoleInterface()
{

  std::vector<std::string> configs;
#ifdef WIN32
  WIN32_FIND_DATA file_data;
  HANDLE h = FindFirstFile((dirConfigFile + "/*").c_str(), &file_data);
  if (h != INVALID_HANDLE_VALUE)
  {
    do
    {
      const std::string file_name = file_data.cFileName;
      const std::string full_file_name = dirConfigFile + "/" + file_name;
      if (full_file_name.find(".xml") != std::string::npos)
        configs.push_back(full_file_name);
    } while (FindNextFile(h, &file_data));
  }
#else

  //DIR* dir;
  //class dirent* ent;
  //class stat st;

  //dir = opendir(dirConfigFile);
  //while ((ent = readdir(dir)) != NULL) {
  //  const std::string file_name = ent->d_name;
  //  const std::string full_file_name = dirConfigFile + "/" + file_name;
  //  if (full_file_name.find(".xml") != std::string::npos)
  //    configs.push_back(full_file_name);
  //  configs.push_back(full_file_name);
  //}
  //closedir(dir);
#endif;


  std::cout << "1. Start default task 1" << std::endl;


  int j = 2;
  for (auto& configFileName : configs)
  {
    std::cout << std::to_string(j) << ". Load Task:\t" << configFileName << std::endl;
    j++;
  }
  int t = 1;
  if (j != 2)
    std::cin >> t;

  if (t < 1 || t >= j)
    throw "Error task numder";
  else if (t == 1)
    DefaultParameters();
  else
  {
    DefaultParameters();
    this->xmlCurrentConfiguration = configs[t - 2];
    LoadXML();
  }

  std::cout << "\n\n" << Print() << "\n" << std::endl;
}
