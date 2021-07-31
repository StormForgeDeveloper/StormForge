

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64
set BUILD_DIR=build%CMAKE_SYSTEM_NAME%


cd %BUILD_DIR%


rem set CMAKE_BUILD_TYPE=Debug

REM cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

REM if ERRORLEVEL 1 goto exit

REM REM robocopy lib ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  /purge
REM REM robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  /purge
REM REM robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin\netcoreapp3.1  /purge



set CMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit

REM robocopy lib ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  
REM robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  
REM robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin\netcoreapp3.1  



cd %~dp0


:exit


if not "%1" == "nopause" pause


