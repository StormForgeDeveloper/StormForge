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
#include "Stream/SFCompressedStream.h"


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

		m_Buffer.reserve(BufferSize);
		m_CompressionBuffer.resize(CompressionBufferSize);

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

		if (dataArray.size() >= (BufferSize - BinHeaderSize))
			dataArray.resize(BufferSize - BinHeaderSize - 1);

		auto remainSizeInBuffer = m_Buffer.capacity() - m_Buffer.size();
		if (remainSizeInBuffer < dataArray.size())
		{
			Flush();
		}

		m_Buffer.Append(dataArray);
		m_Buffer.push_back('\0'); // null terminate
	}

	void LogOutputLogServerComponent::MyOutputHandler::Flush()
	{
		m_CompressionBuffer.Reset();
		OutputMemoryStream memoryStream(m_CompressionBuffer);

		// write header
		const uint8_t Signature[] = { 'S', 'F', 'B', 0 };
		uint32_t compressedSize = 0;
		memoryStream.Write(Signature, countof(Signature));

		auto compressedSizePos = m_CompressionBuffer.size();
		memoryStream.Write(&compressedSize, sizeof(compressedSize));

		// Compress data
		auto compressedDataPos = m_CompressionBuffer.size();
		CompressedOutputStream compressedStream(GetSystemHeap(), memoryStream);
		compressedStream.Write(m_Buffer.data(), m_Buffer.size());

		compressedStream.Flush();
		compressedStream.Close();

		compressedSize = static_cast<uint32_t>(m_CompressionBuffer.size() - compressedDataPos);

		// update compressed size in header area
		memcpy(m_CompressionBuffer.data() + compressedSizePos, &compressedSize, sizeof(compressedSize));

		m_StreamProducer->SendRecord(ArrayView<const uint8_t>(m_CompressionBuffer.size(), m_CompressionBuffer.data()));
		m_Buffer.Reset();
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


