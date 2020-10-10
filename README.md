[![Build Status](https://travis-ci.org/buzyaba/SimEngine.svg?branch=master)](https://travis-ci.org/buzyaba/SimEngine) 
[![Build Status](https://ci.appveyor.com/api/projects/status/github/buzyaba/simengine?svg=true)](https://ci.appveyor.com/project/buzyaba/simengine)

# SimEngine
## To clone the project:
```
  git clone --recursive https://github.com/buzyaba/SimEngine.git
```

## To configure on windows:
Go to scripts and run:
 - GenerateMinimumProject.bat to get `.sln` without graphics support
 - GenerateProject.bat to get `.sln` with graphics support

## Build the project with CMake
1) Configure the build: `Makefile`, `.sln`, etc.
  ```
  mkdir build && cd build
  cmake ..
  ```
2) Build the project:
  ```
  cmake --build .
  ```
3) Run `<project's folder>/build/bin`

## To remove DLL's in assets folder:
Go to scripts and run **RemoveLibrariesFilesWindows.bat** or **RemoveLibrariesFilesLinux.sh** depending on the system.
##  Required dependencies for building on Linux
  ```
  sudo apt install xorg-dev
  sudo apt install libgl1-mesa-dev
  ```
