#!/bin/bash

# Copyright Kyungkun Ko

. build/setup_build_env.sh

Triplet=$SF_VCPKG_TRIPLET
VCPKGDIR=$SF_VCPKGDIR

#WSLENV=VULKAN_SDK/p

echo $VULKAN_SDK
echo $Triplet=$SF_VCPKG_TRIPLET
echo $VCPKGDIR=$SF_VCPKGDIR


deps='vcpkg-pkgconfig-get-modules,
        zlib,
		liblzma,
		openssl,
		tinyxml2,
		libxml2[iconv],
		libbson,
		jsoncpp,
		avro-c,
		libuv,
		libevent,
		lcms,
		tiff,
		libpng,
		icu,
		libiconv,
		jasper,
		openexr,
		jansson,
		freetype,
		libjpeg-turbo,
		sndfile,
        libogg,
        libflac,
		opus,
        protobuf,
		libwebsockets,
		curl,
		librdkafka[zlib],
		mongo-c-driver[icu],
		mysql-connector-cpp,
		zookeeper,
		gtest'

#		pipewire
#		vulkan,

if [ ! -d "$VCPKGDIR" ]
    then 
        git clone https://github.com/Microsoft/vcpkg.git $VCPKGDIR
	else
		pushd $VCPKGDIR
		git pull .
fi

if [ ! -f "vcpkg" ]
	then
	./bootstrap-vcpkg.sh
fi


for dep in ${deps//,/ }
do
	# --clean-after-build
	./vcpkg install $dep --triplet $Triplet 
done

./vcpkg.exe update
./vcpkg.exe upgrade

popd

