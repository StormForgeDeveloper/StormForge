////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : String crc initializer
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFStringCrcComponent.h"
#include "Service/SFService.h"
#include "IO/SFFileInputStream.h"


namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Module
	//

	constexpr StringCrc64 StringCrcLibraryComponent::TypeName;

	StringCrcLibraryComponent::StringCrcLibraryComponent()
		: LibraryComponent(TypeName)
	{

	}

	StringCrcLibraryComponent::~StringCrcLibraryComponent()
	{
	}

	// Initialize server component
	Result StringCrcLibraryComponent::InitializeComponent()
	{
		Result hr = LibraryComponent::InitializeComponent();
		if (!hr) return hr;

		const char* inputPaths[] = {
			"string_list.crcbin",
			"Contents/string_list.crcbin",
		};

		for (auto inputPath : inputPaths)
		{
			FileInputStream readFrom;
			if (!readFrom.Open(inputPath))
				continue;

			SFLog(System, Info, "Loading string crc table! {0}", inputPath);

			auto res = Service::StringDB->LoadStringTable(readFrom);
			if (!res)
			{
				SFLog(System, Error, "Failed to load string crc table! {0}, res:{1}", inputPath, res);
			}
		}

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void StringCrcLibraryComponent::DeinitializeComponent()
	{
		LibraryComponent::DeinitializeComponent();
	}


}//namespace SF 

