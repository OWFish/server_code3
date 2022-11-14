@echo off
mkdir VS_Proj
cd VS_Proj
cmake .. -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Debug
pause