﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated header, Login
//
////////////////////////////////////////////////////////////////////////////////

#include "SFTypedefs.h"
#include "ResultCode/SFResultTable.h"
#include "ResultCode/SFResultCodeLogin.h"



namespace SF {
namespace ResultCode {

	void InitializeResultCodeLogin() {

		auto& codeMap = ResultTable::GetOrAddFacility(1798);
		codeMap.Insert((uint32_t)LOGIN_INVALID_USERNAME, {"LOGIN_INVALID_USERNAME", "Invalid username"});
		codeMap.Insert((uint32_t)LOGIN_INVALID_PASSWORD, {"LOGIN_INVALID_PASSWORD", "Invalid password"});
		codeMap.Insert((uint32_t)LOGIN_ALREADY_LOGGEDIN, {"LOGIN_ALREADY_LOGGEDIN", "Already logged in"});
		codeMap.Insert((uint32_t)LOGIN_ALREADY_LOGGEDIN_OTHERPLACE, {"LOGIN_ALREADY_LOGGEDIN_OTHERPLACE", "Already logged in at another place, and failed to kick"});
		codeMap.Insert((uint32_t)LOGIN_INVALID_SIGNATURE, {"LOGIN_INVALID_SIGNATURE", "Invalid user signature"});
		codeMap.Insert((uint32_t)LOGIN_NO_APP_OWNERSHIP, {"LOGIN_NO_APP_OWNERSHIP", "The user doesn't have app ownership"});
		codeMap.Insert((uint32_t)LOGIN_ACCOUNT_BLOCKED, {"LOGIN_ACCOUNT_BLOCKED", "The user is blocked"});
		codeMap.Insert((uint32_t)LOGIN_ACCOUNT_DOES_NOT_EXIST, {"LOGIN_ACCOUNT_DOES_NOT_EXIST", "The user is not exist"});
		codeMap.Insert((uint32_t)LOGIN_INVALID_PLATFORM_LOGIN, {"LOGIN_INVALID_PLATFORM_LOGIN", "The user's platform login is invalid"});

	}//InitializeResultCode 
}//namespace ResultCode 
}//namespace SF 


