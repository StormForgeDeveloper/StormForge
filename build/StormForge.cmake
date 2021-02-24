
cmake_minimum_required(VERSION 3.16)

message ( "Platform=${CMAKE_SYSTEM_NAME}, Config=${CMAKE_BUILD_TYPE}" )



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

if(WIN32) # MSVC isn't consistent. let's use WIN32 for windows
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
	set(ENABLE_CLANG OFF)
else()
	set(ENABLE_CLANG ON)
endif()


if(ENABLE_CLANG)
	set(CMAKE_C_COMPILER clang)
	set(CMAKE_CXX_COMPILER clang++)
endif(ENABLE_CLANG)

IF(NOT SF_FOLDER)
   SET(SF_FOLDER StormForge)
ENDIF()


#add_definitions(-DNOMINMAX)
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DCURL_STATICLIB)
add_definitions(-DHAVE_STDDEF_H=1)
add_definitions(-DHAVE_SYS_TYPES_H=1)
add_definitions(-DSF_USE_MBEDTLS)
#add_definitions(-DLIBICONV_PLUG)
add_definitions(-DENABLE_PLAYFABSERVER_API)
add_definitions(-DTHREADED) # for zookeeper
add_definitions(-DUSE_STATIC_LIB) # for zookeeper
add_definitions(-DLIBRDKAFKA_STATICLIB) # for rdkafka static lib

add_definitions(-DSF_USE_MBEDTLS)

SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG=1")
SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG=1")


include_directories(AFTER 
	../${SF_FOLDER}/3rdParties/src/mbedtls/mbedtls-2.16.0/include
	../${SF_FOLDER}/3rdParties/src/libiconv/libiconv-1.15/include
	../${SF_FOLDER}/3rdParties/src/libpng/lpng1617
	../${SF_FOLDER}/3rdParties/src/jpeg/jpeg-9a
	../${SF_FOLDER}/3rdParties/src/libxml/libxml2/include
	../${SF_FOLDER}/3rdParties/src/curl/curl/include
	../${SF_FOLDER}/3rdParties/src/zlib/zlib-1.2.8
	../${SF_FOLDER}/3rdParties/src/jsoncpp/jsoncpp/include
	../${SF_FOLDER}/3rdParties/src/zookeeper/zookeeperConnector/include
	../${SF_FOLDER}/Engine/Src/SFCore
	../${SF_FOLDER}/Engine/Src/SFEngine
	../${SF_FOLDER}/Engine/Src/Protocol
)


set(ENGINE_LINK_LIBS SFProtocol SFEngine  SFCore  curl rdkafka iconv png mng jpeg tiff zookeeper jsoncpp mbedtls xml2 zlib)


if(WIN32)

	message ( "Setup Windows configs" )

	add_definitions(-DNOMINMAX)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	add_definitions(-DWIN64)
	add_definitions(-DWIN32)
	add_definitions(-D_WINDOWS)
	add_definitions(-DSTATIC_CONCPP) # mysql cpp conn static


	#always use debug info
	if (ENABLE_CLANG)
		SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
		SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
		SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -Oy-")
		SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Oy-")
		SET (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g")
		SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g")
	else()
		SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Od")
		SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Od")
		SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -Oy-")
		SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Oy-")
		SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Zi")
		SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /Zi")
	endif()

	set(ARTECTURE x64)

	set(PLATFORM_LIBS Ws2_32 Mswsock Shlwapi mysqlcppconn8-static Dnsapi bson-static-1.0 mongoc-static-1.0)
	list(APPEND ENGINE_LINK_LIBS libssl libcrypto)
	
	include_directories(AFTER 
		$ENV{VK_SDK_PATH}/include
		../${SF_FOLDER}/3rdParties/src/mysql/buildWindows/${ARTECTURE}/include
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/$(Configuration)/include
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/mongoc/$(Configuration)/include/libbson-1.0
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/mongoc/$(Configuration)/include/libmongoc-1.0
	)

	link_directories(
		../${SF_FOLDER}/3rdParties/src/openssl/buildWIndows/openssl/lib
		../${SF_FOLDER}/3rdParties/src/mysql/buildWindows/${ARTECTURE}/lib64/vs14/$(Configuration)
		../${SF_FOLDER}/3rdParties/src/mysql/buildWindows/${ARTECTURE}/lib64/vs14
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/$(Configuration)/lib
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/mongoc/$(Configuration)/lib
	)
	
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})


elseif(ANDROID_PLATFORM)

	message ( "Setup Android configs" )

	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -frtti -pthread -fPIC")
 
	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
	SET (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g")

	add_definitions(-D__ANDROID__=1)

	set(PLATFORM_LIBS android jnigraphics log GLESv1_CM GLESv2 EGL)
	list(APPEND ENGINE_LINK_LIBS ssl crypto)

	set(ARTECTURE ${CMAKE_ANDROID_ARCH_ABI})

elseif(IOS)

	message ( "Setup IOS configs" )

	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -frtti -pthread -fPIC")

	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
	SET (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g")

	add_definitions(-D__IOS__=1)
	add_definitions(-DKQUEUE)


	list(APPEND ENGINE_LINK_LIBS ssl crypto)

	set(ARTECTURE ${CMAKE_OSX_ARCHITECTURES})

elseif(UNIX)

	message ( "Setup UNIX configs" )

	SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   -g -frtti -pthread -fPIC")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -fexceptions -frtti -pthread -fPIC")

	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_DEBUG} -O3")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3")

	add_definitions(-D_LINUX_=1)
	add_definitions(-DEPOLL)

	set(PLATFORM_LIBS bson-static-1.0 mongoc-static-1.0 mysqlcppconn8 rt m atomic)
	list(APPEND ENGINE_LINK_LIBS ssl crypto)

	set(ARTECTURE x64)


	include_directories(AFTER 
		/usr/include/mysql-cppconn-8
		/usr/include/vulkan
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/${CMAKE_BUILD_TYPE}/include
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/mongoc/${CMAKE_BUILD_TYPE}/include/libbson-1.0
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/mongoc/${CMAKE_BUILD_TYPE}/include/libmongoc-1.0
	)
	
	link_directories(
		/usr/lib
		/usr/lib/x86_64-linux-gnu/
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/lib
		../${SF_FOLDER}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE}/lib
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/${CMAKE_BUILD_TYPE}/lib
		../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/mongoc/${CMAKE_BUILD_TYPE}/lib
		)

endif()


include_directories(AFTER 
	../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/include
)

#message ("../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/${CMAKE_BUILD_TYPE}/include")
	
link_directories(BEFORE 
	../${SF_FOLDER}/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/lib
)

