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
#include "Object/SFLibraryComponent.h"


namespace SF {


	class UnhandledExceptionHandlerComponent : public LibraryComponent
	{
	public:

		static constexpr FixedString TypeName = "UnhandledExceptionHandlerComponent";

	private:

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

		static char m_DumpFilePathBuffer[1024];

		static long __stdcall CrashHandler(EXCEPTION_POINTERS* ipExPtrs);
		static void WriteCrashDump(EXCEPTION_POINTERS* ipExPtrs, MINIDUMP_TYPE dumpType, const char* strMode);
#endif


	public:

		UnhandledExceptionHandlerComponent();

		virtual const FixedString& GetTypeName() override { return TypeName; }



		// Initialize component
		virtual Result InitializeComponent() override;

		// Terminate component
		virtual void DeinitializeComponent() override;


	};




} // namespace SF


