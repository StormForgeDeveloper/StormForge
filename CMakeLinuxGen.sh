#!/bin/bash



export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64


export BUILD_DIR=build$CMAKE_SYSTEM_NAME
if [ ! -f $BUILD_DIR ]; then
  mkdir $BUILD_DIR
fi
mkdir $BUILD_DIR/{$PROCESS_ARCHITECTUR}Debug
mkdir $BUILD_DIR/{$PROCESS_ARCHITECTUR}Release

cd $BUILD_DIR


export CMAKE_BUILD_TYPE=Debug
cd {$PROCESS_ARCHITECTUR}$CMAKE_BUILD_TYPE
cmake ../../ -G "Unix Makefiles"


export CMAKE_BUILD_TYPE=Release
cd ../{$PROCESS_ARCHITECTUR}$CMAKE_BUILD_TYPE
cmake ../../ -G "Unix Makefiles"


echo Done

