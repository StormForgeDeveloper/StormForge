
cd %~d0
cd %~dp0

call 3rdParties\FindVC.cmd

set NASM_DIR=3rdParties\src\nasm
cmd /c "cd %NASM_DIR% & buildNASM.cmd"

set OPENSSL_DIR=3rdParties\src\openssl
cmd /c "cd %OPENSSL_DIR% & config1.1_Winx64.cmd"

set MYSQL_DIR=3rdParties\src\mysql
cmd /c "cd %MYSQL_DIR% & WinGen.cmd"



pause
