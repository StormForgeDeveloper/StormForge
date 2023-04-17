#!/bin/bash


#export SF_DIR=${PWD##*/}
SF_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

echo SF_DIR=$SF_DIR


export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64


export BUILD_DIR=build$CMAKE_SYSTEM_NAME
if [ ! -d $BUILD_DIR ]; then
  mkdir $BUILD_DIR
fi

if [ ! -d $BUILD_DIR/x64Debug ]; then
  mkdir $BUILD_DIR/x64Debug
fi

if [ ! -d $BUILD_DIR/x64Release ]; then
  mkdir $BUILD_DIR/x64Release
fi


cd $BUILD_DIR

export CMAKE_BUILD_TYPE=Debug
cd $PROCESS_ARCHITECTUR$CMAKE_BUILD_TYPE
cmake ../../ -G "Ninja" \
	-DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME \
	-DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE \
	-DCMAKE_INSTALL_PREFIX=./  \
	-DFBX_SDK_PATH=../../../../FBXSDK

	# -DSF_DIR=$SF_DIR \
	# -DVCPKG_DIR=$SF_DIR/vcpkg \


export CMAKE_BUILD_TYPE=Release
cd ../$PROCESS_ARCHITECTUR$CMAKE_BUILD_TYPE
cmake ../../ -G "Ninja" \
	-DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME \
	-DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE \
	-DCMAKE_INSTALL_PREFIX=./  \
	-DFBX_SDK_PATH=../../../../FBXSDK

#	-DCMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO=Release \
	# -DSF_DIR=$SF_DIR \
	# -DVCPKG_DIR=$SF_DIR/vcpkg \

echo Done

