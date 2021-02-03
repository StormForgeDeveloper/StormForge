
set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64

call 3rdParties\FindVC.cmd

for %%I in (.) do set SF_FOLDER=%%~nxI



if not exist build%CMAKE_SYSTEM_NAME% mkdir build%CMAKE_SYSTEM_NAME%
set BUILD_DIR=build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%


if not exist %BUILD_DIR% mkdir %BUILD_DIR%


cd %BUILD_DIR%

cmake ../../ -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../build%CMAKE_SYSTEM_NAME%/%PROCESS_ARCHITECTUR%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% -DSF_FOLDER=%SF_FOLDER%


cd %~dp0

if not "%1" == "nopause" pause

