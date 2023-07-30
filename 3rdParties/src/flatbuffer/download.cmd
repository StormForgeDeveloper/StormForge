

%~d0
cd %~dp0

bash ./download.sh


call ..\..\..\build\FindVC.cmd


mkdir buildWindows
mkdir buildWindows\Release
mkdir buildWindows\Debug


set BUILD_DIR=buildWindows
set PROCESS_ARCHITECTUR=x64

set CMAKE_BUILD_TYPE=Debug
cd %BUILD_DIR%\%CMAKE_BUILD_TYPE%
cmake ../../flatbuffers -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR% ^
	-DCMAKE_INSTALL_PREFIX=../../../../Windows/%CMAKE_BUILD_TYPE%   ^
	-DVCPKG_DIR=%SF_FOLDER%/vcpkg

cmake --build . --parallel --target install  -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit



set CMAKE_BUILD_TYPE=Release
cd ..\%CMAKE_BUILD_TYPE%

cmake ../../flatbuffers -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR% ^
	-DCMAKE_INSTALL_PREFIX=../../../../Windows/%CMAKE_BUILD_TYPE%   ^
	-DVCPKG_DIR=%SF_FOLDER%/vcpkg

cmake --build . --parallel --target install -- /p:Configuration=%CMAKE_BUILD_TYPE% 

if ERRORLEVEL 1 goto exit




:exit


cd %~dp0

if not "%1" == "nopause" pause

