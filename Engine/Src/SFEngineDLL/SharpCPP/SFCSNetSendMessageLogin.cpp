////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Login Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/LoginMsgClass.h"
#include "Interfaces/Sharp/SFCSUtil.h"



using namespace SF;


// Cmd: Login request
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, const char* InID, const char* InPassword )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::LoginCmd::CalculateMessageSize( InTransactionID, InGameID,InID,InPassword);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::LoginCmd::Create(pMessage,  InTransactionID, InGameID,InID,InPassword);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, const char* InID, const char* InPassword )


// Cmd: Login request with Facebook UID
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginByFacebookCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, uint64_t InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::LoginByFacebookCmd::CalculateMessageSize( InTransactionID, InGameID, InUID,InFaceBookName,InEMail,InFacebookToken);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::LoginByFacebookCmd::Create(pMessage,  InTransactionID, InGameID, InUID,InFaceBookName,InEMail,InFacebookToken);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginByFacebookCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, uint64_t InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )


// Cmd: Login request with Facebook UID
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginBySteamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, uint64_t InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::LoginBySteamCmd::CalculateMessageSize( InTransactionID, InGameID, InSteamUserID,InSteamUserName,InSteamUserToken);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::LoginBySteamCmd::Create(pMessage,  InTransactionID, InGameID, InSteamUserID,InSteamUserName,InSteamUserToken);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginBySteamCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, uint64_t InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken )


// Cmd: Login request
SFDLL_EXPORT int  CSSFNetAdapter_LoginCreateRandomUserCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, const char* InCellPhone )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::CreateRandomUserCmd::CalculateMessageSize( InTransactionID, InGameID,InCellPhone);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::CreateRandomUserCmd::Create(pMessage,  InTransactionID, InGameID,InCellPhone);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginCreateRandomUserCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InGameID, const char* InCellPhone )


// Cmd: Update my score and Get Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_LoginUpdateMyScoreCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InRankingScore, int InRankingType, uint16_t InCount )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::UpdateMyScoreCmd::CalculateMessageSize( InTransactionID, InRankingScore,(RankingType) InRankingType, InCount);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::UpdateMyScoreCmd::Create(pMessage,  InTransactionID, InRankingScore,(RankingType) InRankingType, InCount);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginUpdateMyScoreCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InRankingScore, int InRankingType, uint16_t InCount )


// Cmd: Get Ranking lise
SFDLL_EXPORT int  CSSFNetAdapter_LoginGetRankingListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, int InRankingType, uint8_t InBaseRanking, uint8_t InCount )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::GetRankingListCmd::CalculateMessageSize( InTransactionID,(RankingType) InRankingType, InBaseRanking, InCount);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::GetRankingListCmd::Create(pMessage,  InTransactionID,(RankingType) InRankingType, InBaseRanking, InCount);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginGetRankingListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, int InRankingType, uint8_t InBaseRanking, uint8_t InCount )


// Cmd: For network test
SFDLL_EXPORT int  CSSFNetAdapter_LoginDataTestCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInTestData,const uint8_t* InTestData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::DataTestCmd::CalculateMessageSize( InTransactionID,SF::ArrayView<uint8_t>(_sizeOfInTestData, _sizeOfInTestData, const_cast<uint8_t*>(InTestData)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::DataTestCmd::Create(pMessage,  InTransactionID,SF::ArrayView<uint8_t>(_sizeOfInTestData, _sizeOfInTestData, const_cast<uint8_t*>(InTestData)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginDataTestCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInTestData,const uint8_t* InTestData )


// C2S: Heartbeat
SFDLL_EXPORT int  CSSFNetAdapter_LoginHeartbeatC2SEvt( intptr_t InNativeConnectionHandle )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::HeartbeatC2SEvt::CalculateMessageSize();
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::HeartbeatC2SEvt::Create(pMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginHeartbeatC2SEvt( intptr_t InNativeConnectionHandle )



// Cmd: Write All!! User Score and Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_LoginDebugPrintALLRankingCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InFileName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::DebugPrintALLRankingCmd::CalculateMessageSize( InTransactionID,InFileName);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::DebugPrintALLRankingCmd::Create(pMessage,  InTransactionID,InFileName);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginDebugPrintALLRankingCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InFileName )




// Cmd: Login request
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InGameServerPublicAddress, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID, const char* InErrorReason )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::LoginRes::CalculateMessageSize( InTransactionID, InResult,InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID,InErrorReason);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::LoginRes::Create(pMessage,  InTransactionID, InResult,InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID,InErrorReason);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InGameServerPublicAddress, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID, const char* InErrorReason )



// Cmd: Login request with Facebook UID
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginByFacebookRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InGameServerPublicAddress, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID, const char* InErrorReason )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::LoginByFacebookRes::CalculateMessageSize( InTransactionID, InResult,InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID,InErrorReason);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::LoginByFacebookRes::Create(pMessage,  InTransactionID, InResult,InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID,InErrorReason);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginByFacebookRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InGameServerPublicAddress, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID, const char* InErrorReason )



// Cmd: Login request with Facebook UID
SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginBySteamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InGameServerPublicAddress, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID, const char* InErrorReason )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::LoginBySteamRes::CalculateMessageSize( InTransactionID, InResult,InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID,InErrorReason);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::LoginBySteamRes::Create(pMessage,  InTransactionID, InResult,InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID,InErrorReason);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginLoginBySteamRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InGameServerPublicAddress, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID, const char* InErrorReason )



// Cmd: Login request
SFDLL_EXPORT int  CSSFNetAdapter_LoginCreateRandomUserRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InGameServerPublicAddress, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::CreateRandomUserRes::CalculateMessageSize( InTransactionID, InResult,InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::CreateRandomUserRes::Create(pMessage,  InTransactionID, InResult,InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginCreateRandomUserRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InGameServerPublicAddress, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )



// Cmd: Update my score and Get Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_LoginUpdateMyScoreRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::UpdateMyScoreRes::CalculateMessageSize( InTransactionID, InResult,SF::ArrayView<TotalRankingPlayerInformation>(_sizeOfInRanking, _sizeOfInRanking, const_cast<TotalRankingPlayerInformation*>(InRanking)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::UpdateMyScoreRes::Create(pMessage,  InTransactionID, InResult,SF::ArrayView<TotalRankingPlayerInformation>(_sizeOfInRanking, _sizeOfInRanking, const_cast<TotalRankingPlayerInformation*>(InRanking)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginUpdateMyScoreRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )



// Cmd: Get Ranking lise
SFDLL_EXPORT int  CSSFNetAdapter_LoginGetRankingListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::GetRankingListRes::CalculateMessageSize( InTransactionID, InResult,SF::ArrayView<TotalRankingPlayerInformation>(_sizeOfInRanking, _sizeOfInRanking, const_cast<TotalRankingPlayerInformation*>(InRanking)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::GetRankingListRes::Create(pMessage,  InTransactionID, InResult,SF::ArrayView<TotalRankingPlayerInformation>(_sizeOfInRanking, _sizeOfInRanking, const_cast<TotalRankingPlayerInformation*>(InRanking)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginGetRankingListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )



// Cmd: For network test
SFDLL_EXPORT int  CSSFNetAdapter_LoginDataTestRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInTestData,const uint8_t* InTestData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::DataTestRes::CalculateMessageSize( InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInTestData, _sizeOfInTestData, const_cast<uint8_t*>(InTestData)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::DataTestRes::Create(pMessage,  InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInTestData, _sizeOfInTestData, const_cast<uint8_t*>(InTestData)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginDataTestRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInTestData,const uint8_t* InTestData )



// Cmd: Write All!! User Score and Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_LoginDebugPrintALLRankingRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Login::DebugPrintALLRankingRes::CalculateMessageSize( InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Login::DebugPrintALLRankingRes::Create(pMessage,  InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (uint32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_LoginDebugPrintALLRankingRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )









