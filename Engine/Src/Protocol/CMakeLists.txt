

set(SFPROTOCOL_LIB_FILES
  	SFProtocolPCH.h
	
	Protocol/SFTypes_generated.h

	Protocol/Game_generated.h
	Protocol/GameMessageID.h
	Protocol/GameRPCSendAdapter.h
	Protocol/GameRPCSendAdapter.cpp

	Protocol/PlayInstance_generated.h
	Protocol/PlayInstanceMessageID.h
	Protocol/PlayInstanceRPCSendAdapter.h
	Protocol/PlayInstanceRPCSendAdapter.cpp
	
	Protocol/Generic_generated.h
	Protocol/GenericMessageID.h
	Protocol/GenericRPCSendAdapter.h
	Protocol/GenericRPCSendAdapter.cpp
	
	Protocol/Login_generated.h
	Protocol/LoginMessageID.h

	Protocol/Telemetry_generated.h
	Protocol/TelemetryMessageID.h
	
	SFGenericMessageClass.h
  	SFGenericMessageClass.cpp
	SFProtocolHelper.h
	SFProtocol.h
	SFProtocol.cpp

  )



add_library(SFProtocol STATIC ${SFPROTOCOL_LIB_FILES})
#target_precompile_headers(SFProtocol PRIVATE SFProtocolPCH.h)
target_include_directories (SFProtocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)

#set_target_properties(SFProtocol PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/)

install (TARGETS SFProtocol
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)

