////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 The Braves
// 
// Author : KyungKun Ko
//
// Description : Server constants definitions. 
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Container/SFOrderedLinkedList.h"
#include "Util/SFStringCrc64.h"


namespace SF {


	class AppConfig
	{
	private:

		struct LinkedListNode : public OrderedLinkedList<StringCrc64>::Node
		{
			const char* Value;
		};

		static int m_BufferUsedOffset;
		static char m_SettingBuffer[128 * 1024];

		static OrderedLinkedList<StringCrc64> m_Settings;

	private:

		static Result ProcessSingleParameter(const char* argument);

	public:

		// Process parameter
		static Result ProcessParameter(int numArg, const char* argc[]);
		static Result ProcessParameter(const char* arg);

		// Set setting value
		static Result SetSetting(const char* settingName, const char* value);

		// Get setting value
		static const char* GetSetting(const char* settingName, const char* defaultValue = "");
	};


}

