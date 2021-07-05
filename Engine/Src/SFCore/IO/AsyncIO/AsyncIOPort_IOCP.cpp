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


#include "SFCorePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOPortWriteBufferQueue.h"
#include "IO/AsyncIO/AsyncIOAdapter.h"
#include "IO/AsyncIO/AsyncIOPort_IOCP.h"
#include "IO/AsyncIO/AsyncIOPortSystemImpl.h"

#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "Container/SFSpinSharedBuffer.h"
#include "MemoryManager/SFMemoryPool.h"
#include "MemoryManager/SFMemory.h"
#include "MemoryManager/SFMemoryManager.h"
#include "Util/SFToString.h"


#if SF_PLATFORM == SF_PLATFORM_WINDOWS



namespace SF {
namespace AsyncIO {




	////////////////////////////////////////////////////////////////////////////////
	//
	//	Overlapped I/O structures
	//


	// Clear Buffer
	void IOBUFFER_IOCP::ClearBuffer()
	{
		if( hEvent != WSA_INVALID_EVENT )
			WSACloseEvent( hEvent );
		hEvent = WSA_INVALID_EVENT;
	}








	////////////////////////////////////////////////////////////////////////////////
	//
	//	IOCP thread worker
	//


	void IOCPWorker::Run()
	{
		Result hr = ResultCode::SUCCESS;
		BOOL bResult;
		DWORD dwTransferred = 0;
		IOBUFFER *pOverlapped = nullptr;
		OVERLAPPED *pOverlappedSys = nullptr;
		ULONG_PTR ulKey = 0;
		int iErr = 0;
		int iLastError;
		auto hIOCP = GetOwner()->GetNativeIOSystemHandle();

		while (!CheckKillEvent(DurationMS(0)))
		{
			dwTransferred = 0;
			pOverlapped = nullptr;
			pOverlappedSys = nullptr;
			ulKey = 0;
			iErr = 0;
			iLastError = 0;
			hr = ResultCode::SUCCESS;

			// Getting IOCP status
			bResult = GetQueuedCompletionStatus(hIOCP, &dwTransferred, (PULONG_PTR)&ulKey, &pOverlappedSys, INFINITE);
			pOverlapped = (IOBUFFER*)pOverlappedSys;

			// If End of IOCP signaled
			if (pOverlappedSys == nullptr || pOverlapped == nullptr)
			{
				// Release
				if (ulKey != 0)
				{
					AsyncIOAdapter *pCallback = (AsyncIOAdapter*)ulKey;
					assert(pCallback->GetPendingReadCount() == 0 && pCallback->GetPendingWriteCount() == 0);
					pCallback->OnIOUnregistered();
				}
				continue;
			}


			// Error mapping
			if (!bResult)
			{
				iLastError = GetLastError();
				hr = HRESULT_FROM_WIN32(iLastError);

				switch (iLastError)
				{
				case WSAECONNRESET:
				case WSAENOTSOCK:
				case ERROR_CONNECTION_ABORTED:
				case ERROR_HOST_UNREACHABLE:
				case ERROR_PROTOCOL_UNREACHABLE:
				case ERROR_PORT_UNREACHABLE:
				case ERROR_NETNAME_DELETED:
					hr = ResultCode::IO_CONNECTION_CLOSED;
					break;
				case ERROR_OPERATION_ABORTED:
					SFLog(Net, Info, "IOCP Operation aborted");
					hr = ResultCode::IO_IO_ABORTED;
					break;
				default:
					SFLog(System, Error, "IOCP Operation failed iErr={0}, hr={1:X8}", iLastError, hr);
					break;
				};
			}

			// Operation
			IOBUFFER *pIOBuffer = (IOBUFFER*)pOverlapped;
			AsyncIOAdapter *pCallback = (AsyncIOAdapter*)ulKey;
			switch (pOverlapped->Operation)
			{
			case IOBUFFER_OPERATION::OP_TCPACCEPT:
			{
				hr = pCallback->OnIOReadCompleted(hr, (IOBUFFER_READ*)pIOBuffer);
			}
			break;
			case IOBUFFER_OPERATION::OP_WRITE:
			case IOBUFFER_OPERATION::OP_TCPWRITE:
			case IOBUFFER_OPERATION::OP_UDPWRITE:
			{
				hr = pCallback->OnIOWriteCompleted(hr, (IOBUFFER_WRITE*)pIOBuffer);
			}
			break;
			case IOBUFFER_OPERATION::OP_READ:
			case IOBUFFER_OPERATION::OP_TCPREAD:
			case IOBUFFER_OPERATION::OP_UDPREAD:
				if (ulKey) // TCP operation
				{
					pIOBuffer->OperationSize = dwTransferred;
					hr = pCallback->OnIOReadCompleted(hr, (IOBUFFER_READ*)pIOBuffer);
					pIOBuffer = nullptr;
					pOverlapped = nullptr;
				}
				else
				{
					AssertRel(!"Invalid Key at IOCP");
				}
				break;
			default:
				SFLog(System, Error, "IOCP Invalid Overlapped Operation");
				break;
			};


		} // while(1)

	}




		//////////////////////////////////////////////////////////////////
		//
		//	network IOCP System
		//

	


		IOCPSystem::IOCPSystem(IHeap& memMgr)
			: AsyncIOPortSystem_Impl(memMgr)
		{
		}

		IOCPSystem::~IOCPSystem()
		{
		}

		// Initialize IOCP
		Result IOCPSystem::Initialize( uint uiNumIOCPThread )
		{
			Result hr = ResultCode::SUCCESS;


			m_RefCount.fetch_add(1, std::memory_order_relaxed);

			if( GetNativeIOSystemHandle() != INVALID_NATIVE_HANDLE_VALUE )
			{
				return ResultCode::SUCCESS;// already initialized
			}

			WSADATA wsaData;
			int iErr = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iErr != 0)
			{
				SFLog(Net, Error, "Can't Initialize Winsock DLL err={0}", iErr);
				return iErr;
			}


			SYSTEM_INFO sysInfo;
			memset( &sysInfo, 0, sizeof(sysInfo) );
			GetSystemInfo( &sysInfo );

			// Correct if Incorrect thread count specified
			if( uiNumIOCPThread < 1 ) uiNumIOCPThread = 1;
			if( uiNumIOCPThread > (sysInfo.dwNumberOfProcessors*2) ) uiNumIOCPThread = sysInfo.dwNumberOfProcessors*2;


			// Create IOCP port
			auto nativeIOHandle = CreateIoCompletionPort( INVALID_NATIVE_HANDLE_VALUE, NULL, 0, 0 );
			if (nativeIOHandle == INVALID_NATIVE_HANDLE_VALUE)
			{
				auto result = GetLastResultCode();
				SFLog(System, Info, "IOCP system failed to initialize", result);
				Terminate();
				return result;
			}

			SetNativeIOSystemHandle(nativeIOHandle);

			for( uint iThread = 0; iThread < uiNumIOCPThread; iThread++ )
			{
				auto pWorker = new(GetHeap()) IOCPWorker(this, iThread);
				pWorker->Start();
				AddIOWorker(pWorker);
			}

			SFLog(System, Info, "IOCP system started" );

			return hr;
		}

		// Close IOCP
		void IOCPSystem::Terminate()
		{
			Result hr = ResultCode::SUCCESS;

			CounterType lCount = m_RefCount.fetch_sub(1, std::memory_order_relaxed) - 1;

			if( lCount > 0 )
				return;

			AsyncIOPortSystem_Impl::Terminate();


		Proc_End:

			CloseSystemHandle();

			SFLog(System, Info, "IOCP system closed" );

			return;
		}

		void IOCPSystem::CloseSystemHandle()
		{
			if (GetNativeIOSystemHandle() != INVALID_NATIVE_HANDLE_VALUE)
			{
				// Send IOCP close signal
				if (!PostQueuedCompletionStatus(GetNativeIOSystemHandle(), 0, 0, NULL))
				{
					auto result = GetLastResultCode();
					SFLog(Net, Info, "IOCP system failed to terminate", result);
				}

				CloseHandle(GetNativeIOSystemHandle());
			}

			AsyncIOPortSystem_Impl::CloseSystemHandle();
		}
		




	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network system
	//


	Result AsyncIOPortSystem::RegisterIO(AsyncIOAdapter* cbInstance)
	{
		Result hr = ResultCode::SUCCESS;

		if (!CreateIoCompletionPort((HANDLE)cbInstance->GetIOHandle(), m_Impl->GetNativeIOSystemHandle(), (ULONG_PTR)cbInstance, 0))
		{
			hr = GetLastResultCode();
			SFLog(Net, Error, "Registering socket to IOCP is Failed, hr = {0:X8}", hr);
			return ResultCode::UNEXPECTED;
		}

		cbInstance->OnIORegistered();

		return hr;
	}

	Result AsyncIOPortSystem::UnregisterIO(AsyncIOAdapter* cbInstance)
	{
		Result hr = ResultCode::SUCCESS;

		// This doesn't help actually while a running thread still working on this instance
		// Closing handle will remove it anyway
		//if (!PostQueuedCompletionStatus(GetNetIOSystem().GetNativeIOSystemHandle(), 0, (ULONG_PTR)cbInstance, 0))
		//{
		//	hr = GetLastResultCode();
		//	SFLog(Net, Error, "Registering socket to IOCP is Failed, hr = {0:X8}", hr);
		//	netErr(ResultCode::UNEXPECTED);
		//}

		// Just mark as unregistered
		cbInstance->OnIOUnregistered();

	Proc_End:

		return hr;
	}




} // namespace AsyncIO
} // namespace SF


#else
void Dummp_AsyncIO_IOCP() {}
#endif // SF_PLATFORM == SF_PLATFORM_WINDOWS
