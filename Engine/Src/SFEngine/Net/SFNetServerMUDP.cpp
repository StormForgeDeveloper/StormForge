////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network Server implementation 
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Thread/SFThread.h"
#include "String/SFStrUtil.h"
#include "String/SFToString.h"
#include "Util/SFLog.h"
#include "Protocol/SFProtocol.h"

#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnection.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetServerUDP.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFConnectionTasks.h"
#include "Net/SFConnectionManagerTask.h"
#include "Net/SFNetToString.h"




namespace SF {
namespace Net {

	

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Mobile UDP Server class
	//

	
	ServerMUDP::ServerMUDP(ServerID InServerID, NetClass localClass)
		:ServerUDPBase(InServerID, localClass)
	{
	}

	ServerMUDP::~ServerMUDP()
	{
	}

	Result ServerMUDP::SendRaw(const sockaddr_storage& dstAddress, SharedPointerT<Message::MessageData> &pMsg)
	{
		Result hr = ResultCode::SUCCESS;
		IOBUFFER_WRITE *pSendBuffer = nullptr;

		if (!GetSocketIO()->GetIsIORegistered())
			return ResultCode::SUCCESS_FALSE;

		auto sendCount = GetSocketIO()->IncPendingSendCount();
		unused(sendCount);
		assert(sendCount >= 0);

		netChkPtr(pMsg);

		netMem(pSendBuffer = new(GetHeap()) IOBUFFER_WRITE);
		pSendBuffer->SetupSendUDP(GetSocket(), dstAddress, std::forward<SharedPointerT<Message::MessageData>>(pMsg));

		if (NetSystem::IsProactorSystem())
		{
			netChk(GetSocketIO()->WriteBuffer(pSendBuffer));
		}
		else
		{
			netChk(GetSocketIO()->EnqueueBuffer(pSendBuffer));
		}
		pMsg = nullptr;
		pSendBuffer = nullptr;

	Proc_End:

		if (!hr)
			GetSocketIO()->DecPendingSendCount();

		if (pSendBuffer != nullptr)
		{
			IHeap::Free(pSendBuffer);
		}

		return hr;
	}

	// Make Ack packet and enqueue to SendNetCtrlqueue
	Result ServerMUDP::SendNetCtrl( const sockaddr_storage& dstAddress, uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID )
	{
		Result hr = ResultCode::SUCCESS, hrTem = ResultCode::SUCCESS;
		MsgMobileNetCtrl *pNetCtrl = nullptr;
		MessageDataPtr pMsg;

		netMem( pMsg = Message::MessageData::NewMessage(GetSocketIO()->GetIOHeap(), uiCtrlCode, sizeof(MsgMobileNetCtrl) ) );

		pNetCtrl = (MsgMobileNetCtrl*)pMsg->GetMessageBuff();
		pNetCtrl->PeerID = UID;
		pNetCtrl->msgID.SetSequence(uiSequence);
		pNetCtrl->rtnMsgID = msgID;

		pMsg->GetMessageHeader()->msgID.IDs.Mobile = true;
		pMsg->UpdateChecksum();

		hrTem = SendRaw(dstAddress, pMsg);
		if( !(hrTem) )
		{
			SFLog( Net, Error, "NetCtrl Send failed in direct: DstAddr:{0}, msg:{1:X8}, seq:{2}, hr={3:X8}", 
							dstAddress, 
							msgID.ID, 
							uiSequence, 
							hrTem );

			// ignore io send fail except connection closed
			if( hrTem == ResultCode::IO_CONNECTION_CLOSED )
			{
				goto Proc_End;
			}
		}

	Proc_End:

		return hr;
	}

	Result ServerMUDP::OnPacketWithoutConnection(const struct sockaddr_storage& from, const uint8_t* pData)
	{
		Result hr = ResultCode::SUCCESS;

		if (pData == nullptr)
			return ResultCode::INVALID_ARG;

		MsgMobileNetCtrl *pNetCtrl = (MsgMobileNetCtrl*)pData;
		if (pNetCtrl->Length != sizeof(MsgMobileNetCtrl) 
			&& pNetCtrl->Length != sizeof(MsgMobileNetCtrlSync) 
			&& pNetCtrl->Length != sizeof(Message::MobileMessageHeader))
		{
			// send disconnect
			SFLog(Net, Warning, "Invalid incoming packet size. ignoring from:{0} msgID:{1}, len:{2}", from, pNetCtrl->msgID, pNetCtrl->Length);
			return ResultCode::IO_BADPACKET_SIZE;
		}

		if (!GetIsEnableAccept())
		{
			if (pNetCtrl->msgID.GetMsgID() == PACKET_NETCTRL_CONNECT.GetMsgID()
				|| pNetCtrl->msgID.GetMsgID() == PACKET_NETCTRL_SYNCRELIABLE.GetMsgID()
				|| pNetCtrl->msgID.GetMsgID() == PACKET_NETCTRL_HEARTBIT.GetMsgID()
				|| pNetCtrl->msgID.GetMsgID() == PACKET_NETCTRL_TIMESYNC.GetMsgID())
			{
				// send disconnect
				//SFLog(Net, Warning, "Invalid packet size. Try to disconnect from:{0} msg:{1}", from, pNetCtrl->msgID);
				netChk(SendNetCtrl(from, PACKET_NETCTRL_DISCONNECT, 0, PACKET_NETCTRL_NONE, 0));
			}
			else
			{
				SFLog(Net, Warning, "Invalid packet size. Try to disconnect from:{0} msg:{1}", from, pNetCtrl->msgID);
			}

			return ResultCode::SUCCESS_FALSE;
		}


		// Handle new connection
		if (pNetCtrl->msgID.GetMsgID() != PACKET_NETCTRL_CONNECT.GetMsgID())
		{
			// send disconnect
			SFLog(Net, Debug3, "Invalid incoming packet. Try to disconnect {0}", from);
			netChk(SendNetCtrl(from, PACKET_NETCTRL_DISCONNECT, 0, PACKET_NETCTRL_NONE, 0));
		}
		else if (pNetCtrl->rtnMsgID.ID != SF_PROTOCOL_VERSION)
		{
			// send disconnect
			SFLog(Net, Debug3, "Invalid incoming packet version, received:{0}, expected:{1}. Try to disconnect {2}", pNetCtrl->rtnMsgID.ID, (uint)SF_PROTOCOL_VERSION, from);
			netChk(SendNetCtrl(from, PACKET_NETCTRL_NACK, 0, pNetCtrl->msgID, 0));
			//netChk(SendNetCtrl(pIOBuffer->From, PACKET_NETCTRL_DISCONNECT, 0, PACKET_NETCTRL_NONE, 0));
		}
		else if (pNetCtrl->msgID.ID == PACKET_NETCTRL_ACK)
		{
			// ignore this packet

		}
		else
		{
			PeerInfo local, remote;
			local.SetInfo(GetNetClass(), GetLocalAddress(), GetServerID());
			remote.SetInfo(NetClass::Unknown, from, 0); // Remote will be set later
			Service::ConnectionManager->NewMUDPAddress(GetHeap(), this, GetSocket(), local, remote);
		}

	Proc_End:

		return hr;
	}

	// called when reciving message
	Result ServerMUDP::OnIORecvCompleted( Result hrRes, IOBUFFER_READ* &pIOBuffer )
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Connection> pConnection;
		sockaddr_storage from;
		if (pIOBuffer != nullptr) from = pIOBuffer->NetAddr.From;
		else memset(&from, 0, sizeof(from));

		if( !( hrRes ) )
		{

			switch((uint32_t)hrRes )
			{
			case (uint32_t)ResultCode::IO_CONNECTION_CLOSED:
			case (uint32_t)ResultCode::IO_IO_ABORTED:
				// This error is no more the reason to disconnect a user, just report it
				SFLog(Net, Debug1, "UDP bad RECV IP:{0}", from);
				hr = hrRes;
				break;
			default:
				SFLog(Net, Error, "UDP Recv Msg Failed, SvrMUDP, IP:{0}, hr={1:X8}", from, hrRes );
				break;
			};
		}
		else if(pIOBuffer != nullptr)
		{
			if(pIOBuffer->TransferredSize < sizeof(Message::MobileMessageHeader) )// invalid packet size
				goto Proc_End;

			Message::MobileMessageHeader *pHeader = (Message::MobileMessageHeader*)pIOBuffer->buffer;
			if( !pHeader->msgID.IDs.Mobile )
			{
				SFLog(Net, Warning, "HackWarn : Not allowered connection try from {0}", from);
				goto Proc_End;
			}

			if (pHeader->PeerID != 0)
			{
				Service::ConnectionManager->GetConnectionByPeerID(pHeader->PeerID, pConnection);
			}

			if (pConnection == nullptr)
			{
				Service::ConnectionManager->GetConnectionByAddr(from, pConnection);
			}

			if (pConnection == nullptr)
			{
				OnPacketWithoutConnection(pIOBuffer->NetAddr.From, (const uint8_t*)pIOBuffer->buffer);
				goto Proc_End;
			}

			Assert( pHeader->PeerID == 0 || pConnection->GetRemoteInfo().PeerID == 0 || pConnection->GetRemoteInfo().PeerID == pHeader->PeerID );
			if( pConnection->GetRemoteInfo().PeerID == 0 && pHeader->PeerID != 0 )
			{
				SFLog(Net, Info, "Mapping CID: {0}, PeerID {1}", pConnection->GetCID(), pHeader->PeerID );
				SharedPointerT<EngineTask> pTask = new(GetHeap()) ConnectionManagerTask_RemapPeerID(pConnection, pHeader->PeerID);
				netMem(pTask);
				pTask->Request();
				//netChk( Service::ConnectionManager->PendingRemapPeerID((Connection*)pConnection, pHeader->PeerID) );
			}

			// Update sock address table if need, This is important because all the out going packets will use this address
			if( pConnection->GetRemoteSockAddr() != pIOBuffer->NetAddr.From )
			{
				SFLog(Net, Info, "Remapping Address CID: {0}, Address from:{1}, to:{2}, PeerID from:{3}, to:{4}", pConnection->GetCID(), pConnection->GetRemoteSockAddr(), pIOBuffer->NetAddr.From, pConnection->GetRemoteInfo().PeerID, pHeader->PeerID);
				if (pConnection->GetUseAddressMap())
				{
					// address map update. We can skip this when we don't allow unregistered connection because we are going to update the remote address in place
					// FYI, I think this update only required when login + game server, otherwise This will only need for connection manager for releasing connections
					//netChk(Service::ConnectionManager->PendingAddressRemap((Connection*)pConnection, pConnection->GetRemoteSockAddr(), pIOBuffer->NetAddr.From));
					SharedPointerT<EngineTask> pTask = new(GetHeap()) ConnectionManagerTask_RemapAddress(pConnection, pConnection->GetRemoteSockAddr(), pIOBuffer->NetAddr.From);
					netMem(pTask);
					pTask->Request();
				}
				// Set remote address always. remap only remaps the value in the connection manager table
				//else
				{
					// in-place address change
					pConnection->SetRemoteAddress(pIOBuffer->NetAddr.From);
				}
			}

			netChk( pConnection->OnRecv(pIOBuffer->TransferredSize, (uint8_t*)pIOBuffer->buffer) );
			// Keep these connection can be readable until Onrecv is done
		}

	Proc_End:


		if (NetSystem::IsProactorSystem())
		{
			if (pIOBuffer != nullptr && GetSocketIO()->GetIsIORegistered())
			{
				auto result = pIOBuffer->SetPendingFalse();
				unused(result);
				assert(result);
				GetSocketIO()->PendingRecv(pIOBuffer);
			}
			else
			{
				SFLog(Net, Warning, "NetServerMUDP::OnIORecvCompleted : skip pending recv");
				Util::SafeDelete(pIOBuffer);
			}
		}
		else
		{
			Util::SafeDelete(pIOBuffer);
		}

		GetSocketIO()->DecPendingRecvCount();

		return hr;
	}
	

} // namespace Net
} // namespace SF

