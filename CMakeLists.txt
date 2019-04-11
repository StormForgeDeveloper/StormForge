
cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER clang++)


project(StormForge C CXX)


message ( "Input system = ${CMAKE_SYSTEM_NAME}" )


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

SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")


set(ENGINE_LINK_LIBS SFProtocol SFEngine  SFCore  curl iconv png mng jpeg tiff zookeeper jsoncpp mbedtls xml2 zlib)


include_directories(AFTER 
	3rdParties/src/mbedtls/mbedtls-2.16.0/include
	3rdParties/src/libiconv/libiconv-1.15/include
	3rdParties/src/libpng/lpng1617
	3rdParties/src/jpeg/jpeg-9a
	3rdParties/src/libxml/libxml2/include
	3rdParties/src/curl/curl/include
	3rdParties/src/zlib/zlib-1.2.8
	3rdParties/src/jsoncpp/include
	3rdParties/src/zookeeper/zookeeperConnector/include
	Engine/Src/SFCore
	Engine/Src/SFEngine
	Engine/Src/Protocol
	)



if(WIN32)

	message ( "Setup Windows configs" )

	add_definitions(-DNOMINMAX)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	add_definitions(-DWIN64)
	add_definitions(-DWIN32)
	add_definitions(-D_WINDOWS)


	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Od")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Od")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -Oy-")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Oy-")

	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

	include_directories(AFTER 
		3rdParties/VulkanSDK/1.1.82.1/include
	)
	
	set(ARTECTURE x64)

	set(PLATFORM_LIBS Ws2_32 Mswsock)
	
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

	include_directories(AFTER 
		/usr/include/mysql
		#3rdParties/VulkanSDK/1.1.82.1/include
	)
	
	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})

	set(ARTECTURE x64)


endif()




#set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})



add_subdirectory(3rdParties)
add_subdirectory(Engine/Src/SFCore)
add_subdirectory(Engine/Src/SFEngine)
add_subdirectory(Engine/Src/Protocol)
add_subdirectory(Engine/Src/SFEngineDLL)
add_subdirectory(Test)




