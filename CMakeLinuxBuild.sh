#!/bin/bash



export CMAKE_SYSTEM_NAME=Linux


export BUILD_DIR=Intermediate/$CMAKE_SYSTEM_NAME
cd $BUILD_DIR



export CMAKE_BUILD_TYPE=Debug

cmake --build . 

export CMAKE_BUILD_TYPE=Release

cmake --build .


echo Done

read -n1 -r -p "Press space to continue..." key

