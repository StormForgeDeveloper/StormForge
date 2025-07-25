////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : net system service
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "Container/SFHashTable2.h"
#include "Object/SFSharedPointer.h"
#include "Util/SFStringCrcDB.h"
#include "Task/SFTask.h"



namespace SF {

	namespace Net
	{
		class WriteBufferQueue;
		class SocketIO;
		struct IOBUFFER_ACCEPT;
		struct IOBUFFER_READ;
		struct IOBUFFER_WRITE;
		class Connection;
		}

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network system
	//

	class NetSystemService
	{
	public:
		
		////////////////////////////////////////////////////////////////////////////////
		//
		//	Network IO sub system interface
		//
	
		class NetIOSystem
		{
		private:

			NativeHandle m_IOSystemHandle;

		protected:

			void SetNativeIOSystemHandle(NativeHandle handle) { m_IOSystemHandle = handle; }

		public:
			NetIOSystem()
				: m_IOSystemHandle(INVALID_NATIVE_HANDLE_VALUE)
			{
			}

			virtual ~NetIOSystem()
			{
			}

			NativeHandle GetNativeIOSystemHandle() { return m_IOSystemHandle; }
		
			virtual Result Initialize(uint netThreadCount) { return ResultCode::SUCCESS; }
			virtual void Terminate() {}

			virtual Result MakeSocketNonBlocking(SF_SOCKET sfd) { return ResultCode::FAIL; }
			//virtual Net::WriteBufferQueue* GetWriteBufferQueue() { return nullptr; }

								// Register the socket to KQUEUE
			virtual Result RegisterToNETIO(Net::SocketIO* cbInstance) { return ResultCode::FAIL; }
			virtual Result UnregisterFromNETIO(Net::SocketIO* cbInstance) { return ResultCode::FAIL; }
			
			virtual const char* EventFlagToString(int32_t bufferSize, char* stringBuffer, uint32_t eventFlags) { return ""; }
		};
		
	private:
		
		static NetIOSystem m_DefaultNetIOSystem;

	public:

		virtual NetIOSystem& GetNetIOSystem() { return m_DefaultNetIOSystem; }

		virtual Net::WriteBufferQueue* GetWriteBufferQueue() { return nullptr; }
        virtual Net::IOBUFFER_WRITE* AllocateWriteBuffer() { return nullptr; }
        virtual size_t GetWriteBufferSize() { return 0; }

		///////////////////////////////////////////////////////////////////////////////
		// Socket handling 

		virtual Result SetupCommonSocketOptions(SocketType sockType, SockFamily sockFamily, SF_SOCKET socket, bool acceptedSocket = false) { unused(sockType, socket); return ResultCode::SUCCESS_FALSE; }

		virtual Result RegisterSocket(Net::SocketIO* cbInstance) { unused(cbInstance); return ResultCode::SUCCESS_FALSE; }
		virtual Result UnregisterSocket(Net::SocketIO* cbInstance) { unused(cbInstance); return ResultCode::SUCCESS_FALSE; }
		//Result RegisterSharedSocket(SocketType sockType, SocketIO* cbInstance);

		virtual SF_SOCKET Socket(SockFamily domain, SocketType type) { return INVALID_SOCKET; }
		virtual void CloseSocket(SF_SOCKET sock) { unused(sock); }

		virtual Result Accept(SF_SOCKET sockListen, Net::IOBUFFER_ACCEPT* pAccept) { unused(sockListen, pAccept); return ResultCode::SUCCESS_FALSE; }
		virtual Result HandleAcceptedSocket(SF_SOCKET sockListen, Net::IOBUFFER_ACCEPT* pAccept, sockaddr_storage& remoteAddr) { unused(sockListen, pAccept, remoteAddr); return ResultCode::SUCCESS_FALSE; }

		virtual Result Recv(Net::SocketIO* sock, Net::IOBUFFER_READ* pBuffer) { unused(sock, pBuffer); return ResultCode::SUCCESS_FALSE; }
		virtual Result RecvFrom(Net::SocketIO* sock, Net::IOBUFFER_READ* pBuffer) { unused(sock, pBuffer); return ResultCode::SUCCESS_FALSE; }

		virtual Result Send(Net::SocketIO* sock, Net::IOBUFFER_WRITE* pBuffer) { unused(sock, pBuffer); return ResultCode::SUCCESS_FALSE; }
		virtual Result SendTo(Net::SocketIO* sock, Net::IOBUFFER_WRITE* pBuffer) { unused(sock, pBuffer); return ResultCode::SUCCESS_FALSE; }
	};


}; // namespace SF

