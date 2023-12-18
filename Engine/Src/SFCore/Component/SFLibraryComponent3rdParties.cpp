////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated header, Engine
//
////////////////////////////////////////////////////////////////////////////////


#include "SFTypedefs.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Component/SFLibraryComponent3rdParties.h"
#include "openssl/evp.h"
#include "curl/curl.h"

namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Module
	//

	constexpr StringCrc64 LibraryComponent3rdParties::TypeName;

	LibraryComponent3rdParties::LibraryComponent3rdParties()
		: LibraryComponent(TypeName)
	{

	}

	LibraryComponent3rdParties::~LibraryComponent3rdParties()
	{
	}

	// Initialize server component
	Result LibraryComponent3rdParties::InitializeComponent()
	{
		Result hr = LibraryComponent::InitializeComponent();
		if (!hr) return hr;

        OpenSSL_add_all_algorithms();
        OpenSSL_add_all_digests();

        curl_global_init(CURL_GLOBAL_ALL);

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void LibraryComponent3rdParties::DeinitializeComponent()
	{
        curl_global_cleanup();

		LibraryComponent::DeinitializeComponent();
	}



}//namespace SF 



