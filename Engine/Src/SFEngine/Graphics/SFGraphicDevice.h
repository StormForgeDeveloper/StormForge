////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : GraphicDevice base class
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Component/SFLibraryComponent.h"
#include "Object/SFSharedObjectManager.h"
#include "Graphics/SFRenderThread.h"
#include "Service/SFIGraphicDevice.h"
#include "Container/SFCircularPageQueue.h"
#include "Container/SFCircularBufferQueue.h"
#include "Container/SFDoubleLinkedList.h"
#include "Task/SFTask.h"


namespace SF
{
	class RenderCommand;
	class DeviceResource;
	class RenderTargetChain;

	////////////////////////////////////////////////////////////////////
	//
	//	Render command
	//
	
	class GraphicDevice : public IGraphicDevice
	{
	private:

		// Render command queue
		StaticCircularBufferQueue<20 * 1024 * 1024> m_RenderCommandQueue;

		// Native window
		NativeWindow m_NativeWindow;

		// Width and height of view
		int m_Width, m_Height;

		// Graphics memory heap
		Heap m_Heap;

		// Render thread
		RenderThread m_RenderThread;

		// Resources using to this device
		DoubleLinkedListStaticT<DeviceResource*> m_DeviceResources;

		// Default rendering target chain
		SharedPointerT<RenderTargetChain> m_RenderTargetChain;

		// True when between frame start and frame end
		std::atomic<uint32_t> m_DrawingFrameIndex;

		// 
		SharedObjectManager m_SharedObjectManager;

		// component dependency
		StaticArray<StringCrc64, 2> m_ComponentDependency;

	protected:

		void SetWindow(NativeWindow nativeWindow, int width, int height);

		void SetRenderTargetChain(SharedPointerT<RenderTargetChain>&& renderTargetChain) { m_RenderTargetChain = std::forward<SharedPointerT<RenderTargetChain> >(renderTargetChain); }

		// Register shared object
		void RegisterSharedObject(SharedObject* pSharedObject);

		// Free shared object
		void FreeSharedReference(SharedObject* pObj
#ifdef REFERENCE_DEBUG_TRACKING
			, const char* fileName = __BASE_FILE__, int lineNumber
#endif
		);

		// Add component dependency
		void AddDependency(StringCrc64 dependency);

		// Allow to access RegisterSharedObject
		friend class DeviceResource;


		// Frame begin/end
		virtual bool BeginFrame();
		virtual void RenderFrame();
		virtual void EndFrame();

		// Flush command queue for a frame
		Result RunOneFrame(DurationMS waitingTimeOut = DurationMS(500));

		friend class RenderCommand_KickFrame;
		friend class RenderThread;

	public:
		GraphicDevice();
		virtual ~GraphicDevice();

		// Get component dependency list
		const Array<StringCrc64>& GetComponentDependencies() { return m_ComponentDependency; }

		virtual StaticCircularBufferQueue<20 * 1024 * 1024>* GetRenderCommandQueue() override { return &m_RenderCommandQueue; }

		// Accessors for windows view information
		virtual NativeWindow GetNativeWindow() override { return m_NativeWindow; }
		virtual int GetWidth() override { return m_Width; }
		virtual int GetHeight() override { return m_Height; }

		// Get default render target chain
		RenderTargetChain* GetRenderTargetChain() { return m_RenderTargetChain.GetObjectPtr(); }

		// Memory manager for the device
		virtual IHeap& GetHeap() override { return *m_Heap.get(); }

		// command memeory manager, use same memory heap for now(TODO)
		virtual IHeap& GetCommandHeap() override { return *m_Heap.get(); }

		// Initialize component
		virtual Result Initialize();
		// Terminate component
		virtual void Deinitialize();

		virtual void InitDisplay(NativeWindow pWindow) override;
		virtual void DeinitDisplay() override;
		virtual void OnResize() override;


		///////////////////////////////////////////////////////////////////////////////////
		//
		//	Render command handling
		//

		



		///////////////////////////////////////////////////////////////////////////////////
		//
		//	Resource handling
		//


	};




	//////////////////////////////////////////////////////////////////////////////////////
	//
	//	GraphicDeviceComponent
	//

	template<class GraphicDeviceType>
	class GraphicDeviceComponent : public LibraryComponent
	{
	public:

		const StringCrc64 TypeName = "GraphicDevice";

	private:

		GraphicDeviceType m_GraphicDevice;

	public:
		GraphicDeviceComponent()
			: LibraryComponent(TypeName)
		{
			for (auto itDependency : m_GraphicDevice.GetComponentDependencies())
			{
				AddDependency(itDependency);
			}
		}

		~GraphicDeviceComponent() {}

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override
		{
			LibraryComponent::InitializeComponent();
			return m_GraphicDevice.Initialize();
		}

		// Terminate component
		virtual void DeinitializeComponent() override
		{
			LibraryComponent::DeinitializeComponent();
			m_GraphicDevice.Deinitialize();
		}

	};



}

