

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64
set SRC_BASE=libevent-2.1.12-stable
set SRC_PATH=../../../src/libevent/%SRC_BASE%
set INTERMEDIATE_DIR=..\..\%CMAKE_SYSTEM_NAME%\libevent

if not exist %SRC_PATH%.tar.gz (
	call download.cmd
)

call ..\..\FindVC.cmd



if not exist %INTERMEDIATE_DIR% mkdir %INTERMEDIATE_DIR%
if not exist %INTERMEDIATE_DIR%\Debug mkdir %INTERMEDIATE_DIR%\Debug
if not exist %INTERMEDIATE_DIR%\RelWithDebInfo mkdir %INTERMEDIATE_DIR%\RelWithDebInfo

cd %INTERMEDIATE_DIR%


set CONFIGURATION=Debug
cd %CONFIGURATION%
cmake %SRC_PATH% -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% -DCMAKE_BUILD_TYPE=%CONFIGURATION% ^
	-DEVENT__DISABLE_TESTS=1 -DEVENT__DISABLE_OPENSSL=1 -DEVENT__LIBRARY_TYPE=STATIC


cd ..

set CONFIGURATION=RelWithDebInfo
cd %CONFIGURATION%
cmake %SRC_PATH% -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% -DCMAKE_BUILD_TYPE=%CONFIGURATION% ^
	-DEVENT__DISABLE_TESTS=1 -DEVENT__DISABLE_OPENSSL=1 -DEVENT__LIBRARY_TYPE=STATIC



cd %~dp0
