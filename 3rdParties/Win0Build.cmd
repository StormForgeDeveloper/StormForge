

set NASM_DIR=src\nasm
set OPENSSL_DIR=src\openssl
set MYSQL_DIR=src\mysql

cmd /c "cd %OPENSSL_DIR% & build1.1_Winx64.cmd"
cmd /c "cd %MYSQL_DIR% & WinBuild.cmd"

cd %~dp0

:exit


if not "%1" == "nopause" pause


