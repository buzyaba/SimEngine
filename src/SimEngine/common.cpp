#include "SimEngine/common.h"
#include <algorithm>
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

std::size_t currentTime;
std::size_t currentStep;

std::string getCWD() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

std::string getPath(const std::string path) {
    auto cwd = getCWD();
    std::transform(cwd.begin(), cwd.end(), cwd.begin(), toupper);
    auto i = cwd.find("SIMENGINE");
    return getCWD().substr(0, i+9) + path;
}



void TExternalActionSchedule::ParseString(std::string str, std::vector<double>& tt)
{
  size_t intervalCount = tt.size();
  char* s = new char[str.length() + 1];
  int l = 0;
  strcpy(s, str.c_str());

  char* pp = strtok(s, "_");

  double t = 0;
  while ((pp != 0) && (l < intervalCount))
  {
    sscanf(pp, "%lf", &t);
    tt[l] = t;
    pp = strtok(NULL, "_");
    l++;
  }

  delete[] s;
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

void ParseString(std::string str, std::vector<double> &tt) {
  char *s = new char[str.length() + 1];
  int l = 0;
  strcpy(s, str.c_str());

  char *pp = strtok(s, " ");

  double t = 0;
  while (pp != 0) {
    sscanf(pp, "%lf", &t);
    tt.push_back(t);
    pp = strtok(NULL, " ");
    l++;
  }

  delete[] s;
}