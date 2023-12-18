

set(SFPROTOCOL_LIB_FILES
  	SFProtocolPCH.h

  	Protocol/SFGenericMessageClass.cpp
	
	Protocol/GameMsgClass.cpp
	Protocol/GameMsgDebug.cpp
	Protocol/GameMsgParsing.cpp
	Protocol/LoginMsgClass.cpp
	Protocol/LoginMsgDebug.cpp
	Protocol/LoginMsgParsing.cpp
	Protocol/GameMsgClass.h
	Protocol/GameMsgDebug.h
	Protocol/GameMsgParsing.h
	Protocol/LoginMsgClass.h
	Protocol/LoginMsgDebug.h
	Protocol/LoginMsgParsing.h

	Protocol/PlayInstanceMsgClass.cpp
	Protocol/PlayInstanceMsgClass.h
	Protocol/PlayInstanceMsgDebug.cpp
	Protocol/PlayInstanceMsgDebug.h
	Protocol/PlayInstanceMsgParsing.cpp
	Protocol/PlayInstanceMsgParsing.h
   	Protocol/PlayInstanceNetPolicy.cpp
	Protocol/PlayInstanceNetPolicy.h

	Protocol/GenericMsgClass.cpp
	Protocol/GenericMsgClass.h
	Protocol/GenericMsgDebug.cpp
	Protocol/GenericMsgDebug.h
	Protocol/GenericMsgParsing.cpp
	Protocol/GenericMsgParsing.h
   	Protocol/GenericNetPolicy.cpp
	Protocol/GenericNetPolicy.h

	Protocol/GameNetPolicy.cpp
	Protocol/GameNetPolicy.h
	Protocol/LoginNetPolicy.cpp
	Protocol/LoginNetPolicy.h

	Protocol/SFProtocol.cpp
	Protocol/SFGenericMessageClass.h
	Protocol/SFProtocolHelper.h
	Protocol/SFProtocol.h
	
	SFFlat/Login_generated.h
	SFFlat/Telemetry_generated.h

  )



add_library(SFProtocol STATIC ${SFPROTOCOL_LIB_FILES})
#target_precompile_headers(SFProtocol PRIVATE SFProtocolPCH.h)
target_include_directories (SFProtocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)

#set_target_properties(SFProtocol PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/)

install (TARGETS SFProtocol
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)

