
set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64

call FindVC.cmd

if not exist %CMAKE_SYSTEM_NAME% mkdir %CMAKE_SYSTEM_NAME%
set BUILD_DIR=%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%


if not exist %BUILD_DIR% mkdir %BUILD_DIR%


cd %BUILD_DIR%

cmake ../../ -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../%CMAKE_SYSTEM_NAME%/build


cd %~dp0

if not "%1" == "nopause" pause

