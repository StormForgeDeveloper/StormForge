
#pragma once

#include "UMTypedef.h"

class UMAnimationSequence;

class UMObject
{
public:

private:
	
	UMHashMap<UMString,UINT> m_LinkedObjectID;

	UMHashMap<UMString,void*> m_LinkedObject;

	// character name
	UMString m_NodeName;

	// Animations which is related to this object
	UMArray<UMAnimationSequence*> m_Animations;

public:

	UMObject();
	virtual ~UMObject();

	// Node name
	void SetNodeName( const UMString& nodeName );
	const UMString& GetNodeName();
	
	void SetLinkedObjectID( const UMString& linkedObjectName, UINT linkedObjectID );
	UINT GetLinkedObjectID( const UMString& linkedObjectName );

	void SetLinkedObject( const UMString& linkedObjectName, void* linkedObject );
	void* GetLinkedObject( const UMString& linkedObjectName );

	// Animation
	UINT GetAnimationCount()								{ return m_Animations.size(); }
	void AddAnimation(UMAnimationSequence* animationSequence);
	void ForeachAnimation( std::function<void(UMAnimationSequence*)> animationSequence);
};




