git submodule update --init --recursive
if not exist _buildMP mkdir _buildMP
cd _buildMP
cmake -DBUILD_TESTS=ON -DUSE_OPENGL=OFF ..
cd ..
pause