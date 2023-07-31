#!/bin/bash

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64

#build tools
pushd tool
make
popd

pushd ..
SF_FOLDER=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
popd

echo SF_FOLDER=$SF_FOLDER


echo building main collection
export BUILD_DIR=$CMAKE_SYSTEM_NAME
echo BUILD_DIR=$BUILD_DIR

if [ ! -f $BUILD_DIR ]; then
  echo 	mkdir $BUILD_DIR
  mkdir $BUILD_DIR
fi

if [ ! -f $BUILD_DIR/Debug ]; then
  mkdir $BUILD_DIR/Debug
fi

if [ ! -f $BUILD_DIR/Release ]; then
  mkdir $BUILD_DIR/Release
fi

pushd $BUILD_DIR

export CMAKE_BUILD_TYPE=Debug
pushd $CMAKE_BUILD_TYPE
cmake ../../ -G "Ninja"  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DCMAKE_INSTALL_PREFIX=./    \
	-DSF_FOLDER=$SF_FOLDER \
	-DVCPKG_DIR=$SF_FOLDER/vcpkg
popd

export CMAKE_BUILD_TYPE=Release
pushd $CMAKE_BUILD_TYPE
cmake ../../ -G "Ninja"  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DCMAKE_INSTALL_PREFIX=./   \
	-DSF_FOLDER=$SF_FOLDER \
	-DVCPKG_DIR=$SF_FOLDER/vcpkg
popd

popd



pushd $BUILD_DIR

export CMAKE_BUILD_TYPE=Debug
pushd $CMAKE_BUILD_TYPE
cmake --build . --target install  --config $CMAKE_BUILD_TYPE
popd

if [ $? -ne 0 ]; then
	exit 1
fi

export CMAKE_BUILD_TYPE=Release
pushd $CMAKE_BUILD_TYPE
cmake --build . --target install  --config $CMAKE_BUILD_TYPE
popd

if [ $? -ne 0 ]; then
	exit 1
fi

popd


pushd src/flatbuffer

./download.sh

popd



echo Done

