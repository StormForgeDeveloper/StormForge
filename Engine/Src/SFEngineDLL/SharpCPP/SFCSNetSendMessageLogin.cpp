////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Login Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/LoginMsgClass.h"
#include "SharpCPP/SFCSUtil.h"



using namespace SF;


// Cmd: Login request
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, const char* InID, const char* InPassword )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::LoginCmd::Create(pConnection->GetHeap(), InTransactionID, InGameID,InID,InPassword);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, const char* InID, const char* InPassword )


// Cmd: Login request with Facebook UID
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginByFacebookCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, uint64_t InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::LoginByFacebookCmd::Create(pConnection->GetHeap(), InTransactionID, InGameID, InUID,InFaceBookName,InEMail,InFacebookToken);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginByFacebookCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, uint64_t InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )


// Cmd: Login request
SFDLL_EXPORT int  CSSFNetAdapter_LoginCreateRandomUserCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, const char* InCellPhone )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::CreateRandomUserCmd::Create(pConnection->GetHeap(), InTransactionID, InGameID,InCellPhone);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginCreateRandomUserCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, const char* InCellPhone )


// Cmd: Update my score and Get Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_LoginUpdateMyScoreCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InRankingScore, int InRankingType, uint16_t InCount )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::UpdateMyScoreCmd::Create(pConnection->GetHeap(), InTransactionID, InRankingScore,(RankingType) InRankingType, InCount);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginUpdateMyScoreCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InRankingScore, int InRankingType, uint16_t InCount )


// Cmd: Get Ranking lise
SFDLL_EXPORT int  CSSFNetAdapter_LoginGetRankingListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, int InRankingType, uint8_t InBaseRanking, uint8_t InCount )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::GetRankingListCmd::Create(pConnection->GetHeap(), InTransactionID,(RankingType) InRankingType, InBaseRanking, InCount);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginGetRankingListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, int InRankingType, uint8_t InBaseRanking, uint8_t InCount )


// Cmd: For network test
SFDLL_EXPORT int  CSSFNetAdapter_LoginDataTestCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInTestData,const uint8_t* InTestData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::DataTestCmd::Create(pConnection->GetHeap(), InTransactionID,SF::ArrayView<uint8_t>(_sizeOfInTestData, _sizeOfInTestData, const_cast<uint8_t*>(InTestData)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginDataTestCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInTestData,const uint8_t* InTestData )


// C2S: Heartbeat
SFDLL_EXPORT int  CSSFNetAdapter_LoginHeartbeatC2SEvt( intptr_t InNativeConnectionHandle )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::HeartbeatC2SEvt::Create(pConnection->GetHeap());
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginHeartbeatC2SEvt( intptr_t InNativeConnectionHandle )



// Cmd: Write All!! User Score and Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_LoginDebugPrintALLRankingCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InFileName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::DebugPrintALLRankingCmd::Create(pConnection->GetHeap(), InTransactionID,InFileName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginDebugPrintALLRankingCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InFileName )




// Cmd: Login request
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InGameServerAddr, const NetAddress& InGameServerAddrIPV4, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::LoginRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InGameServerAddr,InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InGameServerAddr, const NetAddress& InGameServerAddrIPV4, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )



// Cmd: Login request with Facebook UID
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginByFacebookRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InGameServerAddr, const NetAddress& InGameServerAddrIPV4, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::LoginByFacebookRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InGameServerAddr,InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginByFacebookRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InGameServerAddr, const NetAddress& InGameServerAddrIPV4, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )



// Cmd: Login request
SFDLL_EXPORT int  CSSFNetAdapter_LoginCreateRandomUserRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InGameServerAddr, const NetAddress& InGameServerAddrIPV4, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::CreateRandomUserRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InGameServerAddr,InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginCreateRandomUserRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const NetAddress& InGameServerAddr, const NetAddress& InGameServerAddrIPV4, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )



// Cmd: Update my score and Get Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_LoginUpdateMyScoreRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::UpdateMyScoreRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<TotalRankingPlayerInformation>(_sizeOfInRanking, _sizeOfInRanking, const_cast<TotalRankingPlayerInformation*>(InRanking)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginUpdateMyScoreRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )



// Cmd: Get Ranking lise
SFDLL_EXPORT int  CSSFNetAdapter_LoginGetRankingListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::GetRankingListRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<TotalRankingPlayerInformation>(_sizeOfInRanking, _sizeOfInRanking, const_cast<TotalRankingPlayerInformation*>(InRanking)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginGetRankingListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )



// Cmd: For network test
SFDLL_EXPORT int  CSSFNetAdapter_LoginDataTestRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInTestData,const uint8_t* InTestData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::DataTestRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInTestData, _sizeOfInTestData, const_cast<uint8_t*>(InTestData)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginDataTestRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInTestData,const uint8_t* InTestData )



// Cmd: Write All!! User Score and Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_LoginDebugPrintALLRankingRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Login::DebugPrintALLRankingRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginDebugPrintALLRankingRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )









