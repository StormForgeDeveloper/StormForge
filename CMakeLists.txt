
cmake_minimum_required(VERSION 3.10)


project(StormForge C CXX)


message ( "Input system = ${CMAKE_SYSTEM_NAME}" )


set(CMAKE_CXX_STANDARD 17)
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)


# set(cmake_runtime_output_directory "${project_binary_dir}/bin/${project_output_dirname}")
# set(cmake_library_output_directory "${project_binary_dir}/lib/${project_output_dirname}")
# set(cmake_archive_output_directory "${project_binary_dir}/lib/${project_output_dirname}")


set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER clang++)




add_definitions(-DNOMINMAX)
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DCURL_STATICLIB)
add_definitions(-DHAVE_STDDEF_H=1)
add_definitions(-DHAVE_SYS_TYPES_H=1)
add_definitions(-DSF_USE_MBEDTLS)



include_directories(AFTER 
	#Bin/lib/Android/openssl/${CMAKE_SYSTEM_NAME}/include
	3rdParties/src/mbedtls/mbedtls-2.16.0/include
	3rdParties/src/libiconv/libiconv-1.14/include
	3rdParties/src/libpng/lpng1617
	3rdParties/src/jpeg/jpeg-9a
	3rdParties/src/libxml/libxml2/include
	Engine/Src/SFCore
	Engine/Src/SFEngine
	Engine/Src/Protocol
	)

#string(REGEX MATCH "Clang" CMAKE_COMPILER_IS_CLANG "${CMAKE_C_COMPILER_ID}")
#string(REGEX MATCH "GNU" CMAKE_COMPILER_IS_GNU "${CMAKE_C_COMPILER_ID}")
#string(REGEX MATCH "IAR" CMAKE_COMPILER_IS_IAR "${CMAKE_C_COMPILER_ID}")
#string(REGEX MATCH "MSVC" CMAKE_COMPILER_IS_MSVC "${CMAKE_C_COMPILER_ID}")






add_subdirectory(Engine/Src/SFCore)
add_subdirectory(Engine/Src/SFEngine)
add_subdirectory(Engine/Src/Protocol)
add_subdirectory(Engine/Src/SFEngineDLL)



