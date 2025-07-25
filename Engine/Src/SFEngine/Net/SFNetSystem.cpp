////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Net base type definitions. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "MemoryManager/SFMemoryManager.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetSystem_EPOLL.h"
#include "Net/SFNetSystem_KQUEUE.h"
#include "Net/SFNetSystem_WinIOCP.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Multithread/SFThread.h"
#include "Util/SFUtility.h"
#include "Container/SFSpinSharedBuffer.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Service/SFEngineService.h"



namespace SF {
	
	NetSystemService::NetIOSystem NetSystemService::m_DefaultNetIOSystem;

	
namespace Net {




	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	NetSystem
	//
	const StringCrc64 NetSystem::TypeName = "NetSystem"_crc64;


	NetSystem::NetSystem(uint recvBufferSize, uint sendBufferSize, uint numThread, uint gatheringBufferSize)
		: LibraryComponent("NetSystem")
		, m_NumThread(numThread)
		, m_GatheringBufferSize(gatheringBufferSize)
		, m_RecvBufferSize(recvBufferSize)
		, m_SendBufferSize(sendBufferSize)
		, m_NetIOSystem(nullptr)
	{
#if KQUEUE
		m_NetIOSystem = new  KQUEUESystem;
#elif EPOLL
		m_NetIOSystem = new  EPOLLSystem;
#else
		m_NetIOSystem = new  IOCPSystem::IOCPSystem;
#endif
	}

	NetSystem::~NetSystem()
	{
		if (m_NetIOSystem != nullptr) delete (m_NetIOSystem);
		m_NetIOSystem = nullptr;
	}

	// Initialize component
	Result NetSystem::InitializeComponent()
	{
		LibraryComponent::InitializeComponent();
		
		Service::NetSystem = this;
        m_pGatheringBufferPool = new MemoryPool(GetSystemHeap(), m_GatheringBufferSize);

		if (m_NetIOSystem != nullptr) 
			m_NetIOSystem->Initialize(m_NumThread);
		
		return ResultCode::SUCCESS;
	}

	// Terminate component
	void NetSystem::DeinitializeComponent()
	{
		LibraryComponent::DeinitializeComponent();

		Service::NetSystem = nullptr;
		//m_pGatheringBufferPool = nullptr;
		
		if (m_NetIOSystem != nullptr) 
			m_NetIOSystem->Terminate();

	}

    Net::IOBUFFER_WRITE* NetSystem::AllocateWriteBuffer()
    {
        IOBUFFER_WRITE* pWriteBuffer = new IOBUFFER_WRITE;
        return pWriteBuffer;
    }

} // namespace Net
} // namespace SF

