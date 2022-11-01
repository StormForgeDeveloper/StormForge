export AVRO_SRC=avro-src-1.11.1
rm -rf $AVRO_SRC
if [ ! -f "$AVRO_SRC.tar.gz" ]; then
	wget https://downloads.apache.org/avro/stable/$AVRO_SRC.tar.gz
fi

if [ ! -d "$AVRO_SRC" ]; then
	tar -xvf $AVRO_SRC.tar.gz
fi

echo patching...
cp -R -v patch/* $AVRO_SRC/
