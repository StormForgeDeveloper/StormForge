

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


call ..\..\FindVC.cmd

if not exist build%CMAKE_SYSTEM_NAME% mkdir build%CMAKE_SYSTEM_NAME%
cd build%CMAKE_SYSTEM_NAME%


set CMAKE_BUILD_TYPE=Debug
cd %CMAKE_BUILD_TYPE%
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

cd ..

set CMAKE_BUILD_TYPE=RelWithDebInfo
cd %CMAKE_BUILD_TYPE%
cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

cd ..
cd ..
