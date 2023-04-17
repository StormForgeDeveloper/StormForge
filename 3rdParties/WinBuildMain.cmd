

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


set BUILD_DIR=%CMAKE_SYSTEM_NAME%



set CMAKE_BUILD_TYPE=Debug
cd %BUILD_DIR%\%CMAKE_BUILD_TYPE%
cmake --build . --parallel --target install  -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit



set CMAKE_BUILD_TYPE=Release
cd ..\%CMAKE_BUILD_TYPE%
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit




:exit


cd %~dp0

if not "%1" == "nopause" pause


