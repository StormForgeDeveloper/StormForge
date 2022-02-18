

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64
export SRC_PATH=../../../src/jansson/2.13
export INTERMEDIATE_DIR=../../$CMAKE_SYSTEM_NAME/jansson


if [ ! -d "$INTERMEDIATE_DIR" ]; then
	mkdir $INTERMEDIATE_DIR
fi

if [ ! -d "$INTERMEDIATE_DIR/Debug" ]; then
	mkdir $INTERMEDIATE_DIR/Debug
fi

if [ ! -d "$INTERMEDIATE_DIR/RelWithDebInfo" ]; then
	mkdir $INTERMEDIATE_DIR/RelWithDebInfo
fi


pushd $INTERMEDIATE_DIR


export CONFIGURATION=Debug
pushd $CONFIGURATION
cmake $SRC_PATH -G "Ninja" -DCMAKE_BUILD_TYPE=$CONFIGURATION  \
	-DCMAKE_INSTALL_PREFIX=../../$CONFIGURATION  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME \
	-DJANSSON_BUILD_DOCS=OFF -DJANSSON_EXAMPLES=OFF -DJANSSON_WITHOUT_TESTS=1

popd


export CONFIGURATION=RelWithDebInfo
pushd $CONFIGURATION
cmake $SRC_PATH -G "Ninja"  -DCMAKE_BUILD_TYPE=$CONFIGURATION \
	-DCMAKE_INSTALL_PREFIX=../../$CONFIGURATION  -DCMAKE_SYSTEM_NAME=$CMAKE_SYSTEM_NAME \
	-DJANSSON_BUILD_DOCS=OFF -DJANSSON_EXAMPLES=OFF -DJANSSON_WITHOUT_TESTS=1

popd
popd


export LD_LIBRARY_PATH=$SavedLinkDir

