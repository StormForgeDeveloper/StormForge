////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject manager
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "Service/SFServices.h"
#include "Service/SFAsyncIOPortService.h"
#include "Service/SFScriptService.h"
#include "Variable/SFVariableFactoryService.h"


//////////////////////////////////////////////////////////////////////
//
//	
//

// When you add a new service Inherits
//  1. Create base interface class with default implementation doing nothing. 
//     ex) 
//class SampleService
//{
//public:
//	virtual void Action1() {}
//	virtual void Action2() {}
//
//};

//  2. Inherit base interface class with implementation
//     ex)
//class SampleService_Impl1 : public SampleService
//{
//public:

//	virtual void Action1() override { /* Do things you need to do */ }
//	virtual void Action2() override { /* Do things you need to do */ }
//	
//};

//  3. Add service instance in Service class
//     ex)		static ServiceInstance<SampleService> SampleService;


namespace SF {


	//////////////////////////////////////////////////////////////////////
	//
	//	Service instance class
	//
	template<class ServiceType>
	class ServiceInstance
	{
	private:

        ServiceType* stm_pBaseInstance = nullptr;
        ServiceType* m_pService = nullptr;

	public:
		ServiceInstance()
		{
            stm_pBaseInstance = new ServiceType;
            if (m_pService == nullptr)
            {
                m_pService = stm_pBaseInstance;
            }
            else
            {
                // If m_pService assignment has happened before this instance initialization. m_pService will have value.
            }
		}

		operator ServiceType*() { return m_pService; }
		ServiceType* operator *() { return m_pService; }
		ServiceType* operator ->() { return m_pService; }

		ServiceInstance& operator = (ServiceType* pNewService)
		{
			if (pNewService == nullptr)
				m_pService = stm_pBaseInstance;
			else
				m_pService = pNewService;

			return *this;
		}

	};



	//////////////////////////////////////////////////////////////////////
	//
	//	Service base class
	//


	namespace Service
	{
		extern ServiceInstance<StringCrcDB> StringDB;
		extern ServiceInstance<AsyncTaskService> AsyncTaskManager;
		extern ServiceInstance<LogService> LogModule;
		extern ServiceInstance<AsyncIOPortService> AsyncIOPort;
		extern ServiceInstance <ScriptEngineService> ScriptEngine;
		extern ServiceInstance<VariableFactoryService> VariableFactory;
	};



} // namespace SF

