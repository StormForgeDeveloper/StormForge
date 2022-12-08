export SRC_PATH=curl
rm -rf $SRC_PATH
if [ ! -d "$SRC_PATH" ]; then
	git clone https://github.com/curl/curl.git
fi

echo patching...
#cp -R -v patch/* $SRC_PATH/
