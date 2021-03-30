
if [ ! -f "lzma1900" ]; then
	sudo wget https://www.7-zip.org/a/lzma1900.7z
fi

if [ ! -d "lzma1900" ]; then
	tar -xvf lzma1900.tar.bz2
fi

#echo patching...
#cp -R -v c/* lzma1900/
