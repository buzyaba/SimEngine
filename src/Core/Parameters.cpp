#define _CRT_SECURE_NO_WARNINGS

#include "Core/Parameters.h"

#include "../lib/pugixml/include/pugixml.hpp"

#include <iostream>
#include <string>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#ifdef WIN32
#include <Windows.h>
#else
#include <dirent.h>
#endif

TParameters GlobalParameters;

void TParameters::LoadXML()
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(xmlCurrentConfiguration.c_str());
  if (result.status != pugi::status_ok)
    return;
  pugi::xml_node config = doc.child("config");
  std::vector<std::size_t> startTime;
  std::vector<std::size_t> endTime;

  for (pugi::xml_node iter = config.first_child(); iter != 0; iter = iter.next_sibling())
  {
    std::string name = iter.name();
    std::string value = iter.child_value();

    if (name == "xmlExternalActionScheduleName")
    {
      if (value != "")
      {
        if (value.find(":") != std::string::npos)
          xmlExternalActionScheduleName = value; //
        else
          xmlExternalActionScheduleName = dirConfigFile + "/" + value;
      }
    }
    else if (name == "xmlSmartThingScheduleName")
    {
      if (value != "")
      {
        if (value.find(":") != std::string::npos)
          xmlSmartThingScheduleName = value; //
        else
          xmlSmartThingScheduleName = dirConfigFile + "/" + value;
      }
    }
    else if (name == "xmlMainSetConfigurationFile")
    {
      if (value != "")
      {
        if (value.find(":") != std::string::npos)
          xmlMainSetConfigurationFile = value; //
        else
          xmlMainSetConfigurationFile = dirConfigFile + "/" + value;
      }
    }
    
    else if (name == "managementProgramDllFile")
    {
      if (value != "")
      {
        managementProgramDllFile = getPath("/assets/management_programs/" + value);
        managementProgram = Dll_Manager::LoadDLLObject<MANAGEMENT_PROGRAM>(Dll_Manager::findDLLPath(managementProgramDllFile));
      }
    }
    else if (name == "type")
    {
      sscanf(value.c_str(), "%d", &type);
    }
    else if (name == "millisecondsInTimeStep")
    {
      sscanf(value.c_str(), "%zu", &millisecondsInTimeStep);
    }
    else if (name == "timeAcceleration")
    {
      sscanf(value.c_str(), "%lf", &timeAcceleration);
    }
    else if (name == "maxStep")
    {
      sscanf(value.c_str(), "%zu", &maxStep);
    }
  }
}

TParameters::TParameters(int argc, char** argv)
{
  char buff[FILENAME_MAX]; //create string buffer to hold path
  GetCurrentDir(buff, FILENAME_MAX);
  cwd = buff;
}

void TParameters::LoadConsoleParameters(int argc, char** argv)
{
  std::cout << "Start program " << cwd << std::endl;

  if (argc == 1)
  {
    auto c_cwd = cwd;
    std::transform(c_cwd.begin(), c_cwd.end(), c_cwd.begin(), toupper);
    size_t i = c_cwd.find("SIMENGINE");
    dirConfigFile = cwd.substr(0, i + 9) + "/ConfigFiles";
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

std::string TParameters::Print()
{
  std::string result = "";
  result += "int type =\t" + std::to_string(type) + "\n";
  /// Имя файла с текущей конфигурацией программы
  result += "std::string xmlCurrentConfiguration = \t" + xmlCurrentConfiguration + "\n";
  /// Имя файла с расписанием для ExternalActionSchedule
  result += "std::string xmlExternalActionScheduleName = \t" + xmlExternalActionScheduleName + "\n";
  /// Имя файла с расписанием для SmartThingSchedule
  result += "std::string xmlSmartThingScheduleName = \t" + xmlSmartThingScheduleName + "\n";
  /// Имя файла с конфигурацией сцены (описываются все объекты, умные вещи и прочее)
  result += "std::string xmlMainSetConfigurationFile = \t" + xmlMainSetConfigurationFile + "\n";

  /// Имя dll с упровляемой программой
  result += "std::string managementProgramDllFile = \t" + managementProgramDllFile + "\n";

  /// Кол-во миллисекунд в одном шаге
  result += "unsigned int millisecondsInTimeStep = \t" + std::to_string(millisecondsInTimeStep) + "\n";
  /* Ускорение времени программы,
  при = 0 программа работает с максимально возможной соростью,
  при = 1 за одну итерацию проходит millisecondsInTimeStep времени **/
  result += "double timeAcceleration = \t" + std::to_string(timeAcceleration) + "\n";
  /// Максимальное число итераций
  result += "std::size_t maxStep = \t" + std::to_string(maxStep) + "\n";

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
  DIR* dir;
  dirent* ent;
  const char *dirConfig = dirConfigFile.c_str();
  dir = opendir(dirConfig);
  while ((ent = readdir(dir)) != NULL) {
   const std::string file_name = ent->d_name;
   const std::string full_file_name = dirConfigFile + "/" + file_name;
   if (full_file_name.find(".xml") != std::string::npos)
     configs.push_back(full_file_name);
  }
  closedir(dir);
#endif

  std::sort(configs.begin(), configs.end());

  int j = 1;
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
  else
  {
    std::cout<<"CONFIGS "<<configs[t - 1];
    this->xmlCurrentConfiguration = configs[t - 1];
    LoadXML();
  }

  std::cout << "\n\n" << Print() << "\n" << std::endl;
}
