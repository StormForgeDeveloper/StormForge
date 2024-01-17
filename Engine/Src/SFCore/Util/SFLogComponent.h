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
#include "Component/SFLibraryComponent.h"
#include "Object/SFSharedPointer.h"
#include "Util/SFLog.h"
#include "IO/SFFile.h"
#include "Util/SFString.h"


namespace SF {

    namespace Log
    {
        extern LogChannel OutputConsole;
    }

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
			MyOutputHandler() : LogOutputHandler("OutputConsole") {}

			void InitConsole();

			virtual void PrintOutput(const Log::LogItem* logMessage) override;
		};

		MyOutputHandler m_Handler;

	public:

		static constexpr StringCrc64 TypeName = "LogOutputConsoleComponent";

		LogOutputConsoleComponent();
		~LogOutputConsoleComponent();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		MyOutputHandler& GetHandler() { return m_Handler; }

		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;
	};


    namespace Log
    {
        extern LogChannel OutputDebugger;
    }

	class LogOutputDebuggerComponent : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "LogOutputDebuggerComponent";

	private:

		class MyOutputHandler : public Log::LogOutputHandler
		{
		public:
			MyOutputHandler() : LogOutputHandler("OutputDebugger") {}
			virtual void PrintOutput(const Log::LogItem* logMessage) override;
		};

		MyOutputHandler m_Handler;

	public:
		LogOutputDebuggerComponent();
		~LogOutputDebuggerComponent();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		MyOutputHandler& GetHandler() { return m_Handler; }


		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;
	};


    namespace Log
    {
        extern LogChannel OutputFile;
    }

	class LogOutputFileComponent : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "LogOutputFileComponent";

	private:

		class MyOutputHandler : public Log::LogOutputHandler
		{
		private:

			PathString m_FilePrefix;
            String m_LogFilePath;
            bool m_OpenNewFileHourly = false;
			File  m_File;
			int m_LogFileCreatedHour = 0;


		public:
			MyOutputHandler(const String& filePrefix, bool bOpenNewHourly);

			void OpenLogFile();

            const PathString& GetLogFilePrefix() const { return m_FilePrefix; }
            const String& GetLogFilePath() const { return m_LogFilePath; }

			virtual void PrintOutput(const Log::LogItem* logMessage) override;

			virtual void Flush() override;
		};

		MyOutputHandler m_Handler;


	public:

		LogOutputFileComponent(const String& filePrefix, bool bOpenNewHourly);
		~LogOutputFileComponent();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		MyOutputHandler& GetHandler() { return m_Handler; }

		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;
	};



}

