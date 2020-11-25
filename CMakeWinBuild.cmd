

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


set BUILD_DIR=build%CMAKE_SYSTEM_NAME%


for %%I in (.) do set SF_FOLDER=%%~nxI


set CMAKE_BUILD_TYPE=Debug
cd %BUILD_DIR%\%PROCESS_ARCHITECTUR%
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit

robocopy lib ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  /purge
robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  /purge
robocopy Engine\Src\SFCore\%CMAKE_BUILD_TYPE%\ ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb
robocopy Engine\Src\SFEngine\%CMAKE_BUILD_TYPE%\ ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  *.pdb
robocopy Engine\Src\Protocol\%CMAKE_BUILD_TYPE%\ ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb



set CMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit

robocopy lib ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  /purge
robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  /purge
robocopy Engine\Src\SFCore\%CMAKE_BUILD_TYPE%\ ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb
robocopy Engine\Src\SFEngine\%CMAKE_BUILD_TYPE%\ ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb
robocopy Engine\Src\Protocol\%CMAKE_BUILD_TYPE%\ ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb


cd %~dp0

:exit


if not "%1" == "nopause" pause


