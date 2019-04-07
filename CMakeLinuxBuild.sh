#!/bin/bash



export CMAKE_SYSTEM_NAME=Linux


export BUILD_DIR=build$CMAKE_SYSTEM_NAME

mkdir $BUILD_DIR/Debug
mkdir $BUILD_DIR/Release

cd $BUILD_DIR



export CMAKE_BUILD_TYPE=Debug
cd $CMAKE_BUILD_TYPE
cmake --build .   --target install --config Debug

export CMAKE_BUILD_TYPE=Release
cd ../$CMAKE_BUILD_TYPE
cmake --build .   --target install --config Release


echo Done


