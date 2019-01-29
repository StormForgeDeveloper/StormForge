////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
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

#include "EngineObject/SFEngineTask.h"

#include "Util/SFLog.h"
#include "Object/SFObject.h"
#include "Service/SFEngineService.h"

#include "SFCSUtil.h"
#include "IO/SFFileInputStream.h"
#include "IO/SFFileOutputStream.h"




using namespace SF;



//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT uint32_t SFFixedString_LoadStringTable(const char* strFileName)
{
	FileInputStream stream(strFileName);
	return (uint32_t)SF::Service::StringDB->LoadStringTable(stream);
}

SFDLL_EXPORT uint32_t SFFixedString_SaveStringTable(const char* strFileName)
{
	FileOutputStream stream(strFileName);
	return (uint32_t)SF::Service::StringDB->SaveStringTable(stream);
}

SFDLL_EXPORT void SFFixedString_AddString(const char* str)
{
	SF::Service::StringDB->AddString(str);
}

SFDLL_EXPORT uint64_t SFFixedString_AddNGetString(const char* str)
{
	return SF::Service::StringDB->AddNGetString(str);
}


SFDLL_EXPORT uint32_t SFFixedString_AddNGetString32(const char* str)
{
	return SF::Service::StringDB->AddNGetString32(str);
}


SFDLL_EXPORT const char* SFFixedString_GetString32(uint32_t hash)
{
	return SF::Service::StringDB->GetString(hash);
}


SFDLL_EXPORT const char* SFFixedString_GetString64(uint64_t hash)
{
	return SF::Service::StringDB->GetString(hash);
}


