#!/bin/bash


SF_PATH=$(dirname "$0")
IS_WINDOWS=$(uname -r | grep Microsoft)
FBX_SDK_INSTALL_FILE_WIN=fbx20201_fbxsdk_vs2017_win.exe
FBX_SDK_INSTALL_FILE_LINUX=fbx20201_fbxsdk_linux.tar.gz

ATF_PATH=$SF_PATH/../ATF


if [ ! -d "$ATF_PATH" ]; then
	echo $ATF_PATH
	git clone https://github.com/blue3k/ATFClone.git $ATF_PATH
fi


pushd $SF_PATH/3rdParties 


if [ ! -f "$FBX_SDK_INSTALL_FILE_WIN" ]; then
    wget https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-1/$FBX_SDK_INSTALL_FILE_WIN
fi

# linux version install doesn't work
#if [ ! -f "$FBX_SDK_INSTALL_FILE_LINUX" ]; then
#	wget https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-1/fbx20201_fbxsdk_linux.tar.gz
#fi


if [ "$IS_WINDOWS" = "" ]; then
	echo Running on Linux
else
	echo Running on Linux subsystem.
	
	if [ ! -d "FBXSDK" ]; then
		cmd.exe /C "cd > pwd.obj"
		WINCWD=$(<pwd.obj)
		cmd.exe /C "$FBX_SDK_INSTALL_FILE_WIN /D=$WINCWD\\FBXSDK"
	fi
fi

# linux version install doesn't work
#tar -xvf fbx20201_fbxsdk_linux.tar.gz -C FBXSDK
#chmod ugo+x FBXSDK/fbx20201_fbxsdk_linux
#./FBXSDK/fbx20201_fbxsdk_linux /usr




# install vulkan SDK

VULKAN_SDK_WIN=VulkanSDK-1.2.148.1-Installer.exe
if [ ! -f "$VULKAN_SDK_WIN" ]; then
	wget https://sdk.lunarg.com/sdk/download/1.2.148.1/windows/$VULKAN_SDK_WIN
fi


if [ "$IS_WINDOWS" = "" ]; then
	echo Running on Linux
else
	echo Running on Linux subsystem.
	if [ ! -d "VulkanSDK" ]; then
		cmd.exe /C "cd > pwd.obj"
		WINCWD=$(<pwd.obj)
		cmd.exe /C "$VULKAN_SDK_WIN /D=$WINCWD\\VulkanSDK"
	fi
fi


if [ ! -f "/etc/apt/sources.list.d/lunarg-vulkan-1.2.148-bionic.list" ]; then
	wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.2.148-bionic.list https://packages.lunarg.com/vulkan/1.2.148/lunarg-vulkan-1.2.148-bionic.list
	sudo apt update
fi

sudo apt install vulkan-sdk


pushd src/mysql/
./setup_ubuntu.sh
popd


# to root
popd


