

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64
set SRC_PATH=../../../src/avro/avro-src-1.10.2
set INTERMEDIATE_DIR=..\..\%CMAKE_SYSTEM_NAME%\avro

call ..\..\FindVC.cmd

if not exist %INTERMEDIATE_DIR% mkdir %INTERMEDIATE_DIR%
if not exist %INTERMEDIATE_DIR%\Debug mkdir %INTERMEDIATE_DIR%\Debug
if not exist %INTERMEDIATE_DIR%\RelWithDebInfo mkdir %INTERMEDIATE_DIR%\RelWithDebInfo

cd %INTERMEDIATE_DIR%


set CONFIGURATION=Debug
cd %CONFIGURATION%
cmake %SRC_PATH%/lang/c -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% ^
	-DZLIB_ROOT=../../%CONFIGURATION%/ -DZLIB_LIBRARY=zlib ^
	-DLZMA_INCLUDE_DIRS=../../../../lzma/xz-5.2.5/src/liblzma/api ^
	-DCMAKE_APPBUNDLE_PATH=../../%CONFIGURATION%;../../%CONFIGURATION%lib;../../../../lzma/xz-5.2.5/src

cd ..

set CONFIGURATION=RelWithDebInfo
cd %CONFIGURATION%
cmake %SRC_PATH%/lang/c -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% ^
	-DZLIB_ROOT=../../%CONFIGURATION%/ -DZLIB_LIBRARY=zlib ^
	-DLZMA_INCLUDE_DIRS=../../../../lzma/xz-5.2.5/src/liblzma/api ^
	-DCMAKE_APPBUNDLE_PATH=../../%CONFIGURATION%;../../%CONFIGURATION%lib;../../../../lzma/xz-5.2.5/src

cd %~dp0
