


set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64

if not exist Intermediate mkdir Intermediate
if not exist Intermediate\%CMAKE_SYSTEM_NAME% mkdir Intermediate\%CMAKE_SYSTEM_NAME%


set BUILD_DIR=Intermediate\%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

cd %BUILD_DIR%


set CMAKE_BUILD_TYPE=Release
cmake ../../../ -G "Visual Studio 15 2017" -A %PROCESS_ARCHITECTUR%





pause


