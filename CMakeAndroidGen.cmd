


set PATH=C:\DevEnv\Android\cmake\3.10.2.4988404\bin;%PATH%
set CMAKE_SYSTEM_NAME=Android
set PROCESS_ARCHITECTUR=armeabi-v7a
set CMAKE_BUILD_TYPE=Debug

if not exist Intermediate mkdir Intermediate
if not exist Intermediate\%CMAKE_SYSTEM_NAME% mkdir Intermediate\%CMAKE_SYSTEM_NAME%


set BUILD_DIR=Intermediate\%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

cd %BUILD_DIR%



cmake ../../../ -G Ninja ^
	-DCMAKE_ANDROID_NDK=%ANDROID_NDK_ROOT% ^
	-DCMAKE_CROSSCOMPILING=true ^
	-DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK_ROOT%\build\cmake\android.toolchain.cmake ^
	-DANDROID_ABI=%PROCESS_ARCHITECTUR% ^
	-DANDROID_PLATFORM=android-23 ^
	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=bin/lib/%CMAKE_SYSTEM_NAME% ^
	-DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE% ^
	-DANDROID_NDK=%ANDROID_NDK_ROOT% ^
	-DCMAKE_C_FLAGS="-D__ANDROID__ -DDEBUG" ^
	-DCMAKE_CXX_FLAGS="-D__ANDROID__ -fexceptions -frtti -DDEBUG" ^
	-DCMAKE_ANDROID_ARCH_ABI=%PROCESS_ARCHITECTUR% ^
	-DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK_ROOT%\build\cmake\android.toolchain.cmake ^
	-DCMAKE_MAKE_PROGRAM=C:\DevEnv\Android\cmake\3.10.2.4988404\bin\ninja.exe ^
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON 


set CMAKE_BUILD_TYPE=Release
set BUILD_DIR=..\..\..\Intermediate\%CMAKE_SYSTEM_NAME%\%PROCESS_ARCHITECTUR%%CMAKE_BUILD_TYPE%
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

cd %BUILD_DIR%
cmake ../../../ -G Ninja ^
	-DCMAKE_ANDROID_NDK=%ANDROID_NDK_ROOT% ^
	-DCMAKE_CROSSCOMPILING=true ^
	-DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK_ROOT%\build\cmake\android.toolchain.cmake ^
	-DANDROID_ABI=%PROCESS_ARCHITECTUR% ^
	-DANDROID_PLATFORM=android-23 ^
	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=bin/lib/%CMAKE_SYSTEM_NAME% ^
	-DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE% ^
	-DANDROID_NDK=%ANDROID_NDK_ROOT% ^
	-DCMAKE_C_FLAGS="-D__ANDROID__ " ^
	-DCMAKE_CXX_FLAGS="-D__ANDROID__ -fexceptions -frtti" ^
	-DCMAKE_ANDROID_ARCH_ABI=%PROCESS_ARCHITECTUR% ^
	-DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK_ROOT%\build\cmake\android.toolchain.cmake ^
	-DCMAKE_MAKE_PROGRAM=C:\DevEnv\Android\cmake\3.10.2.4988404\bin\ninja.exe ^
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON 


pause
