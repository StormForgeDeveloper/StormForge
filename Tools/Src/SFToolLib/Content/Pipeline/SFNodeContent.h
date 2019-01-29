
#pragma once

#include "UMTypedef.h"
#include "UMObject.h"

class UMNodeContentComponent;

class UMNodeContent : public UMObject
{
private:

	// Visibility
	bool m_Visibility;

	UMTransfoSFMatrix m_TransfoSFation;


	// Node component list
	UMArray<UMNodeContentComponent*> m_ComponentList;

	// Parent node
	UMNodeContent* m_pParent;

	// child node
	UMHashSet<UMNodeContent*> m_Children;

private:


public:

	UMNodeContent();
	~UMNodeContent();


	/////////////////////////////////////////////////////////////////////////////////
	//
	// Components
	//

	// Initialize components after load/create
	bool InitializeComponents();

	// Add component
	void AddComponent( UMNodeContentComponent *pNodeComponent );

	template< class ComponentType >
	ComponentType* AddComponent()
	{
		ComponentType *pNewComponent = GetComponent<ComponentType>();
		if( pNewComponent != nullptr )
			return pNewComponent;

		pNewComponent = new ComponentType(*this);
		AddComponent( pNewComponent );
		return pNewComponent;
	}

	template< class ComponentType >
	ComponentType* GetComponent()
	{
		ComponentType *pComponent = nullptr;
		std::for_each( m_ComponentList.begin(), m_ComponentList.end(), [&]( UMNodeContentComponent* pMemberComponent )
		{
			ComponentType *pCurrent = dynamic_cast<ComponentType*>(pMemberComponent);
			if( pCurrent != nullptr )
				pComponent = pCurrent;
		});

		return pComponent;
	}

	bool RemoveComponentOwnership( UMNodeContentComponent* pMemberComponent );

	
	/////////////////////////////////////////////////////////////////////////////////
	//
	// Attributes
	//

	UMTransfoSFMatrix GetGlobalTransfoSF();


	// Visibility
	void SetVisibility( bool visibility );
	bool GetVisibility();

	const UMTransfoSFMatrix& GetTransfoSF()							{ return m_TransfoSFation; }
	void SetTransfoSF( const UMTransfoSFMatrix& transfoSFation )	{ m_TransfoSFation = transfoSFation; }

	/////////////////////////////////////////////////////////////////////////////////
	// Child manuplation

	UMNodeContent* GetParent()										{ return m_pParent; }
	void AddChild( UMNodeContent *pNewChild );
	void RemoveChild( UMNodeContent *pChild );

	UINT GetChildCount();

	void ForeachChildren( std::function<void(UMNodeContent*)> func );
};




