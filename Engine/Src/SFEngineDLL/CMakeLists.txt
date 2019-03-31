


set(SFENGINEDLL_LIB_FILES
  	SharpCPP/SFCSConnection.cpp
	SharpCPP/SFCSConnectionGroup.cpp
	SharpCPP/SFCSEngine.Android.cpp
	SharpCPP/SFCSEngine.IOS.cpp
	SharpCPP/SFCSEngine.Win.cpp
	SharpCPP/SFCSFixedString.cpp
	SharpCPP/SFCSNetMessageIDGame.cpp
	SharpCPP/SFCSNetMessageIDLogin.cpp
	SharpCPP/SFCSNetSendMessageGame.cpp
	SharpCPP/SFCSNetSendMessageLogin.cpp
	SharpCPP/SFCSObject.cpp
	SharpCPP/SFCSServerConfig.cpp
	SharpCPP/SFCSTimeUtil.cpp
	SharpCPP/SFCSTongScript.cpp
	SharpCPP/SFCSTongScriptBytecode.cpp
	SharpCPP/SFCSUtil.cpp
	SharpCPP/SFCSZooKeeper.cpp
	Win/dllmain.cpp
	SFEngineDLLPCH.cpp
	Java/JniConnection.cpp
	Java/JniEngine.cpp
	Java/JniObject.cpp
	Java/JniUtil.cpp

  	SFEngineDLLPCH.h
	SharpCPP/SFCSUtil.h
	Java/JniUtil.h
	pch.h

  )




add_library(SFEngineDLL SHARED ${SFENGINEDLL_LIB_FILES})


add_dependencies(SFEngineDLL SFCore SFEngine SFProtocol)
target_link_libraries(SFEngineDLL SFCore SFEngine SFProtocol iconv)

target_include_directories (SFEngineDLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)


