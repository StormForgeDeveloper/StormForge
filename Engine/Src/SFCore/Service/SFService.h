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
            assert(m_pService == nullptr); // nothing should be assigned yet
            m_pService = stm_pBaseInstance;
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

    // Service singleton 
    template<class ServiceType>
    class ServiceSingleton
    {
    public:
        ServiceSingleton() {}
        ~ServiceSingleton()
        {
            // Cleaning up static inside function isn't simple
            // We just dump them without destroy
        }

        ServiceType* Get()
        {
            static ServiceType* m_pService = nullptr;
            if (m_pService == nullptr)
            {
                m_pService = new ServiceType;
            }

            return m_pService;
        }

        operator ServiceType* () { return Get(); }
        ServiceType* operator *() { return Get(); }
        ServiceType* operator ->() { return Get(); }
    };


	//////////////////////////////////////////////////////////////////////
	//
	//	Service base class
	//


	namespace Service
	{
		extern ServiceSingleton<StringCrcDB> StringDB;
		extern ServiceInstance<AsyncTaskService> AsyncTaskManager;
		extern ServiceInstance<LogService> LogModule;
		extern ServiceInstance<AsyncIOPortService> AsyncIOPort;
		extern ServiceInstance <ScriptEngineService> ScriptEngine;
		extern ServiceInstance<VariableFactoryService> VariableFactory;
	};



} // namespace SF

