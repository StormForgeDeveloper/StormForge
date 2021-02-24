

export MONGOC_DIR=src/mongoc

pushd $MONGOC_DIR
./build.sh


cd %~dp0

:exit


if not "%1" == "nopause" pause


