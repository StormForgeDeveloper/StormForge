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
#include "Util/SFStrUtil.h"
#include "Util/SFUtility.h"
#include "Util/SFLog.h"
#include "Util/SFTrace.h"
#include "Multithread/SFSynchronization.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Component/SFLibraryComponentManager.h"
#include "Container/SFHashTable.h"
#include "MemoryManager/SFMemoryPool.h"


namespace SF {


	LibraryComponent::LibraryComponent(const StringCrc64& name, bool bIsTickable)
		: m_Name(name)
		, m_IsInitialized(false)
        , m_IsTickable(bIsTickable)
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
        , m_TickableComponents(GetSystemHeap())
		, m_IsInitialized(false)
	{
	}

	LibraryComponentManager::~LibraryComponentManager()
	{
	}


	// Clear components
	void LibraryComponentManager::ClearComponents()
	{
		for(int iComponent = int(m_Components.size()) - 1; iComponent >= 0; iComponent--)
		{
            LibraryComponent* pComponent = m_Components[iComponent];
			GetSystemHeap().Delete(pComponent);
		}

        m_Components.Reset();
		m_ComponentByName.Clear();
		m_ComponentByTypeName.Clear();
	}

	// initialize component and its dependencies
	Result LibraryComponentManager::InitializeComponent(LibraryComponent* pComponent)
	{
		Result hr = ResultCode::SUCCESS;

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
                    defCheck(InitializeComponent(pDependency));
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

        defCheck(pComponent->InitializeComponent());
        pComponent->m_IsInitialized = true;

		return hr;
	}



	// Initialize components
	Result LibraryComponentManager::InitializeComponents()
	{
		Result resultCode;

		m_IsInitialized = true;

        for (int iComponent = int(m_Components.size()) - 1; iComponent >= 0; iComponent--)
        {
            LibraryComponent* pComponent = m_Components[iComponent];
            InitializeComponent(pComponent);
        }

        return resultCode;
	}

	Result LibraryComponentManager::DeinitializeComponents()
	{
        // reverse order
        for (int iComponent = int(m_Components.size()) - 1; iComponent >= 0; iComponent--)
        {
            LibraryComponent* pComponent = m_Components[iComponent];
            pComponent->DeinitializeComponent();
        }

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

        m_TickableComponents.RemoveItem(pComponent);

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
            m_Components.RemoveItem(pFound);
        }

        m_TickableComponents.RemoveItem(pRemove);

		if (m_IsInitialized)
			pRemove->DeinitializeComponent();

		return pRemove;
	}


	Result LibraryComponentManager::AddComponent(LibraryComponent* newComponent)
	{
		if (newComponent == nullptr)
			return ResultCode::INVALID_POINTER;

		LibraryComponent *pFound = nullptr;
		bool sameNameFound = m_ComponentByName.Find(newComponent->GetName(), pFound).IsSuccess();
		if (sameNameFound)
		{
            SFLog(System, Warning, "Engine system has component with duplicated name:{0}", newComponent->GetName().ToString());
			return ResultCode::DUPLICATE_COMPONENT;
		}

		auto result = m_ComponentByName.Insert(newComponent->GetName(), newComponent);
		Assert(result);

		// add type map
		m_ComponentByTypeName.Set(newComponent->GetTypeName(), newComponent);
        m_Components.push_back(newComponent);

        if (newComponent->IsTickable())
        {
            m_TickableComponents.push_back(newComponent);
        }

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

    void LibraryComponentManager::ComponentTickUpdate()
    {
        for (LibraryComponent* pComponent : m_TickableComponents)
        {
            pComponent->TickUpdate();
        }
    }
}


