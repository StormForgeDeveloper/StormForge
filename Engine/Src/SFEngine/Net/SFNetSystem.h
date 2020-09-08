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
#include "String/SFStrUtil.h"
#include "Container/SFHashTable.h"
#include "Memory/SFMemoryPool.h"
#include "Thread/SFThread.h"
#include "Net/SFNetUtil.h"
#include "Object/SFLibraryComponent.h"
#include "EngineObject/SFEngineTask.h"

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


	// Get lastest socket error 
	Result GetLastNetSystemResult();



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network system
	//
	class NetSystem : public LibraryComponent, public NetSystemService
	{
	public:

		static constexpr StringCrc64 TypeName = "NetSystem";

	private:

		uint32_t m_NumThread;
		uint32_t m_GatheringBufferSize;
		uint32_t m_RecvBufferSize;
		uint32_t m_SendBufferSize;

		MemoryPool* m_pGatheringBufferPool;

		// Network memory manager
		Heap m_Heap;

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

		virtual const StringCrc64& GetTypeName() override { return TypeName; }
		
		// Initialize component
		virtual Result InitializeComponent() override;

		// Terminate component
		virtual void DeinitializeComponent() override;


		///////////////////////////////////////////////////////////////////////////////
		// 

		virtual IHeap& GetHeap() override { return m_Heap; }
		
		virtual NetIOSystem& GetNetIOSystem() override { return m_NetIOSystem == nullptr ? NetSystemService::GetNetIOSystem() : *m_NetIOSystem; }
		
		virtual WriteBufferQueue* GetWriteBufferQueue() override;


		///////////////////////////////////////////////////////////////////////////////
		// Socket handling 

		virtual Result SetupCommonSocketOptions(SockType sockType, SockFamily sockFamily, SF_SOCKET socket) override;

		virtual Result RegisterSocket(SocketIO* cbInstance) override;
		virtual Result UnregisterSocket(SocketIO* cbInstance) override;
		//Result RegisterSharedSocket(SockType sockType, SocketIO* cbInstance) override;

		virtual SF_SOCKET Socket(SockFamily domain, SockType type) override;
		virtual void CloseSocket(SF_SOCKET sock) override;

		virtual Result Accept(SF_SOCKET sockListen, IOBUFFER_ACCEPT* pAccept) override;
		virtual Result HandleAcceptedSocket(SF_SOCKET sockListen, IOBUFFER_ACCEPT* pAccept, sockaddr_storage& remoteAddr) override;

		virtual Result Recv(SF_SOCKET sock, IOBUFFER_READ* pBuffer) override;
		virtual Result RecvFrom(SF_SOCKET sock, IOBUFFER_READ* pBuffer) override;

		virtual Result Send(SF_SOCKET sock, IOBUFFER_WRITE* pBuffer) override;
		virtual Result SendTo(SF_SOCKET sock, IOBUFFER_WRITE* pBuffer) override;
	};




} // namespace Net
} // namespace SF

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
#include "Net/SFNetSystem_WinIOCP.h"
#else
#include "Net/SFNetSystem_Linux.h"
#endif


