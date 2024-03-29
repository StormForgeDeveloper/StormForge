////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated header, SF
//
////////////////////////////////////////////////////////////////////////////////


#include "SFTypedefs.h"
#include "ResultCode/SFResultTable.h"
#include "ResultCode/SFResultCodeSystem.h"



namespace SF {
namespace ResultCode {

	void InitializeResultCodeSystem() {

		auto& codeMap = ResultTable::GetOrAddFacility(0);

		codeMap.Insert((uint32_t)SUCCESS, {"SUCCESS", "SUCCESS"});
		codeMap.Insert((uint32_t)SUCCESS_FALSE, {"SUCCESS_FALSE", "SUCCESS_FALSE"});
		codeMap.Insert((uint32_t)SUCCESS_YIELD, {"SUCCESS_YIELD", "SUCCESS_YIELD"});
		codeMap.Insert((uint32_t)INVALID_POINTER, {"INVALID_POINTER", "INVALID_POINTER"});
		codeMap.Insert((uint32_t)FAIL, {"FAIL", "FAIL"});
		codeMap.Insert((uint32_t)NOT_IMPLEMENTED, {"NOT_IMPLEMENTED", "NOT_IMPLEMENTED"});
		codeMap.Insert((uint32_t)OUT_OF_MEMORY, {"OUT_OF_MEMORY", "OUT_OF_MEMORY"});
		codeMap.Insert((uint32_t)UNEXPECTED, {"UNEXPECTED", "UNEXPECTED"});
		codeMap.Insert((uint32_t)INVALID_ARG, {"INVALID_ARG", "INVALID_ARG"});
		codeMap.Insert((uint32_t)NO_DATA_EXIST, {"NO_DATA_EXIST", "NO_DATA_EXIST"});
        codeMap.Insert((uint32_t)INVALID_NAME, { "INVALID_NAME", "INVALID_NAME" });
        codeMap.Insert((uint32_t)INVALID_ENUM, { "INVALID_ENUM", "INVALID_ENUM" });

	}//InitializeResultCode 
}//namespace ResultCode 
}//namespace SF 



