////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : Network test
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "Util/SFStringCrc32.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFToString.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageWindow.h"
#include "Protocol/LoginMsgClass.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "UnitTest_Net.h"
#include "Protocol/PlayInstanceMsgClass.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest; 
using namespace SF;


TEST_F(NetTest, NetAddress)
{
    const char* AddressString[] = {
        "192.168.0.84:21001",
        "login.stormforge.art,21001",
        "www.google.com"
    };

    for (auto itAddress : AddressString)
    {
        DynamicArray<NetAddress> netAddresses;
        Result result = NetAddress::ParseNameAddress(itAddress, netAddresses);
        EXPECT_TRUE(result);
    }
}

TEST_F(NetTest, MessageCollection)
{
    MessageCollectionArray collectionArray;
    UniquePtr<MessageCollection> pBuffer(new MessageCollection);

    uint8_t buffer[2048];
    MessageHeader* pMessage = reinterpret_cast<MessageHeader*>(buffer);
    pMessage->Length = sizeof(buffer);
    Result hr = Message::PlayInstance::PlayerStateChangedS2CEvt::Create(pMessage,
        EntityUID(),
        1,
        "Test1",
        2,
        Vector4(0,0,1),
        ArrayView<uint8_t>());
    EXPECT_TRUE(hr);
    hr = pBuffer->AddMessage(pMessage);
    EXPECT_TRUE(hr);

    pMessage->Length = sizeof(buffer);
    hr = Message::PlayInstance::ActorMovementS2CEvt::Create(pMessage,
        EntityUID(),
        ActorMovement());
    EXPECT_TRUE(hr);
    hr = pBuffer->AddMessage(pMessage);
    EXPECT_TRUE(hr);

    auto itMsg = pBuffer->begin();
    EXPECT_TRUE(itMsg);
    const MessageHeader* pMessageRead = itMsg;
    EXPECT_TRUE(pMessageRead->msgID == Message::PlayInstance::PlayerStateChangedS2CEvt::MID);

    ++itMsg;
    EXPECT_TRUE(itMsg);
    pMessageRead = itMsg;
    EXPECT_TRUE(itMsg->msgID == Message::PlayInstance::ActorMovementS2CEvt::MID);

    ++itMsg;
    EXPECT_FALSE(itMsg);
}



//
//TEST_F(NetTest, Message)
//{
//	SF::MessageData *pMsgData = nullptr;
//	const char* strID = "MyID";
//	const char* strPassword = "Pas1234";
//
//	EXPECT_HRESULT_SUCCEEDED( SF::Message::Login::LoginCmd::BuildIMsg( pMsgData, GameID::Conspiracy, strID, strPassword ) );
//
//	EXPECT_EQ(pMsgData->GetMessageHeader()->msgID.IDSeq.MsgID, SF::Message::Login::LoginCmd::MID.IDSeq.MsgID);
//
//	SF::Message::Login::LoginCmd msgClass;
//	EXPECT_HRESULT_SUCCEEDED( msgClass.ParseMessage( pMsgData ) );
//
//	EXPECT_STREQ( strID, msgClass.GetID() );
//	EXPECT_STREQ( strPassword, msgClass.GetPassword() );
//}
//
//
//template< class MessageClassType >
//Result HandleMessage( SF::MessageData *pMsgData, MessageClassType* &pMsgInstance )
//{
//	pMsgInstance = nullptr;
//	if( pMsgData == nullptr )
//		return E_POINTER;
//
//	pMsgInstance = new MessageClassType(pMsgData);
//	Result hr = pMsgInstance->ParseMsg();
//	if( FAILED(hr) )
//		return hr;
//
//	return hr;
//}
//
//TEST_F(NetTest, MessageMap)
//{
//	const char* strID = "MyID";
//	const char* strPassword = "Pas1234";
//	//const char* strNickName = "NickName";
//	const Result InResult = S_FALSE;
//	const SF::AccountID InAccID = 123456;
//	const SF::AuthTicket InTicket = 654321;
//	SF::NetAddress InGameInsSvr;
//	const SF::GameInsUID InInsUID(3,67893);
//
//	Net::SetNetAddress(InGameInsSvr, "127.0.0.1", 1234);
//	typedef std::function<Result(SF::MessageData*)> MessageHandlerType;
//	typedef SF::Svr::MessageHandlerTable<MessageHandlerType> TestMessageTable;
//	SF::CheckCtrMemory();
//	SF::StaticAllocator<10> allocator(SF::STDAllocator::GetInstance());
//	TestMessageTable messageHandlers(allocator);
//	SF::CheckCtrMemory();
//	messageHandlers.Register<SF::Message::Login::LoginCmd>(__FILE__, __LINE__,
//		[&](SF::MessageData *pMsgData)->Result {
//		SF::Message::Login::LoginCmd *pMsg = nullptr;
//			EXPECT_HRESULT_SUCCEEDED(HandleMessage<SF::Message::Login::LoginCmd>(pMsgData, pMsg));
//			if( pMsg ) 
//				IHeap::Delete(pMsg);
//			return S_OK;
//	});
//	messageHandlers.Register<SF::Message::Login::LoginRes>(__FILE__, __LINE__,
//		[&](SF::MessageData *pMsgData)->Result	{
//		SF::Message::Login::LoginRes *pMsg = nullptr;
//		EXPECT_HRESULT_SUCCEEDED(HandleMessage<SF::Message::Login::LoginRes>(pMsgData, pMsg));
//			SF::CheckCtrMemory();
//			if( pMsg ) 
//				IHeap::Delete(pMsg);
//			SF::CheckCtrMemory();
//			return S_OK;
//	});
//	messageHandlers.Register<SF::Message::Game::JoinGameCmd>(__FILE__, __LINE__,
//		[&](SF::MessageData *pMsgData)->Result	{
//			SF::Message::Game::JoinGameCmd *pMsg = nullptr;
//			EXPECT_HRESULT_SUCCEEDED( HandleMessage<SF::Message::Game::JoinGameCmd>( pMsgData, pMsg ) );
//			if( pMsg ) 
//				IHeap::Delete(pMsg);
//			return S_OK;
//	});
//	messageHandlers.Register<SF::Message::Game::JoinGameRes>( __FILE__, __LINE__,
//		[&](SF::MessageData *pMsgData)->Result	{
//			SF::Message::Game::JoinGameRes *pMsg = nullptr;
//			EXPECT_HRESULT_SUCCEEDED( HandleMessage<SF::Message::Game::JoinGameRes>( pMsgData, pMsg ) );
//			if( pMsg ) 
//				IHeap::Delete(pMsg);
//			return S_OK;
//	});
//
//	SF::CheckCtrMemory();
//	const int TestCaseCount = 4;
//	SF::MessageData *pMsgData[TestCaseCount];
//	SF::NetAddress InGameServerAddr;
//	uint64_t InLoginEntityUID;
//
//	memset(pMsgData,0,sizeof(pMsgData));
//	EXPECT_HRESULT_SUCCEEDED(SF::Message::Login::LoginCmd::BuildIMsg(pMsgData[0], GameID::Conspiracy, strID, strPassword));
//	EXPECT_HRESULT_SUCCEEDED(SF::Message::Login::LoginRes::BuildIMsg(pMsgData[1], InResult, InGameServerAddr, InGameServerAddr, InAccID, InTicket, InLoginEntityUID));
//	EXPECT_HRESULT_SUCCEEDED( SF::Message::Game::JoinGameCmd::BuildIMsg( pMsgData[2], InAccID, InTicket, 0 ) );
////	EXPECT_HRESULT_SUCCEEDED( SF::Message::Game::JoinGameRes::BuildIMsg( pMsgData[3], InResult, InInsUID, GameStateID::DefenceOfSuspects, PlayerRole::AngelOfVillagers, 0 ) );
//	SF::CheckCtrMemory();
//	for( int iMsg = 0; iMsg < TestCaseCount; iMsg++ )
//	{
//		Result hr = messageHandlers.HandleMessage( pMsgData[iMsg] );
//		EXPECT_HRESULT_SUCCEEDED(hr);
//		SF::CheckCtrMemory();
//	}
//}
//
//TEST_F(NetTest, Simple)
//{
//	Result hr = S_OK;
//	SF::MessageData *pIMsg = nullptr;
//	TimeStampMS dwTimeStart = Util::Time.GetTimeMs();
//	TimeStampMS dwTime = Util::Time.GetTimeMs();
//	NetAddress destAddress;
//
//	m_pNetClient = dynamic_cast<SF::Net::IClient*>(m_pNet);
//	defChkPtr(m_pNetClient);
//
//	Net::SetNetAddress(destAddress, "127.0.0.1", 4001);
//
//	// Connect TCP server
//	EXPECT_HRESULT_SUCCEEDED(m_pNetClient->ConnectCli(destAddress, m_pIConnection ));
//
//	// Policy create
//	EXPECT_HRESULT_SUCCEEDED( m_pIConnection->CreatePolicy( SF::POLICY_GAME ) );
//
//	// Wait until connection done
//	while( m_pIConnection->GetConnectionState() == SF::Net::IConnection::STATE_CONNECTING )
//	{
//		SF::Net::IConnection::Event curEvent;
//
//		if( SUCCEEDED(m_pIConnection->DequeueConnectionEvent( curEvent ) ) )
//		{
//			switch( curEvent.EventType )
//			{
//			case SF::Net::IConnection::Event::EVT_CONNECTION_RESULT:
//				defTrace( Trace::TRC_INFO, "EVT_CONNECTION_RESULT {0}", curEvent.hr );
//				break;
//			case SF::Net::IConnection::Event::EVT_DISCONNECTED:
//				defTrace( Trace::TRC_INFO, "EVT_DISCONNECTED {0}", curEvent.hr  );
//				break;
//			case SF::Net::IConnection::Event::EVT_STATE_CHANGE:
//				defTrace( Trace::TRC_INFO, "EVT_STATE_CHANGE {0}", curEvent.hr  );
//				break;
//			default:
//				break;
//			};
//		}
//
//		ThisThread::SleepFor(DurationMS(100));
//	}
//
//
//	// Sending Login packet
//	EXPECT_HRESULT_SUCCEEDED( m_pIConnection->GetPolicy<SF::Policy::IPolicyLogin>()->LoginCmd( GameID::Conspiracy, "1", "1234" ) );
//
//
//	// Processing Connection update
//	pIMsg = nullptr;
//	dwTimeStart = Util::Time.GetTimeMs();
//	dwTime = Util::Time.GetTimeMs();
//	while( 1 )
//	{
//		dwTime = Util::Time.GetTimeMs();
//
//		if( m_pIConnection )
//		{
//			SF::Net::IConnection::Event curEvent;
//			// Processing Connection event 
//			while( SUCCEEDED(m_pIConnection->DequeueConnectionEvent( curEvent ) ) )
//			{
//				switch( curEvent.EventType )
//				{
//				case SF::Net::IConnection::Event::EVT_CONNECTION_RESULT:
//					defTrace( Trace::TRC_INFO, "EVT_CONNECTION_RESULT {0:X8}", curEvent.hr );
//					break;
//				case SF::Net::IConnection::Event::EVT_DISCONNECTED:
//					defTrace( Trace::TRC_INFO, "EVT_DISCONNECTED {0:X8}", curEvent.hr  );
//					EXPECT_HRESULT_SUCCEEDED( m_pNetClient->ReleaseConnection( m_pIConnection ) );
//					m_pIConnection = nullptr;
//					goto EndTest;
//					break;
//				case SF::Net::IConnection::Event::EVT_STATE_CHANGE:
//					defTrace( Trace::TRC_INFO, "EVT_STATE_CHANGE {0:X8}", curEvent.hr  );
//					break;
//				default:
//					break;
//				};
//			}
//
//			// Processing received messages
//			if( SUCCEEDED(m_pIConnection->GetRecvMessage( pIMsg ) ) )
//			{
//				defTrace( Trace::TRC_INFO, "Message {0}", pIMsg->GetMessageHeader()->msgID.ID  );
//
//			}
//		}
//
//		ThisThread::SleepFor(DurationMS(100));
//	}
//
//EndTest:
//
//	if( m_pIConnection )
//		EXPECT_HRESULT_SUCCEEDED( m_pIConnection->Disconnect("") );
//
//
//Proc_End:
//
//	EXPECT_HRESULT_SUCCEEDED(hr);
//}

