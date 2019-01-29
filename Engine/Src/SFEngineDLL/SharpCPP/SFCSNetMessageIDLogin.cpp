////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Login Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/Message/LoginMsgClass.h"
#include "SFCSUtil.h"



using namespace SF;


// Cmd: Login request
SFDLL_EXPORT int  CSSFNetMessageID_LoginLoginCmd()
{
 	return SF::Message::Login::LoginCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginLoginCmd()


SFDLL_EXPORT int  CSSFNetMessageID_LoginLoginRes()
{
 	return SF::Message::Login::LoginRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginLoginRes()


// Cmd: Login request with Facebook UID
SFDLL_EXPORT int  CSSFNetMessageID_LoginLoginByFacebookCmd()
{
 	return SF::Message::Login::LoginByFacebookCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginLoginByFacebookCmd()


SFDLL_EXPORT int  CSSFNetMessageID_LoginLoginByFacebookRes()
{
 	return SF::Message::Login::LoginByFacebookRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginLoginByFacebookRes()


// Cmd: Login request
SFDLL_EXPORT int  CSSFNetMessageID_LoginCreateRandomUserCmd()
{
 	return SF::Message::Login::CreateRandomUserCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginCreateRandomUserCmd()


SFDLL_EXPORT int  CSSFNetMessageID_LoginCreateRandomUserRes()
{
 	return SF::Message::Login::CreateRandomUserRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginCreateRandomUserRes()


// Cmd: Update my score and Get Ranking list
SFDLL_EXPORT int  CSSFNetMessageID_LoginUpdateMyScoreCmd()
{
 	return SF::Message::Login::UpdateMyScoreCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginUpdateMyScoreCmd()


SFDLL_EXPORT int  CSSFNetMessageID_LoginUpdateMyScoreRes()
{
 	return SF::Message::Login::UpdateMyScoreRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginUpdateMyScoreRes()


// Cmd: Get Ranking lise
SFDLL_EXPORT int  CSSFNetMessageID_LoginGetRankingListCmd()
{
 	return SF::Message::Login::GetRankingListCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginGetRankingListCmd()


SFDLL_EXPORT int  CSSFNetMessageID_LoginGetRankingListRes()
{
 	return SF::Message::Login::GetRankingListRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginGetRankingListRes()


// Cmd: For network test
SFDLL_EXPORT int  CSSFNetMessageID_LoginDataTestCmd()
{
 	return SF::Message::Login::DataTestCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginDataTestCmd()


SFDLL_EXPORT int  CSSFNetMessageID_LoginDataTestRes()
{
 	return SF::Message::Login::DataTestRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginDataTestRes()


// C2S: Heartbit
SFDLL_EXPORT int  CSSFNetMessageID_LoginHeartBitC2SEvt()
{
 	return SF::Message::Login::HeartBitC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginHeartBitC2SEvt()


// Cmd: Write All!! User Score and Ranking list
SFDLL_EXPORT int  CSSFNetMessageID_LoginDebugPrintALLRankingCmd()
{
 	return SF::Message::Login::DebugPrintALLRankingCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginDebugPrintALLRankingCmd()


SFDLL_EXPORT int  CSSFNetMessageID_LoginDebugPrintALLRankingRes()
{
 	return SF::Message::Login::DebugPrintALLRankingRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_LoginDebugPrintALLRankingRes()










