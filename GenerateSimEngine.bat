git submodule update --init --recursive
if not exist _build mkdir _build
cd _build
cmake -DBUILD_TESTS=ON -DUSE_OPENGL=OFF ..
cmake --build . --config RELEASE
bin\RELEASE\SimEngineLauncher.exe
pause