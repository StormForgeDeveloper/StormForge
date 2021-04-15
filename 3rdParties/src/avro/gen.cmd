

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64
set AVRO_PATH=avro-src-1.10.2

call ..\..\FindVC.cmd

if not exist %CMAKE_SYSTEM_NAME% mkdir %CMAKE_SYSTEM_NAME%
if not exist %CMAKE_SYSTEM_NAME%\Debug mkdir %CMAKE_SYSTEM_NAME%\Debug
if not exist %CMAKE_SYSTEM_NAME%\RelWithDebInfo mkdir %CMAKE_SYSTEM_NAME%\RelWithDebInfo

cd %CMAKE_SYSTEM_NAME%


set CONFIGURATION=Debug
cd %CONFIGURATION%
cmake ../../%AVRO_PATH%/lang/c -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% ^
	-DZLIB_ROOT=../../../zlib/zlib-1.2.8 -DZLIB_LIBRARY=zlib ^
	-DLZMA_INCLUDE_DIRS=../../../../lzma/xz-5.2.5/src/liblzma/api ^
	-DCMAKE_APPBUNDLE_PATH=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%;../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%lib;../../lzma/xz-5.2.5/src

cd ..

set CONFIGURATION=RelWithDebInfo
cd %CONFIGURATION%
cmake ../../%AVRO_PATH%/lang/c -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% ^
	-DZLIB_ROOT=../../../zlib/zlib-1.2.8 -DZLIB_LIBRARY=zlib ^
	-DLZMA_INCLUDE_DIRS=../../../../lzma/xz-5.2.5/src/liblzma/api ^
	-DCMAKE_APPBUNDLE_PATH=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%;../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%lib;../../lzma/xz-5.2.5/src

cd ..
cd ..
