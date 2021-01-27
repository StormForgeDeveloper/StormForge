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
			uint CallSerial = 0;
			void* Context = nullptr;
			CallableType Func;
		};


		EventDelegateList(IHeap& heap)
			: m_DelegateArray(heap)
		{
		}

		void AddDelegateUnique(void* Context, const CallableType& func)
		{
			RemoveDelegateAll(Context);
			AddDelegate(Context, func);
		}

		void AddDelegateUnique(void* Context, CallableType&& func)
		{
			RemoveDelegateAll(Context);
			AddDelegate(Context, Forward<CallableType>(func));
		}

		void AddDelegate(void* Context, const CallableType& func)
		{
			m_DelegateArray.push_back(EventDelegate{ m_CallSerial, Context, func });
		}

		void AddDelegate(void* Context, CallableType&& func)
		{
			m_DelegateArray.push_back(EventDelegate{ m_CallSerial, Context, Forward<CallableType>(func) });
		}

		void RemoveDelegate(void* Context)
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

		void RemoveDelegateAll(void* Context)
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

		void Invoke(ArgTypes&&... args)
		{
			m_CallSerial++;

			for (uint iArray = 0; iArray < m_DelegateArray.size(); iArray++)
			{
				auto& itDelegate = m_DelegateArray[iArray];
				// Skip if it is already invoked
				if (itDelegate.CallSerial == m_CallSerial)
					continue;

				itDelegate.CallSerial = m_CallSerial;
				itDelegate.Func(args...);

				if (itDelegate.CallSerial != m_CallSerial) // something removed
				{
					iArray = 0; // need to search from the beginning
				}
			}
		}

		size_t size() const { return m_DelegateArray.size(); }

	private:

		uint m_CallSerial = 1;
		DynamicArray<EventDelegate> m_DelegateArray;
	};


} // namespace SF

