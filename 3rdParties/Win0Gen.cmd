

call FindVC.cmd

set NASM_DIR=src\nasm
set OPENSSL_DIR=src\openssl
set MYSQL_DIR=src\mysql
set MONGOC_DIR=src\mongoc


rem build helper tools
cd tool
msbuild -m BuildTool.sln /property:Configuration=Release /p:Platform="Any CPU"
cd ..

rem build nasm first. openssl need it
cmd /c "cd %NASM_DIR% & buildNASM.cmd"

rem configure SSL
cmd /c "cd %OPENSSL_DIR% & config1.1_Winx64.cmd"

rem configure MYSQL client lib
cmd /c "cd %MYSQL_DIR% & WinGen.cmd"

rem configure MongoC client lib
cmd /c "cd %MONGOC_DIR% & gen.cmd"

rem configure jansson
cmd /c "cd src/jansson & gen.cmd"


cd %~dp0

if not "%1" == "nopause" pause

