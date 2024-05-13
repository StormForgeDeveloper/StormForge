////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server constants definitions. 
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Component/SFLibraryComponent.h"
#include "Object/SFSharedPointer.h"
#include "Util/SFLog.h"
#include "IO/SFFile.h"
#include "Util/SFString.h"
#include "Online/Websocket/SFWebsocketClientCurl.h"
#include "flatbuffers/base.h"
#include "flatbuffers/flatbuffer_builder.h"

namespace SF {



    namespace Log
    {
        extern LogChannel OutputLogServer;
    }

	class LogOutputLogServerComponent : public LibraryComponent
	{
	private:

		class MyOutputHandler : public Log::LogOutputHandler
		{
		public:

			static constexpr size_t BinHeaderSize = 8;
			static constexpr size_t BufferSize = 16 * 1024;
			static constexpr size_t CompressionBufferSize = size_t(BufferSize * 1.5);


		private:
			//SharedPointerT<StreamDBProducer> m_StreamProducer;

			// It is running on log thread, we don't need double buffering 
			// Moreover, StreamProducer creates a copy of data for transmit
			DynamicArray<uint8_t> m_Buffer;

			DynamicArray<uint8_t> m_CompressionBuffer;

            WebsocketClientCurl m_Client;

            String m_ChannelName;

            ::flatbuffers::FlatBufferBuilder m_Builder;

		public:
			MyOutputHandler()
                : LogOutputHandler("OutputLogServer")
                , m_Client(GetSystemHeap())
                , m_Builder(4096)
            {
            }

			void Init(IHeap& heap, const String& logServer);
			void Deinit();

			virtual void PrintOutput(const Log::LogItem* logMessage) override;
			virtual void Flush() override;

            Result OnRecv(const Array<uint8_t>& recvData);
		};


	public:

		static const StringCrc64 TypeName;

		LogOutputLogServerComponent(const String& logServerAddress);
		~LogOutputLogServerComponent();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		MyOutputHandler& GetHandler() { return m_Handler; }

		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;

	private:

		MyOutputHandler m_Handler;

		String m_LogServerAddress;
	};

}

