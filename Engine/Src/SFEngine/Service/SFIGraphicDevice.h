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
#include "MemoryManager/SFMemoryManager.h"
#include "Task/SFTask.h"
#include "Container/SFCircularBufferQueue.h"
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

		// Render command queue
        using CommandQueue = StaticCircularBufferQueue<20 * 1024 * 1024>;

	public:
		IGraphicDevice() {}
		virtual ~IGraphicDevice() {}

		virtual CommandQueue* GetRenderCommandQueue() { return nullptr; }

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
				return nullptr;

            CommandQueue::ItemWritePtr pBuffer = pRenderCommandQueue->AllocateWrite(sizeof(CommandType));
			auto pCmd = new(pBuffer.data()) CommandType();
			Assert((uintptr_t)pCmd == (uintptr_t)pBuffer.data());

			TaskPtr pTask = new(GetHeap()) CommandNotificationTask;
			pCmd->SetNotificationTask(pTask);

            pBuffer.Reset();
			return std::forward<TaskPtr>(pTask);
		}

		// request command with arg
		template<class CommandType, class ...ArgTypes>
		TaskPtr RequestCommandTask(ArgTypes... args)
		{
			auto pRenderCommandQueue = GetRenderCommandQueue();
			if (pRenderCommandQueue == nullptr)
				return nullptr;

            CommandQueue::ItemWritePtr pBuffer = pRenderCommandQueue->AllocateWrite(sizeof(CommandType));
			auto pCmd = new(pBuffer.data()) CommandType(args...);
			assert((uintptr_t)pCmd == (uintptr_t)pBuffer.data());

			TaskPtr pTask = new(GetHeap()) CommandNotificationTask;
			pCmd->SetNotificationTask(pTask);

            pBuffer.Reset();
			return std::forward<TaskPtr>(pTask);
		}

		// Request command
		template<class CommandType>
		Result RequestCommand()
		{
			auto pRenderCommandQueue = GetRenderCommandQueue();
			if (pRenderCommandQueue == nullptr)
				return ResultCode::SUCCESS_FALSE;

			CommandQueue::ItemWritePtr pBuffer = pRenderCommandQueue->AllocateWrite(sizeof(CommandType));
			auto pCmd = new(pBuffer.data()) CommandType();
			assert((uintptr_t)pCmd == (uintptr_t)pBuffer.data());
            pBuffer.Reset();
			return ResultCode::SUCCESS;
		}

		// request command with arg
		template<class CommandType, class ...ArgTypes>
		Result RequestCommand(ArgTypes... args)
		{
			auto pRenderCommandQueue = GetRenderCommandQueue();
			if (pRenderCommandQueue == nullptr)
				return ResultCode::SUCCESS_FALSE;

			CommandQueue::ItemWritePtr pBuffer = pRenderCommandQueue->AllocateWrite(sizeof(CommandType));
			auto pCmd = new(pBuffer.data()) CommandType(args...);
			assert((uintptr_t)pCmd == (uintptr_t)pBuffer.data());
			unused(pCmd);
            pBuffer.Reset();
			return ResultCode::SUCCESS;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//
		//	Resource handling
		//

		virtual DeviceTexture* CreateTexture(const TextureInitParameter& initParameters) { unused(initParameters);  return nullptr; }
		virtual DeviceResource* CreateBuffer() { return nullptr; }

	};

} // namespace SF
