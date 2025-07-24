////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Raw binary resource
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"


namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	RawBinary
	//
	class RawBinary : public Resource
	{
	public:


	private:

		// Size of the data
		size_t m_DataSize = 0;

		// Data pointer
		uint8_t* m_Data = nullptr;

	public:
		RawBinary(const CallTrack& callTrack = CallTrack());
		virtual ~RawBinary();

		virtual void Dispose() override;

		// Set binary data. the ownership of the data will be taken over
		void SetBinaryData(size_t dataSize, uint8_t* &pData);

		size_t GetBinarySize() const { return m_DataSize; }

		const uint8_t* GetBinaryData() const { return m_Data; }
	};


	typedef SharedPointerT<RawBinary> RawBinaryPtr;
	extern template class SharedPointerT<RawBinary>;

}

