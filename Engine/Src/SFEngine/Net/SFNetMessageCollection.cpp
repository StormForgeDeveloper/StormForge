////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : 2D Spatial grid
//	
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Net/SFNetDef.h"
#include "ResultCode/SFResultCodeLibrary.h"

#include "Net/SFNetMessageCollection.h"


namespace SF
{

    //////////////////////////////////////////////////////////////////////////
    //
    //	MessageCollection
    //

    void* MessageCollection::operator new(size_t size)
    {
        return MessageCollectionArray::stm_MemoryPool->Alloc(sizeof(MessageCollection) + CollectionBufferSize);
    }

    void MessageCollection::operator delete(void* pPtr)
    {
        MessageCollectionArray::stm_MemoryPool->Free(pPtr);
    }

	Result MessageCollection::AddMessage(const MessageHeader* pMessage)
	{
        if ((UsedSize + pMessage->Length) > CollectionBufferSize)
            return ResultCode::OUT_OF_MEMORY;

        memcpy(reinterpret_cast<uint8_t*>(this + 1) + UsedSize, pMessage, pMessage->Length);

        SFLog(Net, Debug8, "MessageCollection::AddMessage msgid:{0}, size:{1}, Offset:{2}", pMessage->msgID, pMessage->Length, UsedSize);

        UsedSize += pMessage->Length;

        return ResultCode::SUCCESS;
	}

	// Reset buffer
    void MessageCollection::Reset()
    {
        UsedSize = 0;
    }



	//////////////////////////////////////////////////////////////////////////
	//
	//	MessageCollectionArray
	//

    SharedPointerT<MemoryPool> MessageCollectionArray::stm_MemoryPool;

    MessageCollectionArray::MessageCollectionArray(size_t maxPacketBufferCount)
        : m_MaxPacketBufferCount(maxPacketBufferCount)
    {
        if (!stm_MemoryPool.IsValid())
        {
            size_t poolAllocationSize = sizeof(MessageCollection) + MessageCollection::CollectionBufferSize;
            stm_MemoryPool = new MemoryPool(GetSystemHeap(), poolAllocationSize);
        }
    }

    MessageCollectionArray::~MessageCollectionArray()
    {
        Reset();
    }

    void MessageCollectionArray::Reset()
    {
        for (MessageCollection* pBuffer : m_MessageCollections)
        {
            IHeap::Free(pBuffer);
        }
        m_MessageCollections.Reset();
    }

    Result MessageCollectionArray::AddMessage(const MessageHeader* pMessage)
    {
        MessageCollection* pBuffer{};
        if (m_MessageCollections.size() != 0)
        {
            pBuffer = m_MessageCollections[m_MessageCollections.size() - 1];
        }

        if (pBuffer == nullptr || !pBuffer->AddMessage(pMessage))
        {
            if (m_MessageCollections.size() >= m_MaxPacketBufferCount)
            {
                return ResultCode::MAX_PACKET;
            }

            pBuffer = new MessageCollection;

            m_MessageCollections.push_back(pBuffer);
            if (!pBuffer->AddMessage(pMessage))
            {
                assert(false);
                return ResultCode::OUT_OF_MEMORY;
            }
        }

        SFLog(Net, Debug8, "MessageCollectionArray::AddMessage msgid:{0}, numCollection:{1}", pMessage->msgID, m_MessageCollections.size());

        return ResultCode::SUCCESS;
    }

    void MessageCollectionArray::MoveAppend(MessageCollectionArray&& src)
    {
        m_MessageCollections.Append(src.m_MessageCollections);
        src.m_MessageCollections.Reset();
    }

    MessageCollectionArray& MessageCollectionArray::operator =(MessageCollectionArray&& src)
    {
        MoveAppend(Forward<MessageCollectionArray>(src));
        return *this;
    }

} // namespace SF
