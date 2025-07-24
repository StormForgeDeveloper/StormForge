////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TString
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFStrFormat.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFString.h"
#include "Util/SFStringFormat.h"
#include "Util/SFUtility.h"


namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	TString
	//


	const String String_Empty("");
	const String String_True("true");
	const String String_False("false");
	const String String_Success("Success");
	const String String_Fail("Fail");

	const WString WString_Empty(L"");
	const WString WString_True(L"true");
	const WString WString_False(L"false");
	const WString WString_Success(L"Success");
	const WString WString_Fail(L"Fail");


	template class TString<char>;
	template class TString<wchar_t>;




} // namespace SF



