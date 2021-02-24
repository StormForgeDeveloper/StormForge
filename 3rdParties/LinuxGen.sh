#!/bin/bash

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64


export BUILD_DIR=$CMAKE_SYSTEM_NAME
if [ ! -f $BUILD_DIR ]; then
  mkdir $BUILD_DIR
fi

if [ ! -f $BUILD_DIR/x64 ]; then
  mkdir $BUILD_DIR/x64
fi

if [ ! -f $BUILD_DIR/x64/Debug ]; then
  mkdir $BUILD_DIR/x64/Debug
fi

if [ ! -f $BUILD_DIR/x64/RelWithDebInfo ]; then
  mkdir $BUILD_DIR/x64/RelWithDebInfo
fi

cd $BUILD_DIR



export CMAKE_BUILD_TYPE=Debug
cd $PROCESS_ARCHITECTUR/$CMAKE_BUILD_TYPE
cmake ../../../ -G "Unix Makefiles"  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DCMAKE_INSTALL_PREFIX=./    


export CMAKE_BUILD_TYPE=RelWithDebInfo
cd ../../$PROCESS_ARCHITECTUR/$CMAKE_BUILD_TYPE
cmake ../../../ -G "Unix Makefiles"  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DCMAKE_INSTALL_PREFIX=./   


echo Done

