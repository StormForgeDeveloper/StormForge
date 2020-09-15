

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
	Protocol/Message/RelayMsgClass.cpp
	Protocol/Message/RelayMsgClass.h
	Protocol/Message/RelayMsgDebug.cpp
	Protocol/Message/RelayMsgDebug.h
	Protocol/Message/RelayMsgParsing.cpp
	Protocol/Message/RelayMsgParsing.h

	Protocol/Policy/GameNetPolicy.cpp
	Protocol/Policy/GameNetPolicy.h
	Protocol/Policy/LoginNetPolicy.cpp
	Protocol/Policy/LoginNetPolicy.h
	Protocol/Policy/RelayNetPolicy.cpp
	Protocol/Policy/RelayNetPolicy.h

	Protocol/SFProtocol.cpp
	Protocol/SFGenericMessageClass.h
	Protocol/SFProtocolHelper.h
	Protocol/SFProtocol.h
  	SFProtocolPCH.h
  )



add_library(SFProtocol STATIC ${SFPROTOCOL_LIB_FILES})

target_include_directories (SFProtocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)

#set_target_properties(SFProtocol PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/)

install (TARGETS SFProtocol
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)

