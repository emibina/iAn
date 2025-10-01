
@echo off
if not exist build mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
echo.
echo Build complete! Executables are in build/bin/Release/
echo.
echo To test the tools:
echo   tool1.exe --help
echo   tool2.exe --help
echo   tool1.exe | tool2.exe --uppercase
pause
