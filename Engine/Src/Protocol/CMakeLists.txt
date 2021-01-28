

set(SFPROTOCOL_LIB_FILES
  	Protocol/SFGenericMessageClass.cpp
	
	Protocol/Message/GameMsgClass.cpp
	Protocol/Message/GameMsgDebug.cpp
	Protocol/Message/GameMsgParsing.cpp
	Protocol/Message/LoginMsgClass.cpp
	Protocol/Message/LoginMsgDebug.cpp
	Protocol/Message/LoginMsgParsing.cpp
	Protocol/Message/GameMsgClass.h
	Protocol/Message/GameMsgDebug.h
	Protocol/Message/GameMsgParsing.h
	Protocol/Message/LoginMsgClass.h
	Protocol/Message/LoginMsgDebug.h
	Protocol/Message/LoginMsgParsing.h
	Protocol/Message/PlayInstanceMsgClass.cpp
	Protocol/Message/PlayInstanceMsgClass.h
	Protocol/Message/PlayInstanceMsgDebug.cpp
	Protocol/Message/PlayInstanceMsgDebug.h
	Protocol/Message/PlayInstanceMsgParsing.cpp
	Protocol/Message/PlayInstanceMsgParsing.h

	Protocol/Policy/GameNetPolicy.cpp
	Protocol/Policy/GameNetPolicy.h
	Protocol/Policy/LoginNetPolicy.cpp
	Protocol/Policy/LoginNetPolicy.h
	Protocol/Policy/PlayInstanceNetPolicy.cpp
	Protocol/Policy/PlayInstanceNetPolicy.h

	Protocol/SFProtocol.cpp
	Protocol/SFGenericMessageClass.h
	Protocol/SFProtocolHelper.h
	Protocol/SFProtocol.h
  	SFProtocolPCH.h
  )



add_library(SFProtocol STATIC ${SFPROTOCOL_LIB_FILES})
#target_precompile_headers(SFProtocol PRIVATE SFProtocolPCH.h)
target_include_directories (SFProtocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)

#set_target_properties(SFProtocol PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/)

install (TARGETS SFProtocol
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)

