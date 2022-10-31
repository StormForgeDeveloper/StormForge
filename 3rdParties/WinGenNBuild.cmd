
@echo on

call FindVC.cmd


rem build helper tools
cmd /c "cd tool & buildTool.cmd"


set NASM_DIR=src\nasm
set OPENSSL_DIR=src\openssl
set MYSQL_DIR=src\mysql

if not exist "Windows\Common\lib\libnasm.lib" (
	echo Building NASM
    cmd /c "cd %NASM_DIR% & buildNASM.cmd"
	
)

if not exist "Windows\Common\lib\libcrypto.lib" (
	echo Building OpenSSL
	cmd /c "cd %OPENSSL_DIR% & config1.1_Winx64.cmd"
	cmd /c "cd %OPENSSL_DIR% & build1.1_Winx64.cmd"
)




rem build MYSQL client lib => we are using precompiled version on window now
if not exist "Windows\RelWithDebInfo\lib\mysqlcppconn8.lib" (
	rem cmd /c "cd %MYSQL_DIR% & WinGen.cmd"
	rem cmd /c "cd %MYSQL_DIR% & WinBuild.cmd"
	cmd /c "cd %MYSQL_DIR% & download.cmd"
)

rem Build main part
cmd /c "call WinGenMain.cmd nopause"
cmd /c "call WinBuildMain.cmd nopause"

rem build MongoC client lib
cmd /c "cd src\mongoc & gen.cmd"
cmd /c "cd src\mongoc & build.cmd"

rem build jansson
cmd /c "cd src/jansson & gen.cmd"
cmd /c "cd src/jansson & build.cmd"

rem build avro
cmd /c "cd src/avro & gen.cmd"
cmd /c "cd src/avro & build.cmd"

rem build libevent
cmd /c "cd src/libevent & gen.cmd"
cmd /c "cd src/libevent & build.cmd"

rem build libevent
cmd /c "cd src/libuv & gen.cmd"
cmd /c "cd src/libuv & build.cmd"

rem build libwebsocket
cmd /c "cd src/ws & gen.cmd"
cmd /c "cd src/ws & build.cmd"


if not "%1" == "nopause" pause

