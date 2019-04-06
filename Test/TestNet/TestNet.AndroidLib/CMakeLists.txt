


set(LIB_FILES
	SFTestJni.cpp
	../TestNet.Shared/TestNetNative.cpp
	../TestNet.Shared/Cube.cpp
  )


include_directories(AFTER
	../TestNet.Shared
)

add_library(TestNet_AndroidLib SHARED ${LIB_FILES})


add_dependencies(TestNet_AndroidLib SFCore SFEngine SFProtocol curl iconv)

target_link_libraries(TestNet_AndroidLib ${ENGINE_LINK_LIBS} ${PLATFORM_LIBS})


install (TARGETS TestNet_AndroidLib
         ARCHIVE DESTINATION test COMPONENT StormForgeTest
         LIBRARY DESTINATION test COMPONENT StormForgeTest
         RUNTIME DESTINATION test COMPONENT StormForgeTest)

