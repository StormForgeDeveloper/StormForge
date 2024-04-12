


set(SFENGINEDLL_LIB_FILES
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSActorMovement.cpp
  	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSConnection.cpp
    ${SF_ENGINEDLL_PATH}/SharpCPP/SFCSEngine.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSEngine.Android.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSEngine.IOS.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSEngine.Win.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSOnlineClient.cpp
    ${SF_ENGINEDLL_PATH}/SharpCPP/SFCSOnlineAPIClient.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSStringCrc.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSLog.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSObject.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSStreamDB.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSTimeUtil.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSTongScript.cpp
	${SF_ENGINEDLL_PATH}/SharpCPP/SFCSTongScriptBytecode.cpp
	${SF_ENGINEDLL_PATH}/Win/dllmain.cpp
	${SF_ENGINEDLL_PATH}/SFEngineDLLPCH.cpp
	${SF_ENGINEDLL_PATH}/Java/JniConnection.cpp
	${SF_ENGINEDLL_PATH}/Java/JniEngine.cpp
	${SF_ENGINEDLL_PATH}/Java/JniObject.cpp
	${SF_ENGINEDLL_PATH}/Java/JniUtil.cpp
  	${SF_ENGINEDLL_PATH}/SFEngineDLLPCH.h
	${SF_ENGINEDLL_PATH}/Java/JniUtil.h
	${SF_ENGINEDLL_PATH}/pch.h
	${SF_ENGINEDLL_PATH}/Interfaces/SFPublicInterface.cpp
  )


add_definitions(-DSF_BUILD_ENGINE_DLL)

