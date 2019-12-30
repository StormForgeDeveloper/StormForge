////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Public Interfaces
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 





namespace SF {


	enum class RelayNetworkState : uint16_t
	{
		None,
		Initialized,
		Connecting,
		Connected,
		Disconnecting,
		Disconnected,
	};


}; // namespace SF

