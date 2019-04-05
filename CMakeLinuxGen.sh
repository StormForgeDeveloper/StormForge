#!/bin/bash



export CMAKE_SYSTEM_NAME=Linux


if [ ! -f Intermediate ]; then
   mkdir Intermediate
fi

export BUILD_DIR=Intermediate/$CMAKE_SYSTEM_NAME
if [ ! -f $BUILD_DIR ]; then
  mkdir $BUILD_DIR
fi

cd $BUILD_DIR



cmake ../../ -G "Unix Makefiles"


echo Done

read -n1 -r -p "Press space to continue..." key

