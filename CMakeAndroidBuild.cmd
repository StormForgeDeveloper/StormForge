


set PATH=C:\DevEnv\Android\cmake\3.10.2.4988404\bin;%PATH%
set CMAKE_SYSTEM_NAME=Android
set PROCESS_ARCHITECTUR=armeabi-v7a

set CMAKE_BUILD_TYPE=Debug
set BUILD_DIR=Intermediate\%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%

cd %BUILD_DIR%

cmake --build .


set CMAKE_BUILD_TYPE=Release
set BUILD_DIR=Intermediate\%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%

cd ../../../%BUILD_DIR%

cmake --build .



pause
