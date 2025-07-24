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
                g_PacketDataPool = new MemoryPool(GetSystemHeap(), sizeof(PacketData));
            }

            return g_PacketDataPool;
        }

    } // namespace Net
} // namespace SF
