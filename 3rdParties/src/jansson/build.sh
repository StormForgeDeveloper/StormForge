

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64
export INTERMEDIATE_DIR=../../$CMAKE_SYSTEM_NAME/jansson


pushd $INTERMEDIATE_DIR


export CONFIGURATION=Debug
pushd $CONFIGURATION
cmake --build . --target install  --config $CONFIGURATION

popd


export CONFIGURATION=RelWithDebInfo
pushd $CONFIGURATION
cmake --build . --target install  --config $CONFIGURATION

popd
popd

