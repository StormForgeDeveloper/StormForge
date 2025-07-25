////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : Packet data
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
    namespace Net {
        //////////////////////////////////////////////////////////////////////////
        //
        //	Packet data class
        //

        // Packet data
        struct PacketData : public Net::IOBUFFER_WRITE
        {
            static const SharedPointerT<MemoryPool>& GetAllocationPool();

            ArrayView<uint8_t> Payload;
            uint8_t PayloadBuffer[Net::Const::PACKET_SIZE_MAX];


            PacketData()
                : Payload(Const::PACKET_SIZE_MAX, 0, PayloadBuffer)
            {
            }

            ~PacketData()
            {
            }

            void* operator new(size_t size) {
                return GetAllocationPool()->Alloc(size);
            }

            // Override operator delete
            void operator delete(void* ptr) {
                GetAllocationPool()->Free(ptr);
            }


            SF_FORCEINLINE bool CanAdd(size_t length) const {
                return (Payload.GetAllocatedSize() - Payload.size()) >= length;
            }

            SF_FORCEINLINE Result AddPacketHeader(uint64_t PeerId)
            {
                PacketHeader* pPacketHeader = reinterpret_cast<PacketHeader*>(Payload.data());

                Payload.resize(Payload.size() + sizeof(PacketHeader));

                pPacketHeader->PeerId = PeerId;

                return ResultCode::SUCCESS;
            }

            SF_FORCEINLINE MessageHeader* AddMessage(const MessageHeader* pMsgHeader)
            {
                if (!CanAdd(pMsgHeader->MessageSize))
                    return nullptr;

                MessageHeader* pDestHeader = reinterpret_cast<MessageHeader*>(Payload.data() + Payload.size());
                Payload.resize(Payload.size() + pMsgHeader->MessageSize);
                memcpy(pDestHeader, pMsgHeader, pMsgHeader->MessageSize);

                return pDestHeader;
            }

            SF_FORCEINLINE uint8_t* GetNextMessagePtr() {
                return Payload.data() + Payload.size();
            }

            void PrepareBufferForIO()
            {
                InitBuff((uint)Payload.size(), Payload.data());
            }
        };


    } // namespace Net
} // namespace SF
