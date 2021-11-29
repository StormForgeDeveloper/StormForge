export LIBMEMCACHED_VERSION=1.0.18
export LIBMEMCACHED_SRC=libmemcached-$LIBMEMCACHED_VERSION
rm -rf $LIBMEMCACHED_SRC



if [ ! -f "$LIBMEMCACHED_SRC.tar.gz" ]; then
	wget https://launchpad.net/libmemcached/1.0/$LIBMEMCACHED_VERSION/+download/$LIBMEMCACHED_SRC.tar.gz
fi

if [ ! -d "$LIBMEMCACHED_SRC" ]; then
	tar -xvf $LIBMEMCACHED_SRC.tar.gz
	pushd $LIBMEMCACHED_SRC
	./configure
	popd
fi

echo patching...
cp -R -v patch_linux/* $LIBMEMCACHED_SRC/

