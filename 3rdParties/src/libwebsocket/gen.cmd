

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64
set SRC_BASE=libwebsockets


if not exist %SRC_BASE%  call download.cmd


call ..\..\FindVC.cmd

if not exist %CMAKE_SYSTEM_NAME% mkdir %CMAKE_SYSTEM_NAME%
if not exist %CMAKE_SYSTEM_NAME%\Debug mkdir %CMAKE_SYSTEM_NAME%\Debug
if not exist %CMAKE_SYSTEM_NAME%\RelWithDebInfo mkdir %CMAKE_SYSTEM_NAME%\RelWithDebInfo

cd %CMAKE_SYSTEM_NAME%


set CONFIGURATION=Debug
cd %CONFIGURATION%
cmake ../../%SRC_BASE% -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% ^
	-DLWS_WITH_ZLIB=1 -DLWS_WITH_LIBEVENT=1 -DLWS_WITH_SHARED=0 ^
	-DLWS_WITH_HTTP2=1 -DLWS_OPENSSL_INCLUDE_DIRS=../../../openssl/buildWindows/openssl/include ^
	-DLWS_OPENSSL_LIBRARIES="../../../openssl/buildWindows/openssl/lib/libssl.lib;../../../openssl/buildWindows/openssl/lib/libcrypto.lib"

cd ..

set CONFIGURATION=RelWithDebInfo
cd %CONFIGURATION%
cmake ../../%SRC_BASE% -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% ^
	-DLWS_WITH_ZLIB=1 -DLWS_WITH_LIBEVENT=1 -DLWS_WITH_SHARED=0 ^
	-DLWS_WITH_HTTP2=1 -DLWS_OPENSSL_INCLUDE_DIRS=../../../openssl/buildWindows/openssl/include ^
	-DLWS_OPENSSL_LIBRARIES="../../../openssl/buildWindows/openssl/lib/libssl.lib;../../../openssl/buildWindows/openssl/lib/libcrypto.lib"

cd ..
cd ..
