


set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


set BUILD_DIR=build%CMAKE_SYSTEM_NAME%



set CMAKE_BUILD_TYPE=Debug
cd %BUILD_DIR%\%PROCESS_ARCHITECTUR%
cmake --build . --parallel --target install  -- /p:Configuration=Debug

robocopy lib ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  /purge
robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  /purge



set CMAKE_BUILD_TYPE=Release
cd ../%PROCESS_ARCHITECTUR%
cmake --build . --parallel --target install -- /p:Configuration=Release

robocopy lib ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\lib  /purge
robocopy bin ..\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%\bin  /purge





pause
