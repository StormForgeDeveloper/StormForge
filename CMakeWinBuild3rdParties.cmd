

set OPENSSL_DIR=3rdParties\src\openssl
cmd /c "cd %OPENSSL_DIR% & build1.1_Winx64.cmd"


set MYSQL_DIR=3rdParties\src\mysql
cmd /c "cd %MYSQL_DIR% & WinBuild.cmd"

