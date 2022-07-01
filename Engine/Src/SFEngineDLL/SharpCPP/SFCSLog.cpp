////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Object
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"



#include "Util/SFLog.h"
#include "Object/SFObject.h"





using namespace SF;




//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT void SFCSLog_LogMessage(int32_t logLevel, const char* message)
{
	if (message == nullptr)
		return;

	switch (logLevel)
	{
	case 0:
		SFLog(Game, Info, "{0}", message);
		break;
	case 1:
		SFLog(Game, Warning, "{0}", message);
		break;
	case 2:
		SFLog(Game, Error, "{0}", message);
		break;
	case 3:
		SFLog(Game, Debug1, "{0}", message);
		break;
	case 4:
		SFLog(Game, Debug2, "{0}", message);
		break;
	case 5:
	default:
		SFLog(Game, Debug3, "{0}", message);
		break;
	}
}

	

SFDLL_EXPORT void SFCSLog_Flush()
{
	Service::LogModule->Flush();
}



