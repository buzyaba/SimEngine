git submodule update --init --recursive
if not exist _buildMP mkdir _buildMP
cd _buildMP
cmake -Dglew-cmake_BUILD_SHARED=OFF -Dglew-cmake_BUILD_SINGLE_CONTEXT=OFF -DBUILD_TESTS=OFF -DBUILD_PLOTTER=OFF ..
cd ..
pause