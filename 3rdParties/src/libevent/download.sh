export ARCHIVE_SRC=libevent-2.1.12-stable
rm -rf $ARCHIVE_SRC
if [ ! -f "$ARCHIVE_SRC.tar.gz" ]; then
	wget https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/$ARCHIVE_SRC.tar.gz
fi

if [ ! -d "$ARCHIVE_SRC" ]; then
	tar -xvf $ARCHIVE_SRC.tar.gz
fi

echo patching...
cp -R -v patch/* $ARCHIVE_SRC/
