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
#include "StreamDB/SFStreamDB.h"



namespace SF {



	class LogOutputLogServerComponent : public LibraryComponent
	{
	private:

		class MyOutputHandler : public Log::LogOutputHandler
		{
		private:
			SharedPointerT<StreamDBProducer> m_StreamProducer;


		public:
			MyOutputHandler(const LogOutputMask& logMask) : LogOutputHandler(logMask) {}

			void Init(IHeap& heap, const String& logServer);
			void Deinit();

			virtual void PrintOutput(const Log::LogItem* logMessage) override;
		};


	public:

		static const StringCrc64 TypeName;

		LogOutputLogServerComponent(const LogOutputMask& logMask, const String& logServerAddress);
		~LogOutputLogServerComponent();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

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

