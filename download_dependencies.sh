#!/bin/bash

# Copyright Kyungkun Ko

. build/setup_build_env.sh

Triplet=$SF_VCPKG_TRIPLET
VCPKGDIR=$SF_VCPKGDIR

#WSLENV=VULKAN_SDK/p

echo $VULKAN_SDK
echo $Triplet=$SF_VCPKG_TRIPLET
echo $VCPKGDIR=$SF_VCPKGDIR

DO_UPGRADE=0
for i in "$@"; do
  case $i in
    -upgrade=*|--upgrade=*)
      DO_UPGRADE="${i#*=}"
      shift # past argument=value
      ;;
    -*|--*)
      echo "Unknown option $i"
      exit 1
      ;;
    *)
      ;;
  esac
done

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
		openal-soft,
		libsndfile,
        libogg,
        libflac,
		opus,
        protobuf,
		recastnavigation,
		libwebsockets,
		msquic[0-rtt],
		librdkafka[zlib],
		mysql-connector-cpp,
		gtest'

#		grpc,
#		zookeeper,
#		pipewire
#		vulkan,

if [ ! -d "$VCPKGDIR" ]
    then 
        git clone https://github.com/Microsoft/vcpkg.git $VCPKGDIR
fi

pushd $VCPKGDIR

if [ ! -f "vcpkg" ]
	then
	./bootstrap-vcpkg.sh
fi


for dep in ${deps//,/ }
do
	# --clean-after-build
	./vcpkg install $dep --triplet $Triplet --recurse
done

./vcpkg install curl[openssl,websockets] --recurse


if [ "$DO_UPGRADE" = "1" ]
then
	echo Upgrading vcpkg packages
	git pull .
	./vcpkg update
	./vcpkg upgrade --no-dry-run --allow-unsupported
else
	echo Skip upgrade
	echo Add parameter "-upgrade=1" to upgrade
fi

popd

pushd 3rdParties

./LinuxGenNBuild.sh

popd

