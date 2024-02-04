#!/bin/bash


SF_PATH=$(dirname "$0")
FBX_SDK_INSTALL_FILE_LINUX=fbx20201_fbxsdk_linux.tar.gz

ATF_PATH=$SF_PATH/../ATF

# https://sdk.lunarg.com/sdk/download/1.2.182.0/linux/vulkansdk-linux-x86_64-1.2.182.0.tar.gz
# install vulkan SDK link
if [ ! -f "/etc/apt/sources.list.d/lunarg-vulkan-jammy.list" ]; then
	wget -q - https://packages.lunarg.com/lunarg-signing-key-pub.asc
	gpg --dearmor lunarg-signing-key-pub.asc
	sudo cp lunarg-signing-key-pub.asc.gpg /usr/share/keyrings/lunarg-signing-key-pub.gpg
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-jammy.list http://packages.lunarg.com/vulkan/lunarg-vulkan-jammy.list
	#Link signing key file. You need to update list file with signedby setting
	echo "deb [signed-by=/usr/share/keyrings/lunarg-signing-key-pub.gpg] https://URL"
	sudo vi /etc/apt/sources.list.d/lunarg-vulkan-jammy.list
	
	sudo apt update
fi


sudo apt-get install -y moreutils git-lfs build-essential clang rsync zip ninja-build libatomic-ops-dev gdb perl pkg-config openjdk-17-jdk dotnet8

# for Vulkan
sudo apt-get install -y vulkan-sdk

# for Icu
sudo apt install -y autoconf autoconf-archive
# for GetText
sudo apt install -y bison
# for openssl through vcpkg
sudo apt install -y linux-libc-dev
# for freetype -> freeglut
sudo apt install -y libxi-dev libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev libxrandr-dev libxxf86vm-dev
# for openal
sudo apt install -y libtool

if [ ! -d "$ATF_PATH" ]; then
	echo $ATF_PATH
	git clone https://github.com/blue3k/ATFClone.git $ATF_PATH
fi


wget https://github.com/Kitware/CMake/releases/download/v3.28.1/cmake-3.28.1-linux-x86_64.sh
chmod au+x cmake-3.28.1-linux-x86_64.sh
sudo mkdir /usr/local/share/cmake-3.28.1
sudo ./cmake-3.28.1-linux-x86_64.sh --skip-license --prefix=/usr/local/share/cmake-3.28.1 
sudo rm -rf /usr/local/bin/cmake
sudo rm -rf /usr/local/bin/ccmake
sudo rm -rf /usr/local/bin/cmake-gui
sudo rm -rf /usr/local/bin/cpack
sudo rm -rf /usr/local/bin/ctest
sudo ln -s /usr/local/share/cmake-3.28.1/bin/ccmake /usr/local/bin/
sudo ln -s /usr/local/share/cmake-3.28.1/bin/cmake /usr/local/bin/
sudo ln -s /usr/local/share/cmake-3.28.1/bin/cmake-gui /usr/local/bin/
sudo ln -s /usr/local/share/cmake-3.28.1/bin/cpack /usr/local/bin/
sudo ln -s /usr/local/share/cmake-3.28.1/bin/ctest /usr/local/bin/



pushd $SF_PATH/3rdParties 

#build tools
pushd tool
make
popd

# linux version install doesn't work
# if [ ! -f "$FBX_SDK_INSTALL_FILE_LINUX" ]; then
	# wget https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-1/fbx20201_fbxsdk_linux.tar.gz
	# sudo apt install uuid-dev libxmu-dev libxi-dev libx11-dev
# fi

# # linux version install doesn't work
# if [ ! -d "FBXSDK_Linux_Install" ]; then
	# mkdir FBXSDK_Linux_Install
# fi
# tar -xvf fbx20201_fbxsdk_linux.tar.gz -C FBXSDK_Linux_Install
# chmod ugo+x FBXSDK_Linux_Install/fbx20201_fbxsdk_linux
# ./FBXSDK/fbx20201_fbxsdk_linux /usr




# to root
popd


./download_dependencies.sh


echo ==============================================================
echo Register test host names 
echo Kafka: SFTestKafka.com
echo host file location
echo   - Windows 10 – “C:\Windows\System32\drivers\etc\hosts”
echo   - Linux – “/etc/hosts”
echo   - Mac OS X – “/private/etc/hosts”
echo ==============================================================

popd


