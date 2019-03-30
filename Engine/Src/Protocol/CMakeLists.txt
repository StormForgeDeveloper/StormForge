

set(SFPROTOCOL_LIB_FILES
  	Protocol/SFGenericMessageClass.cpp
	Protocol/Message/GameMsgClass.cpp
	Protocol/Message/GameMsgDebug.cpp
	Protocol/Message/GameMsgParsing.cpp
	Protocol/Message/LoginMsgClass.cpp
	Protocol/Message/LoginMsgDebug.cpp
	Protocol/Message/LoginMsgParsing.cpp
	Protocol/Policy/GameNetPolicy.cpp
	Protocol/Policy/LoginNetPolicy.cpp
	Protocol/SFProtocol.cpp

  	SFProtocolPCH.h
	Protocol/SFGenericMessageClass.h
	Protocol/Message/GameMsgClass.h
	Protocol/Message/GameMsgDebug.h
	Protocol/Message/GameMsgParsing.h
	Protocol/Message/LoginMsgClass.h
	Protocol/Message/LoginMsgDebug.h
	Protocol/Message/LoginMsgParsing.h
	Protocol/Policy/GameNetPolicy.h
	Protocol/Policy/LoginNetPolicy.h
	Protocol/SFProtocolHelper.h
	Protocol/SFProtocol.h
	Protocol/SFProtocolHelper.inl

  )





add_library(SFProtocol STATIC ${SFPROTOCOL_LIB_FILES})

target_include_directories (SFProtocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)


