

include_directories(
	./
	)


set(SF_STRINGCRCBIN_FILES
	SFStringCrcBin.cpp
  )


add_executable(SFStringCrcBin ${SF_STRINGCRCBIN_FILES})

if(MSVC)
    target_link_options(SFStringCrcBin PRIVATE "LINKER:/NODEFAULTLIB:libcrypto64MDd,/Debug")
endif()

target_link_libraries(SFStringCrcBin ${ENGINE_LINK_LIBS} SFProtocol ${ENGINE_LINK_LIBS} ${PLATFORM_LIBS})


install (TARGETS SFStringCrcBin
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)
