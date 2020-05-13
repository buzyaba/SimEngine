git submodule update --init --recursive
if not exist _build mkdir _build
cd _build
cmake -Dglew-cmake_BUILD_SHARED=OFF -Dglew-cmake_BUILD_SINGLE_CONTEXT=OFF ..
cd ..
pause