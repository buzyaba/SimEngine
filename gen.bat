git submodule update --init --recursive
set START_DIR=%cd%
set ROOT_DIR=%~dp0\..
cd %ROOT_DIR%
if not exist _build mkdir _build
cd _build
cmake ..\SimEngine\
cd %START_DIR%
pause