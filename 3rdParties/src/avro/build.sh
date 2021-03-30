

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64


SavedLinkDir=$LD_LIBRARY_PATH


pushd $CMAKE_SYSTEM_NAME


export CONFIGURATION=Debug
pushd $CONFIGURATION
cmake --build . --target install  --config $CONFIGURATION

popd


export CONFIGURATION=RelWithDebInfo
pushd $CONFIGURATION
cmake --build . --target install  --config $CONFIGURATION

popd
popd

export LD_LIBRARY_PATH=$SavedLinkDir

