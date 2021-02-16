////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net Connection implementation
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Protocol/SFProtocol.h"
#include "Service/SFEngineService.h"

#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnection.h"
#include "Net/SFConnectionTasks.h"
#include "Net/SFConnectionManagerTask.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetUtil.h"
#include "Net/SFNetSystem.h"





namespace SF {

	template class SharedPointerT <Net::Connection>;
	template class WeakPointerT < Net::Connection >;

	namespace Net {


		////////////////////////////////////////////////////////////////////////////////
		//
		//	Network connection base class
		//

		ConnectionTask::ConnectionTask(WeakPointerT<Connection>&& pConnection, EngineTaskTick tick)
			: EngineTask(tick)
			, m_pConnection(std::forward<WeakPointerT<Connection>>(pConnection))
		{
		}


		ConnectionTask_DisconnectNClose::ConnectionTask_DisconnectNClose(Connection* pConnection, const char* reason)
			: EngineTask(EngineTaskTick::AsyncTick)
			, m_Reason(reason)
			, m_pConnection(pConnection)
		{
			m_EnqueuedTime = Util::Time.GetTimeMs();
		}

		ConnectionTask_DisconnectNClose::~ConnectionTask_DisconnectNClose()
		{
			// This is supposed to be cleaned up before come here
			assert(m_pConnection == nullptr);
			if (m_pConnection != nullptr)
			{
				if (m_RemoveConnectionManagerTask != nullptr)
					m_RemoveConnectionManagerTask->Wait();

				// force clean up
				if (m_pConnection->GetConnectionState() != ConnectionState::DISCONNECTED)
					m_pConnection->CloseConnection(m_Reason);

				m_pConnection->Dispose();
				m_pConnection = nullptr;
			}
		}

		void ConnectionTask_DisconnectNClose::Run()
		{

			if (m_pConnection == nullptr)
			{
				Finished();
				return;
			}

			if (m_pConnection->GetConnectionState() != ConnectionState::DISCONNECTED)
				m_pConnection->CloseConnection(m_Reason);

			//m_pConnection->CloseSocket();

			if (!m_RemovedFromConnectionManagerRequested)
			{
				m_RemoveConnectionManagerTask = std::forward<EngineTaskPtr>(Service::ConnectionManager->RemoveConnection(m_pConnection));
				m_RemovedFromConnectionManagerRequested = true;
			}

			if (m_RemoveConnectionManagerTask != nullptr && m_RemoveConnectionManagerTask->GetState() != Task::State::Idle)
			{
				return;
			}

			if (!m_pConnection->CanDelete())
			{
				// Wait max 2 mins
				if (Util::TimeSince(m_EnqueuedTime) < DurationMS(2 * 60 * 1000))
				{
					return;
				}

				SFLog(Net, Warning, "Timeout, force clean up connection CID:{0}", m_pConnection->GetCID());
			}

			// 
			m_pConnection->Dispose();
			m_pConnection = nullptr;

			super::Run();

			Finished();
		}


	} // namespace Net
} // namespace SF

