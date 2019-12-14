////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject manager
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "Container/SFHashTable2.h"
#include "Object/SFSharedPointer.h"
#include "String/SFFixedStringDB.h"
#include "Net/SFNetDef.h"
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
		class ServerNet;
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////
	//
	//	ConnectionManager service
	//

	class ConnectionManagerService
	{
	public:
		////////////////////////////////////////////////////////////////////////////////
		//
		//	Address to connection map
		//

		class Sockaddress : public sockaddr_storage
		{
		public:
			Sockaddress() = default;
			Sockaddress(const Sockaddress& src) = default;
			Sockaddress(const sockaddr_storage& src);
			~Sockaddress() = default;

			Sockaddress& operator =(const Sockaddress& src) = default;

			bool operator >(const Sockaddress& src);
			bool operator ==(const Sockaddress& src);
			bool operator !=(const Sockaddress& src);

			//operator const sockaddr_storage& () { return *this; }
		};

		//////////////////////////////////////////////////////////////////
		// Hash definition
		typedef HashTable2< Sockaddress, SharedPointerT<Net::Connection>, UniqueKeyTrait, ThreadSyncTraitReadWriteT<Sockaddress, SharedPointerT<Net::Connection>>, hash < sockaddr_storage >
		> AddrMap;


		typedef HashTable2<	uint64_t, SharedPointerT<Net::Connection>
		> CIDMap;


		typedef HashTable2<	uint64_t, SharedPointerT<Net::Connection>
		> PeerIDMap;

		// Connection set
		//typedef DualSortedMap<uint64_t, SharedPointerT<Net::Connection>>	ConnectionSet;



	public:

		virtual uint NewCID() { return 0; }
		virtual void FreeCID(uint uiCID) { unused(uiCID); }

		virtual IHeap& GetHeap() { return GetSystemHeap(); }

		// Active connection
		virtual CounterType GetNumActiveConnection() { return 0; }


		virtual void AddConnection(SharedPointerT<Net::Connection>& pConn) { }

		virtual void NewMUDPAddress(IHeap& memMgr, Net::ServerNet* pNet, SF_SOCKET socket, const Net::PeerInfo& local, const Net::PeerInfo& remote) {};
		virtual void NewUDPAddress(IHeap& memMgr, Net::ServerNet* pNet, SF_SOCKET socket, const Net::PeerInfo& local, const Net::PeerInfo& remote) {};

		// Free connection directly
		virtual EngineTaskPtr RemoveConnection(SharedPointerT<Net::Connection>& pConn) { return EngineTaskPtr(); }

		virtual void AddressRemap(SharedPointerT<Net::Connection>& pConn, const sockaddr_storage &addressOrg, const sockaddr_storage &newAddress) { return; }

		// Remap PeerID
		virtual void RemapPeerID(SharedPointerT<Net::Connection>& pConn, uint64_t ticket) { return ; }

		// Disconnect all connection
		virtual Result DisconnectAllConnection() { return ResultCode::SUCCESS_FALSE; }



		// Find and return connection
		virtual Result GetConnectionByAddr(const sockaddr_storage& sockAddr, SharedPointerT<Net::Connection> &pFound) { return ResultCode::FAIL; }
		virtual Result GetConnectionByCID(uint64_t uiCID, SharedPointerT<Net::Connection> &pConn) { return ResultCode::FAIL; }
		virtual Result GetConnectionByPeerID(uint64_t peerID, SharedPointerT<Net::Connection> &pConn) { return ResultCode::FAIL; }

	};

	

}; // namespace SF

