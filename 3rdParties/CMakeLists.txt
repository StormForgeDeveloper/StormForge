



set(CMAKE_USE_MBEDTLS ON)

set(LIB_INSTALL_DIR bin/lib)

add_definitions(-DNOMINMAX)
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DCURL_STATICLIB)
add_definitions(-DHAVE_STDDEF_H=1)
add_definitions(-DHAVE_SYS_TYPES_H=1)



include_directories(AFTER 
	src/curl/curl
	src/libiconv/libiconv-1.15/include
	src/mbedtls/mbedtls-2.16.0/include
	src/libpng/lpng1617
	src/zlib/zlib-1.2.8
)



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


