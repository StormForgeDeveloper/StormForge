
cmake_minimum_required(VERSION 3.16)
include(../build/StormForge.cmake)


project(SF3rdParties C CXX)


set(CMAKE_USE_MBEDTLS ON)

set(LIB_INSTALL_DIR lib)


include_directories(AFTER 
	src/mbedtls/mbedtls-2.16.0/include
	src/libiconv/libiconv-1.15/include
	src/libpng/lpng1617
	src/jpeg/jpeg-9a
	src/libxml/libxml2/include
	src/curl/curl/include
	src/zlib/zlib-1.2.8
	src/jsoncpp/jsoncpp/include
	src/zookeeper/zookeeperConnector/include
	#src/PlayFab/XPlatCppSdk/code/include
)



if(WIN32)

	include_directories(AFTER 
		src/mysql-connector-c++-8.0.18-winx64/include
	)

elseif(ANDROID_PLATFORM)

elseif(IOS)

elseif(UNIX)

endif()



add_subdirectory(src/libiconv)
add_subdirectory(src/curl)
add_subdirectory(src/freetype)
add_subdirectory(src/gtest)
add_subdirectory(src/jasper)
add_subdirectory(src/jpeg)
add_subdirectory(src/jsoncpp)
add_subdirectory(src/lcms)
add_subdirectory(src/libmng)
add_subdirectory(src/libtiff)
add_subdirectory(src/libxml)
add_subdirectory(src/libpng)
add_subdirectory(src/mbedtls)
add_subdirectory(src/memcached)
add_subdirectory(src/rdkafka)
add_subdirectory(src/tinyxml)
add_subdirectory(src/zlib)
add_subdirectory(src/yaml)
add_subdirectory(src/zookeeper)
add_subdirectory(src/SFWinport)
#add_subdirectory(src/PlayFab)


#install(TARGETS src/libiconv/iconv curl freetype gtest jasper jpeg jsoncpp lcms mng tiff xml png mbedtls rdkafka tinyxml zlib yaml DESTINATION bin/lib)

