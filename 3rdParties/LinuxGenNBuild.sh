#!/bin/bash

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64


echo Building mongoc
pushd src/mongoc
./gen.sh
./build.sh
popd


echo Building jansson
pushd src/jansson
./gen.sh
./build.sh
popd


echo Building main collection
export BUILD_DIR=$CMAKE_SYSTEM_NAME
if [ ! -f $BUILD_DIR ]; then
  mkdir $BUILD_DIR
fi

if [ ! -f $BUILD_DIR/Debug ]; then
  mkdir $BUILD_DIR/Debug
fi

if [ ! -f $BUILD_DIR/RelWithDebInfo ]; then
  mkdir $BUILD_DIR/RelWithDebInfo
fi

pushd $BUILD_DIR

export CMAKE_BUILD_TYPE=Debug
pushd $CMAKE_BUILD_TYPE
cmake ../../ -G "Unix Makefiles"  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DCMAKE_INSTALL_PREFIX=./    
popd

export CMAKE_BUILD_TYPE=RelWithDebInfo
pushd $CMAKE_BUILD_TYPE
cmake ../../ -G "Unix Makefiles"  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DCMAKE_INSTALL_PREFIX=./   
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

export CMAKE_BUILD_TYPE=RelWithDebInfo
pushd $CMAKE_BUILD_TYPE
cmake --build . --target install  --config $CMAKE_BUILD_TYPE
popd

if [ $? -ne 0 ]; then
	exit 1
fi

popd



echo Building avro
pushd src/avro
./gen.sh
./build.sh
popd


echo Building libevent
pushd src/libevent
./gen.sh
./build.sh
popd


echo Building libwebsocket
pushd src/libwebsocket
./gen.sh
./build.sh
popd


echo Done

