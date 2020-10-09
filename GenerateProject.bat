git submodule update --init --recursive
if not exist _build mkdir _build
cd _build
cmake ..
cd ..
pause