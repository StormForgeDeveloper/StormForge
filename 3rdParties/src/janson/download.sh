export JANSSON_SRC=2.13
rm -rf $JANSSON_SRC
mkdir $JANSSON_SRC
git clone --branch $JANSSON_SRC https://github.com/akheron/jansson.git ./$JANSSON_SRC
