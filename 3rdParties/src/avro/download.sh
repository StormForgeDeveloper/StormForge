export AVRO_SRC=avro-src-1.10.2
rm -rf $AVRO_SRC
if [ ! -f "$AVRO_SRC.tar.gz" ]; then
	sudo wget https://downloads.apache.org/avro/avro-1.10.2/$AVRO_SRC.tar.gz
fi

if [ ! -d "$AVRO_SRC" ]; then
	tar -xvf $AVRO_SRC.tar.gz
fi

echo patching...
cp -R -v patch/* avro-src-1.10.2/
