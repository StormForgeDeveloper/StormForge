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
 '1')  echo " Using Windows"
	 export CMAKE_SYSTEM_NAME=Windows
	echo $CMAKE_SYSTEM_NAME
	if [ ! -d $CMAKE_SYSTEM_NAME ]; then
		mkdir $CMAKE_SYSTEM_NAME
	fi
	cd $CMAKE_SYSTEM_NAME
	cmake ../ -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME  
     ;;
 '2')  echo  " Using Android"
	export CMAKE_SYSTEM_NAME=Android
	echo $CMAKE_SYSTEM_NAME
	if [ ! -d $CMAKE_SYSTEM_NAME ]; then
		mkdir $CMAKE_SYSTEM_NAME
	fi
	cd $CMAKE_SYSTEM_NAME
	cmake ../ -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME  \
			-DCMAKE_ANDROID_NDK=$ANDROID_NDK_ROOT \
			-DCMAKE_ANDROID_STL_TYPE=c++_static \
			-DCMAKE_ANDROID_API_MIN=23 \
			-DCMAKE_ANDROID_API=25 \
			-DCMAKE_ANDROID_GUI=1
			-DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a \
			-DPROJECT_OUTPUT_DIRNAME="${CMAKE_SYSTEM_NAME}${CMAKE_ANDROID_ARCH_ABI}"
			#-DCMAKE_ANDROID_ARCH_ABI=arm64-v8a 
			#-DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION 
     ;;
 '3')  echo  " Using IOS"
	 export CMAKE_SYSTEM_NAME=Darwin
	echo $CMAKE_SYSTEM_NAME
	if [ ! -d $CMAKE_SYSTEM_NAME ]; then
		mkdir $CMAKE_SYSTEM_NAME
	fi
	cd $CMAKE_SYSTEM_NAME
	cmake ../ -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME  
     ;;
 '4') echo  "Using Linux"
	 export CMAKE_SYSTEM_NAME=Linux
	echo $CMAKE_SYSTEM_NAME
	if [ ! -d $CMAKE_SYSTEM_NAME ]; then
		mkdir $CMAKE_SYSTEM_NAME
	fi
	cd $CMAKE_SYSTEM_NAME
	cmake ../ -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME  
    ;;
 esac





echo Done

read -n1 -r -p "Press space to continue..." key
