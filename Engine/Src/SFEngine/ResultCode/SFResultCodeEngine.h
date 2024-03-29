﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated header, Engine
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <stdint.h>



namespace SF {
	namespace ResultCode {



			// Engine initialization is failed 
			constexpr Result 			ENGINE_INITIALIZATION_FAILED                                       ((int32_t)0xE7020000L);

			// Invalid configuration 
			constexpr Result 			ENGINE_INVALID_CONFIG                                              ((int32_t)0xE7020001L);

			// Connection failed 
			constexpr Result 			ENGINE_CONNECTION_FAILED                                           ((int32_t)0xE7020002L);

			// Connectionlost 
			constexpr Result 			ENGINE_CONNECTION_LOST                                             ((int32_t)0xE7020003L);

			// Invalid character data 
			constexpr Result 			ENGINE_INVALID_CHARACTER                                           ((int32_t)0xE7020004L);

			// Invalid table id 
			constexpr Result 			ENGINE_INVALID_TABLE_ID                                            ((int32_t)0xE7020005L);

			// Invalid platform 
			constexpr Result 			ENGINE_INVALID_PLATFORM                                            ((int32_t)0xE7020006L);

			// Already Used Item 
			constexpr Result 			ENGINE_ALREADY_USED_ITEM                                           ((int32_t)0xE7020007L);

			// Already Used Key 
			constexpr Result 			ENGINE_ALREADY_USED_KEY                                            ((int32_t)0xE7020008L);

			// Invalid online session. probably kicked 
			constexpr Result 			ENGINE_INVALID_ONLINE_SESSION                                      ((int32_t)0xE7020009L);

	void InitializeResultCodeEngine();

	}//namespace ResultCode 
}//namespace SF 





