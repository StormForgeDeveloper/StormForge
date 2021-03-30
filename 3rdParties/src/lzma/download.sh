
if [ ! -f "xz-5.2.5.tar.gz" ]; then
	sudo wget https://cfhcable.dl.sourceforge.net/project/lzmautils/xz-5.2.5.tar.gz
fi

if [ ! -d "xz-5.2.5.tar.gz" ]; then
	tar -xvf xz-5.2.5.tar.gz
fi

#echo patching...
#cp -R -v c/* lzma1900/
