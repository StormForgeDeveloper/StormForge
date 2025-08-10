////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Event delegate 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeSystem.h"


namespace SF
{

	//////////////////////////////////////////////////////////////////////////
	//
	//	Event delegates
	//

	template<class... ArgTypes>
	class EventDelegateList
	{
	public:

		using CallableType = std::function<void(ArgTypes...)>;

		struct EventDelegate
		{
			uintptr_t Context{};
			CallableType Func;
			uint CallSerial = 0;
		};


        EventDelegateList()
        {
        }

		void AddDelegate(const EventDelegate& dele)
		{
			AddDelegate(dele.Context, dele.Func);
		}

		void AddDelegate(EventDelegate&& dele)
		{
			AddDelegate(dele.Context, Forward<CallableType>(dele.Func));
		}

		void AddDelegateUnique(const EventDelegate& dele)
		{
			RemoveDelegateAll(dele.Context);
			AddDelegate(dele.Context, dele.Func);
		}

		void AddDelegateUnique(EventDelegate&& dele)
		{
			RemoveDelegateAll(dele.Context);
			AddDelegate(dele.Context, Forward<CallableType>(dele.Func));
		}

		void AddDelegateUnique(uintptr_t Context, const CallableType& func)
		{
            assert(func);
			RemoveDelegateAll(Context);
			AddDelegate(Context, func);
		}

		void AddDelegateUnique(uintptr_t Context, CallableType&& func)
		{
            assert(func);
			RemoveDelegateAll(Context);
			AddDelegate(Context, Forward<CallableType>(func));
		}

		void AddDelegate(uintptr_t Context, const CallableType& func)
		{
            assert(func);
			m_DelegateArray.push_back(EventDelegate{ Context, func, m_CallSerial });
		}

		void AddDelegate(uintptr_t Context, CallableType&& func)
		{
            assert(func);
			m_DelegateArray.push_back(EventDelegate{ Context, Forward<CallableType>(func), m_CallSerial });
		}

		void RemoveDelegate(uintptr_t Context)
		{
			for (uint iIndex = 0; iIndex < m_DelegateArray.size(); iIndex++)
			{
				if (m_DelegateArray[iIndex].Context == Context)
				{
					m_DelegateArray.RemoveAt(iIndex);
					break;
				}
			}
		}

		void RemoveDelegateAll(uintptr_t Context)
		{
			for (uint iIndex = 0; iIndex < m_DelegateArray.size();)
			{
				if (m_DelegateArray[iIndex].Context == Context)
				{
					m_DelegateArray.RemoveAt(iIndex);
				}
				else
				{
					iIndex++;
				}
			}
		}

		void RemoveDelegateAll()
		{
			m_DelegateArray.Clear();
		}

		void Invoke(const std::remove_reference_t<ArgTypes>&... args)
		{
			auto callSerial = ++m_CallSerial;

			for (uint iArray = 0; iArray < m_DelegateArray.size(); iArray++)
			{
				auto& itDelegate = m_DelegateArray[iArray];
				// Skip if it is already invoked
				if (itDelegate.CallSerial == callSerial)
					continue;

				itDelegate.CallSerial = callSerial;
				itDelegate.Func(args...);

				if (itDelegate.CallSerial != callSerial) // something removed
				{
					iArray = 0; // need to search from the beginning
				}
			}
		}

		//void Invoke(ArgTypes&&... args)
		//{
		//	m_CallSerial++;

		//	for (uint iArray = 0; iArray < m_DelegateArray.size(); iArray++)
		//	{
		//		auto& itDelegate = m_DelegateArray[iArray];
		//		// Skip if it is already invoked
		//		if (itDelegate.CallSerial == m_CallSerial)
		//			continue;

		//		itDelegate.CallSerial = m_CallSerial;
		//		itDelegate.Func(args...);

		//		if (itDelegate.CallSerial != m_CallSerial) // something removed
		//		{
		//			iArray = 0; // need to search from the beginning
		//		}
		//	}
		//}

		size_t size() const { return m_DelegateArray.size(); }

	private:

		uint m_CallSerial = 1;
		DynamicArray<EventDelegate> m_DelegateArray;
	};

} // namespace SF
