

export MONGOC_DIR=src/mongoc

pushd $MONGOC_DIR
./build.sh


popd

:exit


if not "%1" == "nopause" pause


