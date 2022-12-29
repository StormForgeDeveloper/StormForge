#!/bin/bash


SF_PATH=$(dirname "$0")
FBX_SDK_INSTALL_FILE_LINUX=fbx20201_fbxsdk_linux.tar.gz

ATF_PATH=$SF_PATH/../ATF

# https://sdk.lunarg.com/sdk/download/1.2.182.0/linux/vulkansdk-linux-x86_64-1.2.182.0.tar.gz
# install vulkan SDK link
if [ ! -f "/etc/apt/sources.list.d/lunarg-vulkan-jammy.list" ]; then
	wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc
	gpg --dearmor lunarg-signing-key-pub.asc
	sudo cp lunarg-signing-key-pub.asc.gpg /usr/share/keyrings/lunarg-signing-key-pub.gpg
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-jammy.list http://packages.lunarg.com/vulkan/lunarg-vulkan-jammy.list
	#Link signing key file
	echo "deb [signed-by=/usr/share/keyrings/lunarg-signing-key-pub.gpg] https://URL"
	sudo vi /etc/apt/sources.list.d/lunarg-vulkan-jammy.list
	
	sudo apt update
fi


sudo apt install moreutils git-lfs build-essential clang cmake rsync zip ninja-build libatomic-ops-dev gdb
sudo apt install libssl-dev perl libssl-dev pkg-config libsasl2-dev
sudo apt install openjdk-8-jdk
sudo apt install vulkan-sdk

 
sudo apt-get install -y dotnet6
  

if [ ! -d "$ATF_PATH" ]; then
	echo $ATF_PATH
	git clone https://github.com/blue3k/ATFClone.git $ATF_PATH
fi


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




pushd src/mysql/
./setup_ubuntu.sh
popd

pushd src/mongoc/
./download.sh
popd

pushd src/lzma/
./download.sh
popd

pushd src/jansson/
./download.sh
popd

pushd src/avro/
./download.sh
popd

pushd src/llvm/
./download.sh
popd


# to root
popd


pushd Tools/3rdParty/
./setup.sh
popd


echo ==============================================================
echo Register test host names 
echo Zookeeper: SFTestZookeeper.com
echo Kafka: SFTestKafka.com
echo host file location
echo   - Windows 10 – “C:\Windows\System32\drivers\etc\hosts”
echo   - Linux – “/etc/hosts”
echo   - Mac OS X – “/private/etc/hosts”
echo ==============================================================

popd


