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
#include "String/SFStringCrc64.h"
#include "String/SFStringFormat.h"
#include "Service/SFService.h"
#include "Variable/SFVariableBoxing.h"


namespace SF {


	constexpr StringCrc64 LogOutputLogServerComponent::TypeName;




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

	void LogOutputLogServerComponent::MyOutputHandler::PrintOutput(const Log::LogModule::LogItem* logMessage)
	{
		if (logMessage == nullptr || m_StreamProducer == nullptr) return;

		ArrayView<uint8_t> dataArray(logMessage->LogStringSize, reinterpret_cast<const uint8_t*>(logMessage->LogBuff));
		m_StreamProducer->SendRecord(dataArray /*, logMessage->TimeStamp.time_since_epoch().count()*/);
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


