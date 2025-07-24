////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network classes definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetConst.h"
#include "Util/SFStrUtil.h"
#include "Container/SFHashTable.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Multithread/SFThread.h"
#include "Net/SFNetUtil.h"
#include "Component/SFLibraryComponent.h"
#include "EngineObject/SFEngineTask.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageData.h"

#include "Service/SFEngineServices.h"


namespace SF {
namespace Net {

	class Connection;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Overlapped I/O structures
	//

	struct IOBUFFER_WRITE;
	struct IOBUFFER_READ;
	struct IOBUFFER_ACCEPT;
	class SocketIO;

	enum class IOBUFFER_OPERATION : uint8_t
	{
		OP_NONE = 0,
		OP_TCPREAD,
		OP_TCPWRITE,
		OP_TCPACCEPT,
		OP_UDPREAD,
		OP_UDPWRITE,
	};


	// Get latest socket error 
	Result GetLastNetSystemResult();



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network system
	//
	class NetSystem : public LibraryComponent, public NetSystemService
	{
	public:

		static const StringCrc64 TypeName;

	private:

		uint32_t m_NumThread;
        uint32_t m_GatheringBufferSize{};
		uint32_t m_RecvBufferSize;
		uint32_t m_SendBufferSize;

		SharedPointerT<MemoryPool> m_pGatheringBufferPool;

		NetIOSystem* m_NetIOSystem;


	public:

		static inline bool IsProactorSystem()
		{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS  // IOCP
			return true;
#else        // EPOLL/KQUEUE
			return false;
#endif
		}

		NetSystem(uint recvBufferSize, uint sendBufferSize, uint numThread, uint gatheringBufferSize);
		~NetSystem();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }
		
		// Initialize component
		virtual Result InitializeComponent() override;

		// Terminate component
		virtual void DeinitializeComponent() override;


		///////////////////////////////////////////////////////////////////////////////
		// 

	
		virtual NetIOSystem& GetNetIOSystem() override { return m_NetIOSystem == nullptr ? NetSystemService::GetNetIOSystem() : *m_NetIOSystem; }
		
		//virtual WriteBufferQueue* GetWriteBufferQueue() override;

        virtual Net::IOBUFFER_WRITE* AllocateWriteBuffer() override;
        virtual size_t GetWriteBufferSize() override { return m_GatheringBufferSize; }


		///////////////////////////////////////////////////////////////////////////////
		// Socket handling 

		virtual Result SetupCommonSocketOptions(SocketType sockType, SockFamily sockFamily, SF_SOCKET socket, bool acceptedSocket = false) override;

		virtual Result RegisterSocket(SocketIO* cbInstance) override;
		virtual Result UnregisterSocket(SocketIO* cbInstance) override;
		//Result RegisterSharedSocket(SocketType sockType, SocketIO* cbInstance) override;

		virtual SF_SOCKET Socket(SockFamily domain, SocketType type) override;
		virtual void CloseSocket(SF_SOCKET sock) override;

		virtual Result Accept(SF_SOCKET sockListen, IOBUFFER_ACCEPT* pAccept) override;
		virtual Result HandleAcceptedSocket(SF_SOCKET sockListen, IOBUFFER_ACCEPT* pAccept, sockaddr_storage& remoteAddr) override;

		virtual Result Recv(SocketIO* sock, IOBUFFER_READ* pBuffer) override;
		virtual Result RecvFrom(SocketIO* sock, IOBUFFER_READ* pBuffer) override;

		virtual Result Send(SocketIO* sock, IOBUFFER_WRITE* pBuffer) override;
		virtual Result SendTo(SocketIO* sock, IOBUFFER_WRITE* pBuffer) override;
	};




} // namespace Net
} // namespace SF

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
#include "Net/SFNetSystem_WinIOCP.h"
#else
#include "Net/SFNetSystem_Linux.h"
#endif

namespace SF
{
    namespace Net
    {
        // This is type for reserving memory space, don't use it directly
        union IOBUFFER_RW_STORAGE
        {
            IOBUFFER_RW_STORAGE() {}
            ~IOBUFFER_RW_STORAGE() {}

            IOBUFFER_WRITE WriteBuffer;
            IOBUFFER_READ ReadBuffer;
        };
    }
}
