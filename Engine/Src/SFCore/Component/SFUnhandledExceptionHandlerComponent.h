////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Crash reporter win32
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFTypedefs.h"
#include "Component/SFLibraryComponent.h"


namespace SF {


	class UnhandledExceptionHandlerComponent : public LibraryComponent
	{
	public:

		static constexpr StringCrc64 TypeName = "UnhandledExceptionHandlerComponent";

        // Crash external command up to 8K buffer
        // shell command will be executed on crash with dump file name(-dumpfile=<filePath>) will be attached
        static char m_CrashShellCommand[8 * 1024];

	private:

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

        static bool m_bEnableFullDump;
        static char m_DumpFilePathBuffer[1024];

		static long __stdcall CrashHandler(EXCEPTION_POINTERS* ipExPtrs);
		static void WriteCrashDump(EXCEPTION_POINTERS* ipExPtrs, MINIDUMP_TYPE dumpType, const char* strMode);
#endif


	public:

		UnhandledExceptionHandlerComponent(bool bEnableFullDump = false);

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

        // shell command will be executed on crash with dump file name
        void SetCrashShellCommand(const char* command);

		// Initialize component
		virtual Result InitializeComponent() override;

		// Terminate component
		virtual void DeinitializeComponent() override;


	};




} // namespace SF


