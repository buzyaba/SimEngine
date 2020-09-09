#include "Core/common.h"
#include <algorithm>
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

unsigned long int currentTime;
unsigned long int currentStep;

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
