git submodule update --init --recursive
set SCRIPTPATH=%~dp0
cd %SCRIPTPATH%\..\
if not exist _buildMP mkdir _buildMP
cd _buildMP
cmake -DBUILD_TESTS=ON -DUSE_OPENGL=OFF ..
cd ..
pause