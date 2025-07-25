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

	StringCrcLibraryComponent::StringCrcLibraryComponent(const char* stringCrcBinPath)
		: LibraryComponent(TypeName)
		, m_StringCrcBinPath(stringCrcBinPath)
	{

	}

	StringCrcLibraryComponent::~StringCrcLibraryComponent()
	{
	}

	// Initialize server component
	Result StringCrcLibraryComponent::InitializeComponent()
	{
		Result hr = LibraryComponent::InitializeComponent();
		if (!hr.IsSuccess()) return hr;

		const char* inputPaths[] = {
			m_StringCrcBinPath.data(),
			"string_list.crcbin",
		};

		for (auto inputPath : inputPaths)
		{
			if (StrUtil::IsNullOrEmpty(inputPath))
				continue;

			FileInputStream readFrom;
            if (!readFrom.Open(inputPath))
            {
                SFLog(System, Info, "String crc table file doesn't exist! '{0}'", inputPath);
                continue;
            }

			SFLog(System, Info, "Loading string crc table! {0}", inputPath);

			auto res = Service::StringDB->LoadStringTable(readFrom);
			if (!res)
			{
				SFLog(System, Error, "Failed to load string crc table! {0}, res:{1}", inputPath, res);
			}
		}

        // Some must have strings
        Service::StringDB->AddString("static");
        Service::StringDB->AddString("ugc");
        Service::StringDB->AddString("dynamic");
        Service::StringDB->AddString("zone");
        Service::StringDB->AddString("zoneinstance");

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void StringCrcLibraryComponent::DeinitializeComponent()
	{
		LibraryComponent::DeinitializeComponent();
	}


}//namespace SF 

