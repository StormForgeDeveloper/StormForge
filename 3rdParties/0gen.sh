
export MONGOC_DIR=src/mongoc

pushd $MONGOC_DIR

pushd $MONGOC_DIR
./gen.sh


popd

if not "%1" == "nopause" pause

