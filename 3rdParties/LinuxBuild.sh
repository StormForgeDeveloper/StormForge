#!/bin/bash


export CMAKE_SYSTEM_NAME=Linux


export BUILD_DIR=$CMAKE_SYSTEM_NAME


cd $BUILD_DIR


export CMAKE_BUILD_TYPE=Debug
cd x64/$CMAKE_BUILD_TYPE
cmake --build .   --target install  --config Debug

if [ $? -ne 0 ]; then
	exit 1
fi


export CMAKE_BUILD_TYPE=RelWithDebInfo
cd ../../x64/$CMAKE_BUILD_TYPE
cmake --build .   --target install --config RelWithDebInfo

if [ $? -ne 0 ]; then
	exit 2
fi



echo Done


