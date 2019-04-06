


set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


set CMAKE_BUILD_TYPE=Debug
set BUILD_DIR=Intermediate\%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%

cd %BUILD_DIR%

cmake --build . --parallel --target install --config Debug
rem  -- /p:Configuration=Debug

set CMAKE_BUILD_TYPE=Release

cmake --build . --parallel --target install --config Release
rem -- /p:Configuration=Release




pause
