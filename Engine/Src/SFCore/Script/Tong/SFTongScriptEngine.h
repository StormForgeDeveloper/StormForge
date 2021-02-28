////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : StormForge, Tong Script
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Service/SFScriptService.h"
#include "Component/SFLibraryComponent.h"


namespace SF
{

	namespace Tong
	{
		class ScriptEnvironment;

		/////////////////////////////////////////////////////////////////////////////////
		//
		//	ScriptEngine
		//

		class ScriptEngine : public ScriptEngineService, public LibraryComponent
		{
		public:
			static const StringCrc64 TypeName;

		private:

			// Heap for script engine
			Heap m_Heap;

			// Root environment "/"
			Tong::ScriptEnvironment* m_RootEnvironment = nullptr;

		public:

			ScriptEngine(IHeap& heap);
			~ScriptEngine();

			virtual const StringCrc64& GetTypeName() override { return TypeName; }


			// Heap for engine
			IHeap& GetHeap() { return *m_Heap.get(); }


			// Initialize component
			virtual Result InitializeComponent() override;
			// Terminate component
			virtual void DeinitializeComponent() override;


			// Create a script context
			//   @inParent: parent script environment, Child environment will inherit all variables from parent environment
			//   @return: Created environment
			virtual SF::ScriptEnvironment* CreateEnvironment(SF::ScriptEnvironment* inParent, const String& name) override;

		};
	}

}
