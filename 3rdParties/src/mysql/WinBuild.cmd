


set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


set BUILD_DIR=build%CMAKE_SYSTEM_NAME%
cd %BUILD_DIR%\%PROCESS_ARCHITECTUR%



set CMAKE_BUILD_TYPE=Debug
cmake --build . --parallel --target install  -- /p:Configuration=%CMAKE_BUILD_TYPE% 



set CMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . --parallel --target install  -- /p:Configuration=%CMAKE_BUILD_TYPE%



cd ../../
