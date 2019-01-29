
#pragma once

#include "UMTypedef.h"
#include "UMObject.h"

class UMNodeContent;

class UMNodeContentComponent : public UMObject
{
private:

	// Owner NodeContent
	UMNodeContent *m_Owner;

public:

	UMNodeContentComponent( UMNodeContent& owner );
	virtual ~UMNodeContentComponent();

	UMNodeContent& GetOwner() { return *m_Owner; }

	void SwitchComponentOwner( UMNodeContent& newOwner );

	// Initialize components after load/create
	virtual bool InitializeComponent();
};




