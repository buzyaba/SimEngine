git submodule update --init --recursive
set SCRIPTPATH=%~dp0
cd %SCRIPTPATH%\..\
if not exist _build mkdir _build
cd _build
cmake ..
cd ..
pause