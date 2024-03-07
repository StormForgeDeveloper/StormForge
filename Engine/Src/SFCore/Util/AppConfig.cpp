////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : Base type ToString implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "Util/SFStrParserUtil.h"
#include "Util/SFStrUtil.h"
#include "Util/AppConfig.h"


namespace SF
{

	int AppConfig::m_BufferUsedOffset = 0;
	char AppConfig::m_SettingBuffer[128 * 1024];

	OrderedLinkedList<StringCrc64> AppConfig::m_Settings;


	Result AppConfig::ProcessSingleParameter(const char* argument)
	{
		Result hr = ResultCode::SUCCESS;
		char argTempString[1024];
		char* key = nullptr;
		char* value = nullptr;
		const char* seps = ":=";
		StrUtil::StringCopy(argTempString, argument);

		switch (argument[0])
		{
		case '+':
		case '-':
			argument++;
			StrUtil::StringCopy(argTempString, argument);

			key = argTempString;
			value = (char*)StrUtil::FindToken(argTempString, seps);
			if (value != nullptr)
			{
				*value = '\0';
				value++;
			}
			StrUtil::StringLowerInline(key, (int)strlen(key));

			if (value == nullptr)
			{
				hr = SetSetting(key, "true");
				if (!hr.IsSuccess()) return hr;
			}
			else
			{
				hr = SetSetting(key, value);
				if (!hr.IsSuccess()) return hr;
			}

			break;
		default:
			break;
		};

		return hr;
	}

	Result AppConfig::ProcessParameter(const char* arg)
	{
		Result hr = ResultCode::SUCCESS;
		char* curArg = nullptr;
		char settingBufferForParsing[64 * 1024];

		if (arg == nullptr) return ResultCode::INVALID_ARG;

		hr = StrUtil::StringCopy(settingBufferForParsing, arg);
		if (!hr.IsSuccess()) return hr;

		curArg = StrUtil::SkipWhiteSpace(settingBufferForParsing);
		while (curArg != nullptr)
		{
			char* endOfArg = StrUtil::NextWhiteSpace(curArg);
			if (endOfArg != nullptr)
				*endOfArg = '\0';

			hr = ProcessSingleParameter(curArg);
			if (!hr.IsSuccess()) return hr;

			if (endOfArg == nullptr)
				break;

			curArg = StrUtil::SkipWhiteSpace(endOfArg+1);
		}

		return hr;
	}

	Result AppConfig::ProcessParameter(int numArg, const char* argc[])
	{
		Result hr = ResultCode::SUCCESS;

		for (int iArg = 0; iArg < numArg; iArg++)
		{
			hr = ProcessSingleParameter(argc[iArg]);
			if (!hr.IsSuccess()) return hr;
		}

		return hr;
	}


	// Set setting value
	Result AppConfig::SetSetting(const char* settingName, const char* value)
	{
		Result hr = ResultCode::SUCCESS;

		char* bufferPos = m_SettingBuffer + m_BufferUsedOffset;
		INT bufferSize = (INT)countof(m_SettingBuffer) - m_BufferUsedOffset;
		StringCrc64 key;
		decltype(m_Settings)::Node *pPrevNode = nullptr;
		LinkedListNode *pNewNode = nullptr;

		char* curSettingValue = bufferPos;
		hr = StrUtil::StringCopyEx(bufferPos, bufferSize, value);
		if (!hr.IsSuccess()) return hr;

		*bufferPos++ = '\0'; bufferSize--;

		key = StringCrc64(settingName);
		hr = m_Settings.FindPrevNode(key, pPrevNode);
		if (!hr.IsSuccess()) return hr;

		if (pPrevNode->Key == key)
		{
			// We just need to replace the value
			pNewNode = (LinkedListNode*)pPrevNode;
			pNewNode->Value = curSettingValue;
		}
		else
		{
			// Add new value
			char* curSettingName = bufferPos;
			hr = StrUtil::StringLwrEx(bufferPos, bufferSize, settingName);
			if (!hr.IsSuccess()) return hr;

			*bufferPos++ = '\0'; bufferSize--;
			if (bufferSize < (INT)sizeof(LinkedListNode))
				return ResultCode::OUT_OF_MEMORY;

			pNewNode = (LinkedListNode*)bufferPos;
			bufferPos += sizeof(LinkedListNode);
			bufferSize = (decltype(bufferSize))(bufferSize - sizeof(LinkedListNode));

			memset(pNewNode, 0, sizeof(LinkedListNode));
			pNewNode->Key = StringCrc64(curSettingName);
			pNewNode->Value = curSettingValue;

			hr = m_Settings.Insert(pPrevNode, pNewNode->Key, pNewNode);
			if (!hr.IsSuccess()) return hr;
		}

		m_BufferUsedOffset = (INT)countof(m_SettingBuffer) - bufferSize;

		return hr;
	}

	// Get setting value
	const char* AppConfig::GetSetting(const char* settingName, const char* defaultValue)
	{
		decltype(m_Settings)::Node *pPrevNode = nullptr, *pCur = nullptr;
		StringCrc64 key(settingName);

		if (!(m_Settings.FindPrevNode(key, pPrevNode)))
			return defaultValue;

		pCur = pPrevNode->pNext;
		if(pCur == nullptr || pCur->Key != key)
			return defaultValue;

		return ((LinkedListNode*)pCur)->Value;
	}

	void AppConfig::GetSettingArray(const char* settingName, Array<const char*>& outValues)
	{
		decltype(m_Settings)::Node* pPrevNode = nullptr, * pCur = nullptr;
		StringCrc64 key(settingName);

		if (!(m_Settings.FindPrevNode(key, pPrevNode)))
			return;

		pCur = pPrevNode->pNext;
		for (;pCur && pCur->Key == key; pCur = pCur->pNext)
		{
			outValues.push_back(((LinkedListNode*)pCur)->Value);
		}
	}

};	// namespace SF


