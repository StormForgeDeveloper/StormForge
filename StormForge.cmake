


message ( "Platform=${CMAKE_SYSTEM_NAME}, Config=${CMAKE_BUILD_TYPE}" )


set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11


if(WIN32) # MSVC isn't consistent. let's use WIN32 for windows
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++23")
    set(CMAKE_CXX_STANDARD 23)
	set(ENABLE_CLANG OFF)
else()
	#set(ENABLE_CLANG ON)
    set(CMAKE_CXX_STANDARD 20)
    set(ENABLE_CLANG ON)
endif()



if(ENABLE_CLANG)
	set(CMAKE_C_COMPILER clang)
	set(CMAKE_CXX_COMPILER clang++)
endif(ENABLE_CLANG)



IF (NOT DEFINED ${SF_DIR})
	# Use script file directory
	SET(SF_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()

message ( "SF_DIR=${SF_DIR}" )


IF(NOT DEFINED ${VCPKG_DIR})
	set(VCPKG_DIR "${SF_DIR}/vcpkg")
	message ( "Setup default VCPKG_DIR=${VCPKG_DIR}" )
ENDIF()
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
	set(VCPKG_SHARED_TRIPLET ${ARTECTURE}-windows)

elseif(ANDROID_PLATFORM)

	message ( "Setup Android configs" )

	add_definitions(-D__ANDROID__=1)

	set(ARTECTURE ${CMAKE_ANDROID_ARCH_ABI})
	set(VCPKG_TARGET_TRIPLET ${ARTECTURE}-android)
	set(VCPKG_SHARED_TRIPLET ${VCPKG_TARGET_TRIPLET})

elseif(IOS)

	message ( "Setup IOS configs" )

	add_definitions(-D__IOS__=1)
	add_definitions(-DKQUEUE)
	set(CMAKE_MACOSX_RPATH 1)

	set(ARTECTURE ${CMAKE_OSX_ARCHITECTURES})
	set(VCPKG_TARGET_TRIPLET ${ARTECTURE}-ios)
	set(VCPKG_SHARED_TRIPLET ${VCPKG_TARGET_TRIPLET})

elseif(UNIX)

	message ( "Setup UNIX configs" )

	add_definitions(-D_LINUX_=1)
	add_definitions(-DEPOLL)

	set(ARTECTURE x64)
	set(VCPKG_TARGET_TRIPLET ${ARTECTURE}-linux)
	set(VCPKG_SHARED_TRIPLET ${VCPKG_TARGET_TRIPLET})

endif()


set(VCPKG_INSTALL ${VCPKG_DIR}/installed/${VCPKG_TARGET_TRIPLET})
set(CMAKE_PREFIX_PATH  "${VCPKG_INSTALL}/")
set(Protobuf_PROTOC_EXECUTABLE "${VCPKG_INSTALL}/tools/protobuf/protoc")

#for shared library search path on linux
set(CMAKE_INSTALL_RPATH $ORIGIN)

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

message ( "Toolchain=${CMAKE_TOOLCHAIN_FILE}, CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}, VCPKG_INSTALL=${VCPKG_INSTALL}, VCPKG_INCLUDE=${VCPKG_INSTALL}/include" )



set(THIRDPARTY_LIBS )


find_package(ZLIB REQUIRED)
list(APPEND THIRDPARTY_LIBS ${ZLIB_LIBRARY})

find_package(LibLZMA REQUIRED)
#list(APPEND THIRDPARTY_LIBS liblzma::liblzma)
list(APPEND THIRDPARTY_LIBS ${LIBLZMA_LIBRARY})

find_package(jsoncpp CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS JsonCpp::JsonCpp)

#find_package(jansson CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS jansson)

#find_package(avro-c CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS avro)

#find_package(PNG CONFIG REQUIRED)
#list(APPEND THIRDPARTY_LIBS png16)
list(APPEND THIRDPARTY_LIBS ${PNG_LIBRARY})

#find_package(jasper CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS jasper)

find_package(OpenEXR CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS OpenEXR::Iex OpenEXR::IlmThread OpenEXR::OpenEXR OpenEXR::OpenEXRCore OpenEXR::OpenEXRUtil)

find_package(libjpeg-turbo CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS libjpeg-turbo::jpeg-static)

find_package(Freetype CONFIG REQUIRED)
#unlike usage this doesn't work
#list(APPEND THIRDPARTY_LIBS Freetype::Freetype)
list(APPEND THIRDPARTY_LIBS freetype)

#find_package(Iconv CONFIG REQUIRED)
if(WIN32)
	list(APPEND THIRDPARTY_LIBS iconv)
else()
	list(APPEND THIRDPARTY_LIBS ${Iconv_LIBRARIES})
endif()

find_package(OpenSSL REQUIRED)
if(MSVC)
    #list(APPEND THIRDPARTY_LIBS OpenSSL::SSL OpenSSL::Crypto)
 	list(APPEND THIRDPARTY_LIBS libssl libcrypto)
else()
	list(APPEND THIRDPARTY_LIBS ssl crypto)
 endif()

find_package(tinyxml2 CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS tinyxml2::tinyxml2)

find_package(LibXml2 REQUIRED)
list(APPEND THIRDPARTY_LIBS LibXml2::LibXml2)

find_package(libwebsockets CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS websockets)

find_package(libuv CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>)

find_package(Libevent CONFIG REQUIRED)
#list(APPEND THIRDPARTY_LIBS libevent::core libevent::extra libevent::pthreads)
list(APPEND THIRDPARTY_LIBS libevent::core libevent::extra)

find_package(CURL CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS CURL::libcurl)

if (WIN32)
else()
	#list(APPEND THIRDPARTY_LIBS icudt icuin icuio icuuc icudata)
	list(APPEND THIRDPARTY_LIBS icuio icuuc icudata)
endif()


find_package(RdKafka CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS RdKafka::rdkafka RdKafka::rdkafka++)


find_package(Ogg CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS Ogg::ogg)

find_package(FLAC CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS FLAC::FLAC)

# Or use the C++ API
find_package(FLAC CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS FLAC::FLAC++)

find_package(Opus CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS Opus::opus)

find_package(SndFile CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS SndFile::sndfile)

find_package(OpenAL CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS OpenAL::OpenAL)

list(APPEND THIRDPARTY_LIBS flatbuffers)

find_package(Protobuf CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

find_package(gRPC CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts)

find_package(recastnavigation CONFIG REQUIRED)
list(APPEND THIRDPARTY_LIBS RecastNavigation::Detour RecastNavigation::Recast RecastNavigation::DebugUtils RecastNavigation::DetourCrowd)



add_definitions(-DHAVE_CONFIG_H=1)
add_definitions(-DCURL_STATICLIB)
add_definitions(-DHAVE_STDDEF_H=1)
add_definitions(-DHAVE_SYS_TYPES_H=1)
#add_definitions(-DLIBRDKAFKA_STATICLIB) # for rdkafka static lib
#add_definitions(-DBSON_STATIC) # bson static lib


##add_definitions(-DLIBICONV_PLUG)


SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG=1")
SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG=1")


include_directories(AFTER 
	${SF_DIR}/Engine/Src/SFCore
	${SF_DIR}/Engine/Src/SFEngine
	${SF_DIR}/Engine/Src/Protocol
	${SF_DIR}/Engine/Src/Protocol/SFFlat
)

set(ENGINE_LINK_LIBS SFProtocol SFEngine SFProtocol SFEngine SFCore)

list(APPEND ENGINE_LINK_LIBS ${THIRDPARTY_LIBS})

if(WIN32)

	message ( "Setup Windows configs" )

	add_definitions(-DNOMINMAX)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	add_definitions(-DWIN64)
	add_definitions(-DWIN32)
	add_definitions(-D_WINDOWS)

	#always use debug info
	if (ENABLE_CLANG)
		SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
		SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
		SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -Oy-")
		SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Oy-")
		SET (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nonportable-include-path -fexceptions -msimd128 -g")
		SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nonportable-include-path -fexceptions -msimd128 -g")
	else()
		SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Od")
		SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Od")
		SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -Oy-")
		SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Oy-")
		# don't enable /WX. we share this setting with 3rd parties which have a lot of warnings
		SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Zi /W4")
		SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /Zi /W4")
	endif()


	set(PLATFORM_LIBS Ws2_32 Mswsock Shlwapi Userenv Bcrypt Crypt32 Dnsapi)
	
	include_directories(AFTER 
		$ENV{VK_SDK_PATH}/include
	#	${SF_DIR}/3rdParties/${CMAKE_SYSTEM_NAME}/$(Configuration)/include
	)

	# link_directories(
		# ${SF_DIR}/3rdParties/${CMAKE_SYSTEM_NAME}/$(Configuration)/lib
	# )
	
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})


elseif(ANDROID_PLATFORM)

	message ( "Setup Android configs" )
 
	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

	SET (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nonportable-include-path -fexceptions -frtti -pthread -fPIC -g")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nonportable-include-path -fexceptions -frtti -pthread -fPIC -g")

	add_definitions(-D__ANDROID__=1)

	set(PLATFORM_LIBS android jnigraphics log GLESv1_CM GLESv2 EGL)
	#list(APPEND ENGINE_LINK_LIBS ssl crypto)


elseif(IOS)

	message ( "Setup IOS configs" )

	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -frtti -pthread -fPIC")

	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

	SET (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nonportable-include-path -fexceptions -g")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nonportable-include-path -fexceptions -g")

	add_definitions(-D__IOS__=1)
	add_definitions(-DKQUEUE)


	#list(APPEND ENGINE_LINK_LIBS ssl crypto)


elseif(UNIX)

	message ( "Setup UNIX configs" )
	#-lstdc++exp
	SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   -Wno-nonportable-include-path -Wno-ambiguous-reversed-operator -g -frtti -pthread -march=native -msse4 -m64 -fPIC")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-nonportable-include-path -Wno-ambiguous-reversed-operator -g -fexceptions -frtti -march=native -pthread -msse4 -m64 -fPIC")

	SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

	SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

	add_definitions(-D_LINUX_=1)
	add_definitions(-DEPOLL)


	set(PLATFORM_LIBS rt m atomic resolv)

	include_directories(AFTER 
		/usr/include
		/usr/include/vulkan
		${SF_DIR}/3rdParties/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/include
		#${SF_DIR}/3rdParties/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/include/libmemcached
	)
	

	link_directories(
		/usr/lib
		/usr/lib/x86_64-linux-gnu/
		${SF_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE}/lib
		#${SF_DIR}/3rdParties/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib
		)

endif()

include_directories(AFTER 
	${SF_DIR}/3rdParties/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/include
	${SF_DIR}/3rdParties/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/include/libmemcached
)

link_directories(
	${SF_DIR}/3rdParties/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib
	)

