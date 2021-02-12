////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TongScript
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFStrUtil.h"
#include "Service/SFScriptService.h"
#include "Script/Tong/SFTongScriptEngine.h"
#include "Script/Tong/SFTongScriptEnvironment.h"



namespace SF
{
	namespace Tong
	{

		const StringCrc64 ScriptEngine::TypeName = "ScriptEngine"_crc64;

		ScriptEngine::ScriptEngine(IHeap& heap)
			: LibraryComponent(TypeName)
			, m_Heap("ScriptEngine", heap)
		{

		}

		ScriptEngine::~ScriptEngine()
		{
			if (m_RootEnvironment != nullptr)
				IHeap::Delete(m_RootEnvironment);
			m_RootEnvironment = nullptr;
		}

		// Initialize component
		Result ScriptEngine::InitializeComponent()
		{
			auto result = LibraryComponent::InitializeComponent();
			if (!result)
				return result;

			// Create root environment
			m_RootEnvironment = new(GetHeap()) Tong::ScriptEnvironment(GetHeap(), nullptr, "");

			return result;
		}

		// Terminate component
		void ScriptEngine::DeinitializeComponent()
		{

			if (m_RootEnvironment != nullptr)
				IHeap::Delete(m_RootEnvironment);
			m_RootEnvironment = nullptr;

			LibraryComponent::DeinitializeComponent();
		}


		// Create a script context
		//   @inParent: parent script environment, Child environment will inherit all variables from parent environment
		//   @return: Created environment
		SF::ScriptEnvironment* ScriptEngine::CreateEnvironment(SF::ScriptEnvironment* inParent, const String& name)
		{
			return new(GetHeap()) Tong::ScriptEnvironment(GetHeap(), static_cast<Tong::ScriptEnvironment*>(inParent), name);
		}

	}



} // namespace SF


