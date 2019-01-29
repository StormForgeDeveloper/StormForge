////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Render command
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Object/SFObject.h"
#include "Container/SFCircularPageQueue.h"
#include "Task/SFTask.h"

namespace SF
{

	class GraphicDevice;

	////////////////////////////////////////////////////////////////////
	//
	//	Render command
	//

	// TODO: Implement ring buffer allocator for command

	class RenderCommand
	{
	private:
		CallTrack m_CallTrack;
		TaskPtr m_NotificationTask;

	public:
		RenderCommand(const CallTrack& callTrack);
		virtual ~RenderCommand();

		// Notification task
		void SetNotificationTask(TaskPtr& pTask) { m_NotificationTask = pTask; }
		TaskPtr& GetNotificationTask() { return m_NotificationTask; }

		virtual void RunCommand(GraphicDevice* pGraphicDevice) = 0;
	};



	////////////////////////////////////////////////////////////////////
	//
	//	Render command with functor
	//
	template<class Func>
	class RenderCommandFunc : public RenderCommand
	{
	private:
		Func m_Func;

	public:
		RenderCommandFunc(Func func, const CallTrack& callTrack = CallTrack())
			: RenderCommand(callTrack)
			, m_Func(func)
		{
		}

		void RunCommand(GraphicDevice* pGraphicDevice) override
		{
			m_Func(pGraphicDevice);
		}
	};



}

