

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64
export LIB_PATH=2.13

if [ ! -d "$CMAKE_SYSTEM_NAME" ]; then
	mkdir $CMAKE_SYSTEM_NAME
fi

if [ ! -d "$CMAKE_SYSTEM_NAME/Debug" ]; then
	mkdir $CMAKE_SYSTEM_NAME/Debug
fi

if [ ! -d "$CMAKE_SYSTEM_NAME/RelWithDebInfo" ]; then
	mkdir $CMAKE_SYSTEM_NAME/RelWithDebInfo
fi


pushd $CMAKE_SYSTEM_NAME


export CONFIGURATION=Debug
pushd $CONFIGURATION
cmake ../../$LIB_PATH -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$CONFIGURATION  \
	-DCMAKE_INSTALL_PREFIX=../../../../$CMAKE_SYSTEM_NAME/$CONFIGURATION  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME \
	-DJANSSON_BUILD_DOCS=OFF -DJANSSON_EXAMPLES=OFF

popd


export CONFIGURATION=RelWithDebInfo
pushd $CONFIGURATION
cmake ../../$LIB_PATH -G "Unix Makefiles"  -DCMAKE_BUILD_TYPE=$CONFIGURATION \
	-DCMAKE_INSTALL_PREFIX=../../../../$CMAKE_SYSTEM_NAME/$CONFIGURATION  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME \
	-DJANSSON_BUILD_DOCS=OFF -DJANSSON_EXAMPLES=OFF

popd
popd


export LD_LIBRARY_PATH=$SavedLinkDir

