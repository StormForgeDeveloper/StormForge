

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64
export SRC_BASE=libwebsockets

if [ ! -d "$SRC_BASE" ]; then
	./download.sh
fi


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
cmake ../../$SRC_BASE -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$CONFIGURATION  \
	-DCMAKE_INSTALL_PREFIX=../../../../$CMAKE_SYSTEM_NAME/$CONFIGURATION  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME \
	-DLWS_WITH_ZLIB=1 -DLWS_WITH_HTTP2=1 -DLWS_WITH_LIBEVENT=1  -DLWS_WITH_SHARED=0 

popd


export CONFIGURATION=RelWithDebInfo
pushd $CONFIGURATION
cmake ../../$SRC_BASE -G "Unix Makefiles"  -DCMAKE_BUILD_TYPE=$CONFIGURATION \
	-DCMAKE_INSTALL_PREFIX=../../../../$CMAKE_SYSTEM_NAME/$CONFIGURATION  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME \
	-DLWS_WITH_ZLIB=1 -DLWS_WITH_HTTP2=1 -DLWS_WITH_LIBEVENT=1  -DLWS_WITH_SHARED=0 

popd
popd


export LD_LIBRARY_PATH=$SavedLinkDir

