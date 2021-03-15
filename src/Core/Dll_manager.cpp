#include "Core/Dll_manager.h"
#include <iostream>
#ifdef WIN32
    #include <Windows.h>
#else
    #include <dirent.h>
#endif

#ifdef WIN32
  std::vector<HINSTANCE> Dll_Manager::mLibHandles{};
  #else
    std::vector<void *> Dll_Manager::mLibHandles{};
  #endif


std::string Dll_Manager::findDLLPath(const std::string& path) {
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
void Dll_Manager::FreeDllManager()
{
  for (auto& handle : mLibHandles) {
#ifdef WIN32
  FreeLibrary(handle);
#else
  dlclose(handle);
#endif
  handle = NULL;
  }
}

// ------------------------------------------------------------------------------------------------