////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Raw binary resource
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFRawBinary.h"


namespace SF
{
	template class SharedPointerT<RawBinary>;

	RawBinary::RawBinary(const CallTrack& callTrack)
		: Resource("bin", callTrack)
	{

	}

	RawBinary::~RawBinary()
	{
		if (m_Data != nullptr)
			delete (m_Data);

		m_Data = nullptr;
	}

	void RawBinary::Dispose()
	{
		if (m_Data != nullptr)
			delete (m_Data);

		m_DataSize = 0;
		m_Data = nullptr;
	}

	// Set binary data. the ownership of the data will be taken over
	void RawBinary::SetBinaryData(size_t dataSize, uint8_t* &pData)
	{
		if (m_Data != nullptr)
			delete (m_Data);

		m_DataSize = dataSize;
		m_Data = pData;
		pData = nullptr;
	}


}

