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
#include "flatbuffers/base.h"
#include "SFProtocolHelper.h"
#include "MessageBus/SFMessageHeader.h"
#include "Protocol/GenericMessageID.h"
#include "Protocol/Generic_generated.h"

namespace SF {


    namespace Log
    {
        LogChannel OutputLogServer("OutputLogServer", LogOutputType::Max);
    }

	const StringCrc64 LogOutputLogServerComponent::TypeName = Hash64("LogOutputLogServerComponent");

	LogOutputLogServerComponent::LogOutputLogServerComponent(const String& logServerAddress)
		: LibraryComponent(StringCrc64("LogServerOutput"))
		, m_Handler()
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

        SFLog(System, Info, "Log server:{0}, channel:{1}", logServer, Util::GetServiceName());

        // TODO: hard coded accesskey, need to get from client or server config system
        m_Client.AddParameter("AccessKey", "B0B1F3DC-FC87-41EA-8FC2-E0BEDC7E1FDB");
        m_Client.SetReconnectOnDisconnected(true);

        m_Client.Initialize(logServer, "SFGateway");

        m_ChannelName.Format("{0}-{1}", Util::GetTitleEnv(), Util::GetServiceName());
	}

	void LogOutputLogServerComponent::MyOutputHandler::Deinit()
	{
        m_Client.CloseConnection();
	}

	void LogOutputLogServerComponent::MyOutputHandler::PrintOutput(const Log::LogItem* logMessage)
	{
		if (logMessage == nullptr || logMessage->LogStringSize < 1) return;

		// keep \n at the end of string 
		ArrayView<const uint8_t> dataArray(logMessage->LogStringSize, reinterpret_cast<const uint8_t*>(logMessage->LogBuff));

		if (dataArray.size() >= (BufferSize - BinHeaderSize))
			dataArray.resize(BufferSize - BinHeaderSize - 1);

		auto remainSizeInBuffer = m_Buffer.capacity() - m_Buffer.size();
		if (remainSizeInBuffer < dataArray.size())
		{
			Flush();
		}

		m_Buffer.Append(dataArray);
	}

	void LogOutputLogServerComponent::MyOutputHandler::Flush()
	{
        if (!m_Client.IsConnected())
            return;

        if (m_Buffer.size() == 0)
			return;

		m_CompressionBuffer.Reset();
		OutputMemoryStream memoryStream(m_CompressionBuffer);

		// write header
		const uint8_t Signature[] = { 'S', 'F', 'C', 0 };
		uint32_t uncompressedSize = static_cast<uint32_t>(m_Buffer.size());
		memoryStream.Write(Signature, countof(Signature));

		//auto uncompressedSizePos = m_CompressionBuffer.size();
		memoryStream.Write(&uncompressedSize, sizeof(uncompressedSize));

		// Compress data
		CompressedOutputStream compressedStream(GetSystemHeap(), memoryStream);
		compressedStream.Write(m_Buffer.data(), m_Buffer.size());

		compressedStream.Flush();
		compressedStream.Close();

        
        m_Builder.Clear();

        auto dataOffset = m_Builder.CreateVector(m_CompressionBuffer.data(), m_CompressionBuffer.size());
       
        ::flatbuffers::Offset<SF::Flat::Generic::PostLogDataCmd> payloadOffset = SF::Flat::Generic::CreatePostLogDataCmd(m_Builder,
            m_Builder.CreateString(m_ChannelName), dataOffset
        );

        m_Builder.Finish(payloadOffset);

        MessageHeader2 packetHeader;
        packetHeader.TransactionId = TransactionID();
        packetHeader.MessageId = Message::Generic::MID_PostLogDataCmd;
        Result resultPH;
        packetHeader.UpdateNWriteTo(m_Builder, resultPH);

        ArrayView<uint8_t> sendBuffer(m_Builder.GetSize(), (uint8_t*)m_Builder.GetBufferPointer());

        SFLog(System, Debug4, "Send log size:{0}", m_Builder.GetSize());

        m_Client.Send(sendBuffer);

		m_Buffer.Reset();
	}

	// Initialize server component
	Result LogOutputLogServerComponent::InitializeComponent()
	{
        m_LogServerAddress.ReplaceInline("{TitleUID}", Util::GetTitleUID().ToString().c_str());

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


