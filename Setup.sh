#!/bin/bash


SF_PATH=$(dirname "$0")
FBX_SDK_INSTALL_FILE_LINUX=fbx20201_fbxsdk_linux.tar.gz

ATF_PATH=$SF_PATH/../ATF


if [ ! -d "$ATF_PATH" ]; then
	echo $ATF_PATH
	git clone https://github.com/blue3k/ATFClone.git $ATF_PATH
fi


pushd $SF_PATH/3rdParties 


# linux version install doesn't work
#if [ ! -f "$FBX_SDK_INSTALL_FILE_LINUX" ]; then
#	wget https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-1/fbx20201_fbxsdk_linux.tar.gz
#fi

# linux version install doesn't work
#tar -xvf fbx20201_fbxsdk_linux.tar.gz -C FBXSDK
#chmod ugo+x FBXSDK/fbx20201_fbxsdk_linux
#./FBXSDK/fbx20201_fbxsdk_linux /usr




# install vulkan SDK

if [ ! -f "/etc/apt/sources.list.d/lunarg-vulkan-1.2.148-bionic.list" ]; then
	wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.2.148-bionic.list https://packages.lunarg.com/vulkan/1.2.148/lunarg-vulkan-1.2.148-bionic.list
	sudo apt update
fi

sudo apt install vulkan-sdk libssl-dev 


pushd src/mysql/
./setup_ubuntu.sh
popd


# to root
popd


