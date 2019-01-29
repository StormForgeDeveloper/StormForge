////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Async IO
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "Memory/SFMemoryManager.h"
#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOPort_EPOLL.h"
#include "IO/AsyncIO/AsyncIOPort_KQUEUE.h"
#include "IO/AsyncIO/AsyncIOPort_IOCP.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Container/SFSpinSharedBuffer.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Thread/SFThread.h"
#include "Util/SFUtility.h"
#include "Memory/SFMemoryPool.h"



namespace SF {
	namespace AsyncIO {




		////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	AsyncIOPortSystem
		//

		constexpr FixedString AsyncIOPortSystem::TypeName;


		AsyncIOPortSystem::AsyncIOPortSystem(uint numThread)
			: LibraryComponent("AsyncIOPortSystem")
			, m_NumThread(numThread)
			, m_Heap("Net", GetSystemHeap())
			, m_Impl(nullptr)
		{
#if KQUEUE
			m_Impl = new(GetHeap())  KQUEUESystem(GetHeap());
#elif EPOLL
			m_Impl = new(GetHeap())  EPOLLSystem(GetHeap());
#else
			m_Impl = new(GetHeap())  IOCPSystem(GetHeap());
#endif
		}

		AsyncIOPortSystem::~AsyncIOPortSystem()
		{
			if (m_Impl != nullptr) IHeap::Delete(m_Impl);
			m_Impl = nullptr;
		}

		// Initialize component
		Result AsyncIOPortSystem::InitializeComponent()
		{
			LibraryComponent::InitializeComponent();

			Service::AsyncIOPort = this;

			if (m_Impl != nullptr)
				m_Impl->Initialize(m_NumThread);

			return ResultCode::SUCCESS;
		}

		// Terminate component
		void AsyncIOPortSystem::DeinitializeComponent()
		{
			LibraryComponent::DeinitializeComponent();

			Service::AsyncIOPort = nullptr;

			if (m_Impl != nullptr)
				m_Impl->Terminate();

		}


	} // namespace AsyncIO
} // namespace SF

