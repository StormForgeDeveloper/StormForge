////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server constants definitions. 
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Object/SFLibraryComponent.h"
#include "Object/SFSharedPointer.h"
#include "Util/SFLog.h"
#include "IO/SFFile.h"
#include "String/SFString.h"


namespace SF {



	class LogOutputConsoleComponent : public LibraryComponent
	{
	private:

		class MyOutputHandler : public Log::LogOutputHandler
		{
		private:
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
			NativeHandle m_hConsole = INVALID_NATIVE_HANDLE_VALUE;
#endif
		public:
			MyOutputHandler(const LogChannelMask& logMask) : LogOutputHandler(logMask) {}

			void InitConsole();

			virtual void PrintOutput(const Log::LogModule::LogItem* logMessage) override;
		};

		MyOutputHandler m_Handler;

	public:

		static constexpr FixedString TypeName = "LogOutputConsoleComponent";

		LogOutputConsoleComponent(const LogChannelMask& logMask);
		~LogOutputConsoleComponent();

		virtual const FixedString& GetTypeName() override { return TypeName; }

		MyOutputHandler& GetHandler() { return m_Handler; }

		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;
	};



	class LogOutputDebuggerComponent : public LibraryComponent
	{
	public:
		static constexpr FixedString TypeName = "LogOutputDebuggerComponent";

	private:

		class MyOutputHandler : public Log::LogOutputHandler
		{
		public:
			MyOutputHandler(const LogChannelMask& logMask) : LogOutputHandler(logMask) {}
			virtual void PrintOutput(const Log::LogModule::LogItem* logMessage) override;
		};

		MyOutputHandler m_Handler;

	public:
		LogOutputDebuggerComponent(const LogChannelMask& logMask);
		~LogOutputDebuggerComponent();

		virtual const FixedString& GetTypeName() override { return TypeName; }

		MyOutputHandler& GetHandler() { return m_Handler; }


		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;
	};


	class LogOutputFileComponent : public LibraryComponent
	{
	public:
		static constexpr FixedString TypeName = "LogOutputFileComponent";

	private:

		class MyOutputHandler : public Log::LogOutputHandler
		{
		private:

			String m_FilePrefix;
			bool m_OpenNewFileHourly = false;
			File  m_File;
			int m_LogFileCreatedHour = 0;


		public:
			MyOutputHandler(const LogChannelMask& logMask, const String& filePrefix, bool bOpenNewHourly);

			void OpenLogFile();

			virtual void PrintOutput(const Log::LogModule::LogItem* logMessage) override;

			virtual void Flush() override;
		};

		MyOutputHandler m_Handler;


	public:

		LogOutputFileComponent(const LogChannelMask& logMask, const String& filePath, bool bOpenNewHourly);
		~LogOutputFileComponent();

		virtual const FixedString& GetTypeName() override { return TypeName; }

		MyOutputHandler& GetHandler() { return m_Handler; }

		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;
	};



}

