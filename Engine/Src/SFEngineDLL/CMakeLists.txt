

set(SF_ENGINEDLL_PATH .)

include (SFEngineDLLFileList.cmake)


add_library(SFEngineDLL SHARED ${SFENGINEDLL_LIB_FILES})


add_dependencies(SFEngineDLL SFCore SFEngine SFProtocol)

target_precompile_headers(SFEngineDLL PUBLIC SFEngineDLLPCH.h)

target_link_libraries(SFEngineDLL ${ENGINE_LINK_LIBS} ${PLATFORM_LIBS})

target_include_directories (SFEngineDLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)

install (TARGETS SFEngineDLL
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)

if(WIN32 AND NOT ENABLE_CLANG)
	install (FILES $<TARGET_PDB_FILE:SFEngineDLL> DESTINATION bin COMPONENT StormForge)
endif()


