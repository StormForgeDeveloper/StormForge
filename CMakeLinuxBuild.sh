#!/bin/bash



export CMAKE_SYSTEM_NAME=Linux


export BUILD_DIR=build$CMAKE_SYSTEM_NAME

mkdir $BUILD_DIR/x64Debug
mkdir $BUILD_DIR/x64Release

cd $BUILD_DIR



export CMAKE_BUILD_TYPE=Debug
cd x64$CMAKE_BUILD_TYPE
cmake --build .   --target install  --config Debug



export CMAKE_BUILD_TYPE=Release
cd ../x64$CMAKE_BUILD_TYPE
cmake --build .   --target install --config Release



echo Done


