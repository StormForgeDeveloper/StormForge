
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


# set(cmake_runtime_output_directory "${project_binary_dir}/bin/${project_output_dirname}")
# set(cmake_library_output_directory "${project_binary_dir}/lib/${project_output_dirname}")
# set(cmake_archive_output_directory "${project_binary_dir}/lib/${project_output_dirname}")






#add_definitions(-DNOMINMAX)
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DCURL_STATICLIB)
add_definitions(-DHAVE_STDDEF_H=1)
add_definitions(-DHAVE_SYS_TYPES_H=1)
add_definitions(-DSF_USE_MBEDTLS)
#add_definitions(-DLIBICONV_PLUG)


include_directories(AFTER 
	3rdParties/src/mbedtls/mbedtls-2.16.0/include
	3rdParties/src/libiconv/libiconv-1.15/include
	3rdParties/src/libpng/lpng1617
	3rdParties/src/jpeg/jpeg-9a
	3rdParties/src/libxml/libxml2/include
	3rdParties/src/curl/curl
	3rdParties/src/zlib/zlib-1.2.8
	3rdParties/src/jsoncpp/include
	3rdParties/src/zookeeper/zookeeperConnector/include
	Engine/Src/SFCore
	Engine/Src/SFEngine
	Engine/Src/Protocol
	)

if(WIN32)

	add_definitions(-DNOMINMAX)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	add_definitions(-DWIN64)
	add_definitions(-DWIN32)
	add_definitions(-D_WINDOWS)


	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

	include_directories(AFTER 
		3rdParties/VulkanSDK/1.1.82.1/include
	)

	set(PLATFORM_LIBS Ws2_32 Mswsock)
else()
	set(PLATFORM_LIBS android jnigraphics log)
endif()



#string(REGEX MATCH "Clang" CMAKE_COMPILER_IS_CLANG "${CMAKE_C_COMPILER_ID}")
#string(REGEX MATCH "GNU" CMAKE_COMPILER_IS_GNU "${CMAKE_C_COMPILER_ID}")
#string(REGEX MATCH "IAR" CMAKE_COMPILER_IS_IAR "${CMAKE_C_COMPILER_ID}")
#string(REGEX MATCH "MSVC" CMAKE_COMPILER_IS_MSVC "${CMAKE_C_COMPILER_ID}")






add_subdirectory(3rdParties)
add_subdirectory(Engine/Src/SFCore)
add_subdirectory(Engine/Src/SFEngine)
add_subdirectory(Engine/Src/Protocol)
add_subdirectory(Engine/Src/SFEngineDLL)



