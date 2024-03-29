#!/bin/bash

#This is only for c# referencing

if [ ! -d "flatbuffers" ]; then
	git clone --depth 1 --branch v24.3.7 https://github.com/google/flatbuffers.git
	git apply --check ../MSVCStatic.patch
	git am --keep-cr --signoff < ../a_file.patch 
else
	pushd flatbuffers
	git pull

	popd
fi


export CMAKE_SYSTEM_NAME=Linux
export BUILD_DIR=buildLinux

if [ ! -d $BUILD_DIR ]; then
  echo 	mkdir $BUILD_DIR
  mkdir $BUILD_DIR
fi

if [ ! -d $BUILD_DIR/Debug ]; then
  mkdir $BUILD_DIR/Debug
fi

if [ ! -d $BUILD_DIR/Release ]; then
  mkdir $BUILD_DIR/Release
fi

#!/bin/bash


export CMAKE_SYSTEM_NAME=Linux
export BUILD_DIR=buildLinux

if [ ! -d $BUILD_DIR ]; then
  echo 	mkdir $BUILD_DIR
  mkdir $BUILD_DIR
fi

if [ ! -d $BUILD_DIR/Debug ]; then
  mkdir $BUILD_DIR/Debug
fi

if [ ! -d $BUILD_DIR/Release ]; then
  mkdir $BUILD_DIR/Release
fi


pushd $BUILD_DIR

export CMAKE_BUILD_TYPE=Debug
pushd $CMAKE_BUILD_TYPE
cmake ../../flatbuffers -G "Ninja"  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DCMAKE_INSTALL_PREFIX=../../../../Linux/$CMAKE_BUILD_TYPE   \
	-DVCPKG_DIR=$SF_FOLDER/vcpkg

cmake --build . --target install  --config $CMAKE_BUILD_TYPE
popd


export CMAKE_BUILD_TYPE=Release
pushd $CMAKE_BUILD_TYPE
cmake ../../flatbuffers -G "Ninja"  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DCMAKE_INSTALL_PREFIX=../../../../Linux/$CMAKE_BUILD_TYPE   \
	-DVCPKG_DIR=$SF_FOLDER/vcpkg

cmake --build . --target install  --config $CMAKE_BUILD_TYPE
popd


popd
