
cmake_minimum_required(VERSION 3.16)


project(SF3rdParties C CXX)

message ("SF_FOLDER=${SF_FOLDER}, VCPKG_DIR=${VCPKG_DIR}")

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")


if(WIN32)

	message ( "Setup Windows configs" )

	add_definitions(-DNOMINMAX)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	add_definitions(-DWIN64)
	add_definitions(-DWIN32)
	add_definitions(-D_WINDOWS)
	
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	
	set(ARTECTURE x64)
	set(VCPKG_TARGET_TRIPLET ${ARTECTURE}-windows-static)

elseif(ANDROID_PLATFORM)

	message ( "Setup Android configs" )

	add_definitions(-D__ANDROID__=1)

	set(ARTECTURE ${CMAKE_ANDROID_ARCH_ABI})
	set(VCPKG_TARGET_TRIPLET ${ARTECTURE}-android)

elseif(IOS)

	message ( "Setup IOS configs" )

	add_definitions(-D__IOS__=1)
	add_definitions(-DKQUEUE)

	set(ARTECTURE ${CMAKE_OSX_ARCHITECTURES})
	set(VCPKG_TARGET_TRIPLET ${ARTECTURE}-ios)

elseif(UNIX)

	message ( "Setup UNIX configs" )

	add_definitions(-D_LINUX_=1)
	add_definitions(-DEPOLL)

	set(ARTECTURE x64)
	set(VCPKG_TARGET_TRIPLET ${ARTECTURE}-linux)

endif()


set(VCPKG_INSTALL ${VCPKG_DIR}/installed/${VCPKG_TARGET_TRIPLET})
set(CMAKE_PREFIX_PATH  "${VCPKG_INSTALL}/")
set(Protobuf_PROTOC_EXECUTABLE "${VCPKG_INSTALL}/tools/protobuf/protoc")


include_directories(AFTER ${VCPKG_INSTALL}/include)

if(WIN32)
	link_directories(AFTER 
		"${VCPKG_INSTALL}/$(Configuration)/lib"
		"${VCPKG_INSTALL}/lib"
	)
else()
	if("${CMAKE_BUILD_TYPE}" EQUAL "Debug")
		link_directories(AFTER "${VCPKG_INSTALL}/${CMAKE_BUILD_TYPE}/lib")
	else()
		link_directories(AFTER "${VCPKG_INSTALL}/lib")
	endif()
endif()

message ( "Toolchain=${CMAKE_TOOLCHAIN_FILE}, CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}, VCPKG_INSTALL=${VCPKG_INSTALL}" )


set(THIRDPARTY_LIBS )


find_package(ZLIB REQUIRED)
list(APPEND THIRDPARTY_LIBS ${LIBZLIB_LIBRARY})

find_package(LibLZMA REQUIRED)
#list(APPEND THIRDPARTY_LIBS liblzma::liblzma)
list(APPEND THIRDPARTY_LIBS ${LIBLZMA_LIBRARY})

find_package(jsoncpp CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS JsonCpp::JsonCpp)
#list(APPEND THIRDPARTY_LIBS jsoncpp)

#find_package(jansson CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS jansson)

#find_package(avro-c CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS avro)

#find_package(PNG CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS libpng16)

#find_package(jasper CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS jasper)

find_package(OpenEXR CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS OpenEXR::Iex OpenEXR::IlmThread OpenEXR::OpenEXR OpenEXR::OpenEXRCore OpenEXR::OpenEXRUtil)

#find_package(Devil CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS devil jpeg)


find_package(Freetype CONFIG REQUIRED)
#unlike usage this doesn't work
#list(APPEND THIRDPARTY_LIBS Freetype::Freetype)
list(APPEND THIRDPARTY_LIBS freetype)

#find_package(libiconv CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS iconv)

find_package(OpenSSL REQUIRED)
list(APPEND THIRDPARTY_LIBS OpenSSL::SSL OpenSSL::Crypto)

find_package(tinyxml2 CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS tinyxml2::tinyxml2)

find_package(LibXml2 REQUIRED)
list(APPEND THIRDPARTY_LIBS LibXml2::LibXml2)

find_package(libuv CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS $<IF:$<TARGET_EXISTS:uv_a>,uv_a,uv>)

find_package(Libevent CONFIG REQUIRED)
#list(APPEND THIRDPARTY_LIBS libevent::core libevent::extra libevent::pthreads)
list(APPEND THIRDPARTY_LIBS libevent::core libevent::extra)

find_package(CURL CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS CURL::libcurl)

# find_package(RdKafka CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS RdKafka::rdkafka RdKafka::rdkafka++)

# find_package(mongoc-1.0 CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS $<IF:$<TARGET_EXISTS:mongo::mongoc_shared>,mongo::mongoc_shared,mongo::mongoc_static>)

#find_package(bson CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS $<IF:$<TARGET_EXISTS:mongo::bson_static>,mongo::bson_static,mongo::bson_shared>)

# find_package(unofficial-mysql-connector-cpp CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS unofficial::mysql-connector-cpp::connector)

# add_definitions(-DTHREADED) # for zookeeper
# add_definitions(-DUSE_STATIC_LIB) # for zookeeper
# find_package(zookeeper CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS zookeeper::hashtable zookeeper::zookeeper)


# find_package(Ogg CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS Ogg::ogg)

# find_package(FLAC CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS FLAC::FLAC)

# # Or use the C++ API
# find_package(FLAC CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS FLAC::FLAC++)

# find_package(Opus CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS Opus::opus)

# find_package(SndFile CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS SndFile::sndfile)

# find_package(Protobuf CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

# find_package(libwebsockets CONFIG REQUIRED)
# list(APPEND THIRDPARTY_LIBS websockets)



add_definitions(-DHAVE_CONFIG_H=1)
add_definitions(-DCURL_STATICLIB)
add_definitions(-DHAVE_STDDEF_H=1)
add_definitions(-DHAVE_SYS_TYPES_H=1)
#add_definitions(-DSF_USE_MBEDTLS)
#add_definitions(-DLIBRDKAFKA_STATICLIB) # for rdkafka static lib
#add_definitions(-DBSON_STATIC) # bson static lib


set(LIB_INSTALL_DIR lib)



add_subdirectory(src/SFWinport)



