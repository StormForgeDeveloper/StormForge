////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Graphic buffer class
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"

namespace SF
{
	class ResourceManager;



	// Graphic buffer channel format
	enum class GraphicBufferChannelFormat : uint8_t
	{
		Invalid,		// Invalid or Dummy
		Bool,
		Int8,
		Int16,
		Int32,
		Float,
		Vector2,
		Vector3,
		Vector4,
	};



	// Graphic system buffer
	class GraphicBuffer : public Resource
	{
	public:

#pragma pack(push,1)
		struct ChannelDescription
		{
			// buffer data format
			GraphicBufferChannelFormat Format;

			// Data stride
			uint8_t DataStride;

			// Dummy
			uint8_t Dummy[2];
		};
#pragma pack(pop)



		////////////////////////////////////////////////////////////////////
		//
		//	Type definitions
		//

		// Image data lock manager. help for unlock imagedata
		class LockedData
		{
		private:
			GraphicBuffer *m_pGraphicBuffer = nullptr;
			uint8_t* m_pData = nullptr;

		private:
			LockedData(GraphicBuffer *pBuffer, uint8_t* pData);

			friend class Texture;

		public:
			LockedData() {}
			LockedData(LockedData&& src);
			~LockedData();

			// Unlock
			void Unlock();

			operator uint8_t*()
			{
				return m_pData;
			}

			LockedData& operator =(LockedData&& src);
		};


	private:

		// element format
		DynamicArray<ChannelDescription> m_ChannelDescriptors;

		// count of data element
		uint32_t m_ElementCount = 0;

		// data stride
		uint32_t m_ElementStride = 0;

		// In-memory data pointer
		uint8_t * m_pData = nullptr;

		// TODO: Graphics buffer



	public:
		GraphicBuffer(IHeap& heap, FixedString name, const CallTrack& callTrack = CallTrack());
		virtual ~GraphicBuffer();

		// Channel descriptor
		Array<ChannelDescription>& GetChannelDescriptor() { return m_ChannelDescriptors; }

		// Element count
		uint32_t GetElementCount() const { return m_ElementCount; }

		// Element stride
		uint32_t GetElementStride() const { return m_ElementStride; }


		// lock/unlock data
		virtual uint8_t* LockData();
		virtual void UnlockData();
	};


	typedef SharedPointerT<GraphicBuffer> GraphicBufferPtr;
	extern template class SharedPointerT<GraphicBuffer>;

}

