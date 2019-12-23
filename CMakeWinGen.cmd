
set OPENSSL_DIR=3rdParties\src\openssl
cmd /c "cd %OPENSSL_DIR% & config1.1_Winx64.cmd"

set MYSQL_DIR=3rdParties\src\mysql
cmd /c "cd %MYSQL_DIR% & WinGen.cmd"


set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


if not exist build%CMAKE_SYSTEM_NAME% mkdir build%CMAKE_SYSTEM_NAME%
set BUILD_DIR=build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%


if not exist %BUILD_DIR% mkdir %BUILD_DIR%


cd %BUILD_DIR%

cmake ../../ -G "Visual Studio 15 2017" -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../build%CMAKE_SYSTEM_NAME%/%PROCESS_ARCHITECTUR% 




pause


