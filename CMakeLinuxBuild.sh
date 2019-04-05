#!/bin/bash



export CMAKE_SYSTEM_NAME=Linux


export BUILD_DIR=Intermediate/$CMAKE_SYSTEM_NAME

mkdir $BUILD_DIR/Debug
mkdir $BUILD_DIR/Release

cd $BUILD_DIR



export CMAKE_BUILD_TYPE=Debug
cd $CMAKE_BUILD_TYPE
cmake --build . 

export CMAKE_BUILD_TYPE=Release
cd ../$CMAKE_BUILD_TYPE
cmake --build . 


echo Done

read -n1 -r -p "Press space to continue..." key

