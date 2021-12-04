
call FindVC.cmd



rem build helper tools
cd tool
msbuild -m BuildTool.sln /property:Configuration=Release /p:Platform="Any CPU"
cd ..

set NASM_DIR=src\nasm
set OPENSSL_DIR=src\openssl
set MYSQL_DIR=src\mysql

if not exist "NasmBuild.txt" (
	echo Building NASM
	echo %date%-%time% > NasmBuild.txt
    cmd /c "cd %NASM_DIR% & buildNASM.cmd"
	
)

if not exist "OpenSSLBuild.txt" (
	echo Building OpenSSL
	echo %date%-%time% > OpenSSLBuild.txt
	rem build SSL
	cmd /c "cd %OPENSSL_DIR% & config1.1_Winx64.cmd"
	cmd /c "cd %OPENSSL_DIR% & build1.1_Winx64.cmd"
)




rem build MYSQL client lib => we are using precompiled version on window now
rem cmd /c "cd %MYSQL_DIR% & WinGen.cmd"
rem cmd /c "cd %MYSQL_DIR% & WinBuild.cmd"
cmd /c "cd %MYSQL_DIR% & download.cmd"


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


if not "%1" == "nopause" pause

