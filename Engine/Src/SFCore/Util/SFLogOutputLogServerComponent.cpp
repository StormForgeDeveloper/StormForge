////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base type ToString implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFLogOutputLogServerComponent.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "IO/SFFileUtil.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFStringFormat.h"
#include "Service/SFService.h"
#include "Variable/SFVariableBoxing.h"


namespace SF {


	const StringCrc64 LogOutputLogServerComponent::TypeName = Hash64("LogOutputLogServerComponent");




	LogOutputLogServerComponent::LogOutputLogServerComponent(const LogOutputMask& logMask, const String& logServerAddress)
		: LibraryComponent(StringCrc64("LogServerOutput"))
		, m_Handler(logMask)
		, m_LogServerAddress(logServerAddress)
	{
	}

	LogOutputLogServerComponent::~LogOutputLogServerComponent()
	{

	}

	void LogOutputLogServerComponent::MyOutputHandler::Init(IHeap& heap, const String& logServer)
	{
		if (logServer.IsNullOrEmpty())
			return;

		m_StreamProducer = new(heap) StreamDBProducer();

		m_StreamProducer->Initialize(logServer, Util::GetServiceName());
	}

	void LogOutputLogServerComponent::MyOutputHandler::Deinit()
	{
		if (m_StreamProducer != nullptr)
		{
			m_StreamProducer->Flush();
			m_StreamProducer = nullptr;
		}
	}

	void LogOutputLogServerComponent::MyOutputHandler::PrintOutput(const Log::LogItem* logMessage)
	{
		if (logMessage == nullptr || m_StreamProducer == nullptr || logMessage->LogStringSize < 1) return;

		// -1 for removing \n
		ArrayView<const uint8_t> dataArray(logMessage->LogStringSize - 1, reinterpret_cast<const uint8_t*>(logMessage->LogBuff));
		m_StreamProducer->SendRecord(dataArray);
	}

	// Initialize server component
	Result LogOutputLogServerComponent::InitializeComponent()
	{
		m_Handler.Init(GetEngineHeap(), m_LogServerAddress);

		Service::LogModule->RegisterOutputHandler(&m_Handler);

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void LogOutputLogServerComponent::DeinitializeComponent()
	{
		Service::LogModule->UnregisterOutputHandler(&m_Handler);

		m_Handler.Deinit();
	}






}	// namespace SF


