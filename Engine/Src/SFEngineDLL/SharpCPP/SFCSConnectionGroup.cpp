////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
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
#include "Net/SFConnectionMUDP.h"
#include "Net/SFConnectionGroup.h"
#include "Net/SFMessage.h"
#include "Protocol/SFProtocol.h"

#include "SFCSUtil.h"


namespace SF
{

}

using namespace SF;





//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT SharedObject* SFConnectionGroup_NativeCreateConnectionGroup(int32_t maximumQueueBufferSize)
{
	auto pGroup = new(Service::NetSystem->GetHeap()) Net::ConnectionGroup(Service::NetSystem->GetHeap(), maximumQueueBufferSize);
	SharedReferenceInc inc(pGroup);
	//pGroup->RegisterToEngineObjectManager();
	return pGroup;
}



SFDLL_EXPORT intptr_t SFConnectionGroup_NativeDequeueEvent(intptr_t nativeHandle, SET_EVENT_FUNCTION setEventFunc, SET_MESSAGE_FUNCTION setMessageFunc, VariableMapBuilderCS::SET_FUNCTION setValueFunc, VariableMapBuilderCS::SET_ARRAY_FUNCTION setArrayValueFunc)
{
	if (nativeHandle == 0)
		return false;

	auto pGroup = NativeToObject<Net::ConnectionGroup>(nativeHandle);

	// Try to get valid connection event 
	Net::ConnectionGroup::EventInformation eventInfo;
	auto maxTry = pGroup->GetQueuedEventCount();
	for (unsigned iTry = 0; iTry < maxTry; iTry++)
	{
		if(!pGroup->DequeueEvent(eventInfo))
			return false;

		// Skip if connection is released
		Net::ConnectionPtr pConnection(eventInfo.pConnection);
		if (pConnection != nullptr)
			break;
	}

	Net::ConnectionEvent conEvent;
	conEvent.Composited = eventInfo.Event;
	if (eventInfo.pMsg != nullptr)
	{
		setMessageFunc(eventInfo.pMsg->GetMessageHeader()->msgID.IDSeq.MsgID);

		// Fill parameters
		VariableMapBuilderCS builder(setValueFunc, setArrayValueFunc);
		if (!SF::Protocol::ParseMessage(eventInfo.pMsg, builder))
			return false;
	}
	else if (conEvent.Components.EventType != Net::ConnectionEvent::EVT_NONE)
	{
		setEventFunc(conEvent.Components.EventType, (int32_t)(uint32_t)conEvent.Components.hr, conEvent.Components.State);
	}

	else
	{
		return false;
	}

	return true;

}

