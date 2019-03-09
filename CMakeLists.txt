cmake_minimum_required(VERSION 3.7)


project(StormForge)



if (CMAKE_SYSTEM_NAME=Android)
	set(CMAKE_ANDROID_NDK /path/to/android-ndk)
	#set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)
	#set(CMAKE_ANDROID_ARCH_ABI armeabi-v7a)
	set(CMAKE_ANDROID_NDK "${ANDROID_NDK_ROOT}")
	#set(CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION)
	set(CMAKE_ANDROID_STL_TYPE c++_static)
	set(CMAKE_ANDROID_API_MIN 23)
	set(CMAKE_ANDROID_API 25)
	set(CMAKE_ANDROID_GUI 1)
	set(PROJECT_OUTPUT_DIRNAME "${CMAKE_SYSTEM_NAME}${CMAKE_ANDROID_ARCH_ABI}")
	
	add_definitions(NOMINMAX)
elseif (CMAKE_SYSTEM_NAME=Windows)
elseif (CMAKE_SYSTEM_NAME=Linux)
elseif (CMAKE_SYSTEM_NAME=Darwin ) #OSX
endif (CMAKE_SYSTEM_NAME=Android)


set(CMAKE_CXX_STANDARD 17)
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/${PROJECT_OUTPUT_DIRNAME}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib/${PROJECT_OUTPUT_DIRNAME}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib/${PROJECT_OUTPUT_DIRNAME}")


add_definitions(HAVE_CONFIG_H)
add_definitions(CURL_STATICLIB)
add_definitions(HAVE_STDDEF_H=1)
add_definitions(HAVE_SYS_TYPES_H=1)

include_directories(AFTER 
	Bin/lib/Android/openssl/${CMAKE_SYSTEM_NAME}/include
	3rdParties/src/libiconv/libiconv-1.14/include
	3rdParties/src/libpng/lpng1617
	Engine/Src/SFCore
	Engine/Src/SFEngine
	Engine/Src/Protocol
	)

#string(REGEX MATCH "Clang" CMAKE_COMPILER_IS_CLANG "${CMAKE_C_COMPILER_ID}")
#string(REGEX MATCH "GNU" CMAKE_COMPILER_IS_GNU "${CMAKE_C_COMPILER_ID}")
#string(REGEX MATCH "IAR" CMAKE_COMPILER_IS_IAR "${CMAKE_C_COMPILER_ID}")
#string(REGEX MATCH "MSVC" CMAKE_COMPILER_IS_MSVC "${CMAKE_C_COMPILER_ID}")



#include_directories(include/)



add_subdirectory(Engine/Src/SFCore)
add_subdirectory(Engine/Src/SFEngine)
add_subdirectory(Engine/Src/Protocol)
add_subdirectory(Engine/Src/SFEngineDLL)



