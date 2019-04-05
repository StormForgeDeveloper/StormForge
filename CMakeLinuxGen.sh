#!/bin/bash



export CMAKE_SYSTEM_NAME=Linux


if [ ! -f Intermediate ]; then
   mkdir Intermediate
fi

export BUILD_DIR=Intermediate/$CMAKE_SYSTEM_NAME
if [ ! -f $BUILD_DIR ]; then
  mkdir $BUILD_DIR
fi
mkdir $BUILD_DIR/Debug
mkdir $BUILD_DIR/Release

cd $BUILD_DIR


export CMAKE_BUILD_TYPE=Debug
cd $CMAKE_BUILD_TYPE
cmake ../../../ -G "Unix Makefiles"


export CMAKE_BUILD_TYPE=Release
cd ../$CMAKE_BUILD_TYPE
cmake ../../../ -G "Unix Makefiles"


echo Done

read -n1 -r -p "Press space to continue..." key

