#!/bin/bash


export GENCMAKE=./Bin/SFConvertVSProj2CMake.exe



$GENCMAKE +in=Engine/Src/SFCore/SFCore.vcxitems  +makein=Engine/Src/SFCore/CMakeList.in
$GENCMAKE +in=Engine/Src/SFEngine/SFEngine.vcxitems  +makein=Engine/Src/SFEngine/CMakeList.in
$GENCMAKE +in=Engine/Src/Protocol/SFProtocol.vcxitems  +makein=Engine/Src/Protocol/CMakeList.in
$GENCMAKE +in=Engine/Src/SFEngineDLL/SFEngineDLL.Win.vcxproj +in=Engine/Src/SFEngineDLL/SFEngineDLL.Android.vcxproj +makein=Engine/Src/SFEngineDLL/CMakeList.in

echo Generated CMakeList.txt



echo Enter platform
echo 1: Windows
echo 2: Android
echo 3: IOS
echo 4: Linux


read -n1 -r -p "Press space to continue..." key
case "$key" in 
'1')  echo "Using Windows"
	export CMAKE_SYSTEM_NAME=Windows
    ;;
'2')  echo  "Using Android"
	export CMAKE_SYSTEM_NAME=Android
	export CMAKE_ANDROID_ARCH_ABI=armeabi-v7a
    ;;
'3')  echo  "Using IOS"
	export CMAKE_SYSTEM_NAME=Darwin
    ;;
'4') echo  "Using Linux"
   kill -SIGKILL $2
   ;;
esac


mkdir $CMAKE_SYSTEM_NAME
cd $CMAKE_SYSTEM_NAME
cmake ../

cd ..

echo Done

read -n1 -r -p "Press space to continue..." key
