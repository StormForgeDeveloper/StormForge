////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Util/SFLog.h"
#include "Object/SFObject.h"
#include "Service/SFEngineService.h"
#include "Net/SFConnection.h"
#include "Net/SFMessage.h"
#include "SFProtocol.h"
#include "Online/SFOnlineClient.h"
#include "Actor/Movement/SFActorMovement.h"

#include "Interfaces/Sharp/SFCSUtil.h"


using namespace SF;

//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT uint32_t SFActorMovement_NativeGetFramesPerSeconds()
{
	return ActorMovement::FramesPerSeconds;
}

SFDLL_EXPORT uint32_t SFActorMovement_NativeGetDeltaMSPerFrame()
{
	return ActorMovement::DeltaMSPerFrame;
}

SFDLL_EXPORT float SFActorMovement_NativeGetDeltaSecondsPerFrame()
{
	return ActorMovement::DeltaSecondsPerFrame;
}

SFDLL_EXPORT float SFActorMovement_NativeGetMoveFrameTimeoutSeconds()
{
	return ActorMovement::MoveFrameTimeoutSeconds;
}

SFDLL_EXPORT uint32_t SFActorMovement_NativeGetMoveFrameTimeout()
{
	return ActorMovement::MoveFrameTimeout;
}
