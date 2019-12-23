

set OPENSSL_DIR=3rdParties\src\openssl
cmd /c "cd %OPENSSL_DIR% & build1.1_Winx64.cmd"


set MYSQL_DIR=3rdParties\src\mysql
cmd /c "cd %MYSQL_DIR% & WinBuild.cmd"



set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


set BUILD_DIR=build%CMAKE_SYSTEM_NAME%



set CMAKE_BUILD_TYPE=Debug
cd %BUILD_DIR%\%PROCESS_ARCHITECTUR%
cmake --build . --parallel --target install  -- /p:Configuration=%CMAKE_BUILD_TYPE% 


robocopy lib ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  /purge /move
robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  /purge /move



set CMAKE_BUILD_TYPE=Release
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 


robocopy lib ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  /purge /move
robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  /purge /move





pause
