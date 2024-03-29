////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Stack walker
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "SFTypedefs.h"
#include "Multithread/SFThread.h"
#include "Component/SFLibraryComponent.h"
#include "Platform/SFStackWalker.h"



namespace SF {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Stack walker
	//

	class StackWalker : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "StackWalker";

	private:

		static class StackWalkerImpl *stm_pInstance;

	public:

		StackWalker();
		~StackWalker();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override;
			// Terminate component
		virtual void DeinitializeComponent() override;

		static StackWalkerImpl* GetImpl() { return stm_pInstance; }


		// print stack trace
		void PrintStackTrace();
	};


} // namespace SF



