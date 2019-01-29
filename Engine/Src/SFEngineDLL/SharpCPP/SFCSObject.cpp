////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Object
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"



#include "Util/SFLog.h"
#include "Object/SFObject.h"





using namespace SF;




//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT void SFEngine_Object_NativeAddReference(SF::Object* pObject)
{
	auto refCount = pObject->GetReferenceCount();
	auto weakRefCount = pObject->GetWeakReferenceCount();

	unused(refCount);
	assert(refCount >= 1);
	unused(weakRefCount);
	assert(weakRefCount >= 1);
	SharedReferenceInc inc(pObject);
}

SFDLL_EXPORT void SFEngine_Object_NativeReleaseReference(SF::Object* pObject)
{
	SharedReferenceDec dec(pObject);
}

	

