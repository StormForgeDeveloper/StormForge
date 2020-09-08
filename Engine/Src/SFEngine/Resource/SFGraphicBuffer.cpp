////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Graphic buffer class
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFGraphicBuffer.h"


namespace SF
{
	template class SharedPointerT<GraphicBuffer>;



	////////////////////////////////////////////////////////////////////
	//
	//	Graphic buffer
	//



	GraphicBuffer::LockedData::LockedData(GraphicBuffer *pGraphicBuffer, uint8_t* pData)
		: m_pGraphicBuffer(pGraphicBuffer)
		, m_pData(pData)
	{
	}

	GraphicBuffer::LockedData::LockedData(LockedData&& src)
		: m_pGraphicBuffer(src.m_pGraphicBuffer)
		, m_pData(src.m_pData)
	{
		src.m_pGraphicBuffer = nullptr;
		src.m_pData = nullptr;
	}

	GraphicBuffer::LockedData::~LockedData()
	{
		Unlock();
	}

	void GraphicBuffer::LockedData::Unlock()
	{
		if (m_pGraphicBuffer == nullptr || m_pData == nullptr)
			return;

		m_pGraphicBuffer->UnlockData();
		m_pGraphicBuffer = nullptr;
		m_pData = nullptr;
	}


	GraphicBuffer::LockedData& GraphicBuffer::LockedData::operator =(LockedData&& src)
	{
		Unlock();

		m_pGraphicBuffer = src.m_pGraphicBuffer;
		m_pData = src.m_pData;
		src.m_pGraphicBuffer = nullptr;
		src.m_pData = nullptr;

		return *this;
	}

	////////////////////////////////////////////////////////////////////
	//
	//	Graphic buffer
	//

	GraphicBuffer::GraphicBuffer(IHeap& heap, StringCrc64 name, const CallTrack& callTrack)
		: Resource(heap, name, callTrack)
		, m_ChannelDescriptors(heap)
	{

	}


	GraphicBuffer::~GraphicBuffer()
	{

	}


	uint8_t* GraphicBuffer::LockData()
	{
		return m_pData;
	}

	void GraphicBuffer::UnlockData()
	{

	}


}

