////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Scene Graph node
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Object/SFObject.h"
#include "EngineObject/SFEngineObject.h"
#include "Task/SFTimerScheduler.h"
#include "Container/SFDoubleLinkedList.h"

namespace SF {

	struct SceneCloneContext;
	class SceneNode;

#define SCENENODECOMPONENT_DEFINE_SIGNATURE(sig) \
		static constexpr StringCrc64 TypeSignature = #sig;\
		virtual StringCrc64 GetTypeSignature() const override { return TypeSignature; }\


	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SceneNodeComponent class -  interface for task operation
	//

	class SceneNodeComponent : public Object
	{
	public:

		// Update tick mode, this decides when the update function is called
		enum class UpdateTickMode
		{
			None,
			PreUpdate,
			Update,
			PostUpdate,
			BeforeDraw,
		};

	private:

		UpdateTickMode m_UpdateTickMode = UpdateTickMode::None;

		// Owner of this Component
		SceneNode* m_Owner = nullptr;



	protected:

		// Update tick mode
		void SetUpdateTickMode(UpdateTickMode updateMode) { m_UpdateTickMode = updateMode; }

		// Set owner
		void SetOwner(SceneNode* pOwner)
		{
			Assert(m_Owner == nullptr); // you can not assign another owner for same component
			m_Owner = pOwner;
		}


	public:
		// Constructor
		SceneNodeComponent(const StringCrc64& name = "");
		virtual ~SceneNodeComponent();

		// Component signature
		virtual StringCrc64 GetTypeSignature() const { return nullptr; }

		// Dispose
		virtual void Dispose() override;

		// Get owner node
		SceneNode* GetOwner() { return m_Owner; }

		// Change owner
		void ChangeOwner(SceneNode* newOwner);

		// Get update tick mode
		UpdateTickMode GetUpdateTickMode() { return m_UpdateTickMode; }

		// copy properties to new component
		virtual Result CopyProperties(const SceneCloneContext& cloneFlags, SceneNodeComponent* pSrcComponent);

		// child component should overrride this for clone
		virtual SceneNodeComponent* Clone(const SceneCloneContext& cloneFlags, SceneNode* newOwner) { return nullptr; }


		// Initialize component
		virtual Result InitializeComponent(SceneNode* pNode) { return ResultCode::SUCCESS; }


		// Compoentn tick update
		virtual Result Update(DurationMS delta) { return ResultCode::NOT_IMPLEMENTED; }
	};



	extern template class SharedPointerT<SceneNodeComponent>;

}; // namespace SF

