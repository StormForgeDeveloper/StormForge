

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64


SavedLinkDir=$LD_LIBRARY_PATH


pushd build$CMAKE_SYSTEM_NAME


export CONFIGURATION=Debug
pushd $CONFIGURATION
export zlibPath=$(dirname $(readlink -e ../../../../$CMAKE_SYSTEM_NAME/$PROCESS_ARCHITECTUR/$CONFIGURATION/lib/libzlib.a))
export LD_LIBRARY_PATH=$zlibPath
#echo LD_LIBRARY_PATH=$LD_LIBRARY_PATH
cmake --build . --target install  --config $CONFIGURATION

popd


export CONFIGURATION=RelWithDebInfo
pushd $CONFIGURATION
export zlibPath=$(dirname $(readlink -e ../../../../$CMAKE_SYSTEM_NAME/$PROCESS_ARCHITECTUR/$CONFIGURATION/lib/libzlib.a))
# export LD_LIBRARY_PATH=$zlibPath $SavedLinkDir
# echo $LD_LIBRARY_PATH
cmake --build . --target install  --config $CONFIGURATION

popd
popd

export LD_LIBRARY_PATH=$SavedLinkDir

