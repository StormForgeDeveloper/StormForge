


set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


if not exist build%CMAKE_SYSTEM_NAME% mkdir build%CMAKE_SYSTEM_NAME%
set BUILD_DIR=build%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%


if not exist %BUILD_DIR% mkdir %BUILD_DIR%


cd %BUILD_DIR%

cmake ../../ -G "Visual Studio 15 2017" -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../build%CMAKE_SYSTEM_NAME%/%PROCESS_ARCHITECTUR% 


robocopy ..\..\3rdParties\src\mysql\mysql-connector-c++-8.0.18-winx64\lib64\vs14 ..\%PROCESS_ARCHITECTUR%Debug\lib
robocopy ..\..\3rdParties\src\mysql\mysql-connector-c++-8.0.18-winx64\lib64 ..\%PROCESS_ARCHITECTUR%Debug\bin

robocopy ..\..\3rdParties\src\mysql\mysql-connector-c++-8.0.18-winx64\lib64\vs14 ..\%PROCESS_ARCHITECTUR%Release\lib
robocopy ..\..\3rdParties\src\mysql\mysql-connector-c++-8.0.18-winx64\lib64 ..\%PROCESS_ARCHITECTUR%Release\bin



pause


