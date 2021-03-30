

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


set BUILD_DIR=%CMAKE_SYSTEM_NAME%



set CMAKE_BUILD_TYPE=Debug
cd %BUILD_DIR%\%CMAKE_BUILD_TYPE%
cmake --build . --parallel --target install  -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit

REM robocopy ..\build\lib ..\%PROCESS_ARCHITECTUR%\lib\%CMAKE_BUILD_TYPE%  /purge
REM robocopy ..\build\bin ..\%PROCESS_ARCHITECTUR%\bin\%CMAKE_BUILD_TYPE%  /purge



set CMAKE_BUILD_TYPE=RelWithDebInfo
cd ..\%CMAKE_BUILD_TYPE%
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit

REM robocopy ..\build\include ..\%PROCESS_ARCHITECTUR%\include  /s /purge
REM robocopy ..\build\lib ..\%PROCESS_ARCHITECTUR%\lib\%CMAKE_BUILD_TYPE%  /purge
REM robocopy ..\build\bin ..\%PROCESS_ARCHITECTUR%\bin\%CMAKE_BUILD_TYPE%  /purge

cd %~dp0

:exit


if not "%1" == "nopause" pause


