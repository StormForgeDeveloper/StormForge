
cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER clang++)



message ( "Platform=${CMAKE_SYSTEM_NAME}, Config=${CMAKE_BUILD_TYPE}" )


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)


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
	../StormForge/3rdParties/src/mbedtls/mbedtls-2.16.0/include
	../StormForge/3rdParties/src/libiconv/libiconv-1.15/include
	../StormForge/3rdParties/src/libpng/lpng1617
	../StormForge/3rdParties/src/jpeg/jpeg-9a
	../StormForge/3rdParties/src/libxml/libxml2/include
	../StormForge/3rdParties/src/curl/curl/include
	../StormForge/3rdParties/src/zlib/zlib-1.2.8
	../StormForge/3rdParties/src/jsoncpp/jsoncpp/include
	../StormForge/3rdParties/src/zookeeper/zookeeperConnector/include
	../StormForge/3rdParties/src/PlayFab/XPlatCppSdk/code/include
	../StormForge/Engine/Src/SFCore
	../StormForge/Engine/Src/SFEngine
	../StormForge/Engine/Src/Protocol
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

	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Od")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Od")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -Oy-")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Oy-")

	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

	set(ARTECTURE x64)

	set(PLATFORM_LIBS Ws2_32 Mswsock Shlwapi mysqlcppconn8-static Dnsapi)
	list(APPEND ENGINE_LINK_LIBS libssl libcrypto)
	
	include_directories(AFTER 
		../VulkanSDK/include
		../StormForge/3rdParties/src/mysql/buildWindows/${ARTECTURE}/include
	)

	link_directories(
		../StormForge/3rdParties/src/openssl/buildWIndows/openssl/lib
		../StormForge/3rdParties/src/mysql/buildWindows/${ARTECTURE}/lib64/vs14/$(Configuration)
		../StormForge/3rdParties/src/mysql/buildWindows/${ARTECTURE}/lib64/vs14
)
	
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})
	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}$(Configuration))

elseif(ANDROID_PLATFORM)

	message ( "Setup Android configs" )

	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -frtti -pthread -fPIC")
 
	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

	add_definitions(-D__ANDROID__=1)

	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})

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

	add_definitions(-D__IOS__=1)
	add_definitions(-DKQUEUE)


	list(APPEND ENGINE_LINK_LIBS ssl crypto)

	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})

	set(ARTECTURE ${CMAKE_OSX_ARCHITECTURES})

elseif(UNIX)

	message ( "Setup UNIX configs" )

	SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fexceptions -frtti -pthread -fPIC")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fexceptions -frtti -pthread -fPIC")

	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_DEBUG} -O3")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3")


	add_definitions(-D_LINUX_=1)
	add_definitions(-DEPOLL)

	set(PLATFORM_LIBS rt m)
	list(APPEND ENGINE_LINK_LIBS ssl crypto)

	include_directories(AFTER 
		/usr/include/mysql-cppconn-8
		/usr/include/vulkan
	)
	
	link_directories(
		/usr/lib
		/usr/lib/x86_64-linux-gnu/
		#/usr/local/mysql/connector-c++-8.0/lib64/debug
		#../StormForge/3rdParties/src/mysql/linuxLib/lib64
		../StormForge/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/lib
		../StormForge/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE}/lib
		)

	set(PLATFORM_LIBS mysqlcppconn8 rt m)

	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})

	set(ARTECTURE x64)


endif()


include_directories(AFTER 
	../StormForge/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/include
	../StormForge/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/${CMAKE_BUILD_TYPE}/include
)

#message ("../StormForge/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/${CMAKE_BUILD_TYPE}/include")
	
link_directories(BEFORE 
	../StormForge/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/lib
	../StormForge/3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/${CMAKE_BUILD_TYPE}/lib
)

