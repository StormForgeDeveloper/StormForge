#!/bin/bash

SF_PATH=$(dirname "$0")

ATF_PATH=$SF_PATH/../ATF


sudo apt-get install -y moreutils git-lfs build-essential clang rsync zip ninja-build libatomic-ops-dev gdb perl pkg-config openjdk-17-jdk dotnet8 cmake

# Install vulkan SDK
if [ ! -f "/etc/apt/sources.list.d/lunarg-vulkan-1.3.296-noble.list" ]; then
	wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.296-noble.list https://packages.lunarg.com/vulkan/1.3.296/lunarg-vulkan-1.3.296-noble.list
	sudo apt update
	sudo apt install vulkan-sdk
fi

# for Icu
sudo apt install -y autoconf autoconf-archive
# for GetText
sudo apt install -y bison
# for openssl through vcpkg
sudo apt install -y linux-libc-dev
# for freetype(freeglut) and jasper require some libs from system packages
sudo apt install -y libxi-dev libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev libxrandr-dev libxxf86vm-dev
# for openal
sudo apt install -y libtool


pushd $SF_PATH/3rdParties 

#build tools
pushd tool
make
popd


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


