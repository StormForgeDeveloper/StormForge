

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64
set INTERMEDIATE_DIR=..\..\%CMAKE_SYSTEM_NAME%\libws


call ..\..\FindVC.cmd

cd %INTERMEDIATE_DIR%

set CMAKE_BUILD_TYPE=Debug
cd %CMAKE_BUILD_TYPE%
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

cd ..

set CMAKE_BUILD_TYPE=RelWithDebInfo
cd %CMAKE_BUILD_TYPE%
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 


cd %~dp0