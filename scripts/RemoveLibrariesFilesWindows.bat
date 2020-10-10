@echo OFF

set SCRIPTPATH=%~dp0

for /r %SCRIPTPATH%\..\assets %%a in (*.dll) do del %%a
for /r %SCRIPTPATH%\..\assets %%a in (*.pdb) do del %%a
for /r %SCRIPTPATH%\..\assets %%a in (*.ilk) do del %%a