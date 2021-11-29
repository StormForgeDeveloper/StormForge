export LIBMEMCACHED_VERSION=1.0.18
export LIBMEMCACHED_SRC=libmemcached-$LIBMEMCACHED_VERSION
rm -rf $LIBMEMCACHED_SRC

https://launchpad.net/libmemcached/1.0/1.0.18/+download/libmemcached-1.0.18.tar.gz

if [ ! -f "$LIBMEMCACHED_SRC.tar.gz" ]; then
	wget https://launchpad.net/libmemcached/1.0/$LIBMEMCACHED_VERSION/+download/$LIBMEMCACHED_SRC.tar.gz
fi

if [ ! -d "$LIBMEMCACHED_SRC" ]; then
	tar -xvf $LIBMEMCACHED_SRC.tar.gz
fi

echo patching...
cp -R -v patch/* $LIBMEMCACHED_SRC/

