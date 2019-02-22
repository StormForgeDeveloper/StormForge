////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Graphic device interface
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "Container/SFHashTable2.h"
#include "Object/SFSharedPointer.h"
#include "Memory/SFMemoryManager.h"
#include "String/SFFixedStringDB.h"
#include "Task/SFTask.h"
#include "Container/SFCircularBuffer.h"
#include "Resource/SFTextureFormat.h"



namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	Render command
	//

	class RenderTargetChain;
	class DeviceTexture;
	class DeviceResource;
	class RenderCommand;



	class IGraphicDevice
	{
	protected:

		//// Render command queue
		//CircularBuffer<20 * 1024 * 1024> m_RenderCommandQueue;


	public:
		IGraphicDevice() {}
		virtual ~IGraphicDevice() {}

		virtual CircularBuffer<20 * 1024 * 1024>* GetRenderCommandQueue() { return nullptr; }

		virtual IHeap& GetHeap() { return GetSystemHeap(); }

		// command memory manager, use same memory heap for now(TODO)
		virtual IHeap& GetCommandHeap() { return GetSystemHeap(); }


		virtual NativeWindow GetNativeWindow() { return NativeWindow(0); }
		virtual int GetWidth() { return 0; }
		virtual int GetHeight() { return 0; }


		virtual void InitDisplay(NativeWindow pWindow) { unused(pWindow); }
		virtual void DeinitDisplay() {}
		virtual void OnResize() {}




		///////////////////////////////////////////////////////////////////////////////////
		//
		//	Render command handling
		//


		// Command Notification Task
		class CommandNotificationTask : public Task
		{
		public:
			virtual void Run() override {}
		};

		// Request command
		template<class CommandType>
		TaskPtr RequestCommandTask()
		{
			auto pRenderCommandQueue = GetRenderCommandQueue();
			if (pRenderCommandQueue == nullptr)
				return;

			auto pBuffer = pRenderCommandQueue->Reserve(sizeof(CommandType));
			auto pCmd = new(pBuffer) CommandType();
			Assert((uintptr_t)pCmd == (uintptr_t)pBuffer);

			TaskPtr pTask = new(GetHeap()) CommandNotificationTask;
			pCmd->SetNotificationTask(pTask);

			pRenderCommandQueue->SetReadyForRead(pBuffer);
			return std::forward<TaskPtr>(pTask);
		}

		// request command with arg
		template<class CommandType, class ...ArgTypes>
		TaskPtr RequestCommandTask(ArgTypes... args)
		{
			auto pRenderCommandQueue = GetRenderCommandQueue();
			if (pRenderCommandQueue == nullptr)
				return;

			auto pBuffer = pRenderCommandQueue->Reserve(sizeof(CommandType));
			auto pCmd = new(pBuffer) CommandType(args...);
			Assert((uintptr_t)pCmd == (uintptr_t)pBuffer);

			TaskPtr pTask = new(GetHeap()) CommandNotificationTask;
			pCmd->SetNotificationTask(pTask);

			pRenderCommandQueue->SetReadyForRead(pBuffer);
			return std::forward<TaskPtr>(pTask);
		}

		// Request command
		template<class CommandType>
		Result RequestCommand()
		{
			auto pRenderCommandQueue = GetRenderCommandQueue();
			if (pRenderCommandQueue == nullptr)
				return;

			auto pBuffer = pRenderCommandQueue->Reserve(sizeof(CommandType));
			auto pCmd = new(pBuffer) CommandType();
			Assert((uintptr_t)pCmd == (uintptr_t)pBuffer);
			return pRenderCommandQueue->SetReadyForRead(pBuffer);
		}

		// request command with arg
		template<class CommandType, class ...ArgTypes>
		Result RequestCommand(ArgTypes... args)
		{
			auto pRenderCommandQueue = GetRenderCommandQueue();
			if (pRenderCommandQueue == nullptr)
				return ResultCode::SUCCESS_FALSE;

			auto pBuffer = pRenderCommandQueue->Reserve(sizeof(CommandType));
			auto pCmd = new(pBuffer) CommandType(args...);
			Assert((uintptr_t)pCmd == (uintptr_t)pBuffer);
			unused(pCmd);
			return pRenderCommandQueue->SetReadyForRead(pBuffer);
		}



		///////////////////////////////////////////////////////////////////////////////////
		//
		//	Resource handling
		//


		virtual DeviceTexture* CreateTexture(const TextureInitParameter& initParameters) { unused(initParameters);  return nullptr; }
		virtual DeviceResource* CreateBuffer() { return nullptr; }

	};

	

}; // namespace SF

