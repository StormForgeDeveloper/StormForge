
#include "stdafx.h"
#include "UMObject.h"
#include "UMAnimationSequence.h"



UMObject::UMObject()
{
}

UMObject::~UMObject()
{
}

// Node name
void UMObject::SetNodeName( const UMString& nodeName )
{
	m_NodeName = nodeName;
}


const UMString& UMObject::GetNodeName()
{
	return m_NodeName;
}


void UMObject::SetLinkedObjectID( const UMString& linkedObjectName, UINT linkedObjectID )
{
	m_LinkedObjectID.insert( std::make_pair( linkedObjectName, linkedObjectID ) );
}

UINT UMObject::GetLinkedObjectID( const UMString& linkedObjectName )
{
	auto itFound = m_LinkedObjectID.find( linkedObjectName );
	if( itFound != m_LinkedObjectID.end() )
		return itFound->second;

	return 0;
}

void UMObject::SetLinkedObject( const UMString& linkedObjectName, void *linkedObjectID )
{
	m_LinkedObject.insert( std::make_pair( linkedObjectName, linkedObjectID ) );
}

void* UMObject::GetLinkedObject( const UMString& linkedObjectName )
{
	auto itFound = m_LinkedObject.find( linkedObjectName );
	if( itFound != m_LinkedObject.end() )
		return itFound->second;

	return 0;
}


// Animation
void UMObject::AddAnimation(UMAnimationSequence* animationSequence)
{
	if( animationSequence == nullptr )
		return;

	m_Animations.push_back(animationSequence);
}

void UMObject::ForeachAnimation( std::function<void(UMAnimationSequence*)> func)
{
	std::for_each(m_Animations.begin(),m_Animations.end(), func);
}


