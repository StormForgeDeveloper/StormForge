
#include "stdafx.h"

#include "UMNodeContent.h"
#include "UMNodeContentComponent.h"



UMNodeContent::UMNodeContent()
	:m_Visibility(true)
	,m_pParent(nullptr)
{
}

UMNodeContent::~UMNodeContent()
{
	std::for_each( m_ComponentList.begin(), m_ComponentList.end(), [&]( UMNodeContentComponent* component )
	{
		delete component;
	});
	m_ComponentList.clear();

	std::for_each( m_Children.begin(), m_Children.end(), [&]( UMNodeContent* pChild )
	{
		delete pChild;
	});
	m_Children.clear();
}

// Initialize components after load/create
bool UMNodeContent::InitializeComponents()
{
	bool isSucceeded = true;
	std::for_each( m_ComponentList.begin(), m_ComponentList.end(), [&]( UMNodeContentComponent* component )
	{
		isSucceeded |= component->InitializeComponent();
	});
	return true;
}

void UMNodeContent::AddComponent( UMNodeContentComponent *pNodeComponent )
{
	assert(pNodeComponent!=nullptr);
	if( pNodeComponent == nullptr) return;

	m_ComponentList.push_back(pNodeComponent);
}

bool UMNodeContent::RemoveComponentOwnership( UMNodeContentComponent* pMemberComponent )
{
	assert(pMemberComponent);
	assert(&pMemberComponent->GetOwner() == this);
	if( pMemberComponent == nullptr || &pMemberComponent->GetOwner() != this )
		return false;

	for( auto itComp = m_ComponentList.begin(); itComp != m_ComponentList.end(); itComp++ )
	{
		if( *itComp == pMemberComponent )
		{
			m_ComponentList.erase(itComp);
			return true;
		}
	}

	return false;
}

UMTransfoSFMatrix UMNodeContent::GetGlobalTransfoSF()
{
	if( GetParent() != nullptr )
		return GetParent()->GetGlobalTransfoSF() * GetTransfoSF();
	else
		return GetTransfoSF();
}

// Visibility
void UMNodeContent::SetVisibility( bool visibility )
{
	m_Visibility = visibility;
}

bool UMNodeContent::GetVisibility()
{
	return m_Visibility;
}

// Child manuplation
void UMNodeContent::AddChild( UMNodeContent *pNewChild )
{
	// Check wheather it is a already child or not
	if( m_Children.find( pNewChild ) != m_Children.end() )
		return;

	pNewChild->m_pParent = this;

	m_Children.insert( pNewChild );
}

void UMNodeContent::RemoveChild( UMNodeContent *pChild )
{
	if( m_Children.find(pChild) == m_Children.end() )
		return;

	pChild->m_pParent = nullptr;
	m_Children.erase( pChild );
}

UINT UMNodeContent::GetChildCount()
{
	return m_Children.size();
}

void UMNodeContent::ForeachChildren( std::function<void(UMNodeContent*)> func )
{
	std::for_each( m_Children.begin(), m_Children.end(), func );
}


