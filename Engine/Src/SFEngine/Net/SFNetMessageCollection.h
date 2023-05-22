////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : 2D Spatial grid 
//	
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Container/SFStaticLinkedList.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetConst.h"

namespace SF {

    class MemoryPool;

	//////////////////////////////////////////////////////////////////////////
	//
	//	Packet buffer class
	//

    class MessageIterator
    {
    public:
        MessageIterator()
        {
        }

        MessageIterator(const Array<uint8_t>& buffer)
            : Buffer(buffer)
        {
        }

        MessageIterator& operator ++()
        {
            const MessageHeader* pHeader = get();
            if (pHeader)
            {
                CurPos += pHeader->Length;
            }

            return *this;
        }

        uint GetCurPos() const { return CurPos; }

        const MessageHeader* get() const
        {
            if (CurPos >= Buffer.size())
            {
                return nullptr;
            }

            const MessageHeader* pHeader = reinterpret_cast<const MessageHeader*>(Buffer.data() + CurPos);
            if ((CurPos + pHeader->Length) > Buffer.size())
            {
                // Likely broken
                assert(false);
                return nullptr;
            }

            return pHeader;

        }

        operator const MessageHeader* () const
        {
            return get();
        }

        const MessageHeader* operator ->() const
        {
            return get();
        }

        operator bool() const
        {
            return get() != nullptr;
        }

    private:
        uint CurPos = 0;
        Array<uint8_t> Buffer;
    };

	struct MessageCollection
	{
        static constexpr size_t CollectionBufferSize = 4 * 1024;
        uint8_t CollectionBuffer[CollectionBufferSize];

        // New packet buffer
        void* operator new(size_t size);
        void operator delete(void* pPtr);

		SF_FORCEINLINE size_t capacity() const { return CollectionBufferSize; }
        SF_FORCEINLINE size_t size() const { return UsedSize; }

        // Add message
		Result AddMessage(const MessageHeader* pMessage);

		// release buffer
		void Reset();

        SF_FORCEINLINE uint8_t* GetDataPtr()
        {
            return reinterpret_cast<uint8_t*>(this + 1);
        }

        SF_FORCEINLINE const uint8_t* GetDataPtr() const
        {
            return const_cast<MessageCollection*>(this)->GetDataPtr();
        }

        // Get first message data pointer
		SF_FORCEINLINE const MessageHeader* GetMessageDataPtr()
        {
            return reinterpret_cast<const MessageHeader*>(GetDataPtr());
        }

        MessageIterator begin() const { return MessageIterator(ArrayView<uint8_t>(UsedSize, const_cast<uint8_t*>(GetDataPtr()))); }
        MessageIterator end() const { return MessageIterator(); }

		// Used buffer size
		size_t UsedSize{};
	};



	// 
	class MessageCollectionArray
	{
	public:
        MessageCollectionArray(size_t maxPacketBufferCount = 20);
        ~MessageCollectionArray();

        // purge all message buffer
        void Reset();

        // collection count
        SF_FORCEINLINE size_t GetCollectionCount() const { return m_MessageCollections.size(); }

        // Add message
        Result AddMessage(const MessageHeader* pMessage);

        // move packet buffers in src to this instance. packet buffers are append to current list
        void MoveAppend(MessageCollectionArray&& src);

        // get stored message array
        const Array<MessageCollection*>& GetPacketArray() const { return m_MessageCollections; }

        auto begin() const { return m_MessageCollections.begin(); }
        auto end() const { return m_MessageCollections.end(); }

        MessageCollectionArray& operator =(MessageCollectionArray&& src);

	private:
        friend struct MessageCollection;
        static SharedPointerT<MemoryPool> stm_MemoryPool;

        size_t m_MaxPacketBufferCount = 4;

		DynamicArray<MessageCollection*> m_MessageCollections;
	};



} // namespace SF
