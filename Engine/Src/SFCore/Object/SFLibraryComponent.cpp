////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "String/SFStrUtil.h"
#include "Util/SFUtility.h"
#include "Util/SFLog.h"
#include "Multithread/SFSynchronization.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Object/SFLibraryComponentManager.h"
#include "Container/SFHashTable.h"
#include "MemoryManager/SFMemoryPool.h"



namespace SF {


	LibraryComponent::LibraryComponent(const StringCrc64& name)
		: m_Name(name)
		, m_IsInitialized(false)
		, m_Dependencies(GetSystemHeap())
	{
		CheckCtrMemory();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Component career base class
	//


		// Constructor
	LibraryComponentManager::LibraryComponentManager()
		: m_ComponentByName(GetSystemHeap())
		, m_ComponentByTypeName(GetSystemHeap())
		, m_IsInitialized(false)
	{
	}

	LibraryComponentManager::~LibraryComponentManager()
	{
	}


	// Clear components
	void LibraryComponentManager::ClearComponents()
	{
		m_ComponentByName.ForeachOrder(0, (int)m_ComponentByName.size(), [](const StringCrc64& name, LibraryComponent* pComponent)
		{
			unused(name);
			GetSystemHeap().Delete(pComponent);
		});

		m_ComponentByName.Clear();
		m_ComponentByTypeName.Clear();
	}

	// initialize component and its dependencies
	Result LibraryComponentManager::InitializeComponent(LibraryComponent* pComponent)
	{
		Result result = ResultCode::SUCCESS;

		if (pComponent->GetIsInitialized())
			return ResultCode::SUCCESS;

		for (auto itDependency : pComponent->GetDependencies())
		{
			auto pDependency = GetComponentByType(itDependency);
			if (pDependency != nullptr)
			{
				if (pComponent == pDependency)
				{
					// Circular dependency
					assert(false);
				}
				else if (!pDependency->GetIsInitialized())
				{
					auto res = pComponent->InitializeComponent();
					if (!res) result = res;
				}
			}
			else
			{
				// Missing dependency
				assert(false);
			}

		}

		if (pComponent->GetIsInitialized())
			return ResultCode::SUCCESS;

		auto res = pComponent->InitializeComponent();
		if (!res) result = res;

		return result;
	}



	// Initialize components
	Result LibraryComponentManager::InitializeComponents()
	{
		Result resultCode;

		m_IsInitialized = true;

		return m_ComponentByName.ForeachOrder(0, (int)m_ComponentByName.size(), [&](const StringCrc64& name, LibraryComponent* pComponent)
		{
			unused(name);
			auto result = InitializeComponent(pComponent);
			if (!result) resultCode = result;
		});
	}

	Result LibraryComponentManager::DeinitializeComponents()
	{
		m_ComponentByName.ForeachOrder(0, (int)m_ComponentByName.size(), [](const StringCrc64& name, LibraryComponent* pComponent)
		{
			unused(name);
			pComponent->DeinitializeComponent();
		});

		m_IsInitialized = false;

		return ResultCode::SUCCESS;
	}

	// Add component
	LibraryComponent* LibraryComponentManager::RemoveComponent(LibraryComponent* pComponent)
	{
		LibraryComponent* pRemove = nullptr;
		auto result = m_ComponentByName.Remove(pComponent->GetName(), pRemove);
		if (!result)
		{
			return nullptr;
		}
		Assert(pRemove == pComponent);

		// Remove from type list
		LibraryComponent *pFound = nullptr;
		if (m_ComponentByTypeName.Find(pRemove->GetTypeName(), pFound) && pFound == pRemove)
		{
			m_ComponentByTypeName.Remove(pRemove->GetTypeName(), pRemove);
		}

		if (m_IsInitialized)
			pRemove->DeinitializeComponent();

		return pRemove;
	}

	LibraryComponent* LibraryComponentManager::RemoveComponent(const StringCrc64& name)
	{
		LibraryComponent* pRemove = nullptr;
		auto result = m_ComponentByName.Remove(name, pRemove);
		if (!result)
		{
			return nullptr;
		}

		// Remove from type list
		LibraryComponent *pFound = nullptr;
		if (m_ComponentByTypeName.Find(pRemove->GetTypeName(), pFound) && pFound == pRemove)
		{
			m_ComponentByTypeName.Remove(pRemove->GetTypeName(), pRemove);
		}

		if (m_IsInitialized)
			pRemove->DeinitializeComponent();

		return pRemove;
	}


	Result LibraryComponentManager::AddComponent(LibraryComponent* newComponent)
	{
		if (newComponent == nullptr)
			return ResultCode::INVALID_POINTER;

		LibraryComponent *pFound = nullptr;
		bool sameNameFound = m_ComponentByName.Find(newComponent->GetName(), pFound);
		if (sameNameFound)
		{
			return ResultCode::DUPLICATE_COMPONENT;
		}

		auto result = m_ComponentByName.Insert(newComponent->GetName(), newComponent);
		Assert(result);

		// add type map
		m_ComponentByTypeName.Set(newComponent->GetTypeName(), newComponent);

		if (m_IsInitialized)
			newComponent->InitializeComponent();

		return result;
	}


	LibraryComponent* LibraryComponentManager::GetComponentByName(const StringCrc64& name)
	{
		LibraryComponent* pFound = nullptr;
		auto result = m_ComponentByName.Find(name, pFound);
		if (!result) return nullptr;

		return pFound;
	}

	LibraryComponent* LibraryComponentManager::GetComponentByType(const StringCrc64& typeName)
	{
		LibraryComponent* pFound = nullptr;
		auto result = m_ComponentByTypeName.Find(typeName, pFound);
		if (!result) return nullptr;

		return pFound;
	}



}


