﻿////////////////////////////////////////////////////////////////////////////////
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
#include "ResultCode/SFResultCodeLibrary.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeEngineComponent.h"



namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Module
	//

	constexpr StringCrc64 LibraryComponentEngineResultCode::TypeName;

	LibraryComponentEngineResultCode::LibraryComponentEngineResultCode()
		: LibraryComponent(TypeName)
	{

	}

	LibraryComponentEngineResultCode::~LibraryComponentEngineResultCode()
	{
	}

	// Initialize server component
	Result LibraryComponentEngineResultCode::InitializeComponent()
	{
		Result hr = LibraryComponent::InitializeComponent();
		if (!hr) return hr;

		ResultCode::InitializeResultCodeSystem();
		ResultCode::InitializeResultCodeSF();
		ResultCode::InitializeResultCodeEngine();

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void LibraryComponentEngineResultCode::DeinitializeComponent()
	{
		LibraryComponent::DeinitializeComponent();
	}



}//namespace SF 



