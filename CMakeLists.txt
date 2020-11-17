
cmake_minimum_required(VERSION 3.16)

include (build/StormForge.cmake)

project(StormForge C CXX)

include_directories(AFTER 
	3rdParties/src/mbedtls/mbedtls-2.16.0/include
	3rdParties/src/libiconv/libiconv-1.15/include
	3rdParties/src/libpng/lpng1617
	3rdParties/src/jpeg/jpeg-9a
	3rdParties/src/libxml/libxml2/include
	3rdParties/src/curl/curl/include
	3rdParties/src/zlib/zlib-1.2.8
	3rdParties/src/jsoncpp/jsoncpp/include
	3rdParties/src/zookeeper/zookeeperConnector/include
	3rdParties/src/PlayFab/XPlatCppSdk/code/include
	Engine/Src/SFCore
	Engine/Src/SFEngine
	Engine/Src/Protocol
	)



if(WIN32)

	include_directories(AFTER 
		../VulkanSDK/include
		3rdParties/src/mysql/buildWindows/${ARTECTURE}/include
	)
	
elseif(ANDROID_PLATFORM)

elseif(IOS)

elseif(UNIX)
	
endif()


include_directories(AFTER 
	3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/include
)
	
link_directories(BEFORE 3rdParties/${CMAKE_SYSTEM_NAME}/${ARTECTURE}/lib)

#set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})




add_subdirectory(Engine/Src/SFCore)
add_subdirectory(Engine/Src/SFEngine)
add_subdirectory(Engine/Src/Protocol)
add_subdirectory(Engine/Src/SFEngineDLL)
add_subdirectory(Test)




