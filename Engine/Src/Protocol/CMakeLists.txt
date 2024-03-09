

set(SFPROTOCOL_LIB_FILES
  	SFProtocolPCH.h
	
	SFFlat/SFTypes_generated.h
	SFFlat/LocalTypes_generated.h

	Protocol/GameMsgClass.cpp
	Protocol/GameMsgDebug.cpp
	Protocol/GameMsgParsing.cpp
	Protocol/GameMsgClass.h
	Protocol/GameMsgDebug.h
	Protocol/GameMsgParsing.h
	Protocol/GameNetPolicy.cpp
	Protocol/GameNetPolicy.h

	SFFlat/Game_generated.h
	Protocol/GameMessageID.h

	Protocol/PlayInstanceMsgClass.cpp
	Protocol/PlayInstanceMsgClass.h
	Protocol/PlayInstanceMsgDebug.cpp
	Protocol/PlayInstanceMsgDebug.h
	Protocol/PlayInstanceMsgParsing.cpp
	Protocol/PlayInstanceMsgParsing.h
   	Protocol/PlayInstanceNetPolicy.cpp
	Protocol/PlayInstanceNetPolicy.h
	
	SFFlat/PlayInstance_generated.h
	Protocol/PlayInstanceMessageID.h
	
	Protocol/GenericMsgClass.cpp
	Protocol/GenericMsgClass.h
	Protocol/GenericMsgDebug.cpp
	Protocol/GenericMsgDebug.h
	Protocol/GenericMsgParsing.cpp
	Protocol/GenericMsgParsing.h
   	Protocol/GenericNetPolicy.cpp
	Protocol/GenericNetPolicy.h

	SFFlat/Generic_generated.h
	Protocol/GenericMessageID.h
	

	SFGenericMessageClass.h
  	SFGenericMessageClass.cpp
	SFProtocolHelper.h
	SFProtocol.h
	SFProtocol.cpp
	
	SFFlat/Login_generated.h
	Protocol/LoginMessageID.h

	SFFlat/Telemetry_generated.h
	Protocol/TelemetryMessageID.h

  )



add_library(SFProtocol STATIC ${SFPROTOCOL_LIB_FILES})
#target_precompile_headers(SFProtocol PRIVATE SFProtocolPCH.h)
target_include_directories (SFProtocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)

#set_target_properties(SFProtocol PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/)

install (TARGETS SFProtocol
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)

