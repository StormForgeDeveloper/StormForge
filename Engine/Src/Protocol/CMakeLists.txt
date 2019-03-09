cmake_minimum_required(VERSION 3.7)



set(PROTOCOL_LIB_FILES
  	Protocol/Protocol/SFGenericMessageClass.cpp
	Protocol/Protocol/Message/GameMsgClass.cpp
	Protocol/Protocol/Message/GameMsgDebug.cpp
	Protocol/Protocol/Message/GameMsgParsing.cpp
	Protocol/Protocol/Message/LoginMsgClass.cpp
	Protocol/Protocol/Message/LoginMsgDebug.cpp
	Protocol/Protocol/Message/LoginMsgParsing.cpp
	Protocol/Protocol/Policy/GameNetPolicy.cpp
	Protocol/Protocol/Policy/LoginNetPolicy.cpp
	Protocol/Protocol/SFProtocol.cpp

  	Protocol/SFProtocolPCH.h
	Protocol/Protocol/SFGenericMessageClass.h
	Protocol/Protocol/Message/GameMsgClass.h
	Protocol/Protocol/Message/GameMsgDebug.h
	Protocol/Protocol/Message/GameMsgParsing.h
	Protocol/Protocol/Message/LoginMsgClass.h
	Protocol/Protocol/Message/LoginMsgDebug.h
	Protocol/Protocol/Message/LoginMsgParsing.h
	Protocol/Protocol/Policy/GameNetPolicy.h
	Protocol/Protocol/Policy/LoginNetPolicy.h
	Protocol/Protocol/SFProtocolHelper.h
	Protocol/Protocol/SFProtocol.h
	Protocol/Protocol/SFProtocolHelper.inl

  )




include_directories(../SFCore)
include_directories(../SFEngine)






