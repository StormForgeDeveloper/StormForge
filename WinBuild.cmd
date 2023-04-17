

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64
set OPENSSL_DIR=3rdParties\src\openssl
set SF_DIR=%~dp0
set BUILD_DIR_BASE=build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%


set CMAKE_BUILD_TYPE=Debug
set BUILD_DIR=%BUILD_DIR_BASE%%CMAKE_BUILD_TYPE%

cd %BUILD_DIR%

cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit


REM robocopy lib %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  /purge
REM robocopy bin %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  /purge
REM robocopy bin %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin\netcoreapp3.1  /purge
REM robocopy Engine\Src\SFCore\%CMAKE_BUILD_TYPE%\ %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb
REM robocopy Engine\Src\SFEngine\%CMAKE_BUILD_TYPE%\ %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  *.pdb
REM robocopy Engine\Src\Protocol\%CMAKE_BUILD_TYPE%\ %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb

REM rem copy openssl dlls
REM robocopy %~dp0\%OPENSSL_DIR%\buildWindows\openssl\bin %~dp0\%BUILD_DIR%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin *.dll *.pdb

cd ..\..


set CMAKE_BUILD_TYPE=Release
set BUILD_DIR=%BUILD_DIR_BASE%%CMAKE_BUILD_TYPE%

cd %BUILD_DIR%

cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit

cd ..\..

REM robocopy lib %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  
REM robocopy bin %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  
REM robocopy bin %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin\netcoreapp3.1  
REM robocopy bin %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin\net5.0-windows
REM robocopy bin %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin\publish  
REM robocopy Engine\Src\SFCore\%CMAKE_BUILD_TYPE%\ %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb
REM robocopy Engine\Src\SFEngine\%CMAKE_BUILD_TYPE%\ %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb
REM robocopy Engine\Src\Protocol\%CMAKE_BUILD_TYPE%\ %SF_DIR%\build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib *.pdb


REM rem copy openssl dlls
REM robocopy %~dp0\%OPENSSL_DIR%\buildWindows\openssl\bin %~dp0\%BUILD_DIR%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin *.dll *.pdb



cd %~dp0


:exit


if not "%1" == "nopause" pause


