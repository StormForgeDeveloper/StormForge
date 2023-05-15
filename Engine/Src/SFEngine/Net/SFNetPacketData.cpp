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

#include "Net/SFNetPacketData.h"


namespace SF
{
    namespace Net {

        //////////////////////////////////////////////////////////////////////////
        //
        //	PacketData
        //

        static SharedPointerT<MemoryPool> g_PacketDataPool;

        const SharedPointerT<MemoryPool>& PacketData::GetAllocationPool()
        {
            if (!g_PacketDataPool.IsValid())
            {
                g_PacketDataPool = new(GetSystemHeap()) MemoryPool(GetSystemHeap(), sizeof(PacketData));
            }

            return g_PacketDataPool;
        }

        PacketData* PacketData::NewPacketData()
        {
            // We have new operator overriding on IOBUFFER_WRITE. only regular new or buffer
            //PacketData::GetAllocationPool()->Alloc(sizeof(PacketData));
            return new(*(IHeap*)PacketData::GetAllocationPool().get()) PacketData;
        }

    } // namespace Net
} // namespace SF
